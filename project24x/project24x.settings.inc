<?php

define('PROJECT24X_ORDER_NONE', 0);
define('PROJECT24X_ORDER_NID', 1);
define('PROJECT24X_ORDER_CREATED', 2);
define('PROJECT24X_ORDER_UPDATED', 3);
define('PROJECT24X_ORDER_RANDOM', 4);

/**
 * Implements hook_permissions()
 */
function project24x_permission() {
  return array(
    'administer project24x' => array(
      'title' => t('Access Project 24x'),
      'description' => t('Perform administration tasks for Project 24x.')
    )
  );
}
/**
 * Implements hook_menu()
 */
function project24x_menu() {
  $items['admin/config/project24x'] = array(
    'title' => 'Project 24x settings',
    'type' => MENU_NORMAL_ITEM,
    'page callback' => 'drupal_get_form',
    'page arguments' => array('project24x_admin_form'),
    'access arguments' => array('administer project24x')
  );
  return $items;
}

/**
 * Administer form for Project 24x
 */
function project24x_admin_form($form) {
  $form['project24x_order_option'] = array(
    "#type" => "select",
    "#title" => t("Select the order of the nodes."),
    "#default_value" => variable_get("project24x_order_option", true),
    "#options" => project24x_get_order_options(),
  );

  $form['project24x_sort_option'] = array(
    "#type" => "select",
    "#title" => t("Select the sort option."),
    "#default_value" => variable_get("project24x_sort_option", true),
    "#options" => drupal_map_assoc(array('ASC', 'DESC')),
  );

  return system_settings_form($form);
}

function project24x_get_order_options() {
  $options = array(
    PROJECT24X_ORDER_NID => t('By Node ID'),
    PROJECT24X_ORDER_CREATED => t('By the time is was created'),
    PROJECT24X_ORDER_UPDATED => t('By the time is was updated'),
    PROJECT24X_ORDER_RANDOM => t('Random'),
  );

  return $options;
}
