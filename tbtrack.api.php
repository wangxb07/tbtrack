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
      // if your module will implements ranking for platform
      'ranking' => array(
        'search uri' => array(
          'host' => '',
          'path' => '',
        ),
        'selector callback' => '',
      ),
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

/**
 * Registers your module as an list of platform attach params
 */
function hook_tbtrack_platform_attach_params() {
  return array(
    'ranking' => array(
      'search host' => array(
        '#required' => TRUE,
        '#default_value' => 'http://taobao.com',
      ),
      'search path' => array(
        '#default_value' => '/search',
        '#required' => TRUE,
      ),
      'selector callback' => array(
        '#required' => TRUE,
      ),
    ),
  );
}