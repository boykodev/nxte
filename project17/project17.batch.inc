<?php

// menu callback function - sets up the batch
function project17_batch_task($params) {
  $batch = array(
    'operations' => array(),
    'finished' => 'project17_batch_task_finished',
    // runs after batch is finished
    'title' => t('Processing Export'),
    'init_message' => t('Export is starting.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Export has encountered an error.'),
  );

  if ($handle = fopen($params['csv_file'], 'r')) {
    $delimiter = $params['text_delimiter'] ? $params['text_delimiter'] : ',';
    $enclosure = $params['field_delimiter'] ? $params['field_delimiter'] : '"';

    // skip specified header rows
    if (ctype_digit($params['skip_rows'])) {
      for ($i = 0; $i < $params['skip_rows']; $i++) {
        fgetcsv($handle, 4096, $delimiter, $enclosure);
      }
    }

    while ($line = fgetcsv($handle, 4096, $delimiter, $enclosure)) {
      $batch['operations'][] = array(
        'project17_batch_task_process',
        array($line)
      );
    }
    fclose($handle);
  }

  batch_set($batch);
  batch_process('admin/config/project17'); // page to return to after complete
}

function project17_batch_task_process($line) {
  $values = array(
    'title' => $line[0],
    'email' => $line[1],
    'desc' => $line[2],
    'image' => $line[3]
  );

  $node = new stdClass();

  $node->uid = 1;
  $node->type = "csv_import";
  $node->title = $values['title'];
  $node->status = NODE_PUBLISHED;
  $node->language = LANGUAGE_NONE;

  $node->body[$node->language][0]['value'] = $values['desc'];
  $node->field_email[$node->language][0]['email'] = $values['email'];

  // download and save image
  $image = system_retrieve_file($values['image'], NULL, FALSE, FILE_EXISTS_REPLACE);
  $file = project17_save_image($image);
  // add image to image field
  $node->field_image[LANGUAGE_NONE]['0']['fid'] = $file->fid;

  node_save($node);
}

function project17_batch_task_finished($success, $results, $operations) {
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
 * Save image to files directory
 * @param $file_drupal_path
 * @param int $uid
 * @param int $status
 * @return mixed|object
 */
function project17_save_image($file_drupal_path, $uid = 1, $status = FILE_STATUS_PERMANENT) {
  $files = file_load_multiple(array(), array('uri' => $file_drupal_path));
  $file = reset($files);

  if (!$file) {
    $file = (object) array(
      'filename' => basename($file_drupal_path),
      'filepath' => $file_drupal_path,
      'filemime' => file_get_mimetype($file_drupal_path),
      'filesize' => filesize($file_drupal_path),
      'uid' => $uid,
      'status' => $status,
      'timestamp' => time(),
      'uri' => $file_drupal_path,
    );
    drupal_write_record('file_managed', $file);
  }
  return $file;
}
