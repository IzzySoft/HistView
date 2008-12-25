<?
 #############################################################################
 # HistView                                 (c) 2003-2008 by Itzchak Rehberg #
 # written by Itzchak Rehberg <devel@izzysoft.de>                            #
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
 * @copyright (c) 2003-2008 by Itzchak Rehberg and IzzySoft
 * @version $Revision$ $Date$
 */
class hvconfig {
  function hvconfig() {
   //=====================================================[ General Settings ]===
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
   //====================================================[ HistView Settings ]===
   //====================================================[ Download Settings ]===
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
   /** Default icon
    * @class hvconfig
    * @attribute string deficon Complete &lt;IMG&gt; tag
    */
   $this->deficon  = "<IMG SRC='/icons/generic.gif' ALT='[*]' BORDER='0'>";
   /** URL directory where all other icons are stored
    * @class hvconfig
    * @attribute string icondir
    */
   $this->icondir  = "/images/icons";
   //------------------------------------------------------[ Database to use ]---
   /** Database to store download statistics. To override these settings later,
    *  it won't work this way -- use the <code>db_setup</code> method instead!
    * @class hvconfig
    * @attribute array db Array with the elements: host, database, user, pass, table
    */
   $this->db["host"]     = "localhost";
   $this->db["database"] = "webstat";
   $this->db["user"]     = "guest";
   $this->db["pass"]     = "guest";
   $this->db["table"]    = "downloads";
 }
}
