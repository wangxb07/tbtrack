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
    $variables = array(
      '#type' => TBTRACK_RANKING_TABLE_TYPE_ALL,
      '#product' => $product,
      '#platform' => $platform,
    );
    $output['ranking ' . $platform]['avg table'] = tbtrack_ranking_build_table($variables);
    $output['ranking ' . $platform]['avg table'] = tbtrack_ranking_build_table($variables);
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

  $variables = array(
    '#product' => $product,
    '#platform' => $platform,
  );

  $variables['#type'] = TBTRACK_RANKING_TABLE_TYPE_ALL;
  $output['tables']['all'] = tbtrack_ranking_build_table($variables);
  $variables['#type'] = TBTRACK_RANKING_TABLE_TYPE_AVG;
  $output['tables']['avg'] = tbtrack_ranking_build_table($variables);

  $output['tables']['keywords'] = array(
    '#type' => 'form',
    '#title' => t('Keywords history'),
    '#attributes' => array(
      'classes' => array(
        'product-keywords-wrapper',
      )
    ),
  );

  $variables['#type'] = TBTRACK_RANKING_TABLE_TYPE_KEYWORD;

  foreach ($product->field_keywords->value() as $keyword) {
    $keyword_table = array();
    $keyword_table = array(
      '#title' => $keyword->name,
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $variables['#keyword'] = $keyword;
    $keyword_table['table'] = tbtrack_ranking_build_table($variables);

    $output['tables']['keywords'][$keyword->tid] = $keyword_table;

    $keyword_extends = array();
    $keyword_extends = module_invoke_all('tbtrack_ranking_keyword_report_platform', $variables);
    if (is_array($keyword_extends)) {
      foreach($keyword_extends as $extend) {
        $output = array_merge($output, $extends);
      }
    }
  }

  unset($variables['#type']);

  $extends = module_invoke_all('tbtrack_ranking_product_report_platform', $variables);
  if (is_array($extends)) {
    foreach($extends as $extend) {
      $output = array_merge($output, $extends);
    }
  }

  return $output;
}

