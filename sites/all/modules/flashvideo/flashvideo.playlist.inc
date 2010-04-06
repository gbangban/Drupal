<?php

// $Id$

/**
 * @file
 * This file creates the FlashVideo playlist functionality.
 */

/**
 *  flashvideo_getplaylist - Returns an XML representation of the playlist.
 */
function flashvideo_getplaylist($fid_arg) {
  /* General Rules:
   *
   * File ID (arg(0)) - Can be given as a single file, or a sequence like "29-38-89-22", where each File ID is separated by a "-".
   *
   * If a File ID sequence is given, the playlist will play in the order of the sequence.
   *
   */

  if ($fid_arg) {
    $contents = '';                                      // To store the contents of the XML lists.
    $fid_array = array();
    $fids = array();
    if (isset($fid_arg) && !preg_match("/[^0-9\-]/", $fid_arg)) {        // If they pass only one File ID, then this means they only want to play one file
      $clean_fids = preg_replace("/[^0-9\-]/", "", $fid_arg);          // Clean the argument...
      $fids = explode("-", $clean_fids);                        // A sequence can also be given : example "23-53" plays fid 23 and fid 53 sequencially.
      array_walk($fids, create_function('&$n', '$n = trim($n);'));       // Trim all the elements
      $fid_array = $fids;
      if (is_array($fid_array)) {
        array_walk($fid_array, 'fid_format');                     // Format all the elements
      }
      else {
        $fid_array = 'f.fid='. $fid_array;
      }
    }

    // TO-DO:  Commercial manager plugs in here... future enhancments

    $flashmime = flashvideo_get_flash_query();
    $fid_query = ($fid_array) ? 'AND ('. implode(' OR ', $fid_array) .')' : '';
    $query = "SELECT n.title, n.type, f.fid, f.filename, f.filepath
		FROM {flashvideo} AS fv
		LEFT JOIN {files} AS f ON fv.fid = f.fid
		LEFT JOIN {node} AS n ON n.nid = fv.nid
		WHERE $flashmime
		AND (fv.status=3)
		%s";
    $result = db_query($query, $fid_query);

    $all_files = array();
    while ($file = db_fetch_object($result)) {                            // Walk through all the files
      $all_files[] = $file;
    }

    // We need to construct a files list based off of the order of the $fids array.
    $files = array();
    if ($fids) {
      foreach ($fids as $fid) {
        foreach ($all_files as $file) {
          if (trim($fid) == $file->fid) {
            $files[] = $file;
            continue 2;             // Continue with the $fids iteration (That's what the 2 does...)
          }
        }
      }
    }
    else {
      $files = $all_files;
    }

    if ($files) {
      $played_intro = FALSE;
      $counter = 0;
      foreach ($files as $index => $file) {
        // Play the intro video.
        $output_dir = flashvideo_variable_get($file->type, 'outputdir', '') .'/';   // The output directory
        $output_dir = ($output_dir == '/') ? '' : $output_dir;
        $intro_video = flashvideo_variable_get($file->type, 'intro', '');
        $outro_video = flashvideo_variable_get($file->type, 'outro', '');

        if (!$played_intro && ($intro_video != '')) {
            $intro_path = check_url(file_create_url($output_dir . $intro_video));
            $contents .= '<track><title>Intro</title><location>'. $intro_path .'</location><album>commercial</album></track>';
          $played_intro = TRUE;
        }

        // Give other modules a chance to override...
        if (!($filepath = module_invoke_all('flashvideo_get_file', $file, $file->type))) {
          $filepath = check_url(file_create_url($output_dir . basename($file->filepath)));
        }
        else {
          $filepath = $filepath['file'];
        }

        $contents .= "<track>\n";
        $counter++;
        $contents .= "<title>". $file->title ." Video ". $counter ." - ". $file->filename ."</title>\n";
        $contents .= "<location>". $filepath ."</location>\n";
        $contents .= "</track>\n";

        if (($index == (count($files) - 1)) && $outro_video) {
          $outro_path = check_url(file_create_url($output_dir . $outro_video));
          $contents .= "<track><title>Outro</title><location>". $outro_path ."</location><album>commercial</album></track>\n";
        }
      }
    }

    if ($contents != '') {
      header("Content-Type: application/xml");
      $xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
      $xml .= "<playlist version=\"1\" xmlns=\"http://xspf.org/ns/0/\">\n<trackList>\n"; // Start off the XML file contents
      $xml .= $contents; // Fill in all the rest.
      $xml .= "</trackList>\n</playlist>"; // Finish off the XML file contents
      echo $xml;
    }
  }
}