<?php
// $Id: nodewords_verification_tags.nodewords.hooks.inc,v 1.1.2.2 2010/03/21 13:11:24 kiam Exp $

/**
 * @file
 * Nodewords support file.
 */

/**
 * Implements hook_nodewords_tags_info().
 */
function nodewords_verification_tags_nodewords_tags_info() {
  $tags = array(
    'bing_webmaster_center' => array(
      'callback' => 'nodewords_verification_tags_bing_webmaster_center',
      'context' => array(
        'allowed' => array(
          NODEWORDS_TYPE_FRONTPAGE,
        ),
      ),
      'label' => t('Bing Webmaster Center verification code'),
      'templates' => array(
        'head' => array(
          'msvalidate.01' => NODEWORDS_META,
        ),
      ),
    ),
    'google_webmaster_tools' => array(
      'callback' => 'nodewords_verification_tags_google_webmaster_tools',
      'context' => array(
        'allowed' => array(
          NODEWORDS_TYPE_FRONTPAGE,
        ),
      ),
      'label' => t('Google Webmaster Tools verification code'),
      'templates' => array(
        'head' => array(
          'google-site-verification' => NODEWORDS_META,
        ),
      ),
    ),
    'yahoo_site_explorer' => array(
      'callback' => 'nodewords_verification_tags_yahoo_site_explorer',
      'context' => array(
        'allowed' => array(
          NODEWORDS_TYPE_FRONTPAGE,
        ),
      ),
      'label' => t('Yahoo! Site Explorer verification code'),
      'templates' => array(
        'head' => array(
          'y_key' => NODEWORDS_META,
        ),
      ),
    ),
  );

  return $tags;
}
