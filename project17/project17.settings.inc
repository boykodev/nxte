<?php

/**
 * Implements hook_permissions()
 */
function project17_permission() {
  return array(
    'administer project17' => array(
      'title' => t('Access Project 17'),
      'description' => t('Perform administration tasks for Project 17.')
    )
  );
}

/**
 * Implements hook_menu()
 */
function project17_menu() {
  $items['admin/config/project17'] = array(
    'title' => 'Project 17 settings',
    'type' => MENU_NORMAL_ITEM,
    'page callback' => 'drupal_get_form',
    'page arguments' => array('project17_admin_form'),
    'access arguments' => array('administer project17')
  );
  return $items;
}

/**
 * Administer form for Project 17
 */
function project17_admin_form($form, &$form_state) {

  $form['#attributes'] = array(
    'enctype' => 'multipart/form-data'
  );

  $form['project17_csv_file'] = array(
    '#title' => t('CSV File'),
    '#type' => 'file',
    '#description' => 'Choose your CSV file here',
  );

  $form['project17_text_delimiter'] = array(
    '#type' => 'textfield',
    '#title' => t('Used text delimiter'),
    '#description' => t("Specify a text delimiter. Defaults to ' , '"),
    '#default_value' => variable_get('project17_text_delimiter', '')
  );

  $form['project17_field_delimiter'] = array(
    '#type' => 'textfield',
    '#title' => t('Used field delimiter'),
    '#description' => t("Specify a field delimiter. Defaults to ' \" '"),
    '#default_value' => variable_get('project17_field_delimiter', '')
  );

  $form['project17_skip_rows'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of header rows to skip'),
    '#description' => t('Specify a number of header rows to skip. Defaults to zero rows'),
    '#default_value' => variable_get('project17_skip_rows', ''),
    '#attributes' => array(
      ' type' => 'number'
    )
  );

  $form['#submit'][] = 'project17_form_submit';
  $form['#validate'][] = 'project17_save_csv';

  return system_settings_form($form);
}

/**
 * Implements hook_form_alter().
 */
function project17_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'project17_admin_form') {
    $form['actions']['submit']['#value'] = t('Perform Batch task');
  }
}

function project17_save_csv(&$form, &$form_state) {
  $validators = array(
    'file_validate_extensions' => array('csv'),
  );

  $file = file_save_upload('project17_csv_file', $validators, "public://", FILE_EXISTS_REPLACE);

  if ($file) {
    $form_state['values']['project17_csv_file'] = $file->destination;
  } else {
    form_set_error('project17', t('Unable to copy upload file'));
  }
}

/**
 * Form submit callback
 */
function project17_form_submit($form, &$form_state) {
  $params = array(
    'text_delimiter' => $form['project17_text_delimiter']['#value'],
    'field_delimiter' => $form['project17_field_delimiter']['#value'],
    'skip_rows' => $form['project17_skip_rows']['#value'],
    'csv_file' => $form_state['values']['project17_csv_file']
  );

  project17_batch_task($params);
}
