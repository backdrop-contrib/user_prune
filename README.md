User Prune
==========

User Prune lets you delete inactive users in batches based on criteria you specify. The pruning be scheduled as a cron job, or executed a single time.

The main criteria is the time since the user last logged in or, if never logged in before, the time since the user was created.

Additional criteria:

* Users with a certain status (blocked or active).
* Users with certain roles.
* Users who never posted comments.
* Users who never created nodes.
* Users have subscriptions via Notifications module.
* Users that are a part of an Organic Group.
* Users who have submitted a webform.
* Users who have requested a translation job through TMGMT.

Installation
------------

* Install this module using the official Backdrop CMS instructions at
  <https://backdropcms.org/guide/modules>.

How to use
----------

* Go to the main field list of a webform.
* Add a telephone element to your form.

Issues
------

Bugs and Feature requests should be reported in the Issue Queue:
<https://github.com/backdrop-contrib/user_prune/issues>

Current Maintainers
-------------------

* Herb v/d Dool <https://github.com/herbdool>

Credits
-------

* Ported to Backdrop by Herb v/d Dool <https://github.com/herbdool>
* Originally developed for Drupal by ViktorT <https://www.drupal.org/u/viktor-t>.

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.
