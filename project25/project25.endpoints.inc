<?php

/**
 * Endpoint for api/node/{nid}
 * @param $nid
 */
function project25_endpoint_single($nid) {
  $query = project25_get_node_query();
  $query->condition('nid', $nid);

  $result = $query->execute()->fetch();
  echo drupal_json_encode($result);
}

/**
 * Endpoint for api/node/random
 */
function project25_endpoint_random_single() {
  $query = project25_get_node_query();
  $query->orderRandom();

  $result = $query->execute()->fetch();
  unset($result->random_field);

  echo drupal_json_encode($result);
}

/**
 * Endpoint for api/node/random/{type}
 * @param $type
 */
function project25_endpoint_random_of_type($type) {
  $query = project25_get_node_query();
  $query->condition('type', $type);
  $query->orderRandom();

  $result = $query->execute()->fetch();
  unset($result->random_field);

  echo drupal_json_encode($result);
}

/**
 * Endpoint for api/node/list
 * Optional parameters - 'from' and 'to'
 * @param null $from
 * @param null $to
 */
function project25_endpoint_list($from = NULL, $to = NULL) {
  $query = project25_get_node_query();

  // apply range
  if (!is_null($from) && !is_null($to)) {
    $query->range($from, $to);
  }

  $result = $query->execute()->fetchAll();
  unset($result->random_field);

  echo drupal_json_encode($result);
}

/**
 * Endpoint for api/node/list/{type}
 * Optional parameters - 'from' and 'to'
 * @param $type
 * @param null $from
 * @param null $to
 */
function project25_endpoint_list_of_type($type, $from = NULL, $to = NULL) {
  $query = project25_get_node_query();
  $query->condition('type', $type);

  // apply range
  if (!is_null($from) && !is_null($to)) {
    $query->range($from, $to);
  }

  $result = $query->execute()->fetchAll();
  unset($result->random_field);

  echo drupal_json_encode($result);
}

/**
 * Get the db_query for nodes
 * @return $this|\SelectQueryInterface
 */
function project25_get_node_query() {
  $query = db_select('node', 'n');
  $query->leftJoin('field_data_body', 'd', '(d.entity_id = n.nid AND d.entity_type = :node)', array(':node' => 'node'));
  $query->fields('n', array('nid', 'type', 'title', 'created', 'changed'));
  $query->fields('d', array('body_value'));

  return $query;
}
