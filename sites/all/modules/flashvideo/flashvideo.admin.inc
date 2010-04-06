<?php

// $Id$

/**
 * @file
 * This file controls the admin form for the FlashVideo module.
 */

/**
 * Checks all of their PHP settings to make sure that their PHP directives are all set according to the recommended settings.
 */

function _flashvideo_get_php_settings() {
  $file_uploads        =  ini_get('file_uploads');      // Whether or not to allow HTTP file uploads
  $post_max_size       =  ini_get('post_max_size');      // Get their Max Post size.
  $upload_max_filesize   =  ini_get('upload_max_filesize');  // Get their Max Upload size.
  $max_execution_time    =  ini_get('max_execution_time');  // Get their Max Execution Time.
  $max_input_time      =  ini_get('max_input_time');     // This sets the maximum time in seconds a script is allowed to parse input data, like POST, GET and file uploads

  // Give them an error if they have file uploads turned off.
  if ($file_uploads != "1") {
    drupal_set_message(t('File uploads (file_uploads) are not enabled in your php.ini file. The FlashVideo module will not work unless this directive is set.'), 'error');
  }

  $output = t('<p><strong>IMPORTANT NOTE:</strong> In order for the FlashVideo module to work according to design, some parameters need to be set in your <b>php.ini</b> file or the root <b>.htaccess</b> file.  These parameters are as follows:</p>');
  $output .= '<p style="padding-left: 10px;"><ul>';
  $output .=  t('<li><em>post_max_size</em> - The maximum allowed POST size.  Must be greater than or equal to Maximum Upload Size.</li>');
  $output .=  t('<li><em>upload_max_filesize</em> - The maximum allowed file upload size.</li>');
  $output .=  t('<li><em>max_execution_time</em> - The maximum allowed time (in seconds) that a script is allowed to run.  Needed for long file conversions.</li>');
  $output .=  t('<li><em>max_input_time</em> - The maximum time (in seconds) a script is allowed to parse input data, like POST, GET and file uploads.  Needed to keep large uploads from timing out.</li>');
  $output .= '</ul></p>';
  $output .= t('<p>The following shows the recommended values for these parameters followed by your current settings.</p>');
  $output .= '<table>';
  $output .=   '<tr>';
  $output .=     t('<th>Recommended Settings:</th>');
  $output .=     t('<th>Your Current Settings:</th>');
  $output .=   '</tr>';
  $output .=   '<tr>';
  $output .=     '<td><ul>';
  $output .=       t('<li><em>post_max_size=100M</em></li>');
  $output .=       t('<li><em>upload_max_filesize=100M</em></li>');
  $output .=       t('<li><em>max_execution_time=1000</em></li>');
  $output .=       t('<li><em>max_input_time=1000</em></li>');
  $output .=     '</ul></td>';
  $output .=     '<td><ul>';
  $output .=       t('<li><em>post_max_size=!post_max_size</em></li>', array('!post_max_size' => $post_max_size));
  $output .=       t('<li><em>upload_max_filesize=!upload_max_filesize</em></li>', array('!upload_max_filesize' => $upload_max_filesize));
  $output .=       t('<li><em>max_execution_time=!max_execution_time</em></li>', array('!max_execution_time' => $max_execution_time));
  $output .=       t('<li><em>max_input_time=!max_input_time</em></li>', array('!max_input_time' => $max_input_time));
  $output .=     '</ul></td>';
  $output .=   '</tr>';
  $output .= '</table>';
  $output .= t('<p><strong>Warning: Please consult your hosting provider or a professional before making the recommended changes. Maintainers of the FlashVideo module will not be held responsible for any malfunctions due to this change. Change these PHP settings at your own risk!</strong></p>');

  return $output;
}

/**
 * The main settings page : Administer >> FlashVideo Settings.
 *
 * @return A drupal form showing a list of all node types for the FlashVideo Module.
 *
 */
