<?
 #############################################################################
 # HistView                                 (c) 2003-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <devel@izzysoft.de>                            #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Download Class: Scans directories and provides download links             #
 #############################################################################

 /* $Id$ */

/** Scanning a directory and checking for download files
 * @package Api
 * @class download
 * @author Izzy (devel@izzysoft.de)
 * @copyright (c) 2007 by Itzchak Rehberg and IzzySoft
 * @version $Revision$ $Date$
 */
class download {
  var $excludes = array(".","..","files.htm","files.php","index.php","index.htm","index.html");
  var $deficon  = "<IMG SRC='/icons/generic.gif' ALT='[*]' BORDER='0'>";
  var $icondir  = "/images/icons";
  var $filelist = array(); // Array[0..n] of array[name,version,sortver,file,icon[,size,date]]
  var $dltype   = "internal";
  var $argsep   = ";";

  /** Initial setup of default filetypes and date format
   * @constructor download
   * @param optional string basedir What to cut off to generate a download link.
   *        This is usually your web servers document root. This parameter is
   *        not needed when using the internal download method (default).
   * @param optional string icondir URL of the directory where the icons reside
   */
  function download($basedir="",$icondir="") {
    $this->set_filetype("tar","/^([\w-\.]+)\-(\d+)\.(\d+)\.(\d+)\.tar\.gz/","tar.gz","tgz.png");
    $this->set_filetype("deb","/^([\w-\.]+)\_(\d+)\.(\d+)\.(\d+)\-[0-9a-z]*(\d+)_[\w]+\.deb/","deb","deb.png");
    $this->set_filetype("rpm","/^([\w]+)\-(\d+)\.(\d+)\.(\d+)\-[0-9a-z]*(\d+)\.[\w]+\.rpm/","rpm","rpm.png");
    $this->set_dateformat("d.m.Y");
    $this->basedir = $basedir;
    if (!empty($icondir)) $this->icondir = $icondir;
  }

  /** Setup file types
   * @method set_filetype
   * @param string type Short name for the type, e.g. "rpm", "deb", "tar"
   * @param string mask Corresponding regexp mask. The back references should be
   *        set such that <ul><li>\1 is the name of the software</li>
   *        <li>\2.\3.\4 make up the version</li>
   *        <li>optional \5 sets the release number (required for *.deb and *.rpm)</li></ul>
   * @param string extension File extension to identify this type - e.g. "deb" or "tar.gz"
   * @param optional string icon Complete img tag to display for this type
   */
  function set_filetype($type,$mask,$extension,$icon="") {
    $this->mask[$type] = $mask;
    $this->ext[$type]  = $extension;
    if (empty($icon)) $this->icon[$type] = $this->deficon;
    else $this->icon[$type] = "<IMG SRC='".$this->icondir."/$icon' ALT='*' BORDER='0'>";
  }

  /** Set the date format to use
   * @method set_dateformat
   * @param format Date format to use (refer to the PHP manual of date)
   */
  function set_dateformat($format) {
    $this->dateformat = $format;
  }

  /** Set the directory (URL) where your icons reside
   * @method set_icondir
   * @param string dir URL of the directory where the icons reside
   */
  function set_icondir($dir) {
    $this->icondir = $dir;
  }

  /** Setup exclude list
   * @method set_excludes
   * @param array excludes Array of files to exclude from listings
   * @param optional boolean replace Replace the preset list (TRUE) or append to it (FALSE)? Default is to append.
   */
  function set_excludes($excl,$replace=FALSE) {
    if ($replace) $this->excludes = $excl;
    else $this->excludes = array_merge($this->excludes,$excl); 
  }

  /** Set download linktype
   * @method set_dllinktype
   * @param string type type of the link
   */
  function set_dllinktype($type) {
    $this->dltype = $type;
  }

  /** Set the argument separator
   *  This is how to separate arguments in the URL. Default is ";" - you may
   *  want to set this to "&"
   * @method set_argsep
   * @param string separator
   */
  function set_argsep($sep) {
    $this->argsep = $sep;
  }

  /** Scan another directory
   *  Switches to another directory. This resets the internal file array and starts over.
   *  The filelist array will not be reset, so entries are added to it.
   * @method scan_dir
   * @param string dir Directory to scan
   * @param optional integer dirnum If you run multiple directories via an array, you can store the index here. Will be added to the DL URL, when internal DL method is used.
   */
  function scan_dir($dir,$dirnum="") {
    if (isset($this->files)) unset ($this->files);
    $this->dir = $dir;
    if(is_dir($dir))  {
      $thisdir = dir($dir);
      $version = 0; $fname = "";
      while($entry=$thisdir->read()) {
        if (!in_array($entry,$this->excludes)) $this->files[] = $entry;
      }
    }
    $this->interprete_filelist($dirnum);
  }

