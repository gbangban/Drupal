<?php
// $Id$

/**
 * @file
 * This is a template file, used for creation of the "Embed" box.
 */
?>
<strong><?php print flashvideo_variable_get($node_type, 'embedtext', 'Embed:') ?></strong>
<input id="embed_code" type="text" size="<?php print flashvideo_variable_get($node_type, 'embedsize', 40); ?>" value='<?php print $object; ?>' class="vidURLField" onClick="this.focus();this.select();" readonly="true">