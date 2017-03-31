<?php

/**
 * Implements hook_permissions()
 */
function project11b_permission() {
  return array(
    'administer project11b' => array(
      'title' => t('Access Project 11B'),
      'description' => t('Perform administration tasks for Project 11B.')
    )
  );
}
/**
 * Implements hook_menu()
 */
function project11b_menu() {
  $items['admin/config/project11b'] = array(
    'title' => 'Project 11B settings',
    'type' => MENU_NORMAL_ITEM,
    'page callback' => 'drupal_get_form',
    'page arguments' => array('project11b_admin_form'),
    'access arguments' => array('administer project11b')
  );
  return $items;
}

/**
 * Administer form for Project 11B
 */
function project11b_admin_form($form, &$form_state) {

  $form['project11b_allowed_ips'] = array(
    '#type' => 'textarea',
    '#title' => t('Allowed IPs'),
    '#description' => t('Enter one per line'),
    '#default_value' => variable_get('project11b_allowed_ips', ''),
  );

  $form['project11b_form_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Form title'),
    '#default_value' => variable_get('project11b_form_title', ''),
  );

  $form['project11b_allowed_submits'] = array(
    '#type' => 'textfield',
    '#title' => t('Allowed submits'),
    '#default_value' => variable_get('project11b_allowed_submits', 5),
    '#attributes' => array(
      ' type' => 'number'
    )
  );

  return system_settings_form($form);
}
