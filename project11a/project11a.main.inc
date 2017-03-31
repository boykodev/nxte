<?php

/**
 * Implements hook_node_update().
 */
function project11a_node_update($node) {
  if (!_project11a_type_is_allowed($node->type)) return;

  $table_name = 'project11a_data';
  $node_id = $node->nid;

  if (_project11a_node_unpublished($node)) {
    _project11a_delete_records($node_id);
  } else {
    $entry_data = array(
      'user_id' => $node->uid,
      'node_id' => $node_id,
      'node_type' => $node->type,
      'timestamp' => time(),
      'ip_address' => ip_address()
    );
    drupal_write_record($table_name, $entry_data);
  }
}

/**
 * Implements hook_node_delete().
 */
function project11a_node_delete($node) {
  if (!_project11a_type_is_allowed($node->type)) return;

  _project11a_delete_records($node->nid);
}

/* HELPER FUNCTIONS */

/**
 * Deletes all records in module table
 * @param $node_id
 */
function _project11a_delete_records($node_id) {
  db_delete('project11a_data')
    ->condition('node_id', $node_id)
    ->execute();
}

/**
 * Determine if node was just unpublished
 * @param $node
 * @return bool
 */
function _project11a_node_unpublished(&$node) {
  // spliting conditions according to Coding Standarts
  $is_not_published = ($node->status == NODE_NOT_PUBLISHED);
  $was_published = ($node->original->status == NODE_PUBLISHED);

  return $is_not_published && $was_published;
}

/**
 * Check if node type is allowed
 */
function _project11a_type_is_allowed($type) {
  $allowed_types = variable_get('project11a_allowed_types', array());
  return in_array($type, $allowed_types, true);
}
