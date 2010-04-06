<?php
// $Id$

/**
 * @file
 * A template file that displays the thumbnail image.
 */
?>
<?php if ($link) {
  print '<a href="'. url('node/'. $nid, array('absolute' => TRUE)) .'">';
} ?>
<?php if ($url) { ?>
  <?php if ($width || $height) { ?>
    <img class="flashvideo_thumbnail" src="<?php print $url; ?>" width="<?php print $width; ?>" height="<?php print $height; ?>" alt="<?php print t('Watch this video!'); ?>" />
  <?php }
  else { ?>
    <img class="flashvideo_thumbnail" src="<?php print $url; ?>" alt="<?php print t('Watch this video!'); ?>" />
  <?php } ?>
<?php }
else { ?>
  <img class="flashvideo_thumbnail_mia" src="<?php print base_path() . drupal_get_path('module', 'flashvideo'); ?>/thumbnail_MIA.png" alt="<?php print t('Thumbnail unavailable'); ?>" />
<?php } ?>

<?php if ($link) {
  print '</a>';
}