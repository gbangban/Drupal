<?php

// $Id$

/**
 * @file
 * The views plugin for the FlashVideo module is developed and maintained by
 *  user mikesmullin at http://drupal.org/user/108440
 *
 * This include file implements views functionality on behalf of the
 * flashvideo.module.
 */

/**
 * Implementation of hook_views_handlers().
 */
function flashvideo_views_views_handlers() {
  return array(
    'handlers' => array(
      'views_field_handler_flashvideo_nid' => array(
        'parent' => 'views_handler_field',
        'path' => drupal_get_path('module', 'flashvideo_views'),
      )
    )
  );
}

/**
 * Implementation of hook_views_data().
 *
 * Exposes all fields to the views system.
 */
function flashvideo_views_views_data() {
  $data = array();

  $data['flashvideo']['table']['group']  = t('FlashVideo');

  $data['flashvideo']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'files' => array(
      'left_field' => 'fid',
      'field' => 'fid',
    ),
  );

  $data['flashvideo']['nid'] = array(
    'title' => t('Video'),
    'help' => t('Add a flashvideo thumbnail or video as a field to this view.'),
    'field' => array(
      'handler' => 'views_field_handler_flashvideo_nid',
      'click sortable' => FALSE,
    ),
  );

  return $data;
}