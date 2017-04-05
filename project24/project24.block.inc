<?php

define('PROJECT24_BLOCK_TITLE', t('Node teaser block'));

/**
 * Implements hook_block_info()
 */
function project24_block_info() {
  $blocks['textblock'] = array(
    'info' => PROJECT24_BLOCK_TITLE,
    'cache' => DRUPAL_NO_CACHE
  );

  return $blocks;
}

/**
 * Implements hook_block_view()
 */
function project24_block_view($delta = '') {
  $block = array();

  switch ($delta) {
    case 'textblock':
      $block['subject'] = PROJECT24_BLOCK_TITLE;
      $block['content'] = project24_get_block();
      break;
  }

  return $block;
}

/**
 * Callback for a block
 */
function project24_get_block() {
  $nids = variable_get('project24_selected_nodes', array());
  // alter nodes order
  drupal_alter('project24_nodes_order', $nids);

  $nodes = node_load_multiple($nids);

  // hook to change nodes data
  module_invoke_all('project24_node_block', $nodes);
  $view = node_view_multiple($nodes, 'teaser');

  return drupal_render($view);
}
