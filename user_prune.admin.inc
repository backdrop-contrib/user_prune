<?php

// $Id$

/**
 * Admin page for User Prune.
 */
function user_prune_admin() {
	$output = '<p>' . t("Use this form to set up a cron job for the pruning of users. The specifications you make here will be executed on every cron run. You can also choose to prune the users immediately.") . '</p><p>' . t("The limiting criteria will not be set unless a value has been entered in the text field.");
	$output .= drupal_get_form('user_prune_admin_form');
	
	return $output;
}

/**
 * Form definition for the admin page.
 */
function user_prune_admin_form() {
	$form = array();
	
	$form['never_logged_in'] = array(
		'#type' => 'fieldset',
		'#title' => t('Users who have never logged in')
	);
	$form['never_logged_in']['prune_never'] = array(
		'#type' => 'checkbox',
		'#title' => t('Prune users who have never logged in.'),
		'#default_value' => variable_get('prune_never', 0)
	);
	$form['never_logged_in']['prune_never_registered_limit_message'] = array(
		'#type' => 'item',
		'#title' => t('Limit to users who have been registered for more than'),
	);
	$form['never_logged_in']['prune_never_registered_limit_length'] = array(
		'#type' => 'textfield',
		'#size' => 1,
		'#default_value' => variable_get('prune_never_registered_limit_length', '')
	);
	$form['never_logged_in']['prune_never_registered_limit_unit'] = array(
		'#type' => 'select',
		'#options' => array(31556926 => t('Years'), 2629744 => t('Months'), 604800 => t('Weeks'), 86400 => t('Days'), 3600 => t('Hours')),
		'#default_value' => variable_get('prune_never_registered_limit_unit', 2629744)
	);
	
	$form['has_logged_in'] = array(
		'#type' => 'fieldset',
		'#title' => t('Users who have logged in before')
	);
	$form['has_logged_in']['prune_logged_in'] = array(
		'#type' => 'checkbox',
		'#title' => t('Prune users who have logged in before'),
		'#default_value' => variable_get('prune_logged_in', 0)
	);
	$form['has_logged_in']['prune_logged_in_logged_in_limit_message'] = array(
		'#type' => 'item',
		'#title' => t("Limit to users who haven't logged in for"),
	);
	$form['has_logged_in']['prune_logged_in_logged_in_limit_length'] = array(
		'#type' => 'textfield',
		'#size' => 1,
		'#default_value' => variable_get('prune_logged_in_logged_in_limit_length', '')
	);
	$form['has_logged_in']['prune_logged_in_logged_in_limit_unit'] = array(
		'#type' => 'select',
		'#options' => array(31556926 => t('Years'), 2629744 => t('Months'), 604800 => t('Weeks'), 86400 => t('Days'), 3600 => t('Hours')),
		'#default_value' => variable_get('prune_logged_in_logged_in_limit_unit', 2629744)
	);
	$form['has_logged_in']['prune_logged_in_registered_limit_message'] = array(
		'#type' => 'item',
		'#title' => t('Limit to users who have been registered for more than'),
	);
	$form['has_logged_in']['prune_logged_in_registered_limit_length'] = array(
		'#type' => 'textfield',
		'#size' => 1,
		'#default_value' => variable_get('prune_logged_in_registered_limit_length', '')
	);
	$form['has_logged_in']['prune_logged_in_registered_limit_unit'] = array(
		'#type' => 'select',
		'#options' => array(31556926 => t('Years'), 2629744 => t('Months'), 604800 => t('Weeks'), 86400 => t('Days'), 3600 => t('Hours')),
		'#default_value' => variable_get('prune_logged_in_registered_limit_unit', 2629744)
	);
	
	$form['prune_now'] = array(
		'#type' => 'fieldset',
		'#title' => t('Prune Now'),
		'#description' => t('You can use the criteria set above to prune users immediately. Any changes you made to the form will not be saved.'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE
	);
	$form['prune_now']['go'] = array(
		'#type' => 'submit',
		'#value' => t('Prune Now')
	);
	
	$form['prune_per_run'] = array(
		'#type' => 'select',
		'#title' => t('How many users to delete per run?'),
		'#description' => t('Deleting too many users at a time can cause your request to time out. Set this number to something your server can handle.'),
		'#options' => array(100 => 100, 75 => 75, 50 => 50, 25 => 25, 10 => 10),
		'#default_value' => variable_get('prune_per_run', 50)
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save Configuration')
	);
	
	return $form;
}

/**
 * Validate callback for the admin page.
 */
function user_prune_admin_form_validate($form, &$form_state) {
	// shortcut
	$values = $form_state['values'];
	
	// check if the text fields are numeric
	$limit_lengths = array('prune_never_registered_limit_length' => $values['prune_never_registered_limit_length'], 'prune_logged_in_logged_in_limit_length' => $values['prune_logged_in_logged_in_limit_length'], 'prune_logged_in_registered_limit_length' => $values['prune_logged_in_registered_limit_length']);
	
	foreach ($limit_lengths as $key => $limit_length) {
		if ($limit_length) {
			if (!is_numeric($limit_length)) {
				form_set_error($key, t('The value must be numeric.'));
			}
		}
	}
}

/**
 * Submit callback for the admin page.
 */
function user_prune_admin_form_submit($form, &$form_state) {
	$values = $form_state['values'];
	
	//print_r($values);
	
	if ($values['op'] == t('Save Configuration')) {
		variable_set('prune_never', $values['prune_never']);
		variable_set('prune_never_registered_limit_length', $values['prune_never_registered_limit_length']);
		// reset the unit if the length is blank
		if ($values['prune_never_registered_limit_length'] == '') {
			variable_set('prune_never_registered_limit_unit', 2629744);
		}
		else {
			variable_set('prune_never_registered_limit_unit', $values['prune_never_registered_limit_unit']);
		}
		variable_set('prune_logged_in', $values['prune_logged_in']);
		variable_set('prune_logged_in_logged_in_limit_length', $values['prune_logged_in_logged_in_limit_length']);
		if ($values['prune_logged_in_logged_in_limit_length'] == '') {
			variable_set('prune_logged_in_logged_in_limit_unit', 2629744);
		}
		else {
			variable_set('prune_logged_in_logged_in_limit_unit', $values['prune_logged_in_logged_in_limit_unit']);
		}
		variable_set('prune_logged_in_registered_limit_length', $values['prune_logged_in_registered_limit_length']);
		if ($values['prune_logged_in_registered_limit_length'] == '') {
			variable_set('prune_logged_in_registered_limit_unit', 2629744);
		}
		else {
			variable_set('prune_logged_in_registered_limit_unit', $values['prune_logged_in_registered_limit_unit']);
		}
		variable_set('prune_per_run', $values['per_run']);
		
		drupal_set_message(t('The configuration options have been saved.'));
	}
	elseif ($values['op'] == t('Prune Now')) {
		user_prune_delete($values);
	}
}

/**
 * The function that takes care of deleting users.
 */
function user_prune_delete($values, $cron = FALSE) {
	// find the uids we need to delete
	$uids = array();
	if ($values['prune_never']) {
		$sql = 'SELECT uid FROM {users} WHERE login = 0';
		if ($values['prune_never_registered_limit_length']) {
			$rollback = $values['prune_never_registered_limit_length'] * $values['prune_never_registered_limit_unit'];
			$limit = time() - $rollback;
			$sql .= ' AND created < ' . $limit;
		}
		
		// can't delete the anonymous user or the super-user
		$sql .= ' AND uid <> 0 AND uid <> 1';
		
		$result = db_query($sql);
		while ($data = db_fetch_object($result)) {
			$uids[] = $data->uid;
		}
	}
	
	if ($values['prune_logged_in']) {
		$sql = 'SELECT uid FROM {users} WHERE login <> 0';
		if ($values['prune_logged_in_logged_in_limit_length']) {
			$logged_in_rollback = $values['prune_logged_in_logged_in_limit_length'] * $values['prune_logged_in_logged_in_limit_unit'];
			$limit = time() - $logged_in_rollback;
			$sql .= ' AND login < ' . $limit;
		}
		if ($values['prune_logged_in_registered_limit_length']) {
			$registered_rollback = $values['prune_logged_in_registered_limit_length'] * $values['prune_logged_in_registered_limit_unit'];
			$limit = time() - $registered_rollback;
			$sql .= ' AND created < ' . $limit;
		}
		
		// can't delete the anonymous user or the super-user
		$sql .= ' AND uid <> 0 AND uid <> 1';
		
		$result = db_query($sql);
		while ($data = db_fetch_object($result)) {
			$uids[] = $data->uid;
		}
	}
	
	// check to make sure the number of uids are in the per-run limit and if not force it to be
	if (count($uids) > $values['prune_per_run']) {
		$leftover = count($uids) - $values['prune_per_run'];
		shuffle($uids);
		$chunks = array_chunk($uids, $values['prune_per_run']);
		$uids = $chunks[0];
	}
	
	foreach ($uids as $uid) {
		user_delete(array(), $uid);
	}
	
	if (!$cron) {
		$message = t('@count users have been pruned.', array('@count' => count($uids)));
		if ($leftover) {
			$message .= ' ' . t("@leftover users met your criteria but weren't deleted.", array('@leftover' => $leftover));
		}
	
		drupal_set_message($message);
	}
}