function flashvideo_settings() {

  //Must have "administer site configuration" and "administer flashvideo" privilages.
  if (!user_access('administer flashvideo') || !user_access('administer site configuration')) {
    drupal_access_denied();
  }

  // We need to change the max upload size, and also add the extensions to the file uploads.
  $size = variable_get('upload_uploadsize_default', 1);
  $user_size = variable_get('upload_usersize_default', 1);

  if ($size == 1)
    variable_set('upload_uploadsize_default', 100);

  if ($user_size == 1)
    variable_set('upload_usersize_default', 1000);

  /**
   *   Add any new extensions to the upload allowed extensions.
   */

  $extensions = variable_get('upload_extensions_default', 'jpg jpeg gif png txt html doc xls pdf ppt pps');
  $filetypes = flashvideo_get_allowed_filetypes();
  foreach ($filetypes as $ext => $filetype) {
    if ($filetypes[$ext]['mimetype'] && strpos($extensions, $ext) === FALSE)
      $extensions .= ' '. $ext;
  }
  variable_set('upload_extensions_default', $extensions);

  $header = array(t('Content Type'), t('Status'), t('Operations'));

  // Create a list of all node types.
  $types = node_get_types();

  // Global settings don't work with FileField integration
  if (!module_exists('filefield') || flashvideo_variable_get(NULL, 'flashvideo_filefield', 0) == FALSE) {
    $status = flashvideo_variable_get(NULL, 'flashvideo_global_enable', 0) ? '(Enabled)' : '(Disabled)';
    $rows[] = array("Global Settings", $status, l(t('Global FlashVideo Settings (For all node types).'), "admin/settings/flashvideo/edit/global"));
  }

  foreach ($types as $type) {
    $status = flashvideo_variable_get($type->type, 'enable', 0) ? '(Enabled)' : '(Disabled)';
    $rows[] = array($type->name, $status, l(t('Edit settings for this content type.'), "admin/settings/flashvideo/edit/$type->type"));
  }

  $output = _flashvideo_get_php_settings();

  // Global settings don't work with FileField integration
  if (module_exists('filefield') && flashvideo_variable_get(NULL, 'flashvideo_filefield', 0)) {
    $output .= t('<p><strong>Content Type Settings</strong> - Use the links below to enable FlashVideo functionality for each of the specific content types you\'ve defined in your Drupal site. Also note that some variables are not specific to a particular content type (such as the FFMPEG binary path). For these variables, you will find them in the !link.</p>', array('!link' => l(t('Universal Settings'), 'admin/settings/flashvideo/universal')));
  }
  else {
    $output .= t('<p><strong>Global FlashVideo Settings</strong> - The global settings allow you to make changes to all node types by using one configuration.  Please note, however, that if any content type-specific parameters are specified, they will override the Global Settings for that node type.  Also note that some variables are not specific to a particular content type (such as the FFMPEG binary path). For these variables, you will find them in the !link.</p>', array('!link' => l(t('Universal Settings'), 'admin/settings/flashvideo/universal')));
  }
  $output .= theme('table', $header, $rows);
  return $output;
}

/**
 * The main settings page called when a node type is selected in the Administer >> FlashVideo Settings.
 *
 * @return A drupal form for the correct node type.
 *
 */
function flashvideo_settings_main() {
  //Must have "administer site configuration" and "administer flashvideo" privilages.
  if (!user_access('administer flashvideo') || !user_access('administer site configuration')) {
    drupal_access_denied();
  }

  $args = func_get_args();
  $node_type = $args[0];

  if ($node_type) {
    return drupal_get_form('flashvideo_settings_form', $node_type);
  }
}

/**
 * The FlashVideo Settings form.
 *
 * @param $node_type
 *  The node type for given settings form.
 *
 * @return A completed form array.
 *
 */
