<?php

/**
 * Settings form
 */
function project11b_form($form, &$form_state) {

  // FIELDS
  $form['fname'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#size' => 21,
  );

  $form['lname'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#size' => 21,
  );

  $form['gender'] = array(
    '#type' => 'select',
    '#title' => t('Select gender'),
    '#options' => _project11b_select_options(),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  // VALIDATION
  $form['#validate'][] = 'project11b_form_validate';
  $form['#submit'][] = 'project11b_form_submit';

  return $form;
}


/**
 * Validation logic
 */
function project11b_form_validate($form, &$form_state) {

  if (!preg_match('/^[\p{L}\s\'.-]+$/', $form['fname']['#value'])) {
    form_set_error('fname', 'First name validation error');
  }

  if (!preg_match('/^[\p{L}\s\'.-]+$/', $form['lname']['#value'])) {
    form_set_error('lname', 'Last name validation error');
  }

  if (!in_array($form['gender']['#value'], array(0, 1))) {
    form_set_error('gender', "There's no other gender ;)");
  }
}

/**
 * Submit logic
 */
function project11b_form_submit($form, &$form_state) {
  $is_allowed_to_submit = _project11b_is_allowed_to_submit(ip_address());
  $entry_data = array(
    'fname' => $form['fname']['#value'],
    'lname' => $form['lname']['#value'],
    'gender' => $form['gender']['#value'],
    'timestamp' => time(),
    'ip_address' => ip_address()
  );

  if ($is_allowed_to_submit) {
    $success = drupal_write_record(PROJECT11B_TABLE_NAME, $entry_data);
  } else {
    $success = false;
  }

  if ($success) {
    watchdog('form_submit', "Form was submitted: %data",
      array('%data' => implode(', ', $entry_data)), WATCHDOG_INFO);
    drupal_set_message('Thanks! Your form has been submitted.');
  } else {
    watchdog('form_submit', "Form submit error: %data",
      array('%data' => implode(', ', $entry_data)), WATCHDOG_ERROR);
    drupal_set_message('Sorry. Some error happened.', 'error');
  }
}
