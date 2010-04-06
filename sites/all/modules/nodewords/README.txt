; $Id: README.txt,v 1.27.2.19 2010/02/17 15:14:51 kiam Exp $

This module allows you to set some meta tags for the different resources exposed
by your site: nodes, users, views, taxonomy filters and error pages are some
examples.

Giving more attention to the important keywords and/or description on your site
allows you to get better search engine positioning (given that you really only
provide the keywords which exist in the content itself, and do not try to lie).

This version of the module only works with Drupal 6.x.

Features
------------------------------------------------------------------------------
This is a brief of features provided by this module:

* You can separately specify the meta tags to show on some specific pages of
  your site (the front page, the error 403 page, the error 404 page), or to use
  in specific situations (the pages with a pager, i.e.).

* A pluggable system allow the inclusion of new meta tags apart from the ones
  provided by this module.

* The current supported basic meta tags are ABSTRACT, CANONICAL, COPYRIGHT,
  GEO.POSITION, DESCRIPTION, ICBM, KEYWORDS, PICS-LABEL, REVISIT-AFTER, ROBOTS.
  These meta tags are provided by the module Basic meta tags.

* Additionally, you may include site verification meta tags used by external
  sources: Google Webmaster Tools, Microsoft Bing Webmaster Center, Yahoo! Site
  Explorer.
  These meta tags are provided by the module Site verification meta tags.

* Additionally you may include the Dublin Core meta tag schema.
  These meta tags are provided by the module Extra meta tags.

* You can select which of the available tags will be available for edition, and
  which will be exposed in the HTML of your site.

* You can specify a default meta tag ROBOTS value used for all pages, but easily
  override it for every page.

* All text of the DESCRIPTION and KEYWORDS meta tags are added to the search
  system so they are searchable too; other meta tags could be added to the
  search system too (depending on the code implemented from the module).

Other modules integration
-------------------------
Nodewords integrates other modules for automatic selection of meta tags.

* All terms of some specified vocabularies associated with a node can be added
  to the meta tag KEYWORDS content.

* On taxonomy pages, the term description is used as the meta tag DESCRIPTION.
  The term itself is added to the list of KEYWORDS. You can override the
  description to use, if you wish.

* Previous versions of this module provided support for Views and Panels. This
  feature has been removed from Nodewords 6.x-1.x since August 15, 2009; as the
  module provides an API allowing other modules to integrate with it.

* This module may also integrate Taggadelic, CCK, and other resources.

Installing Nodewords (aka Meta tags) (first time installation)
------------------------------------------------------------------------------
1. Backup your database.

2. Copy the module as normal.
   More information about installing contributed modules could be found at
   "Install contributed modules" [1].

3. Enable the "Nodewords" module from the module administration page
   (Administer >> Site configuration >> Modules).

4. Configure the module (see "Configuration" below).

5. You should enable other modules providing meta tags. There are three modules
   implementing meta tags:
   - Basic meta tags: for typical DESCRIPTION, ABSTRACT, COPYRIGHT meta tags.
   - Extra meta tags: for Dublin meta tag Schema.
   - Site verification meta tags: for specific API meta tags by search engines.

Updating Nodewords (aka Meta tags) (module version upgrade)
------------------------------------------------------------------------------
1. Verify that the version you are going to upgrade contains all the features
   your are using in your Drupal setup. Some features could have been removed
   or replaced by others.

2. Read carefully in the project issue tracking about upgrade paths problems
   before you start the upgrade process. Some versions don't support a clean
   upgrade path that may left your site meta tags unusable.

3. Backup your database.

4. Update current module code with latest recommended version. Previous versions
   could have bugs already reported and fixed in the last version.

4. Complete the update process, set maintenance mode, call the update.php script
   and finish the update operation. For more information please go to:
   http://groups.drupal.org/node/19513

4. Verify your module configuration and check that the features you are using
   work as expected. Also verify that all required modules are enabled, and
   permissions are set as desired.

Note: Whenever you have the chance, try an update in a local or development
      copy of your site.


Configuration
------------------------------------------------------------------------------
1. On the access control administration page ("Administer >> User management
   >> Access control") you need to assign:

   - the "administer meta tags" permission to the roles that are allowed to
     administer the meta tags (such as setting the default values and/or
     enabling the possibility to edit them),

   - the "edit XYZ tag" permission to the roles that are allowed to set and
     edit meta tags for the content (there is a permission for each of the
     meta tags currently defined).

   All users will be able to see the assigned meta tags.

2. On the settings page ("Administer >> Content management >> Nodewords") you
   can specify the default settings for the module. To access this page users
   need the "administer meta tags" permission.

3. You should enable meta tags for editing before they are available for use.
   The same operation should be done for meta tag output. Only allowed Meta tags
   are available for editing or exposed in the HTML of your site.

4. The front page is an important page for each website. Therefore, you can
   specifically set the meta tags to use on the front page meta tags settings
   page ("Administer >> Content management >> Nodewords >> Front page").
   Users need the "administer meta tags" permission to do this. When there are
   resources providing meta tags promoted in the front page, you may Force the
   usage of "Front page" meta tags superseeding all of them.

   Alternatively, you can opt not to set the meta tags for the front page on
   this page, but to use the meta tags of the view, panel or node the front page
   points to. To do this, you need to uncheck the "Use front page meta tags"
   option on the settings page.

   Note that, in contrast to previous versions of this module, the site mission
   and/or site slogan are no longer used as DESCRIPTION or ABSTRACT on the front
   page!

5. You can completely disable the possibility to edit meta tags for each
   individual content type by editing the content type settings in
   "Administer >> Content management >> Content types"; by default meta tags are
   enabled for all content types. When the editing of node meta tags is
   disabled, the module will still output the default values.

   Other settings are available for the generation of meta tags in the same
   page.


Related modules
------------------------------------------------------------------------------
Starting from nodewords-5.x-1.9 the following modules extend the nodewords
functionality:

- Meta tags Node Type, by Ariel Barreiro
- Meta Tags by Path, by Shannon Lucas

The latest development snapshot (6.x-1.x-dev), and version 6.x-1.1 or higher
implement a functionality similar to the one implemented in the module
Meta Tags by Path, which is not anymore required for those versions.

To assure compatibility between Nodewords and Meta tags Node Type, use the
latest version available of Nodewords and Meta tags Node Type; previous versions
were not compatible with the recent changes in Nodewords.

Credits / Contact
------------------------------------------------------------------------------
Original author of this module is Andras Barthazi. Mike Carter [2] and
Gabor Hojtsy [3] provided some feature enhancements. Alberto Paderno [5] is the
current maintainer.

Best way to contact the authors is to submit a (support/feature/bug) issue in
the project issue queue at http://drupal.org/project/issues/nodewords.

References
------------------------------------------------------------------------------
[1]  http://drupal.org/node/70151
[2]  http://drupal.org/user/13164
[3]  http://drupal.org/user/4166
[4]  http://drupal.org/user/22598
[5]  http://drupal.org/user/55077