function flashvideo_settings_form() {

  $args = func_get_args();
  $node_type = $args[1];

  $form['flashvideo_'. $node_type .'_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable the FlashVideo for all nodes of this type: <strong>@node_type</strong>', array('@node_type' => $node_type)),
    '#default_value' => flashvideo_variable_get($node_type, 'enable', 0),
    '#description' => t("Enable the FlashVideo for this Node Type.")
  );

  if (module_exists('filefield') && flashvideo_variable_get(NULL, 'flashvideo_filefield', 0)) {
    $form['flashvideo_'. $node_type .'_cck_original_video_field'] = array(
      '#type' => 'select',
      '#title' => t('Use FlashVideo to convert files from this CCK file field'),
      '#description' => t('The file field that your users use to upload their video file.<br /><strong>Note:</strong> You must create this file field yourself on your @node_type content type. You\'ll then be able to select it from this list.', array('@node_type' => $node_type)),
      '#options' => _flashvideo_get_cck_fields($node_type),
      '#default_value' => flashvideo_variable_get($node_type, 'cck_original_video_field', 0),
    );
    $form['flashvideo_'. $node_type .'_cck_finished_video_field'] = array(
      '#type' => 'select',
      '#title' => t('Save the finished video to this CCK file field'),
      '#description' => t('The field where the converted video will be placed.<br /><strong>Note:</strong> You must create this file field yourself on your @node_type content type. You\'ll then be able to select it from this list.<br /><strong>Note:</strong> Because this field is meant to be filled in by the FlashVideo module, this field will no longer be visible on the node creation form.', array('@node_type' => $node_type)),
      '#options' => _flashvideo_get_cck_fields($node_type),
      '#default_value' => flashvideo_variable_get($node_type, 'cck_finished_video_field', 0),
    );
    $form['flashvideo_'. $node_type .'_cck_finished_thumbnail_field'] = array(
      '#type' => 'select',
      '#title' => t('Save the finished thumbnail image to this CCK file field'),
      '#description' => t('The field where the generated thumbnail image will be placed.<br /><strong>Note:</strong> You must create this file field yourself on your @node_type content type. You\'ll then be able to select it from this list.<br /><strong>Note:</strong> Because this field is meant to be filled in by the FlashVideo module, this field will no longer be visible on the node creation form.', array('@node_type' => $node_type)),
      '#options' => _flashvideo_get_cck_fields($node_type),
      '#default_value' => flashvideo_variable_get($node_type, 'cck_finished_thumbnail_field', 0),
    );
  }
  else { // Since they don't have FileField, they'll need to use core Upload module.
    $form['flashvideo_'. $node_type .'_require'] = array(
      '#type' => 'checkbox',
      '#title' => t('Require the FlashVideo for this node type.'),
      '#default_value' => flashvideo_variable_get($node_type, 'require', 0),
      '#description' => t('If checked, the video will be required to submit this node type.')
    );
  }

  $form['flashvideo_'. $node_type .'_disabletag'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable the [video] tag.'),
    '#default_value' => flashvideo_variable_get($node_type, 'disabletag', 0),
    '#description' => t('This is used to create a more secure method for users to not be able to place their own [video] tags.  You should use <strong>print flashvideo_get_video($node);</strong> in your template to replace it.')
  );

  $form['flashvideo_'. $node_type .'_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Change Node Status after Conversion.'),
    '#default_value' => flashvideo_variable_get($node_type, 'status', 1),
    '#description' => t('If checked, the status for the node containing the video will be changed to "Published" after a successful video conversion.')
  );

  $form['flashvideo_'. $node_type .'_convert'] = array(
    '#type' => 'checkbox',
    '#title' => t('Convert videos immediately.'),
    '#default_value' => flashvideo_variable_get($node_type, 'convert', 0),
    '#description' => t('If checked, an attempt will be made to convert videos to Flashvideo (*.flv) files immediately after adding or editing a node, without having to wait for cron.')
  );

  $form['flashvideo_'. $node_type .'_import'] = array(
    '#type' => 'textfield',
    '#title' => t('Video Import Directory.'),
    '#default_value' => flashvideo_variable_get($node_type, 'import', ($node_type .'_import')),
    '#description' => t('The Video Import Directory is a directory located within your <strong>files</strong> directory dedicated specifically for video importing. The FlashVideo module will then scan all files within this directory and automatically add all video files to your drupal site, convert them, and move them to your output directory.')
  );

  if (!module_exists('filefield') || flashvideo_variable_get(NULL, 'flashvideo_filefield', 0) == FALSE) {
    // Field title and weight are usually determined by CCK.
    // These fields will only display if the users is using the core Upload module.
    $form['flashvideo_'. $node_type .'_title'] = array(
      '#title' => t('FlashVideo Upload Title'),
      '#type' => 'textfield',
      '#default_value' => flashvideo_variable_get($node_type, 'title', t('Video Upload')),
      '#maxlength' =>  128,
      '#description' => t('The title for the Video Upload for this node.')
    );
    $form['flashvideo_'. $node_type .'_weight'] = array(
      '#title' => t('FlashVideo Upload Weight'),
      '#type' => 'textfield',
      '#default_value' => flashvideo_variable_get($node_type, 'weight', -10),
      '#maxlength' =>  10,
      '#description' => t('Determines how high in the submit form you would like to have the video upload. The lower the value, the higher the placement.')
    );
  }

  $form['flashvideo_'. $node_type .'_mode'] = array(
    '#title' => t('Window Mode'),
    '#type' => 'select',
    '#options' => array('none' => 'none', 'transparent' => 'transparent', 'window' => 'window'),
    '#default_value' => flashvideo_variable_get($node_type, 'mode', 'window'),
    '#description' => t('Selects which window mode you would like for your player to operate under (denoted by the <b>wmode</b> parameter in the object code)
      <ul>
        <li><b>none</b> - <em>No window mode</em></li>
        <li><b>wmode=transparent</b> - <em>Allows for other elements to drop in front of the video (like a drop-down list), without the video showing over those elements.</em></li>
        <li><b>wmode=window</b> - <em>Allows for the video to have full-screen support.</em></li>
      </ul>')
  );

  $form['flashvideo_'. $node_type .'_embed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show an Embed Video Textbox'),
    '#default_value' => flashvideo_variable_get($node_type, 'embed', 0),
    '#description' => t('Adds an Embed video textbox to allow people to embed this video in their sites.')
  );

  $form['flashvideo_'. $node_type .'_embedtext'] = array(
    '#title' => t('Embed Text'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get($node_type, 'embedtext', 'Embed:'),
    '#maxlength' =>  128,
    '#description' => t('The text to show for the embed text box.')
  );

  $form['flashvideo_'. $node_type .'_embedsize'] = array(
    '#title' => t('Embed Text Box Size'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get($node_type, 'embedsize', 40),
    '#maxlength' =>  10,
    '#description' => t('The size of the embed text box.')
  );

  $form['flashvideo_'. $node_type .'_download'] = array(
    '#type' => 'checkbox',
    '#title' => t('Attach Video Player Download Link'),
    '#default_value' => flashvideo_variable_get($node_type, 'download', 0),
    '#description' => t('Add a link to download the player at the bottom of the video object.')
  );

  if (!module_exists('filefield') || flashvideo_variable_get(NULL, 'flashvideo_filefield', 0) == FALSE) {
    // FileField already provides interface for how to display uploaded files.
    // These fields will only display if the users is using the core Upload module.
    $form['flashvideo_'. $node_type .'_downloadfile'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add an original video download Link'),
      '#default_value' => flashvideo_variable_get($node_type, 'downloadfile', 0),
      '#description' => t('Add a link to download the original video at the bottom of the player.')
    );
    $form['flashvideo_'. $node_type .'_downloadtext'] = array(
      '#title' => t('Download Text'),
      '#type' => 'textfield',
      '#default_value' => flashvideo_variable_get($node_type, 'downloadtext', ''),
      '#maxlength' =>  255,
      '#description' => t('The text that is displayed to the user to download the video. <strong>Leave empty if you wish to just show the filename.</strong>')
    );
    $form['flashvideo_'. $node_type .'_attachment'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show Videos as Attachments'),
      '#default_value' => flashvideo_variable_get($node_type, 'attachment', 0),
      '#description' => t('Checking this box will show all videos in the attachments section of this node type.')
    );
  }

  $form['performance'] = array(
    '#type' => 'fieldset',
    '#title' => t('Performance'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );

  $form['performance']['flashvideo_'. $node_type .'_searchthumb'] = array(
    '#type' => 'checkbox',
    '#title' => t('Search for thumbnails in the Node Body.'),
    '#default_value' => flashvideo_variable_get($node_type, 'searchthumb', 0),
    '#description' => t('Checking this box will allow you to have video thumbnails in the Node body, at a performance cost.')
  );

  $form['performance']['flashvideo_'. $node_type .'_searchvideo'] = array(
    '#type' => 'checkbox',
    '#title' => t('Search for videos in the Node Teaser.'),
    '#default_value' => flashvideo_variable_get($node_type, 'searchvideo', 0),
    '#description' => t('Checking this box will allow you to have video objects in the Node Teasers, at a slight performance cost.')
  );

  $form['player'] = array(
    '#type' => 'fieldset',
    '#title' => t('Flash Player Settings'),
    '#description' => t('Settings for the Flash Player'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );

  $form['player']['flashvideo_'. $node_type .'_player'] = array(
    '#title' => t('Flash Player Name'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get($node_type, 'player', 'Player.swf'),
    '#maxlength' =>  128,
    '#description' => t('The name of the Flash Player.  Note: This player MUST reside in the main "files" directory to work.'),
    '#required' => TRUE
  );

  $form['player']['flashvideo_'. $node_type .'_flashvars'] = array(
    '#title' => t('Custom FlashVars (do not change for default functionality)'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get($node_type, 'flashvars', 'file=@video'),
    '#maxlength' =>  1024,
    '#description' => t('This text field will allow for custom FlashVars to be passed to your Flash Player.  In your FlashVars, you can use the following placeholders to represent certain variables which the FlashVideo module will then replace with the actual value.
      <ul>
        <li><b>@video</b> - <em>String</em> - Placeholder for the path of the video to play.</li>
        <li><b>@thumbnail</b> - <em>String</em> - Placeholder for the path of the thumbnail of the video.</li>
      </ul>Example: <strong>file=@video&amp;image=@thumbnail</strong> will play the video using its thumbnail as the intro image.'),
    '#required' => FALSE
  );

  $form['player']['flashvideo_'. $node_type .'_logo'] = array(
    '#title' => t('Flash Player Logo'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get($node_type, 'logo', ''),
    '#maxlength' =>  128,
    '#description' => t('The name of the logo file to place as a watermark in the bottom right of the Flash Player.  Example: <b>logo.png</b>  Note:  This logo MUST reside in the same directory as the player.'),
    '#required' => FALSE
  );

  $form['player']['flashvideo_'. $node_type .'_logolink'] = array(
    '#title' => t('Watermark (Logo) Link'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get($node_type, 'logolink', ''),
    '#maxlength' =>  128,
    '#description' => t('The URL in which you would like your watermark (logo) to link too.'),
    '#required' => FALSE
  );

  $form['player']['flashvideo_'. $node_type .'_intro'] = array(
    '#title' => t('Flash Player Intro Video'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get($node_type, 'intro', ''),
    '#maxlength' =>  128,
    '#description' => t('The name of an intro video file to play at the beginning of all video files.  Example: <b>intro.flv</b>  Note:  This logo MUST be a *.flv file and MUST reside in the same directory as the player.'),
    '#required' => FALSE
  );

  $form['player']['flashvideo_'. $node_type .'_outro'] = array(
    '#title' => t('Flash Player Outro Video'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get($node_type, 'outro', ''),
    '#maxlength' =>  128,
    '#description' => t('The name of an outro video file to play at the end of all video files.  Example: <b>outro.flv</b>  Note:  This logo MUST be a *.flv file and MUST reside in the same directory as the player.'),
    '#required' => FALSE
  );

  $form['player']['flashvideo_'. $node_type .'_introimg'] = array(
    '#title' => t('Flash Player Intro Image'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get($node_type, 'introimg', ''),
    '#maxlength' =>  128,
    '#description' => t('If your intro does not need to be a video, you can just specify an intro image here.  This dramatically saves on bandwidth.  Example: <b>intro.png</b> Note: This logo MUST reside in the same directory as the player.'),
    '#required' => FALSE
  );

  $form['player']['flashvideo_'. $node_type .'_introthumb'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Thumbnail as Intro Image.'),
    '#default_value' => flashvideo_variable_get($node_type, 'introthumb', 1),
    '#description' => t('Check this checkbox if you would like to use the generated thumbnail as the intro image.')
  );

  $form['player']['flashvideo_'. $node_type .'_introtime'] = array(
    '#title' => t('Intro Image Time'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get($node_type, 'introtime', '3'),
    '#maxlength' =>  128,
    '#description' => t('The amount of time to show the intro image in seconds.'),
    '#required' => FALSE
  );

  $form['player']['flashvideo_'. $node_type .'_autostart'] = array(
    '#title' => t('Default AutoStart'),
    '#type' => 'select',
    '#options' => array('true' => 'true', 'false' => 'false'),
    '#default_value' => flashvideo_variable_get($node_type, 'autostart', 'true'),
    '#maxlength' =>  128,
    '#description' => t('If the player should default to play automatically or not.'),
    '#required' => TRUE
  );

  $form['player']['flashvideo_'. $node_type .'_repeattype'] = array(
    '#title' => t('Repeat Type'),
    '#type' => 'select',
    '#options' => array('true' => 'true', 'false' => 'false', 'list' => 'list'),
    '#default_value' => flashvideo_variable_get($node_type, 'repeattype', 'false'),
    '#description' => t('This will set the type of repeat setting for your video (or playlist), they are as follows:
      <ul>
        <li><b>true</b> - <em>Continously playback your movie/playlist</em></li>
        <li><b>false</b> - <em>The player will stop playback after every item to preserve bandwidth.</em></li>
        <li><b>list</b> - <em>Will playback all items in a playlist once.</em></li>
      </ul>')
  );

  $form['ffmpeg'] = array(
    '#type' => 'fieldset',
    '#title' => t('FFMPEG settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );

  $form['ffmpeg']['flashvideo_'. $node_type .'_cmd'] = array(
    '#title' => t('ffmpeg Command'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get($node_type, 'cmd', '-i @input -f flv -acodec mp3 -ar 22050 -ab 64k -ac 1 @output'),
    '#maxlength' =>  512,
    '#description' => t('This is the command to give to the ffmpeg executable. Refer to the <a href="http://ffmpeg.mplayerhq.hu/ffmpeg-doc.html">FFMPEG Online Documentation</a> for more information.<br/>The following parameters can be used:
      <ul>
        <li><b>@input</b> - <em>The input file will replace this tag.</em></li>
        <li><b>@output</b> - <em>The output file will replace this tag.</em></li>
      </ul>'),
    '#required' => TRUE
  );

  $form['ffmpeg']['flashvideo_'. $node_type .'_thumbcmd'] = array(
    '#title' => t('ffmpeg Thumbnail Command'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get($node_type, 'thumbcmd', '-y -i @input -vframes 1 -ss @thumbtime -an -vcodec mjpeg -f rawvideo -s "@thumbsize" @output'),
    '#maxlength' =>  256,
    '#description' => t('This is the command to give to the ffmpeg executable. Refer to the <a href="http://ffmpeg.mplayerhq.hu/ffmpeg-doc.html">FFMPEG Online Documentation</a> for more information.<br/>The following parameters can be used:
      <ul>
        <li><b>@input</b> - <em>The input file will replace this tag.</em></li>
        <li><b>@output</b> - <em>The output file will replace this tag.</em></li>
        <li><b>@thumbtime</b> - <em>The time to wait before taking a snapshot.</em></li>
        <li><b>@thumbsize</b> - <em>The string representation of the size of the thumbnail such as "130x100"</em></li>
      </ul>'),
    '#required' => TRUE
  );

  $form['ffmpeg']['flashvideo_'. $node_type .'_delete'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete Original Video.'),
    '#default_value' => flashvideo_variable_get($node_type, 'delete', 0),
    '#description' => t('Checking this checkbox will delete the original video after conversion. <strong>Warning: The FlashVideo CCK plugin will not work with this enabled!</strong>')
  );

  if (!module_exists('filefield') || flashvideo_variable_get(NULL, 'flashvideo_filefield', 0) == FALSE) {
    // FileField already provides interface for choosing a filepath for uploaded files.
    // These fields will only display if the users is using the core Upload module.
    $form['ffmpeg']['flashvideo_'. $node_type .'_userootpath'] = array(
      '#type' => 'checkbox',
      '#title' => t('Output Directories reference from Drupal Root.'),
      '#default_value' => flashvideo_variable_get($node_type, 'userootpath', 0),
      '#description' => t('Checking this checkbox will force all the output directories to be referenced from the root of the Drupal path instead of the files directory.')
    );
    $form['ffmpeg']['flashvideo_'. $node_type .'_originaldir'] = array(
      '#title' => t('Original Directory'),
      '#type' => 'textfield',
      '#default_value' => flashvideo_variable_get($node_type, 'originaldir', ''),
      '#maxlength' =>  128,
      '#description' => t('The directory to contain the original video after conversion.'),
      '#required' => FALSE
    );
    $form['ffmpeg']['flashvideo_'. $node_type .'_outputdir'] = array(
      '#title' => t('Output Directory'),
      '#type' => 'textfield',
      '#default_value' => flashvideo_variable_get($node_type, 'outputdir', ''),
      '#maxlength' =>  128,
      '#description' => t('The output directory to contain the thumbnail and converted video.'),
      '#required' => FALSE
    );
  }

  $form['ffmpeg']['flashvideo_'. $node_type .'_size'] = array(
    '#title' => t('Video Default Size'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get($node_type, 'size', '450x337'),
    '#maxlength' =>  10,
    '#description' => t('The default size of the video, if none is given in the [video] tag.  Width x Height.  Example "450x337"'),
    '#required' => TRUE
  );

  $form['ffmpeg']['flashvideo_'. $node_type .'_maxsize'] = array(
    '#title' => t('Video Maximum Dimensions'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get($node_type, 'maxsize', ''),
    '#maxlength' =>  10,
    '#description' => t('The maximum dimensions that you want the finished video to be. If the dimensions of the uploaded file are larger, the video will be resized during conversion. Aspect ratio will be preserved.<br />Width x Height. Example: "450x350"<br /><strong>Warning</strong>: If you enter maximum dimensions here, be sure that you have NOT added a size (-s) parameter to your "ffmpeg Command" above.')
  );

  $form['ffmpeg']['flashvideo_'. $node_type .'_thumbsize'] = array(
    '#title' => t('Thumbnail Size'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get($node_type, 'thumbsize', '130x100'),
    '#maxlength' =>  10,
    '#description' => t('The size of the thumnail. Width x Height. Example "130x100"'),
    '#required' => TRUE
  );

  $form['ffmpeg']['flashvideo_'. $node_type .'_thumbtime'] = array(
    '#title' => t('Thumbnail Time'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get($node_type, 'thumbtime', '00:00:02'),
    '#maxlength' =>  10,
    '#description' => t('The amount of time to move from the beginning of the video before taking a snapshot.  Example "00:00:02" is 2 seconds.'),
    '#required' => TRUE
  );

  $form['ffmpeg']['flashvideo_'. $node_type .'_thumblink'] = array(
    '#title' => t('Make Thumbnails a Link?'),
    '#type' => 'select',
    '#options' => array('yes' => 'yes', 'no' => 'no'),
    '#default_value' => flashvideo_variable_get($node_type, 'thumblink', 'yes'),
    '#maxlength' =>  128,
    '#description' => t('If yes, the thumbnails will be a link to the node that has the video.'),
    '#required' => TRUE
  );

  return _system_settings_form($form);
}

/**
 * All settings for FlashVideo which aren't specific to content types.
 */
function flashvideo_universal_settings_form() {
  if (module_exists('filefield')) {
    $form['preferences'] = array(
      '#type' => 'fieldset',
      '#title' => t('Preferences'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['preferences']['flashvideo_filefield'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use the CCK FileField module for uploads.'),
      '#default_value' => flashvideo_variable_get(NULL, 'flashvideo_filefield', 0),
      '#description' => t('By default, the FlashVideo module is configured to use the Drupal core "Upload" module for video uploads. If you would rather use FileField, check this box.'),
      '#element_validate' => array('flashvideo_universal_settings_filefield_validate'),
    );
  }
  $form['types'] = array(
    '#type' => 'fieldset',
    '#title' => t('Types'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['types']['flashvideo_video_filetypes'] = array(
    '#title' => t('<em>[FileType, MIMEType, DefaultPlayer]</em> configuration'),
    '#type' => 'textarea',
    '#rows' => 5,
    '#default_value' => flashvideo_variable_get(NULL, 'flashvideo_video_filetypes', FLASHVIDEO_FILETYPE_STRING),
    '#maxlength' =>  1024,
    '#description' => t('This section governs which video types (usually the extension) can be used by this module as well as the MIME type, and default player for each.  Use the format <strong>[FileType, MIMEType, Player]</strong> to add new ones.  If the file type does not have a valid MIME type, then just use <strong>0</strong>.  Also, the default player is referenced as the text after <strong>theme_flashvideo_play_</strong>, so if you wish to add a new player to flashvideo_objects.inc, you should not need to touch the flashvideo.module file.<br /><strong>Note:</strong> Please use only one configuration per line.'),
  );
  $form['types']['flashvideo_mimetypes'] = array(
    '#title' => t('Flash MIME Types'),
    '#type' => 'textarea',
    '#rows' => 5,
    '#default_value' => flashvideo_variable_get(NULL, 'flashvideo_mimetypes', FLASHVIDEO_MIMETYPE_STRING),
    '#maxlength' =>  1024,
    '#description' => t('The MIME types that will be considered a Flash Video.<br /><strong>Note:</strong> Please use only one MIME type per line.'),
  );
  $form['ffmpeg'] = array(
    '#type' => 'fieldset',
    '#title' => t('FFMPEG settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['ffmpeg']['flashvideo_ffmpegphp'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use FFMPEG-PHP to extract video information.'),
    '#default_value' => flashvideo_variable_get(NULL, 'flashvideo_ffmpegphp', 0),
    '#description' => t('Checking this box will extract the uploaded video information, but is not essential to making this module work.'),
  );
  $form['ffmpeg']['flashvideo_binpath'] = array(
    '#title' => t('ffmpeg Path'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get(NULL, 'flashvideo_binpath', '/usr/bin/ffmpeg'),
    '#maxlength' =>  128,
    '#description' => t('The path to the ffmpeg binary.'),
    '#required' => TRUE,
  );
  $form['ffmpeg']['flashvideo_binpath_metadata'] = array(
    '#title' => t('flvtool2 Path'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get(NULL, 'flashvideo_binpath_metadata', ''),
    '#maxlength' =>  128,
    '#description' => t('The path to the flvtool2 binary (adds metadata). Might be installed at /usr/bin/flvtool2.'),
  );
  $form['ffmpeg']['flashvideo_maxconvert'] = array(
    '#title' => t('Maximum Conversions per Cron'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get(NULL, 'flashvideo_maxconvert', 10),
    '#maxlength' =>  10,
    '#description' => t('The maximum amount of conversions allowed for each cron cycle.'),
    '#required' => TRUE,
  );
  $form['ffmpeg']['flashvideo_maxfail'] = array(
    '#title' => t('Maximum Failures'),
    '#type' => 'textfield',
    '#default_value' => flashvideo_variable_get(NULL, 'flashvideo_maxfail', 5),
    '#maxlength' =>  10,
    '#description' => t('The maximum amount of conversion failures, before it reverts to using standard (non-Flash) video display.'),
    '#required' => TRUE,
  );
  $form['ffmpeg']['flashvideo_logdata'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log Conversion Data.'),
    '#default_value' => flashvideo_variable_get(NULL, 'flashvideo_logdata', 0),
    '#description' => t('Logs all conversion information in the <b>ffmpeg_data</b> table. This can be helpful for debugging.'),
  );
  return _system_settings_form($form);
}

/**
 * Validation function. Makes certain that "global settings" are disabled when FileField integration is enabled.
 */
function flashvideo_universal_settings_filefield_validate($element, $form_state) {
  if ($form_state['values']['flashvideo_filefield'] == TRUE && flashvideo_variable_get(NULL, 'flashvideo_global_enable', 0)) {
    $name = '%flashvideo_global%';
    db_query("DELETE FROM {variable} WHERE name LIKE '%s'", $name);
    cache_clear_all('variables', 'cache');
  }
}

function _system_settings_form($form) {
  // Custom version of D6 function. D6 version doesn't give weight to buttons.
  // Giving weight to the buttons allows plugin modules to do form_alter just prior to the buttons.
  $form['buttons'] = array(
    '#weight' => 5,
  );
  $form['buttons']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration') );
  $form['buttons']['reset'] = array('#type' => 'submit', '#value' => t('Reset to defaults') );

  if (!empty($_POST) && form_get_errors()) {
    drupal_set_message(t('The settings have not been saved because of the errors.'), 'error');
  }
  $form['#submit'][] = 'system_settings_form_submit';
  $form['#theme'] = 'system_settings_form';
  return $form;
}