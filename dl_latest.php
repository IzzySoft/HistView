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

# Find and send the latest version as Debian package
if ($dl->send_latest("histview","deb","/usr/src/debian/DEBS/all")) exit;

# Display error if nothing was found
else echo "<P ALIGN='center' STYLE='color:#f00'>Sorry - but the requested file was not found here.</P>\n";

?>