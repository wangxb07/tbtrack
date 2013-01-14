<?php

/**
 * @file The file for Tbtrack ranking feature
 */


/**
 * tbtrack module ranking function instructions callback
 */
function tbtrack_ranking_instructions() {
  $output = array();
  return $output;
}

/**
 * fetch all form
 */
function tbtrack_ranking_query_all_form($form, &$form_state) {
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Query'),
  );

  return $form;
}

/**
 * Submit handler for tbtrack_ranking_query_all_form
 */
function tbtrack_ranking_query_all_form_submit() {
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
          $keywords[] = array(
            'name' => $keyword->name,
            'product_id' => $product_id,
            'platform' => $name,
          );
        }
      }
    }
    tbtrack_ranking_batch_query_helper($keywords);
  } else {
    drupal_set_message(t('no product!'));
  }
}

/**
 * Ranking Batch fetch process
 */
function _tbtrack_ranking_batch_query_process($keywords, &$context) {
  if (count($keywords) == 0) {
    $context['finished'] = 1;
    return FALSE;
  }

  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['max'] = count($keywords);
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['keywords'] = $keywords;
  }

  // Process nodes by groups of 1.
  $keyword = array_shift($context['sandbox']['keywords']);
  // Update our progress information.
  $context['sandbox']['progress']++;

  $ranking = 0;
  $result = tbtrack_ranking_remote_query($keyword['name'], $keyword['product_id'], $keyword['platform'], $ranking);
  if ($result) {
    tbtrack_ranking_insert($keyword['name'], $keyword['product_id'], $keyword['platform'], $ranking);
  } else {
    dd(t('!keyword !product_id out of ranking', array('!keyword' => $keyword['name'], '!product_id' => $keyword['product_id'])));
  }

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Ranking batch fetch finished callback
 */
function _tbtrack_ranking_batch_query_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('The ranking fetch has been performed.'));
  }
  else {
    drupal_set_message(t('An error occurred and processing did not complete.'), 'error');
    $message = format_plural(count($results), '1 item successfully processed:', '@count items successfully processed:');
    $message .= theme('item_list', array('items' => $results));
    drupal_set_message($message);
  }
}

/**
 * The form for query single keywords
 */
function tbtrack_ranking_query_form($form, &$form_state) {
  $form['keyword'] = array(
    '#type' => 'textfield',
    '#title' => t('Keyword'),
    '#required' => TRUE,
  );

  $form['product'] = array(
    '#type' => 'fieldset',
    '#title' => 'Product ID',
  );

  $platforms = tbtrack_get_platform_info();
  foreach ($platforms as $platform) {
    $form['product'][$platform['field']] = array(
      '#type' => 'textfield',
      '#title' => t('!platform Product ID', array('!platform' => $platform['title'])),
      '#required' => FALSE,
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Query'),
    '#weight' => 100,
  );

  if (!isset($form_state['values']) || $form_state['values']['keyword'] == '') {
    return $form;
  }

  $keyword = $form_state['values']['keyword'];

  $form['results'] = array('#type' => 'container', '#attributes' => array('class' => array('container-inline')));
  $form['results']['keyword'] = array('#markup' => $keyword, '#post_render' => array('_tbtrack_add_div'));

  foreach(tbtrack_get_platform_info() as $name => $platform) {
    if (!isset($form_state['values'][$platform['field']]) || empty($form_state['values'][$platform['field']])) {
      continue;
    }
    $ranking = 0;
    $product_id = $form_state['values'][$platform['field']];
    if($result = tbtrack_ranking_remote_query($keyword, $product_id, $name, $ranking)) {
      $form['results'][$name]['product'] = array(
        '#post_render' => array('_tbtrack_add_div'),
        '#prefix' => '<label>' . $platform['title'] . 'Product ID: </label>',
        '#markup' => $product_id,
      );
      $form['results'][$name]['platform'] = array(
        '#post_render' => array('_tbtrack_add_div'),
        '#prefix' => '<label>Platform: </label>',
        '#markup' => $platform['title'],
      );
      $form['results'][$name]['ranking'] = array(
        '#post_render' => array('_tbtrack_add_div'),
        '#prefix' => '<label>Ranking: </label>',
        '#markup' => $ranking,
      );
      $form['results'][$name]['product info'] = array(
        '#post_render' => array('_tbtrack_add_div'),
        '#prefix' => '<label>Product information: </label>',
        '#markup' => $result->plaintext,
      );
    } else {
      $form['results'][$name]['not found'] = array(
        '#post_render' => array('_tbtrack_add_div'),
        '#markup' => t('keyword for !platform not found that product id', array('!platform' => $platform['title'])),
      );
    }
  }

  return $form;
}

/**
 * Validation handler for tbtrack_ranking_query_form
 */
function tbtrack_ranking_query_form_validate($form, &$form_state) {
}

/**
 * Submit handler for tbtrack_ranking_query_form
 */
function tbtrack_ranking_query_form_submit($form, &$form_state) {
  if ($form_state['values']['keyword'] == '') {
    form_set_error('keyword', t('Please enter some keywords.'));
  }
  $form_state['rebuild'] = TRUE;
}

