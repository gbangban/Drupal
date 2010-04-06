<?php
// $Id$

/**
 * @file
 * This is a template file, used for displaying converted Flash videos.
 */
?>
<object id="flashvideo" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" width="<?php print $video['width']; ?>" height="<?php print $video['height']; ?>" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab">
  <param name="movie" value="<?php print $player; ?>" />
  <param name="FlashVars" value="<?php print $flashvars; ?>" />
  <param name="quality" value="high" />
  <param name="wmode" value="<?php print $wmode; ?>" />
  <?php if ($wmode == 'window') {
    print '<param name="allowfullscreen" value="true" />';
  } ?>
  <?php print $params; ?>
  <embed name="flashvideo" allowScriptAccess="always" src="<?php print $player; ?>"
    width="<?php print $video['width']; ?>"
    height="<?php print $video['height']; ?>"
    border="0"
    type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer"
    wmode="<?php print $wmode; ?>"
    <?php if ($wmode == 'window') {
      print 'allowfullscreen="true"';
    } ?>
    quality="high"
    flashvars="<?php print $flashvars; ?>" />
  </embed>
</object>