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
  // query database and get records of product
  $ids = db_select('node', 'n')->fields('n', array('nid'))
    ->condition('type', 'products')
    ->execute()
    ->fetchCol();

  if ($ids) {
    // flat keywords from products
    $keywords = array();
    $platforms = tbtrack_get_platform_info();

    foreach ($ids as $id) {
      // all products
      $product = entity_metadata_wrapper('node', $id);
      // all keywords for product
      foreach ($product->field_keywords->value() as $keyword) {
        // all platforms
        foreach ($platforms as $name => $platform) {
          $product_id = $product->{$platform['field']}->value();
          if (empty($product_id)) {
            continue;
          }

          $ranking = 0;
          $result = tbtrack_ranking_remote_query($keyword->name, $product_id, $name, $ranking);
          if ($result) {
            tbtrack_ranking_insert($keyword->name, $product_id, $name, $ranking);
          }
          else {
            drush_print(t('!keyword !product_id out of ranking', array('!keyword' => $keyword->name, '!product_id' => $product_id)));
          }
        }
      }
    }
  } else {
    drush_print('no product!');
  }
}

