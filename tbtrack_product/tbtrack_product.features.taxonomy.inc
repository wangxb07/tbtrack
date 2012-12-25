<?php
/**
 * @file
 * tbtrack_product.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function tbtrack_product_taxonomy_default_vocabularies() {
  return array(
    'keywords' => array(
      'name' => 'keywords',
      'machine_name' => 'keywords',
      'description' => 'taobao search keywords',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
  );
}
