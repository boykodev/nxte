<?php

/**
 * Implements hook_permissions()
 */
function project24_permission() {
  return array(
    'administer project24' => array(
      'title' => t('Access Project 24'),
      'description' => t('Perform administration tasks for Project 24.')
    )
  );
}
/**
 * Implements hook_menu()
 */
function project24_menu() {
  $items['admin/config/project24'] = array(
    'title' => 'Project 24 settings',
    'type' => MENU_NORMAL_ITEM,
    'page callback' => 'drupal_get_form',
    'page arguments' => array('project24_admin_form'),
    'access arguments' => array('administer project24')
  );
  return $items;
}

/**
 * Administer form for Project 24
 */
function project24_admin_form($form) {
  $form['project24_selected_nodes'] = array(
    "#type" => "select",
    '#multiple' => TRUE,
    "#title" => t("Select your node."),
    "#default_value" => variable_get("project24_selected_nodes", true),
    "#options" => project24_get_all_nodes(),
  );

  return system_settings_form($form);
}

function project24_get_all_nodes() {
  $result = array();

  $nids = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->execute()
    ->fetchCol();

  $nodes = node_load_multiple($nids);

  foreach ($nodes as $nid => $node) {
    $result[$nid] = $node->title;
  }

  return $result;
}
