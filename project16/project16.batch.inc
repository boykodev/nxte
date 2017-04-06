<?php

// menu callback function - sets up the batch
function project16_batch_task($params) {
  $batch = array(
    'operations' => array(),
    'finished' => 'project16_batch_task_finished',
    // runs after batch is finished
    'title' => t('Processing Export'),
    'init_message' => t('Export is starting.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Export has encountered an error.'),
  );
  $progress = 0; // where to start
  $limit = 100; // how many to process for each run
  $max = 100; // how many records to process until stop - can do query here to get max times to run
  while ($progress < $max) {
    $batch['operations'][] = array(
      'project16_batch_task_process',
      array($progress, $limit, $params)
    );
    $progress = $progress + $limit;
  }
  batch_set($batch);
  batch_process('admin/config/project16'); // page to return to after complete
}

// this is what runs multiple times per batch
// progress and limit and is updated during each run
function project16_batch_task_process($progress, $limit, $params, &$context) {
  // use $progress and $limit to only run that amount of records
  // example using db_select
  $query = db_select('node', 'n');
  $query->fields('n', array('nid'));
  $query->orderBy('n.nid', 'ASC');
  $query->range($progress, $limit);
  $nids = $query->execute()->fetchCol();
  $nodes = node_load_multiple($nids);

  $data = array();
  foreach ($nodes as $node) {
    // check if title contains string (case insensitive)
    $title_match = $params['match'] === '' ||
      stripos($node->title, $params['match']) !== false;

    if ($title_match) {
      $data[] = array(
        $node->nid,
        $node->title,
        $node->name,
        date('d-m-Y h:i:s', $node->created)
      );
    }
  }

  // export CSV only if data present
  if ($data) {
    $headers = array();
    if ($params['headers']) {
      $headers = array(
        'Node ID',
        'Node title',
        'Node author',
        'Time the Node was created'
      );
    }
    project16_csv_export($headers, $data);
  } else {
    drupal_set_message('No matching nodes were found', 'error');
  }

  // update progress for message
  $progress = $progress + $limit;
  // update message during each run so you know where you are in the process
  $context['message'] = 'Now processing ' . $progress . ' - ' . $context['results'][0] . ' exported';
}

function project16_batch_task_finished($success, $results, $operations) {
  if (!$success) {
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array(
      '%error_operation' => $error_operation[0],
      '@arguments' => print_r($error_operation[1], TRUE)
    ));
    drupal_set_message($message, 'error');
  }
}

/**
 * Saving data to .csv file
 * Thanks: http://fragmentedthought.com/fragments/writing-csv-files-using-drupal
 * @param $headers
 * @param $data
 */
function project16_csv_export($headers, $data) {
  $path = 'public://csv_export/';
  $filename = 'export-' . REQUEST_TIME . '.csv';
  // Ensure the directory
  if( !file_prepare_directory($path, FILE_CREATE_DIRECTORY) ){
    drupal_set_message( t('Unable to create directory in file system. Check permissions and try again.'), 'error' );
    return;
  }
  // Ensure the file
  $file = file_save_data('', $path . $filename);
  if( !$file ){
    drupal_set_message( t('Unable to write to file system. Check permissions and try again.'), 'error' );
    return;
  }
  // Stream data - This is a simplified example. Better to do it in a batch if you have a high volume of data
  $fh = fopen($file->uri, 'w');
  if( !$fh ){
    drupal_set_message( t('Unable open file for writing. Check permissions and try again.'), 'error' );
    return;
  }

  if ($headers) {
    fputcsv($fh, $headers);
  }

  foreach ($data as $row) {
    fputcsv($fh, $row);
  }

  fclose($fh);
  // Notify the filesystem of the size change
  $file->filesize = filesize($file->uri);
  file_save($file);
  // Tell the user where we stuck it
  drupal_set_message( t('Export complete. <a href="!url">!filename</a>.', array(
    '!url' => file_create_url($file->uri),
    '!filename' => $filename,
  )));
}
