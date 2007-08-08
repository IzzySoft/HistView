<?
 #############################################################################
 # HistView                                 (c) 2003-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <devel@izzysoft.de>                            #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Viewer for history files as used in development                           #
 #############################################################################

 /* $Id$ */

/** Processing a history file and prepare it for HTML output
 * @class histview
 * @author Izzy (devel@izzysoft.de)
 * @copyright (c) 2003-2007 by Itzchak Rehberg and IzzySoft
 */
class histview {
  var $hv_version = "0.1.3";
  var $download= "http://www.izzysoft.de/ftp/net/div/izzysoft/hv.php";
  var $plus   = "+";
  var $minus  = "-";
  var $change = "*";
  var $bug    = "!";
  var $ver    = "v";
  var $ignore = array("\$","#","--","==");
  var $iplus   = "<IMG SRC='/icons/burst.gif' BORDER='0'>";
  var $iminus  = "<IMG SRC='/icons/transfer.gif' BORDER='0'>";
  var $ichange = "<IMG SRC='/icons/image1.gif' BORDER='0'>";
  var $ibug    = "<IMG SRC='/icons/alert.red.gif' BORDER='0'>";
  var $itar    = "<IMG SRC='/icons/box2.gif' BORDER='0'>";
  var $ideb    = "<IMG SRC='/icons/box2.gif' BORDER='0'>";
  var $irpm    = "<IMG SRC='/icons/box2.gif' BORDER='0'>";
  var $tarbase = "";
  var $debbase = "";
  var $rpmbase = "";
  var $basedir = "";
  var $relname = "";
  var $max_relnum = 9;
  var $arch    = "noarch";
  var $umark;  # user defined marks
  var $umarks; # user defined marks

  var $lastchange;
  var $input   = array(); # content of input file
  var $output  = array(); # HTML output
  var $version = array(); # array 1..n of objects w/ properties num,
                          #       array 1..n of object changes(mark,content)
  var $idx;               # index 1..n of last elements: object(ver,mark)

  /** Create an instance and read the input file into the internal array
   * @constructor histv
   * @param string infile input file name
   * @param optional basename basename for files (e.g. "histview" for histview-0.1.3-izzy1.noarch.rpm)
   */
  function histview($infile,$name="") {
    if (!empty($name)) $this->basename = $name;
    $this->lastchange = "Last modified: ".date("F d Y",filemtime($infile));
    $this->input = file($infile);
    $this->idx->ver  = 0;
    $this->idx->mark = 0;
    $this->copy    = "2003-2007 by <A HREF='http://www.qumran.org/homes/izzy/' TARGET='_blank'>"
                   . "Itzchak Rehberg</A> &amp; <A HREF='http://www.izzysoft.de/' "
                   . "TARGET='_blank'>IzzySoft</A>";
  }

  /** Process the input file
   * @class histview
   * @method process
   * @return boolean success
   */
  function process() {
    $lines = count($this->input);
    for ($i=0;$i<$lines;++$i) {
      $this->pline($this->input[$i]);
    }
  }

  /** Override default icon settings
   *  icons can either be a character/string or a complete IMG tag
   * @class histview
   * @method set_icon
   * @param optional string plus FeatureAdd Icon
   * @param optional string minus Removed stuff Icon
   * @param optional string change Changed stuff Icon
   * @param optional string bug BugFix Icon
   * @param optional string tar Tarball Icon
   * @param optional string deb Debian Icon
   * @param optional string rpm RPM Icon
   * @return boolean success
   */
  function set_icon($iplus="",$iminus="",$ichange="",$ibug="",$itar="",$ideb="",$irpm="") {
    $details = array("iplus","iminus","ichange","ibug","itar","ideb","irpm");
    foreach ($details as $var) {
      if ($$var!="") $this->$var = $$var;
    }
  }

  /** Override base URLs for archives. With $type='base' set the string to cut
   *  of to leave the download URL. Example: Your files are somewhere below
   *  /var/www/files/download, and your servers document root is /var/www, so
   *  you would specify "/var/www" here. If your files reside outside the
   *  servers document root, say below /var/ftp/download, you should create a
   *  directory alias called "/ftp/" pointing to /var/ftp, and specify "/var"
   *  here.
   * @method set_basedir
   * @param string type tar, deb, rpm or base
   * @param string dir the directory for this type
   */
  function set_basedir($type,$dir) {
    switch ($type) {
      case "tar"  : $this->tarbase = $dir; break;
      case "deb"  : $this->debbase = $dir; break;
      case "rpm"  : $this->rpmbase = $dir; break;
      case "base" : $this->basedir = $dir; break;
    }
  }