  /** Get the list of files
   * @method get_filenames
   * @return array Array[0..n] of filenames
   */
  function get_filenames() {
    return $this->files;
  }

  /** Get full (interpreted) filelist
   * @method get_filelist
   * @return array Array[0..n] of file arrays.
   *         File array has the properties dir,name,version,sortver,file, icon, ilink (link with icon) and flink (link with filename).
   *         If add_details was run before, size, date and desc are also available.
   */
  function get_filelist() {
    return $this->filelist;
  }

  /** Generate list of all files incl. basic information
   *  Is called from method scan_dir
   * @method private interprete_filelist
   * @param optional integer dirnum If you run multiple directories via an array, you can store the index here. Will be added to the DL URL, when internal DL method is used.
   */
  function interprete_filelist($dirnum="") {
    $i=count($this->filelist);
    foreach($this->files as $file) {
      foreach ($this->ext as $type=>$ext) {
        preg_match("/.*(${ext})\$/",$file,$match);
	if (!empty($match[1])) break;
      }
      preg_match($this->mask[$type],$file,$matches);
      if (!empty($matches[1])) {
        $name = $matches[1];
	$version = $matches[2].".".$matches[3].".".$matches[4];
	$sortver = $matches[2]*1000000+$matches[3]*10000+$matches[4]*100;
	if (isset($matches[5])) {
	  $version .= ".".$matches[5];
	  $sortver += $matches[5];
	}
	switch ($this->dltype) {
	  case "internal" :
	  	$linkto = $_SERVER["PHP_SELF"]."?file=$file";
		if (!empty($dirnum)||$dirnum===0) $linkto .= $this->argsep."dirnum=$dirnum";
		break;
	  default         :
	  	$linkto = substr($this->dir,strlen($this->basedir))."/$file";
		break;
	}
	$ilink = "<A HREF='$linkto'>".$this->icon[$type]."</A>";
	$flink = "<A HREF='$linkto'>$file</A>";
	$this->filelist[$i] = array("dir"=>$this->dir,"name"=>$name,"type"=>$type,"version"=>$version,"sortver"=>$sortver,"file"=>$file,"icon"=>$this->icon[$type],"ilink"=>$ilink,"flink"=>$flink);
	++$i;
      }
    }
  }

  /** Sort array by given key
   * @method private ar_sort_by
   * @param arr Array to sort
   * @param orderby Field to order by
   * @param optional boolean rev Reverse order (default:false)
   * @param optional integer method One of the constants SORT_REGULAR,
   *        SORT_NUMERIC, SORT_STRING, SORT_LOCALE_STRING
   */
  function ar_sort_by($arr, $orderby, $reverse=false, $flags=SORT_REGULAR) {
    // Create 1-dimensional named array with just sortfield (in stead of record) values
    $named_hash = array();
    foreach($arr as $key=>$fields)
            $named_hash["$key"] = $fields[$orderby];
    // Order 1-dimensional array, maintaining key-value relations  
    if($reverse) $rc = arsort($named_hash,$flags) ;
    else $rc = asort($named_hash, $flags);
    if ($rc) $ok = "OK"; else $ok = "Failure!";
    // Create copy of named records array in order of sortarray 
    $sorted_records = array();
    foreach($named_hash as $key=>$val)
      $sorted_records["$key"]= $arr[$key];
    return array_merge($sorted_records); // named_recs_sort()
  }

  /** Sort filelist by version
   * @method sort_by_version
   * @param optional boolean rev Reverse order? Default: False
   */
  function sort_by_version($rev=FALSE) {
    $this->filelist = $this->ar_sort_by($this->filelist,"sortver",$rev,SORT_NUMERIC);
  }

  /** Sort by filename
   * @method sort_by_filename
   * @param optional boolean rev Reverse order? Default: False
   */
  function sort_by_filename($rev=FALSE) {
    $this->filelist = $this->ar_sort_by($this->filelist,"file",$rev);
  }

