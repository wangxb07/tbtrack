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

/**
 * The hook implements for append everything to product node content
 * @param node entity $node
 * @param string $view_mode
 * @param string $platform platform name
 */
function hook_tbtrack_product_node_view($node, $view_mode, $platform) {
  $result = db_select('tbtrack_ranking', 'r')->fields('r')
    ->condition('product_id', $product->{$platform['field']}->value())
    ->condition('platform', $name)
    ->execute();

  $rows = array();
  while ($record = $result->fetchAssoc()) {
    $rows[$record['rid']] = array(
      'keyword' => $record['keyword'],
      'ranking' => $record['ranking'],
      'created' => format_date($record['created'], 'short'),
    );
  }

  $node->content['ranking'][$name . ' table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('No content available.'),
  );
}

/**
 * The hook implements for append everything to product ranking platform report
 * @param array $output render array
 * @param EntityMetadataWrapper $product
 * @param string $platform platform name
 */
function hook_tbtrack_ranking_product_report_platform(&$output, $product, $platform) {
  // build yourself array for rander
  $output['title'] = array('#markup' => 'Hello world');
}