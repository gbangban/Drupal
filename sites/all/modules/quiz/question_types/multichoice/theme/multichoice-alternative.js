// $Id: multichoice-alternative.js,v 1.1.2.1 2009/08/11 15:27:07 falcon Exp $
/**
 * @file
 * JS enabling the quiz taker to click anywhere in a table row to mark a checkbox/radio button.
 */
Drupal.behaviors.multichoiceAlternativeBehavior = function(context) {
  $('.multichoice_row')
  .filter(':has(:checkbox:checked)')
  .addClass('selected')
  .end()
  .click(function(event) {
    $(this).toggleClass('selected');
    if (event.target.type !== 'checkbox') {
      $(':checkbox', this).attr('checked', function() {
        return !this.checked;
      });
      $(':radio', this).attr('checked', true);
      if ($(':radio', this).html() != null) {
        $('.multichoice_row').removeClass('selected');
    	  $(this).addClass('selected');
      }
    }
  });
};