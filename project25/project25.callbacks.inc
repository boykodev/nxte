<?php

/**
 * Callback for api/node/{nid}
 * @param $nid
 */
function project25_callback_single($nid) {
  if (ctype_digit($nid)) {
    project25_endpoint_single(intval($nid));
  } else {
    project25_json_error('The node argument is invalid');
  }

  project25_log_request();
}

/**
 * Callback for api/node/random
 */
function project25_callback_random_single() {
  project25_endpoint_random_single();
  project25_log_request();
}

/**
 * Callback for api/node/random/{type}
 * @param $type
 */
function project25_callback_random_of_type($type) {
  project25_endpoint_random_of_type($type);
  project25_log_request();
}

/**
 * Callback for api/node/list
 */
function project25_callback_list() {
  $params = drupal_get_query_parameters();

  if (isset($params['from']) && isset($params['to'])) {
    $from = $params['from'];
    $to = $params['to'];

    if (ctype_digit($from) && ctype_digit($to)) {
      project25_endpoint_list($from, $to);
    } else {
      project25_json_error('Request parameters are invalid');
    }
  } else {
    project25_endpoint_list();
  }
}

/**
 * Callback for api/node/list/{type}
 * @param $type
 */
function project25_callback_list_of_type($type) {
  $params = drupal_get_query_parameters();

  if (isset($params['from']) && isset($params['to'])) {
    $from = $params['from'];
    $to = $params['to'];

    if (ctype_digit($from) && ctype_digit($to)) {
      project25_endpoint_list_of_type($type, $from, $to);
    } else {
      project25_json_error('Request parameters are invalid');
    }
  } else {
    project25_endpoint_list_of_type($type);
  }

  project25_log_request();
}

/**
 * Log request error and return JSON with a error message
 * @param $text
 */
function project25_json_error($text) {
  // works on PHP < 5.4
  header("HTTP/1.1 400 Bad Request");

  $error = array(
    'error' => $text
  );

  echo drupal_json_encode($error);
  project25_log_request(true);
}

/**
 * Log requests and request errors
 * @param bool $error
 */
function project25_log_request($error = false) {
  $log_once = &drupal_static('log_once');
  if ($log_once) return;

  $link = $_SERVER['REQUEST_URI'];

  if ($error) {
    watchdog('project25_api', 'Error performing JSON API request.', array(), WATCHDOG_ERROR, $link);
  } else {
    watchdog('project25_api', 'Request to JSON API was performed.', array(), WATCHDOG_NOTICE, $link);
  }

  $log_once = true;
}