  /** Set the release extension for *.deb/*.rpm
   *  For the fictive package dummy-0.1.2-johnny3.noarch.rpm this would be "johnny"
   * @method set_relname
   * @param string relname
   */
  function set_relname($relname) {
    $this->relname = $relname;
  }

  /** Set the maximum release number
   *  To take our example from set_basedir again (dummy-0.1.2-johnny3.noarch.rpm),
   *  the relnum of that package is "3" (the number immediately following the
   *  release extension). To find the latest package, histview would "replace"
   *  this part by $i, counting down from max_relnum to 0 until it finds a file.
   * @method set_max_relnum
   * @parameter integer relnum
   */
  function set_max_relnum($num) {
  }

  /** Override default identifier mark settings
   *  Identifier marks are the characters used to identify the changes, such
   *  as a "+" for a new feature or a "!" for a bug
   * @class histview
   * @method set_mark
   * @param optional string plus FeatureAdd mark
   * @param optional string minus Removed stuff mark
   * @param optional string change Changed stuff mark
   * @param optional string bug BugFix mark
   * @param optional string ver Version mark
   * @return boolean success
   */
  function set_mark($plus="",$minus="",$change="",$bug="",$version="") {
    $details = array("plus","minus","change","bug","version");
    foreach ($details as $var) {
      if ($$var!="") $this->$var = $$var;
    }
  }

  /** Add another mark to the set
   * @class histview
   * @method add_mark
   * @param string name
   * @param string symbol
   * @param string icon
   * @return boolean success
   */
  function add_mark($name,$symbol,$icon) {
    if (isset($this->umark->$name)) return FALSE;
    if (strlen($symbol) != 1) return FALSE;
    $this->umark->$name->symbol = $symbol;
    $this->umark->$name->icon   = $icon;
    $this->umarks["$symbol"] = $name;
    return TRUE;
  }

  /** Process a single line from the input file
   * @class histview
   * @method pline
   * @param string line
   * @return boolean success
   */
  function pline($line) {
    $tline  = trim($line);
    $t1char = substr($tline,0,1);
    $t2char = substr($tline,1,1);
    $first  = substr($line,0,1);
    # strip off the ignored lines (empty ones and comments)
    if ( empty($tline)  ||
         in_array($t1char,$this->ignore)  ||
         in_array($t1char.$t2char,$this->ignore) ) return TRUE;
    switch ($t1char) {
      case $this->ver    : if ( (is_numeric($t2char)) ) {
                       ++$this->idx->ver;
                       $this->idx->mark = 0;
                       $this->version[$this->idx->ver]->num = $tline;
                       return TRUE;
                     } else {
		       $this->version[$this->idx->ver]->changes[$this->idx->mark]->content .= " $tline";
		     }
                     break;
      case $this->plus   : ++$this->idx->mark;
                     $this->version[$this->idx->ver]->changes[$this->idx->mark]->mark = $this->iplus;
                     $this->version[$this->idx->ver]->changes[$this->idx->mark]->content = substr($tline,1);
                     return TRUE; break;
      case $this->minus  : ++$this->idx->mark;
                     $this->version[$this->idx->ver]->changes[$this->idx->mark]->mark = $this->iminus;
                     $this->version[$this->idx->ver]->changes[$this->idx->mark]->content = substr($tline,1);
                     return TRUE; break;
      case $this->change : ++$this->idx->mark;
                     $this->version[$this->idx->ver]->changes[$this->idx->mark]->mark = $this->ichange;
                     $this->version[$this->idx->ver]->changes[$this->idx->mark]->content = substr($tline,1);
                     return TRUE; break;
      case $this->bug    : ++$this->idx->mark;
                     $this->version[$this->idx->ver]->changes[$this->idx->mark]->mark = $this->ibug;
                     $this->version[$this->idx->ver]->changes[$this->idx->mark]->content = substr($tline,1);
                     return TRUE; break;
      default      : # first we need to check for user defined marks now
                     if (isset($this->umarks["$t1char"]) && $t2char==" ") {
                       ++$this->idx->mark;
                       $name = $this->umarks["$t1char"];
                       $this->version[$this->idx->ver]->changes[$this->idx->mark]->mark = $this->umark->$name->icon;
                       $this->version[$this->idx->ver]->changes[$this->idx->mark]->content = substr($tline,1);
                       return TRUE; break;
                     }
                     # now we can be sure it is just a continued line
                     if(isset($this->version[$this->idx->ver]))
                     $this->version[$this->idx->ver]->changes[$this->idx->mark]->content .= " $tline";
    }
  }

