<?php
// $Id: flashvideo-vimeo.tpl.php,v 1.1.2.2 2009/03/07 19:06:21 attheshow Exp $

/**
 * @file
 * This is a template file, used for displaying Vimeo videos.
 */
?>
<object width="<?php print $video['width']; ?>" height="<?php print $video['height']; ?>">
  <param name="movie" value="http://vimeo.com/moogaloop.swf?clip_id=<?php print $videoid; ?>&amp;server=vimeo.com&amp;show_title=0&amp;show_byline=0&amp;show_portrait=0&amp;color=ffffff&amp;fullscreen=1" />
  <param name="allowscriptaccess" value="always" />
  <param name="wmode" value="<?php print $wmode; ?>" />
  <?php if ($wmode == 'window') {
    print '<param name="allowfullscreen" value="true" />';
  } ?>
  <embed src="http://vimeo.com/moogaloop.swf?clip_id=<?php print $videoid; ?>&amp;server=vimeo.com&amp;show_title=0&amp;show_byline=0&amp;show_portrait=0&amp;color=ffffff&amp;fullscreen=1"
    base="http://vimeo.com" width="<?php print $video['width']; ?>" height="<?php print $video['height']; ?>" allowScriptAccess="always" type="application/x-shockwave-flash"  pluginspage="http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash">
  </embed>
</object>