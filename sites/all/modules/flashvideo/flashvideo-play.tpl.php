<?php
// $Id$

/**
 * @file
 * A template file that controls what code goes into the generic video player.
 */
?>
<div id="video-player" align="center">
  <?php print $video_object; ?>
  <?php if (flashvideo_variable_get($video['node_type'], 'embed', 0)) { ?>
    <br/><?php print $video_embed; ?>
  <?php } ?>
  <?php if (flashvideo_variable_get($video['node_type'], 'download', 0)) { ?>
    <p><?php print t('Problems viewing videos?'); ?><br/><?php print l($text, $url, array('absolute' => TRUE)); ?></p>
  <?php } ?>
  <?php
    if (user_access('download original')) {
      $video_text = flashvideo_variable_get($video['node_type'], 'downloadtext', '');
      $output = '';

      if (flashvideo_variable_get($video['node_type'], 'downloadfile', 0) && (!module_exists('filefield') || flashvideo_variable_get(NULL, 'flashvideo_filefield', 0) == FALSE)) {
        if ($video_text == '') {
          $output .= '<p>'. t('Download the original:') .' ';
          $output .= l(basename($video['original_video']), file_create_url($video['original_video']), array('title' => basename($video['original_video']), 'absolute' => TRUE)) .'</p>';
        }
        else {
          $output .= '<p>'. l($video_text, file_create_url($video['original_video']), array('title' => $video_text, 'absolute' => TRUE)) .'</p>';
        }
      }
      print $output;
    }
  ?>
</div>