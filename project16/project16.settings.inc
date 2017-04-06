<?php

/**
 * Implements hook_permissions()
 */
function project16_permission() {
  return array(
    'administer project16' => array(
      'title' => t('Access Project 16'),
      'description' => t('Perform administration tasks for Project 16.')
    )
  );
}
/**
 * Implements hook_menu()
 */
function project16_menu() {
  $items['admin/config/project16'] = array(
    'title' => 'Project 16 settings',
    'type' => MENU_NORMAL_ITEM,
    'page callback' => 'drupal_get_form',
    'page arguments' => array('project16_admin_form'),
    'access arguments' => array('administer project16')
  );
  return $items;
}

/**
 * Administer form for Project 16
 */
function project16_admin_form($form, &$form_state) {

  $form['project16_match_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Match title'),
    '#description' => t('Export only nodes that have this text in title'),
    '#default_value' => variable_get('project16_match_title', '')
  );

  $form['project16_add_headers'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add CSV headers'),
    '#description' => t('Whether show headers in CSV export'),
    '#default_value' => variable_get('project16_add_headers', 0)
  );

  $form['project16_perform_batch'] = array(
    '#type' => 'checkbox',
    '#title' => t('Initiate Batch'),
    '#description' => t('Perform Batch task'),
  );

  $form['#submit'][] = 'project16_form_submit';

  return system_settings_form($form);
}

/**
 * Form submit callback
 */
function project16_form_submit($form) {
  $perform_batch = $form['project16_perform_batch']['#value'];
  if ($perform_batch) {
    $params = array(
      'headers' => $form['project16_add_headers']['#value'],
      'match' => $form['project16_match_title']['#value']
    );

    project16_batch_task($params);
  }
}
