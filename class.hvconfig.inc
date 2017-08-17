<?php
 #############################################################################
 # HistView                                 (c) 2003-2017 by Itzchak Rehberg #
 # written by Itzchak Rehberg <devel AT izzysoft DOT de>                     #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Configuration for HistView and Download Class                             #
 #############################################################################

 /* $Id$ */

/** Configuration for HistView and Download Class
 * @package Api
 * @class hvconfig
 * @author Izzy (devel@izzysoft.de)
 * @copyright (c) 2003-2017 by Itzchak Rehberg and IzzySoft
 * @version $Revision$ $Date$
 */
class hvconfig {
  function hvconfig() {
   //====================================================[ General Settings ]===
   /** Separator for arguments in the URL
    * @class hvconfig
    * @attribute string argsep
    * @brief Though "&" works for most sites (and even is used by most sites),
    *        this does not conform to the W3C standards since it usually
    *        introduces some entity. So if you can, use ";" instead.
    */
   $this->argsep = ";";
   /** How to handle files to download: Use Download Class ("internal"),
    *  or directly link to them ("direct")
    * @class hvconfig
    * @attribute string dltype
    */
   $this->dltype = "internal";
   //===================================================[ HistView Settings ]===
   //-----------------------------------------[ ChangeLog formatting issues ]---
   /** ChangeLog Symbol for new feature
    * @class hvconfig
    * @attribute string plus
    */
   $this->plus   = "+";
   /** ChangeLog Symbol for removed things
    * @class hvconfig
    * @attribute string minus
    */
   $this->minus  = "-";
   /** ChangeLog Symbol for a change
    * @class hvconfig
    * @attribute string change
    */
   $this->change = "*";
   /** ChangeLog Symbol for a bug
    * @class hvconfig
    * @attribute string bug
    */
   $this->bug    = "!";
   /** ChangeLog Symbol introducing the version number
    * @class hvconfig
    * @attribute string ver
    */
   $this->ver    = "v";
   /** ChangeLog Symbol introducing a line to be ignored
    * @class hvconfig
    * @attribute string ignore
    */
   $this->ignore = array("\$","#","--","==");
   //----------------------------------------------------[ Icons to be used ]---
   /** Icon for new feature
    * @class hvconfig
    * @attribute string iplus
    */
   $this->iplus   = "<IMG SRC='/icons/burst.gif' BORDER='0' ALT='+' TITLE='New!'>";
   /** Icon for removed stuff
    * @class hvconfig
    * @attribute string iminus
    */
   $this->iminus  = "<IMG SRC='/icons/transfer.gif' BORDER='0' ALT='-' TITLE='Removed'>";
   /** Icon for a change
    * @class hvconfig
    * @attribute string ichange
    */
   $this->ichange = "<IMG SRC='/icons/image1.gif' BORDER='0' ALT='*' TITLE='Changed'>";
   /** Icon for a bug
    * @class hvconfig
    * @attribute string ibug
    */
   $this->ibug    = "<IMG SRC='/icons/alert.red.gif' BORDER='0' ALT='!' TITLE='Bugfix'>";
   /** Icon for tar files
    * @class hvconfig
    * @attribute string itar
    */
   $this->itar    = "<IMG SRC='icons/tgz.png' BORDER='0' ALT='*' TITLE='Tar Archive'>";
   /** Icon for Debian packages
    * @class hvconfig
    * @attribute string ideb
    */
   $this->ideb    = "<IMG SRC='icons/deb.png' BORDER='0' ALT='*' TITLE='Debian Package'>";
   /** Icon for RPM packages
    * @class hvconfig
    * @attribute string irpm
    */
   $this->irpm    = "<IMG SRC='icons/rpm.png' BORDER='0' ALT='*' TITLE='RPM Package'>";
   //---------------------------------------------------------[ CSS classes ]---
   /** CSS class for a new feature
    * @class hvconfig
    * @attribute string cplus
    */
   $this->cplus   = "feature";
   /** CSS class for removed stuff
    * @class hvconfig
    * @attribute string cminus
    */
   $this->cminus  = "removed";
   /** CSS class for a change comment
    * @class hvconfig
    * @attribute string cchange
    */
   $this->cchange = "changed";
   /** CSS class for a bug comment
    * @class hvconfig
    * @attribute string cbug
    */
   $this->cbug    = "bugfix";
   //--------------------------------------------------[ Directory Settings ]---
   /** Base directory. Most times this is your web servers DOCUMENT_ROOT.
    *  For details, see also histview::set_basedir(). Leave empty if you are
    *  using the download class (i.e. hvconfig::dltype is set to "internal").
    * @class hvconfig
    * @attribute string basedir
    */
   $this->basedir = "";
   /** Directory holding the *.deb files for download. This is often the same
    *  for all your apps, since it mostly points to the same repository
    * @class hvconfig
    * @attribute string debbase
    */
   $this->debbase = "/var/repo/debian";
   /** Directory holding the *.rpm files for download. This is often the same
    *  for all your apps, since it mostly points to the same repository
    * @class hvconfig
    * @attribute string rpmbase
    */
   $this->rpmbase = "/var/repo/redhat.dist";
   /** Directory holding your *.tar.gz files for download. If you have only one,
    *  it will be sufficient to define it here. Otherwise, you will have to
    *  override this setting in the corresponding PHP file
    * @class hvconfig
    * @attribute string tarbase
    */
   $this->tarbase = "/var/www/downloads";
   //-------------------------------------------------------[ Miscellaneous ]---
   /** Default architecture for packages (RPM style - for Debian, it will be
    *  calculated based on this)
    * @class hvconfig
    * @attribute string arch
    */
   $this->arch = "noarch";
   /** Release Name - this is the (optional) string appended to the official
    *  version number, as you find it e.g. for Medibuntu with "medibuntu" in
    *  "googleearth-4.3_4.3.7204.836-0medibuntu1_i386.deb"
    * @class hvconfig
    * @attribute string relname
    */
   $this->relname = "";
   /** Highest release number to expect. The release number is the number
    *  following the relname (or, if relname is not set, the version).
    *  Example: "prog-0.3.5-1_i386.deb" and "prog-0.3.5-johnny1_i386.deb"
    *  both have the relnum set to "1". HistView is looping to find the latest
    *  release - so here we tell it when to stop at latest.
    * @class hvconfig
    * @attribute integer max_relnum
    */
   $this->max_relnum = 9;
   /** Map filenames to prognames. If the filename does not directly reflect
    *  the prog name you want to record into your stats table, you can set up
    *  a map entry here. Example: A new version of your lib package is not
    *  100% backwards compatible, so you name the new packages "mylib2"
    *  instead of simply "mylib" as it was before. But for statistics you
    *  do not want a new progname. So in your hv-localconf.inc, you write:
    *  $this->map_names['mylib2'] = 'mylib';
    * @class hvconfig
    * @attribute array map_names (array[filename]=progname]
    */
   $this->map_names = array();
   //===================================================[ Download Settings ]===
   /** Action for requests w/o referer
    *  Valid actions are: "pass" (no action), "deny" (reject request), "whois"
    *  (network check - and reject crawler networks)
    * @class hvconfig
    * @attribute string noRefererAction
    */
   $this->noRefererAction = "pass";
   /** IP Blacklist file (e.g. from http://sblam.com/blacklist.txt)
    * @class hvconfig
    * @attribute string blacklistfile
    */
   $this->blacklistfile = dirname(__FILE__)."/hv_ipblacklist";
   /** Action to perform when remote address is contained in blacklist file
    *  Valid actions are: "pass" (no action), "deny" (reject request)
    * @class hvconfig
    * @attribute string blacklistAction
    */
   $this->blacklistAction = "pass";
   /** Read crawler network names from a file
    * @class hvconfig
    * @attribute string crawlerfile
    */
   $this->crawlerfile = dirname(__FILE__)."/histview_crawlernets";
   /** Read bots to ignore from a file
    * @class hvconfig
    * @attribute string ignorefile
    */
   $this->ignorefile = dirname(__FILE__)."/histview_ignorebots";
   /** Read bots to reject from a file
    * @class hvconfig
    * @attribute string rejectfile
    */
   $this->rejectfile = dirname(__FILE__)."/histview_rejectbots";
   /** Header for rejected clients
    * @class hvconfig
    * @attribute string rejectheader
    */
   $this->rejectheader = "HTTP/1.1 403 Forbidden";
   /** Message to give to rejected clients
    * @class hvconfig
    * @attribute string rejectmsg
    */
   $this->rejectmsg = "<html><head><title>403 Forbidden</title></head><body>Bots should not download files here.</body></html>";
   /** Files to exclude
    * @class hvconfig
    * @attribute array excludes
    */
   $this->excludes = array(".","..","files.htm","files.php","index.php","index.htm","index.html");
   /** Icon to use by default. This must be a complete &lt;IMG&gt; tag.
    * @class hvconfig
    * @attribute string deficon
    */
   $this->deficon  = "<IMG SRC='/icons/generic.gif' ALT='[*]' BORDER='0'>";
   /** URL directory where all other icons are stored
    * @class hvconfig
    * @attribute string icondir
    */
   $this->icondir  = "/images/icons";
   /** Shall we use the statistic functions (download counter)?
    *  0-No, 1-Yes
    * @class hvconfig
    * @attribute integer statisticsmode
    */
   $this->statisticsmode = 1;
   //-----------------------------------------------------[ Download Limits ]---
   /** Limit the download per IP and prog to a given number within a given time.
    *  If set to 0, there will be no limit. If you want to use this, keep in
    *  mind there may be good reasons for multiple downloads of the same prog,
    *  e.g. if you provide multiple formats (RPM,DEB,TGZ) - so a good number
    *  for the limit is the number of formats provided plus a "chance" for trouble,
    *  say formats + 2
    * @class hvconfig
    * @attribute integer dlFileLimit
    */
   $this->dlFileLimit = 0;
   /** Time interval (in seconds) to monitor for limits. Make it small enough,
    *  but not too small. The best setting also depends on the average size of
    *  the files you offer for download, your setting for $dlFileLimit, and the
    *  assumed transfer rates. Say you assume a single download to be done in
    *  30s, and you want to permit 5 downloads, they would take 2:30 minutes.
    *  If a bot/crawler is firing them, it's done by that. Add a bit for
    *  eventual trouble in routing, so you should be fine with 5min (300s).
    *  Remember that every *ATTEMPT* will be considered, so this value should
    *  be fine in this case.
    * @class hvconfig
    * @attribute integer dlTimeLimit
    */
   $this->dlTimeLimit = 300;
   /** Shall the database table recording data to check the download attempts
    *  for limiting them be purged automatically? This is recommended, so the
    *  sample config sets this to TRUE.
    * @class hvconfig
    * @attribute boolean dlLimitAutopurge
    */
   $this->dlLimitAutopurge = TRUE;
   //-----------------------------------------------------[ Database to use ]---
   /** Database to store download statistics. Irrelevant (i.e. not used) when
    *  statistics are turned off (statisticsmode=0). To override these settings
    *  later, it won't work this way -- use the <code>db_setup</code> method
    *  instead! The array defined here has the elements host, database, user,
    *  pass, table
    * @class hvconfig
    * @attribute array db
    */
   $this->db["host"]       = "localhost";
   $this->db["database"]   = "webstat";
   $this->db["user"]       = "guest";
   $this->db["pass"]       = "guest";
   $this->db["table"]      = "downloads";
   $this->db["limitTable"] = "hvlimits";
   //------------------------------------------[ local/personal adjustments ]---
   // to make your future updates easier, place your personal preferences into
   // a personal file named "hv-localconf.inc" in the same directory as this
   // file is located in - we include it here to override the defaults:
   if (file_exists(dirname(__FILE__)."/hv-localconf.inc"))
     include(dirname(__FILE__)."/hv-localconf.inc");
   //------------------------------------------------------[ internal stuff ]---
   // please don't touch this ;)
   $this->hv_version = "0.1.7";
   $this->homepage = "https://github.com/IzzySoft/HistView";
 }
}
