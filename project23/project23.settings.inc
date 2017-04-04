<?php

/**
 * Implements hook_permissions()
 */
function project23_permission() {
  return array(
    'administer project23' => array(
      'title' => t('Access Project 23'),
      'description' => t('Perform administration tasks for Project 23.')
    )
  );
}
/**
 * Implements hook_menu()
 */
function project23_menu() {
  $items['admin/config/project23'] = array(
    'title' => 'Project 23 settings',
    'type' => MENU_NORMAL_ITEM,
    'page callback' => 'drupal_get_form',
    'page arguments' => array('project23_admin_form'),
    'access arguments' => array('administer project23')
  );
  return $items;
}

/**
 * Administer form for Project 23
 */
function project23_admin_form($form) {
  $form['project23_dropdown'] = array(
    "#type" => "select",
    "#title" => t("Select your node."),
    "#default_value" => variable_get("project23_dropdown", true),
    "#options" => project23_get_all_nodes(),
  );

  $form['project23_blocktext'] = array(
    '#type' => 'textarea',
    '#title' => t('Text for block'),
    '#default_value' => variable_get('project23_blocktext', ''),
  );

  $form['project23_input1'] = array(
    '#type' => 'textfield',
    '#title' => t('Input field 1'),
    '#default_value' => variable_get('project23_input1', ''),
  );

  $form['project23_input2'] = array(
    '#type' => 'textfield',
    '#title' => t('Input field 2'),
    '#default_value' => variable_get('project23_input2', ''),
  );

  $form['token_help'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array('node', 'input'),
  );

  return system_settings_form($form);
}

function project23_get_all_nodes() {
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
