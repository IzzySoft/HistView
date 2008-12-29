# =============================================================================
# HistView                             (c) 2003 by IzzySoft (devel@izzysoft.de)
# -----------------------------------------------------------------------------
# $Id$
# -----------------------------------------------------------------------------
# Display history file of development packages  
# =============================================================================

Contents
--------

1) What it is
2) Copyright and warranty
3) Requirements
4) Limitations
5) Installation
6) Configuration
6) Usage

===============================================================================

1) What it is
-------------

When developing some piece of software, one usually records its development
history in an ASCII file, preceding all changes with a "hint" of the kind of
change - such as an "+" for a new addition, or a "!" for a bug fix. After a
while, one decides to release the package. And a while later the question
arises, how to present the latest changes to users who wish to see the list
of changes first to decide whether it's worth to update.
At this moment, one can just place the plain text file somewhere accessible
on the net - but wouldn't it look smarter to have it formatted as a nice
HTML document? If you would like this, but don't want to waste time rewriting
the history in HTML, HistView ist for you: it just reads in the history file,
and formats it in HTML. Provided you use a style similiar to what I do :)

===============================================================================

2) Copyright and Warranty
-------------------------

This little program is (c)opyrighted by Andreas Itzchak Rehberg
(devel@izzysoft.de) and protected by the GNU Public License Version 2 (GPL).
For details on the License see the file LICENSE in this directory. The
contents of this archive may only be distributed all together.

===============================================================================

3) Requirements
---------------

You need PHP 4 to use this piece of software. Further requirements are those
of PHP 4 itself - and some Web server that supports PHP 4.

===============================================================================

4) Limitations
--------------

Up to a certain degree, your history files must look like mine - I mean,
syntactically. That is, each line must be clearly identifyable:
Lines starting with "#", "$" or "--" are treated as comments and are ignored
(you may configure these "identifiers" inside of histview.inc to add/remove
identifiers). The line naming the version must have a distinct identifier
(I use the syntax "v<version-number>", so the "v" is the identifier here).
All identifiers can be configured via the histview::set_mark() method. See
the example histview.php included with this package for more information.

===============================================================================

5) Installation
---------------

Very easy: just copy the *.inc files somewhere into your PHP include path (but
keep them together in the same directory). If the local path (".") is in this
list, you may also decide to put them all into the same directory as your
calling page (in the example: histview.php).

===============================================================================

6) Configuration
----------------

An example configuration file is provided with class.hvconfig.inc. All settings
are well commented there, so you can see what they mean. Most of them have
defaults which should fit in ~90% of all cases. If you need to define different
values for the one or other, this is better done in a separate file named
hv-localconf.inc - which must reside in the very same directory the other
configuration file is placed into. If that file exists, it will automagically
be included into the distributed configuration file, so the default settings
will be overridden - but your personal settings will remain intact when
updating to a newer version, though the configuration file may be updated with
additional settings, again having suitable defaults.

===============================================================================

7) Usage
--------

As example, I provided histview.php with this package - which is set up to
display histview.hist (the history file of HistView) as default. You can use
this file for a quick start.
For a complete reference to the methods, please refer to the Api documentation
shipping with the distribution.


Have fun!
Izzy.
