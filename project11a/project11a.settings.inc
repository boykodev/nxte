<?php

/**
 * Implements hook_permissions()
 */
function project11a_permission() {
  return array(
    'administer project11a' => array(
      'title' => t('Access Project 11A'),
      'description' => t('Perform administration tasks for Project 11A.')
    )
  );
}
/**
 * Implements hook_menu()
 */
function project11a_menu() {
  $items['admin/config/project11a'] = array(
    'title' => 'Project 11A settings',
    'type' => MENU_NORMAL_ITEM,
    'page callback' => 'drupal_get_form',
    'page arguments' => array('project11a_admin_form'),
    'access arguments' => array('administer project11a')
  );
  return $items;
}

/**
 * Administer form for Project 11A
 */
function project11a_admin_form($form, &$form_state) {

  $form['project11a_max_entries'] = array(
    '#type' => 'textfield',
    '#title' => t('Max entries'),
    '#default_value' => variable_get('project11a_max_entries', 100),
    '#attributes' => array(
      ' type' => 'number'
    )
  );

  $content_types = _project11a_get_types();
  if ($content_types) {
    $form['project11a_allowed_types'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Allowed content types'),
      '#options' => drupal_map_assoc($content_types),
      '#default_value' => variable_get('project11a_allowed_types', array())
    );
  }

  return system_settings_form($form);
}

function _project11a_get_types() {
  return array_keys(node_type_get_types());
}
