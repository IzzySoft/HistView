<?php
 #############################################################################
 # HistView                                 (c) 2003-2017 by Itzchak Rehberg #
 # written by Itzchak Rehberg <devel@izzysoft.de>                            #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Download Class Example: Scan the directory this file is located in and    #
 # create a list of downloadable files with details about them               #
 #############################################################################

 /* $Id$ */

#==================================================================[ Setup ]===
$title = "Download List";	# Page title / Caption
include("class.download.inc");	# Include the download class and
$dl = new download();		# create an instance
# Set a different file name format for tar archives: xxxx0.0.0.tgz
# where "xxxx" stands for any amount of letters/digits/-/_/. and
# 0.0.0 for the version number
$dl->set_filetype("tar","/^([\w-\.]+)(\d+)-(\d+)-(\d+).tgz/","tgz","tgz.png");
$e404 = "";     # Here we store the error (if any)

#=============================================================[ Processing ]===
#----------------------------------------------[ Was a download requested? ]---
if (!empty($_REQUEST["file"])) {
  # Optional for statistics. See dl_latest.php for table description
  #$dl->db_setup("localhost","statistics","guest","guest","downloads");
  # If the requested file is found (usually, if not called from some old, cached
  # copy of the page) send it and exit
  if ($dl->sendfile($_REQUEST["file"],dirname(__FILE__))) exit;
  # Still here? So the file was not found, we need an error message
  $e404 = "\n<DIV CLASS='ebox'>Sorry - but the requested file was not found here.</DIV>";
}

#-----------------------------------------------------[ Scan the directory ]---
$dl->scan_dir(dirname(__FILE__));	# Scan the current directory
$dl->sort_by_version(1);		# order by true version
$dl->add_details(dirname(__FILE__));	# add size, date etc. to the list

#============================================================[ Page Output ]===
#----------------------------------------------------------------[ Heading ]---
?>
<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'>
<HTML><HEAD>
  <TITLE><?=$title?></TITLE>
  <LINK REL="stylesheet" TYPE="text/css" HREF="filelist.css">
  <META http-equiv="Content-Type" content="text/html; charset=UTF8">
</HEAD><BODY><?=$e404?>
<TABLE BORDER='1' CELLSPACING='1' CELLPADDING='4'>
  <TR CLASS='super'>
    <TH CLASS='super' COLSPAN="4"><?=$title?></TH>
  </TR>
  <TR CLASS="head">
    <TD CLASS="head">Filename</TD>
    <TD CLASS="head">Size</TD>
    <TD CLASS="head">Date</TD>
    <TD CLASS="head">Description</TD>
  </TR>
<?php
#--------------------------------------------------------------[ File list ]---
# Here we loop the created file list (array) and create one table row per file
foreach ($dl->filelist as $file) {
  echo " <TR>\n  <TD CLASS='name'>".$file["ilink"]."&nbsp;".$file["file"]."</TD>\n"
       . "  <TD CLASS='size' nowrap>".$file["size"]."</TD>\n"
       . "  <TD CLASS='date'>".$file["date"]."</TD>\n"
       . "  <TD CLASS='desc'>".$file["desc"]."</TD>\n </TR>\n";;
}
#-----------------------------------------------------------------[ Footer ]---
?>
</TABLE>
</BODY></HTML>