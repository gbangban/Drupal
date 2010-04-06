// $Id: questions_import.js,v 1.1.2.6 2010/01/05 15:31:00 falcon Exp $

/**
 * supporting Javascript code for questions_import module
 */

$(document).ready(function() {
	
  var updateDestination = function() {
    if ($('#edit-destination-type option:selected').val() === 'existing_quiz') {
      $('#edit-destination-title-wrapper').hide();
      $('#edit-quiz-wrapper').show();
    } else {
      $('#edit-destination-title-wrapper').show();
      $('#edit-quiz-wrapper').hide();
    }
  }

  // show the appropriate inputs depending on destination type
  updateDestination();
  $('#edit-destination-type').change(updateDestination);
  
	
  // show separator field if the selected value is "native csv"
  if ($("#edit-import-type option:selected").val() === 'native_csv')
    $('#edit-field-separator-wrapper').show();
  // invoke these lines when the list selected item changes
  $('#edit-import-type').change(function() {
    // show separator field if the selected value is "native csv"
    if ($("#edit-import-type option:selected").val() === 'native_csv')
      $('#edit-field-separator-wrapper').show();
    else
      $('#edit-field-separator-wrapper').hide();
  });
});
