// $Id: multichoice-alternative-creation.js,v 1.1.2.2 2009/12/07 15:54:28 falcon Exp $
/**
 * @file
 * JS enabling one filter fieldset to controll filter formats for all textareas in alternatives.
 */
Drupal.behaviors.multichoiceBehavior = function(context) {
  $('.multichoice_filter:first :radio').click(function(){
	var myValue = $(this).val();
    $('.multichoice_filter:not(:first) :radio[value='+myValue+']').click();
    $('.multichoice_filter:not(:first) :radio[value='+myValue+']').change();
  });
  var defaultValue = $('.multichoice_filter:first :radio[checked=1]').val();
  $('.multichoice_filter:not(:first):not(.multichoiceBehavior-processed) :radio[value='+defaultValue+']').click().change().addClass('multichoiceBehavior-processed');
  $('.multichoice_filter:not(:first)').hide().addClass('multichoiceStayHidden');
  $('.multichoice_filter:first').insertAfter('#input-all-ph');
  var oldToggle = Drupal.toggleFieldset;
  Drupal.toggleFieldset = function(context) {
    oldToggle(context);
    $('.multichoiceStayHidden').hide();
  };
};