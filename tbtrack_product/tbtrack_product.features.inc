<?php
/**
 * @file
 * tbtrack_product.features.inc
 */

/**
 * Implements hook_views_api().
 */
function tbtrack_product_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function tbtrack_product_node_info() {
  $items = array(
    'products' => array(
      'name' => t('产品'),
      'base' => 'node_content',
      'description' => t('taobao product which need fetch ranking.'),
      'has_title' => '1',
      'title_label' => t('名称'),
      'help' => '',
    ),
  );
  return $items;
}
