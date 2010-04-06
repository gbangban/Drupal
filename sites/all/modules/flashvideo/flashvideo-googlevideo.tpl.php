<?php
// $Id$

/**
 * @file
 * This is a template file, used for displaying Google videos.
 */
?>
<!--[if !IE]> <-->
<object type="application/x-shockwave-flash" width="<?php print $video['width']; ?>" height="<?php print $video['height']; ?>" data="http://video.google.com/googleplayer.swf?docId=<?php print $videoid; ?>">
<!--> <![endif]-->';

<!--[if IE]>
<object type="application/x-shockwave-flash" width="<?php print $video['width']; ?>" height="<?php print $video['height']; ?>" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,40,0">
<![endif]-->

  <param name="movie" value="http://video.google.com/googleplayer.swf?docId=<?php print $videoid; ?>" />
  <param name="quality" value="best" />
  <param name="bgcolor" value="#ffffff" />
  <param name="allowScriptAccess" value="sameDomain" />
  <param name="scale" value="noScale" />
  <param name="wmode" value="<?php print $wmode; ?>" />
  <?php if ($wmode == 'window') {
    print '<param name="allowfullscreen" value="true" />';
  } ?>
  <param name="salign" value="TL" />
  <param name="FlashVars" value="playerMode=embedded" />
  <?php print $params; ?>
  <p><?php print t('Your browser is not able to display this multimedia content.'); ?></p>
</object>