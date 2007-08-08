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
 
 $prog = $_REQUEST["prog"];
 if (empty($prog)) $prog = "HistView";
 
 include("histview.inc");
 $file = strtolower($prog).".hist";
 # Simple method, no download links to provide:
 $hv = new histview($file);
 # Providing download links:
 #$hv = new histview($file,strtolower($prog));
 #$hv->set_icon("","","","","<IMG SRC='icons/tgz.png' BORDER='0'>","<IMG SRC='icons/deb.png' BORDER='0'>","<IMG SRC='icons/rpm.png' BORDER='0'>");
 #$hv->set_basedir("base","/var");
 #$hv->set_basedir("tar","/var/ftp/downloads");
 #$hv->set_basedir("deb","/var/repo/debian");
 #$hv->set_basedir("rpm","/var/repo/redhat/RPMS.dist");
 #$hv->set_relname("johnny");

 $hv->process();
 $history = $hv->out();
 $title = "History for $prog";
 echo "<HTML><HEAD>\n"
    . ' <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-15"/>'."\n"
    . ' <LINK REL="stylesheet" TYPE="text/css" HREF="histview.css">'."\n"
    . " <TITLE>$title</TITLE>\n"
    . "</HEAD><BODY>\n<H2>$title</H2>\n";
 echo $history."\n</BODY></HTML>\n";
?>