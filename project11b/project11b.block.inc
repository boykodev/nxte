<?php

/**
 * Block logic
 */

/**
 * Implements hook_block_info()
 */
function project11b_block_info() {
  $blocks['formblock'] = array(
    'info' => t(PROJECT11B_FORM_TITLE),
  );

  return $blocks;
}

/**
 * Implements hook_block_view()
 */
function project11b_block_view($delta = '') {
  $block = array();

  switch ($delta) {
    case 'formblock':
      $block['subject'] = t(PROJECT11B_FORM_TITLE);
      $block['content'] = drupal_get_form('project11b_form');
      break;
  }
  return $block;
}