  /** Add details to the filelist (fields "size" and "date")
   * @method add_details
   * @param optional string descdir Directory where the description files reside.
   *        Name of a description file must be either &lt;name&gt;.desc (for a
   *        general, version independent description) or
   *        &lt;name&gt;_&lt;version&gt;.desc (description bound to a specific
   *        version). The latter one is used (if found), the first one otherwise
   *        (if found). Descriptions will be preceded by "&lt;name&gt; v&lt;version&gt;".
   *        If a description file is found, it then will be added after an additional
   *        line break (&lt;BR&gt;).
   * @param optional boolean descreplace Replace the short desc (TRUE, default)
   *        or append to it (FALSE)
   */
  function add_details($descdir="",$descreplace=TRUE) {
    $fc = count($this->filelist);
    for ($i=0;$i<$fc;++$i) {
      $fname = $this->filelist[$i]["dir"]."/".$this->filelist[$i]["file"];
      $size = filesize($fname);
      if ($size>1048576) { // MB
        $size = sprintf("%01.1f",round($size/1048576,1))." MB";
      } elseif ($size>1024) { // kB
        $size = sprintf("%01.1f",round($size/1024,1))." kB";
      } else { // B
        $size .= " B";
      }
      $this->filelist[$i]["size"] = $size;
      $this->filelist[$i]["date"] = date($this->dateformat,filemtime($fname));
      $this->filelist[$i]["desc"] = $this->filelist[$i]["name"]." v".$this->filelist[$i]["version"];
      if (!empty($descdir)) {
        $basename = $descdir."/".$this->filelist[$i]["name"];
        if (file_exists($basename."_".$this->filelist[$i]["version"].".desc")) $dfile = $basename."_".$this->filelist[$i]["version"].".desc";
        elseif (file_exists($basename.".desc")) $dfile = $basename.".desc";
        else continue;
	if ($descreplace)
          $this->filelist[$i]["desc"] = file_get_contents($dfile);
	else
          $this->filelist[$i]["desc"] .= "<BR>".file_get_contents($dfile);
      }
    }
  }

  /** Download a file
   * @method sendfile
   * @param string filename File to download
   * @param optional string directory Directory where the file resides (if other than the recent one)
   * @return boolean file_sent TRUE if file found, FALSE otherwise
   */
  function sendfile($fname,$dir="") {
    if (empty($dir)) $dir = $this->dir;
    $file = $dir."/".$fname;
    if (!file_exists($file)) return FALSE;
    if ($fd = fopen ($file,"rb")) {
      $this->dbcounter($fname);
      $fsize = filesize($file);
      header("Content-type: application/octet-stream");
      header("Content-Disposition: attachment; filename=\"".$fname."\"");
      header("Content-length: $fsize");
      fpassthru($fd);
      fclose($fd);
      return TRUE;
    }
  }

  /** Increase download counter in the database
   * @method dbcounter
   * @param string filename Filename to process
   */
  function dbcounter($file) {
    if (!isset($this->dbuser)) return;
    foreach ($this->ext as $type=>$ext) {
      preg_match("/.*(${ext})\$/",$file,$match);
      if (!empty($match[1])) break;
    }
    preg_match($this->mask[$type],$file,$matches);
    if (!empty($matches[1])) {
      $date = date('Y-m-d');
      $name = $matches[1];
      $version = $matches[2].".".$matches[3].".".$matches[4];
      $query = "INSERT INTO ".$this->dbtable." (dl_date,prog,newver,referrer)"
             . " VALUES ('$date','$name','$version','".$_SERVER['HTTP_REFERER']."')";
      require_once ( "db_mysql.inc" );
      $db = new db_mysql;
      $db->Host     = $this->dbhost;
      $db->Database = $this->database;
      $db->User     = $this->dbuser;
      $db->Password = $this->dbpass;
      @$db->query($query);
    }
  }

  /** Setup database connection
   * @method db_setup
   * @param string host hostname the DB is running on
   * @param string database Name of the database to use
   * @param string user DB User to connect with
   * @param string passwd Password to use
   * @param string table Name of the download table
   */
  function db_setup($host,$db,$user,$pass,$table) {
    $this->dbhost   = $host;
    $this->database = $db;
    $this->dbuser   = $user;
    $this->dbpass   = $pass;
    $this->dbtable  = $table;
  }

  /** Send latest version
   * @method send_latest
   * @param string prog Which program is requested
   * @param string type What type of archive (first parameter of set_filetype)
   * @param optional string directory Directory where the file resides (if it was not scanned yet)
   * @return boolean file_send Whether we found something to send.
   */
  function send_latest($prog,$type,$dir) {
    if (!empty($dir)) $this->scan_dir($dir);
    $fc = count($this->filelist);
    for ($i=0;$i<$fc;++$i) {
      if ($this->filelist[$i]["name"] != $prog) continue;
      if ($this->filelist[$i]["type"] != $type) continue;
      $list[$i] = $this->filelist[$i];
    }
    if (!is_array($list)) return FALSE;
    $list = $this->ar_sort_by($list,"sortver");
    $list = array_merge($list); // re-arrange keys
    $fc = count($list);
    if (!$this->sendfile($list[$fc-1]["file"],$dir)) return FALSE;
    return TRUE;
  }

} // class download
?>