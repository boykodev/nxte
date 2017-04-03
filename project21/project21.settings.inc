<?php

/**
 * Implements hook_permissions()
 */
function project21_permission() {
  return array(
    'administer project21' => array(
      'title' => t('Access Project 21'),
      'description' => t('Perform administration tasks for Project 21.')
    )
  );
}
/**
 * Implements hook_menu()
 */
function project21_menu() {
  $items['admin/config/project21'] = array(
    'title' => 'Project 21 settings',
    'type' => MENU_NORMAL_ITEM,
    'page callback' => 'drupal_get_form',
    'page arguments' => array('project21_admin_form'),
    'access arguments' => array('administer project21')
  );
  return $items;
}

/**
 * Administer form for Project 21
 */
function project21_admin_form($form, &$form_state) {

  $form['project21_clear_caches'] = array(
    '#type' => 'checkbox',
    '#title' => t('Clear all table caches?'),
  );

  $form['#submit'][] = 'project21_form_submit';

  return system_settings_form($form);
}

/**
 * Submit logic
 */
function project21_form_submit($form) {
  $clear_module_cache = (bool) $form['project21_clear_caches']['#value'];

  if ($clear_module_cache) {
    project21_cache_rebuild();
    drupal_set_message('Cache was cleared!');
  } else {
    drupal_set_message('Cache was NOT cleared!');
  }
}
