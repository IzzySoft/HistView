<?
 #############################################################################
 # HistView Client                          (c) 2003-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <devel@izzysoft.de>                            #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Calls HistView Api to display a history file                              #
 # Call it as "histview.php?prog=XxX". The Title will then change to "XxX"   #
 # and the historyfile xxx.hist (note: lower case) will be displayed.        #
 #############################################################################

 /* $Id$ */
 
#==================================================================[ Setup ]===
#-------------------------------[ Read request vars and do some protection ]---
$prog = $_REQUEST["prog"];
# $prog should only contain letters, digits and "_"
if (empty($prog) || @preg_match("/[^\w]/u",$prog)) $prog = "HistView";
# $file should be alphanumeric - no special chars or / or \
$file = $_REQUEST["file"];
if (empty($file) || @preg_match("/[^\w\s-\pL]/u",$file)) unset ($file);
# $dir should only be one of ours - here: "tar","deb","rpm"
$dir  = $_REQUEST["dir"];
if (!empty($dir) && !in_array($dir,array("tar","deb","rpm"))) unset ($file,$dir);

#------------------------------------------------------[ Setup directories ]---
$dirs = array( "tar" => "/var/ftp/downloads",
               "deb" => "/var/repo/debian",
               "rpm" => "/var/repo/redhat/RPMS.dist" );
$charset = "iso-8859-15";

#========================================================[ Process Request ]===
#----------------------------------------------[ Was a download requested? ]---
if (!empty($_REQUEST["file"])) {
  include("class.download.inc");
  if (!empty($file) && !empty($dir)) {
    $dl = new download();
    if ($dl->sendfile($file,$dirs[$dir])) exit;
  }
  $e404 = "\n<DIV CLASS='ebox'>Sorry - but the requested file was not found here.</DIV>";
} else {
  $e404 = "";
}

#-----------------------------------------------[ Display the history file ]---
include("histview.inc");
$file = strtolower($prog).".hist";
# Simple method, no download links to provide:
#$hv = new histview($file);
# Providing download links:
$hv = new histview($file,strtolower($prog));
# Setting up the directories
$hv->set_basedir("tar", $dirs["tar"]);

# Process the page
$hv->process();
$history = $hv->out();
$title = "History for $prog";
echo "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'>\n";
echo "<HTML><HEAD>\n"
   . " <META HTTP-EQUIV='Content-Type' CONTENT='text/html; charset=$charset'/>\n"
   . ' <LINK REL="stylesheet" TYPE="text/css" HREF="histview.css">'."\n"
   . " <TITLE>$title</TITLE>\n"
   . "</HEAD><BODY>\n<H2>$title</H2>\n";
echo $e404;
echo $history."\n</BODY></HTML>\n";
?>