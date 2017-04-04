<?php

define('PROJECT23_BLOCK_TITLE', t('Text block'));

/**
 * Implements hook_block_info()
 */
function project23_block_info() {
  $blocks['textblock'] = array(
    'info' => PROJECT23_BLOCK_TITLE,
  );

  return $blocks;
}

/**
 * Implements hook_block_view()
 */
function project23_block_view($delta = '') {
  $block = array();

  switch ($delta) {
    case 'textblock':
      $block['subject'] = PROJECT23_BLOCK_TITLE;
      $block['content'] = project23_get_textblock();
      break;
  }

  return $block;
}

/**
 * Callback for a block
 */
function project23_get_textblock() {
  $token_data = array();

  $nid = variable_get('project23_dropdown', 0);
  $blocktext = variable_get('project23_blocktext', '');

  if ($nid) {
    $node = node_load($nid);
    $token_data['node'] = $node;
  }

  return token_replace($blocktext, $token_data);
}
