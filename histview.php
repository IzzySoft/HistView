<?
 #############################################################################
 # HistView Client                               (c) 2003 by Itzchak Rehberg #
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
 
 if (empty($prog)) $prog = "HistView";
 
 include("histview.inc");
 $file = strtolower($prog).".hist";
 $hv = new histview($file);
 $hv->process();
 $history = $hv->out();
 $title = "History for $prog";
 echo "<HTML><HEAD>\n"
    . ' <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-15"/>'."\n"
    . ' <LINK REL="stylesheet" TYPE="text/css" HREF="main.css">'."\n"
    . " <TITLE>$title</TITLE>\n"
    . "</HEAD><BODY>\n<H2>$title</H2>\n";
 echo $history."\n</BODY></HTML>\n";
?>