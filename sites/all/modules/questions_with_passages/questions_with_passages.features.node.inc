<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _questions_with_passages_node_info() {
  $items = array(
    'passge_container' => array(
      'name' => t('Passage with questions'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Question'),
      'min_word_count' => '100',
      'help' => '',
    ),
  );
  return $items;
}
