<?
 #############################################################################
 # HistView                                      (c) 2003 by Itzchak Rehberg #
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
 * @copyright (c) 2003 by Itzchak Rehberg and IzzySoft
 */
class histview {
  var $hv_version = "0.1.1";
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

  var $lastchange;
  var $input   = array(); # content of input file
  var $output  = array(); # HTML output
  var $version = array(); # array 1..n of objects w/ properties num,
                          #       array 1..n of object changes(mark,content)
  var $idx;               # index 1..n of last elements: object(ver,mark)

  /** Create an instance and read the input file into the internal array
   * @constructor histv
   * @param string infile input file name
   */
  function histview($infile) {
    $this->lastchange = "Last modified: ".date("F d Y",filemtime($infile));
    $this->input = file($infile);
    $this->idx->ver  = 0;
    $this->idx->mark = 0;
    $this->copy    = "2003 by <A HREF='http://www.qumran.org/homes/izzy/' TARGET='_blank'>"
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
   * @return boolean success
   */
  function set_icon($iplus="",$iminus="",$ichange="",$ibug="") {
    $details = array("iplus","iminus","ichange","ibug");
    foreach ($details as $var) {
      if ($$var!="") $this->$var = $$var;
    }
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
      default      : $this->version[$this->idx->ver]->changes[$this->idx->mark]->content .= " $tline";
    }
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
      $output .= " <TR><TH COLSPAN='2'>".$this->version[$i]->num."</TH></TR>\n";;
      $chgs = count($this->version[$i]->changes);
      for ($k=1;$k<=$chgs;++$k) {
        $output .= " <TR><TD VALIGN='middle'>".$this->version[$i]->changes[$k]->mark."</TD>\n"
                .  "     <TD VALIGN='middle'>".$this->version[$i]->changes[$k]->content."</TD></TR>\n";
      }
    }
    $output .= " <TR><TD COLSPAN='2'><DIV ALIGN='center'><FONT SIZE='-2'>"
            .  "Generated by <A HREF='".$this->download."'>HistView</A> v"
            .  $this->hv_version." &copy; ".$this->copy
            .  "</FONT></DIV></TD></TR>\n";
    $output .= "</TABLE>\n";
    return $output;
  }

}
?>