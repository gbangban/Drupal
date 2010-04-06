<?php

/**
 * Helper to implementation of hook_user_default_permissions().
 */
function _questions_with_passages_user_default_permissions() {
  $permissions = array();

  // Exported permission: access quiz
  $permissions[] = array(
    'name' => 'access quiz',
    'roles' => array(
      '0' => 'student',
      '1' => 'teacher',
    ),
  );

  // Exported permission: view own quiz results
  $permissions[] = array(
    'name' => 'view own quiz results',
    'roles' => array(
      '0' => 'student',
      '1' => 'teacher',
    ),
  );

  // Exported permission: view results for own quiz
  $permissions[] = array(
    'name' => 'view results for own quiz',
    'roles' => array(
      '0' => 'student',
      '1' => 'teacher',
    ),
  );

  return $permissions;
}
