<?php

/**
 * @file tbtrack module page callback define here
 */

/**
 * default report for product ranking
 */
function tbtrack_ranking_product_report_default($node) {
  if ($node->type != 'products') {
    drupal_set_message(t('Sorry, current node is not a product'));
    drupal_goto('node/' . $node->nid);
  }
  $output = array();

  $product = entity_metadata_wrapper('node', $node->nid);

  foreach (array_keys(tbtrack_get_platform_info()) as $platform) {
    $output['ranking ' . $platform]['#post_render'] = array('_tbtrack_add_div');
    $output['ranking ' . $platform]['title'] = array(
      '#markup' => t('Information for platform !platform', array('!platform' => $platform)),
      '#post_render' => array('_tbtrack_add_div'),
    );
    $output['ranking ' . $platform]['avg table'] = tbtrack_ranking_build_table($product, $platform, TBTRACK_RANKING_TABLE_TYPE_AVG);
    $output['ranking ' . $platform]['avg table'] = tbtrack_ranking_build_table($product, $platform, TBTRACK_RANKING_TABLE_TYPE_AVG);
  }

  return $output;
}

/**
 * platform report for product ranking
 */
function tbtrack_ranking_product_report_platform($node, $platform) {
  if ($node->type != 'products') {
    drupal_set_message(t('Sorry, current node is not a product'));
    drupal_goto('node/' . $node->nid);
  }
  $output = array();

  $product = entity_metadata_wrapper('node', $node->nid);

  $output['tables']['all'] = tbtrack_ranking_build_table($product, $platform, TBTRACK_RANKING_TABLE_TYPE_ALL);
  $output['tables']['avg'] = tbtrack_ranking_build_table($product, $platform, TBTRACK_RANKING_TABLE_TYPE_AVG);

  $extends = module_invoke_all('tbtrack_ranking_product_report_platform', $product, $platform);
  if (is_array($extends)) {
    foreach($extends as $extend) {
      $output = array_merge($output, $extends);
    }
  }

  return $output;
}