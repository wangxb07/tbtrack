<?php
/**
 * @file
 * tbtrack_product.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function tbtrack_product_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'keyword';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Keyword';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '关键字';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 »';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'name',
      'rendered' => 1,
      'rendered_strip' => 1,
    ),
  );
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: 分类术语: 内容 using keywords */
  $handler->display->display_options['relationships']['reverse_field_keywords_node']['id'] = 'reverse_field_keywords_node';
  $handler->display->display_options['relationships']['reverse_field_keywords_node']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['relationships']['reverse_field_keywords_node']['field'] = 'reverse_field_keywords_node';
  $handler->display->display_options['relationships']['reverse_field_keywords_node']['required'] = TRUE;
  /* 字段: 分类术语: 名称 */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* 字段: 内容: 图片 */
  $handler->display->display_options['fields']['field_product_image']['id'] = 'field_product_image';
  $handler->display->display_options['fields']['field_product_image']['table'] = 'field_data_field_product_image';
  $handler->display->display_options['fields']['field_product_image']['field'] = 'field_product_image';
  $handler->display->display_options['fields']['field_product_image']['relationship'] = 'reverse_field_keywords_node';
  $handler->display->display_options['fields']['field_product_image']['label'] = '';
  $handler->display->display_options['fields']['field_product_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_product_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_product_image']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => 'content',
  );
  /* 字段: 内容: 标题 */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'reverse_field_keywords_node';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Contextual filter: 内容: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'reverse_field_keywords_node';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['exception']['title'] = '全部';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: 分类词汇表: 机读名称 */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'keywords' => 'keywords',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'keyword';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '关键字';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['keyword'] = array(
    t('Master'),
    t('关键字'),
    t('more'),
    t('Apply'),
    t('重置'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« 第一页'),
    t('‹ 前一页'),
    t('下一页 ›'),
    t('末页 »'),
    t('field_keywords'),
    t('全部'),
    t('Page'),
  );
  $export['keyword'] = $view;

  $view = new view();
  $view->name = 'products';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Products';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '产品';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 »';
  $handler->display->display_options['style_plugin'] = 'table';
  /* 字段: 内容: 图片 */
  $handler->display->display_options['fields']['field_product_image']['id'] = 'field_product_image';
  $handler->display->display_options['fields']['field_product_image']['table'] = 'field_data_field_product_image';
  $handler->display->display_options['fields']['field_product_image']['field'] = 'field_product_image';
  $handler->display->display_options['fields']['field_product_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_product_image']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => 'content',
  );
  /* 字段: 内容: 标题 */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* 字段: 内容: 淘宝产品ID */
  $handler->display->display_options['fields']['tbtrack_taobao_product_id']['id'] = 'tbtrack_taobao_product_id';
  $handler->display->display_options['fields']['tbtrack_taobao_product_id']['table'] = 'field_data_tbtrack_taobao_product_id';
  $handler->display->display_options['fields']['tbtrack_taobao_product_id']['field'] = 'tbtrack_taobao_product_id';
  /* 字段: 内容: 天猫产品ID */
  $handler->display->display_options['fields']['tbtrack_tmall_product_id']['id'] = 'tbtrack_tmall_product_id';
  $handler->display->display_options['fields']['tbtrack_tmall_product_id']['table'] = 'field_data_tbtrack_tmall_product_id';
  $handler->display->display_options['fields']['tbtrack_tmall_product_id']['field'] = 'tbtrack_tmall_product_id';
  /* 字段: 内容: keywords */
  $handler->display->display_options['fields']['field_keywords']['id'] = 'field_keywords';
  $handler->display->display_options['fields']['field_keywords']['table'] = 'field_data_field_keywords';
  $handler->display->display_options['fields']['field_keywords']['field'] = 'field_keywords';
  $handler->display->display_options['fields']['field_keywords']['label'] = '关键字';
  $handler->display->display_options['fields']['field_keywords']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_keywords']['delta_offset'] = '0';
  /* Sort criterion: 内容: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: 内容: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['exception']['title'] = '全部';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: 内容: 已发表 */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: 内容: 类型 */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'products' => 'products',
  );
  /* Filter criterion: 内容: 标题 */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = '产品名';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: 内容: keywords (field_keywords) */
  $handler->display->display_options['filters']['field_keywords_tid']['id'] = 'field_keywords_tid';
  $handler->display->display_options['filters']['field_keywords_tid']['table'] = 'field_data_field_keywords';
  $handler->display->display_options['filters']['field_keywords_tid']['field'] = 'field_keywords_tid';
  $handler->display->display_options['filters']['field_keywords_tid']['value'] = '';
  $handler->display->display_options['filters']['field_keywords_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_keywords_tid']['expose']['operator_id'] = 'field_keywords_tid_op';
  $handler->display->display_options['filters']['field_keywords_tid']['expose']['label'] = '关键字';
  $handler->display->display_options['filters']['field_keywords_tid']['expose']['operator'] = 'field_keywords_tid_op';
  $handler->display->display_options['filters']['field_keywords_tid']['expose']['identifier'] = 'field_keywords_tid';
  $handler->display->display_options['filters']['field_keywords_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_keywords_tid']['vocabulary'] = 'keywords';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'products';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '产品';
  $handler->display->display_options['menu']['description'] = '我的产品表格';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['products'] = array(
    t('Master'),
    t('产品'),
    t('more'),
    t('Apply'),
    t('重置'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« 第一页'),
    t('‹ 前一页'),
    t('下一页 ›'),
    t('末页 »'),
    t('图片'),
    t('标题'),
    t('淘宝产品ID'),
    t('天猫产品ID'),
    t('关键字'),
    t('全部'),
    t('产品名'),
    t('Page'),
  );
  $export['products'] = $view;

  return $export;
}
