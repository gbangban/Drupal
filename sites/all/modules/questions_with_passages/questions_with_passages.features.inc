<?php

/**
 * Implementation of hook_node_info().
 */
function questions_with_passages_node_info() {
  module_load_include('inc', 'questions_with_passages', 'questions_with_passages.features.node');
  $args = func_get_args();
  return call_user_func_array('_questions_with_passages_node_info', $args);
}

/**
 * Implementation of hook_user_default_permissions().
 */
function questions_with_passages_user_default_permissions() {
  module_load_include('inc', 'questions_with_passages', 'questions_with_passages.defaults');
  $args = func_get_args();
  return call_user_func_array('_questions_with_passages_user_default_permissions', $args);
}
