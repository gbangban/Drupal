<?php
// $Id: long_answer.theme.inc,v 1.1.2.4 2010/01/07 15:43:35 falcon Exp $

/**
 * @file
 * Theme functions for long_answer.
 */

/**
 * Implementation of theme_$type_feedback().
 * This is basically useless for long answer questions.
 */
function theme_long_answer_feedback($quiz, $report) {
  $output = '<div class="quiz_summary_text"><strong>' . t('Q:') . '</strong>'.
    check_markup($report->body, $report->format) .
    '<br /><em>'.
    t('The answer to this question will be scored by hand.')
    . '</em></div>';
  return $output;
}