  /** Check whether there is a file to download - and create URL if any
   * @method getdlurl
   * @param string type Type (one of tar, deb, rpm)
   * @return string href complete href string if found, empty string else
   */
  function getdlurl($type,$fname,$version) {
    $img = array("tar"=>$this->itar,"deb"=>$this->ideb,"rpm"=>$this->irpm);
    $pos = strpos($version,"(");
    switch ($type) {
      case "tar" : $f = trim($this->tarbase."/${fname}-".substr($version,1,$pos-2)).".tar.gz"; break;
      case "deb" : for ($i=$this->max_relnum;$i>=0;--$i) {
                     $f = trim($this->debbase."/${fname}_".substr($version,1,$pos-2))."-".$this->relname.$i."_";
                     if ($this->arch=="noarch") $f .= "all.deb";
		     else $f .= $this->arch.".deb";
		     if (file_exists($f)) break;
		   }
		   break;
      case "rpm" : for ($i=$this->max_relnum;$i>=0;--$i) {
    		     $f = trim($this->rpmbase."/${fname}-".substr($version,1,$pos-2))."-".$this->relname.$i.".".$this->arch.".rpm";
		     if (file_exists($f)) break;
		   }
		   break;
    }
    if (file_exists($f)) {
      $f = substr($f,strlen($this->basedir));
      $f = "<A HREF='$f'>";
      if (!empty($img[$type])) $f .= $img[$type]; else $f .= $type;
      $f .= "</A>";
      return $f;
    }
    return "";
  }

  /** Generate the output array
   * @class histview
   * @method out
   * @return array HTML formatted history
   */
  function out() {
    $output = "<DIV ALIGN='center'><FONT SIZE='-2'>" . $this->lastchange
            . "</FONT></DIV>\n"
            . "<TABLE WIDTH='95%' BORDER='0' ALIGN='center'>\n";
    $vers = count($this->version);
    for ($i=1;$i<=$vers;++$i) {
      if (!empty($this->tarbase)) $tarfile = $this->getdlurl("tar",$this->basename,$this->version[$i]->num);
      if (!empty($this->debbase)) $debfile = $this->getdlurl("deb",$this->basename,$this->version[$i]->num);
      if (!empty($this->rpmbase)) $rpmfile = $this->getdlurl("rpm",$this->basename,$this->version[$i]->num);
      $dllink = "${tarfile}${debfile}${rpmfile}";
      if (!empty($dllink)) {
        $dllink = "<SPAN ALIGN='right'>$dllink</SPAN>";
        $output .= " <TR><TH COLSPAN='2'><TABLE WIDTH='100%' BORDER='0'><TR><TH>".$this->version[$i]->num."</TH><TH WIDTH='66px'>$dllink</TH></TR></TABLE></TH></TR>\n";;
      } else $output .= " <TR><TH COLSPAN='2'>".$this->version[$i]->num."</TH></TR>\n";;
      $chgs = count($this->version[$i]->changes);
      for ($k=1;$k<=$chgs;++$k) {
        $output .= " <TR><TD VALIGN='middle'>".$this->version[$i]->changes[$k]->mark."</TD>\n"
                .  "     <TD VALIGN='middle'>".$this->version[$i]->changes[$k]->content."</TD></TR>\n";
      }
    }
    $output .= " <TR><TH COLSPAN='2'></TH>\n <TR><TD COLSPAN='2'><DIV ALIGN='center'><FONT SIZE='-2'>"
            .  "Generated by <A HREF='".$this->download."'>HistView</A> v"
            .  $this->hv_version." &copy; ".$this->copy
            .  "</FONT></DIV></TD></TR>\n";
    $output .= "</TABLE>\n";
    return $output;
  }

}
?>