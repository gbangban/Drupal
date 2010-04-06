<?php
// $Id$

/**
 * @file
 * This include file implements views functionality on behalf of the
 * flashvideo.module.
 */

/**
 * A handler to provide proper displays for videos.
 */
class views_field_handler_flashvideo_nid extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();
    $options['flashvideo_field'] = array('default' => 'thumbnail');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['flashvideo_field'] = array(
      '#type' => 'select',
      '#title' => t('FlashVideo Field'),
      '#options' => array(
        'thumbnail' => 'Thumbnail',
        'video' => 'Video',
      ),
      '#default_value' => isset($this->options['flashvideo_field']) ? $this->options['flashvideo_field'] : 'thumbnail',
    );
  }

  function render($values) {
    $node = node_load($values->nid);
    switch ($this->options['flashvideo_field']) {
      case 'thumbnail':
        return flashvideo_get_thumbnail($node);
      case 'video':
        return flashvideo_get_video($node);
      default:
        return parent::render($values);
    }
  }
}