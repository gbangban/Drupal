<?php
// $Id$

/**
 * @file
 * This is a template file, used for displaying Brightcove videos.
 */
?>
<!--[if !IE]> <-->
<object type="application/x-shockwave-flash" width="<?php print $video['width']; ?>" height="<?php print $video['height']; ?>" data="http://admin.brightcove.com/destination/player/player.swf">
<!--> <![endif]-->

<!--[if IE]>
<object type="application/x-shockwave-flash" width="<?php print $video['width']; ?>" height="<?php print $video['height']; ?>" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,40,0">
<![endif]-->

  <param name="movie" value="http://admin.brightcove.com/destination/player/player.swf" />
  <param name="quality" value="best" />
  <param name="bgcolor" value="#ffffff" />
  <param name="allowScriptAccess" value="sameDomain" />
  <param name="scale" value="noScale" />
  <param name="wmode" value="<?php print $wmode; ?>" />
  <?php if ($wmode == 'window') {
    print '<param name="allowfullscreen" value="true" />';
  } ?>
  <param name="salign" value="TL" />
  <param name="FlashVars" value="<?php if ($wmode == 'window') {
    print 'allowfullscreen=true&';
  } ?>initVideoId=<?php print $videoid; ?>&servicesURL=http://www.brightcove.com&viewerSecureGatewayURL=https://www.brightcove.com&cdnURL=http://admin.brightcove.com&autoStart=<?php print $video['autostart']; ?>" />
  <?php print $params; ?>
  <embed src="http://admin.brightcove.com/destination/player/player.swf"
    bgcolor="#FFFFFF" flashVars="<?php if ($wmode == 'window') {
      print 'allowFullScreen=true&';
    } ?>initVideoId=<?php print $videoid; ?>&servicesURL=http://www.brightcove.com&viewerSecureGatewayURL=https://www.brightcove.com&cdnURL=http://admin.brightcove.com&autoStart=<?php print $video['autostart']; ?>"
    base="http://admin.brightcove.com" name="bcPlayer" width="<?php print $video['width']; ?>" height="<?php print $video['height']; ?>" wmode="<?php print $wmode; ?>" allowScriptAccess="always" seamlesstabbing="false" type="application/x-shockwave-flash" swLiveConnect="true" pluginspage="http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash">
  </embed>
  <p><?php print t('Your browser is not able to display this multimedia content.'); ?></p>
</object>