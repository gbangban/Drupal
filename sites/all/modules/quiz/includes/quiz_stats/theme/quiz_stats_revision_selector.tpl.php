<?php 
// $Id: quiz_stats_revision_selector.tpl.php,v 1.1.2.1 2009/10/29 10:03:50 falcon Exp $
print '<p>'. $content['explanation'] .'</p>';
print '<p>';
$counter = 1;
foreach ($content['links'] as $key => $value) {
  print ' | '. l(t('revision !num', array('!num' => $counter++)),$value);
}
print ' |</p>';
?>