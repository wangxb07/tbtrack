<?php
/**
 * @file
 * tbtrack_product.features.inc
 */

/**
 * Implements hook_node_info().
 */
function tbtrack_product_node_info() {
  $items = array(
    'products' => array(
      'name' => t('Products'),
      'base' => 'node_content',
      'description' => t('taobao product which need fetch ranking.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}
