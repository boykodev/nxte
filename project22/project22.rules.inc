<?php

/**
 * Implements hook_rules_event_info().
 */
function project22_rules_event_info() {
  $items = array(
    'project22_caches_flushed' => array(
      'label' => t('Cache was cleared'),
      'group' => t('Project 22'),
    ),
    'project22_module_enabled' => array(
      'label' => t('Module was enabled'),
      'group' => t('Project 22'),
      'variables' => array(
        'modules' => array(
          'type' => 'value',
          'label' => t('Modules that were enabled')
        ),
      ),
    ),
  );

  return $items;
}

/**
 * Implements hook_rules_condition_info().
 */
function project22_rules_condition_info() {
  $items = array(
    'project22_condition_username_six_chars' => array(
      'module' => 'project22',
      'label' => t('Username is 6 characters long'),
      'parameter' => array(
        'user' => array(
          'type' => 'user',
          'label' => t('Active user'),
        ),
      ),
      'group' => t('Project 22'),
    ),
    'project22_condition_module_x' => array(
      'module' => 'project22',
      'label' => t('Module is X'),
      'parameter' => array(
        'modules' => array(
          'type' => 'value',
          'label' => t('Modules that ware enabled')
        ),
      ),
      'group' => t('Project 22'),
    ),
  );

  return $items;
}

/**
 * Implements hook_rules_action_info().
 */
function project22_rules_action_info() {
  $items = array(
    'project22_action_increment_var' => array(
      'module' => 'project22',
      'label' => t('Increment var'),
      'group' => t('Project 22'),
    ),
  );

  return $items;
}

// trigger project22_caches_flushed
function project22_flush_caches() {
  rules_invoke_event('project22_caches_flushed');
  watchdog('project22', t('project22_caches_flushed was triggered'));
}

// trigger project22_module_enabled
function project22_modules_enabled($modules) {
  rules_invoke_event('project22_module_enabled', $modules);
  watchdog('project22', t('project22_caches_flushed was triggered'));
}

// condition - username has 6 characters
function project22_condition_username_six_chars($user) {
  return $user && mb_strlen($user->name) === 6;
}

// condition - module X was enabled
function project22_condition_module_x($modules) {
  $module_x = 'locale';
  return in_array($module_x, $modules);
}

// action - increment a variable
function project22_action_increment_var() {
  $project22_increment = variable_get('project22_increment', 0);
  $incremented = ++$project22_increment;
  variable_set('project22_increment', $incremented);
  watchdog('project22', t("project22 was incremented to $incremented"));
}
