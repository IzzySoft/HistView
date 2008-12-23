<?
 #############################################################################
 # HistView                                 (c) 2003-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <devel@izzysoft.de>                            #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Download Class Example: Find the highest version and send it              #
 #############################################################################

 /* $Id$ */

include("download.class.inc");

# Create an instance of the download class
$dl = new download();

# Optional if we want to create statistics. The table needs at least the
# fields dl_date (DATE),prog (VARCHAR 30),newver (VARCHAR 10),referrer (varchar 100)
#$dl->db_setup("localhost","statistics","guest","guest","downloads");

# Shall we ignore some user agents when increasing the download counters? Agents
# to be ignored we can read from a file having one agent per line, lines
# starting with a "#" will be ignored
if (file_exists(dirname(__FILE__)."/histview_ignorebots")) {
  $ignorebots = file(dirname(__FILE__)."/histview_ignorebots");
  foreach ($ignorebots as $bot) {
    $bot = trim($bot);
    if (!empty($bot) && substr($bot,0,1)!="#") $dl->ignore_bot($bot);
  }
}
# Same as above - but these agents get no file, they get a "403" error instead
if (file_exists(dirname(__FILE__)."/histview_rejectbots")) {
  $rejectbots = file(dirname(__FILE__)."/histview_rejectbots");
  foreach ($rejectbots as $bot) {
    $bot = trim($bot);
    if (!empty($bot) && substr($bot,0,1)!="#") $dl->reject_bot($bot);
  }
}

# Find and send the latest version as Debian package
if ($dl->send_latest("histview","deb","/usr/src/debian/DEBS/all")) exit;

# Display error if nothing was found
else echo "<P ALIGN='center' STYLE='color:#f00'>Sorry - but the requested file was not found here.</P>\n";

?>