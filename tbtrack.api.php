<?php

/**
 * @file
 * Hooks provided by the tbtrack module.
 */

/**
 * Registers your module as an list of platform
 */
function hook_tbtrack_platform_info() {
  return array(
    'tmall' => array(
      'title' => 'TMall',
      'search uri' => array(
        'host' => '',
        'path' => '',
      ),
      'selector callback' => '',
    ),
    'taobao' => array(
      'title' => 'Taobao',
      'search uri' => array(
        'host' => '',
        'path' => '',
      ),
      'selector callback' => '',
    ),
  );
}