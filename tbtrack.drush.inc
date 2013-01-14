<?php
/**
 * @file
 * Drush support for the tbtrack module
 */

function tbtrack_drush_command() {
  $items = array();

  $items['tbtrack-fetchall'] = array(
    'description' => 'Perform command that fetch all product keywords current ranking',
    'drupal dependencies' => array('tbtrack'),
  );

  return $items;
}

/**
 * run ranking fetch process function
 */
function drush_tbtrack_fetchall() {
  tbtrack_fetchall_ranking_drush();
}

