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
            'platform_info' => $platform,
            'platform_name' => $name,
          );
        }
      }
    }

    $batch = array(
      'operations' => array(
        array('_tbtrack_batch_query_process', array($keywords))
      ),
      'finished' => '_tbtrack_batch_query_finished',
      'title' => t('Processing'),
      // We use a single multi-pass operation, so the default
      // 'Remaining x of y operations' message will be confusing here.
      'progress_message' => '',
      'error_message' => t('The fetch ranking has encountered an error.'),
      // The operations do not live in the .module file, so we need to
      // tell the batch engine which file to load before calling them.
      'file' => drupal_get_path('module', 'tbtrack') . '/tbtrack.module',
    );
    batch_set($batch);
  } else {
    drupal_set_message(t('no product!'));
  }
}

/**
 * Ranking Batch fetch process
 */
function _tbtrack_batch_query_process($keywords, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($keywords);
    $context['sandbox']['keywords'] = $keywords;
  }

  // Process nodes by groups of 1.
  $keyword = array_shift($context['sandbox']['keywords']);
  // Update our progress information.
  $context['sandbox']['progress']++;

  $ranking = 0;
  $result = tbtrack_remote_query($keyword['name'], $keyword['product_id'], $keyword['platform_info'], $ranking);
  if ($result) {
    tbtrack_ranking_insert($keyword['name'], $keyword['product_id'], $keyword['platform_name'], $ranking);
  } else {
    dd(t('out of ranking'));
  }

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Ranking batch fetch finished callback
 */
function _tbtrack_batch_query_finished($success, $results, $operations) {
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
 * insert ranking info into database
 */
function tbtrack_ranking_insert($keyword, $product_id, $platform, $ranking) {
  return db_insert('tbtrack_ranking')->fields(array(
      'keyword' => $keyword,
      'product_id' => $product_id,
      'platform' => $platform,
      'ranking' => $ranking,
      'created' => time()
    ))->execute();
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
    if($result = tbtrack_remote_query($keyword, $product_id, $platform, $ranking)) {
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
        '#prefix' => '<label>Product infomation: </label>',
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

/**
 * fetch data function
 */
function tbtrack_remote_query($keyword, $product_id, $platform, &$ranking = 0, $page_offset = NULL) {
  $old_keyword = $keyword;
  $charset = str_replace("-", "", strtolower($platform['charset']));
  if ($charset != 'utf8') {
    $keyword = iconv('UTF-8', $charset, $old_keyword);
  }

  // current page ranking
  $page_ranking = 0;

  // TODO configurable page size
  $page_size = $platform['page size'];

  // TODO configurable header info
  $options['max_redirects'] = 255;
  $options['headers']['User-Agent'] = 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:17.0) Gecko/20100101 Firefox/17.0';

  // build url
  if ($page_offset === NULL) {
    $url = $platform['search uri']['host'] . $platform['search uri']['path'] . "?q=" . urlencode($keyword);
  } else {
    $url = $platform['search uri']['host'] . $platform['search uri']['path']
      . "?q=" . urlencode($keyword)
      . "&n=" . $page_size
      . "&s=" . $page_offset;
  }

  // send request
  $response = drupal_http_request($url, $options);

  // process result by platform selector callback
  if ($response->code == 200) {
    if ($charset != 'utf8') {
      $html = str_get_html(iconv($charset, 'UTF-8', $response->data));
    } else {
      $html = str_get_html($response->data);
    }

    foreach ($html->find($platform['selector formula']) as $e) {
      $page_ranking ++;
      if ($matched = call_user_func_array($platform['selector callback'], array($e, $product_id))) {
        $ranking += $page_ranking;
        return $matched;
      }
    }
  } else {
    return FALSE;
  }

  $ranking += $page_size;
  // TODO configurable page limit
  if ($ranking >= $page_size && $ranking < $page_size * 10 ) {
    return tbtrack_remote_query($old_keyword, $product_id, $platform, $ranking, $ranking);
  }
  return FALSE;
}

/**
 * Implements hook_node_view().
 */
function tbtrack_node_view($node, $view_mode) {
  if ($view_mode == 'full' && $node->type == 'products') {
    $header = array(
      'keyword' => array('data' => t('Keyword'), 'field' => 'keyword'),
      'ranking' => array('data' => t('Ranking'), 'field' => 'ranking'),
      'created' => array('data' => t('Created'), 'field' => 'created', 'sort' => 'desc'),
    );

    $product = entity_metadata_wrapper('node', $node->nid);
    $platforms = tbtrack_get_platform_info();

    $node->content['ranking'] = array(
      '#prefix' => 'Ranking'
    );

    foreach ($platforms as $name => $platform) {
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

      $node->content['ranking'][$name] = array(
        '#prefix' => t('<h4>Ranking table for !platform</h4>', array('!platform' => $platform['title'])),
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
        '#empty' => t('No content available.'),
      );
    }
  }
}