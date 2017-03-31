<?php

/*
 * Constants
 */
define('PROJECT11B_TABLE_NAME', 'project11b_data');
define('PROJECT11B_FORM_TITLE', variable_get('project11b_form_title', 'Form Block'));

/*
 * Provide options for form select
 */
function _project11b_select_options() {
  return array(
    t('Male'),
    t('Female'),
    t('Other')
  );
}

/*
 * Get total form submitted by ip
 */
function _project11b_total_submits_by_id($ip_address) {
  $query = db_select(PROJECT11B_TABLE_NAME)
    ->condition('ip_address', $ip_address);
  $query->addExpression('count(*)');

  return $query->execute()->fetchField();
}

/*
 * Get all allowed ips
 */
function _project11b_get_allowed_ips() {
  $allowed_ips = array();
  $allowed_ips_str = variable_get('project11b_allowed_ips', '');
  $allowed_ips_str = trim($allowed_ips_str);

  if ($allowed_ips_str) {
    $allowed_ips = preg_split('/\R/', $allowed_ips_str);
  }

  return $allowed_ips;
}

/*
 * Get if ip is allowed to submit more forms
 */
function _project11b_is_allowed_to_submit($ip_address) {
  $allowed_ips = _project11b_get_allowed_ips();
  if (in_array($ip_address, $allowed_ips, true)) {
    $limit = variable_get('project11b_allowed_submits', 5);
    $total = _project11b_total_submits_by_id($ip_address);

    return ($total < $limit);
  }

  return false;
}
