<?php

/**
 * Implements hook_cron().
 */
function project11a_cron() {
  $query = db_select('project11a_data');
  $query->addExpression('count(*)');
  $total = $query->execute()->fetchField();

  $max_entries = variable_get('project11a_max_entries', 0);

  if ($total > $max_entries) {
    // remove all entries
    db_delete('project11a_data')->execute();
  }
}
