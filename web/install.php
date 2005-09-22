<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
          "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html lang="en">
<?php include("frames/head.php"); ?>
<body>
<?php include("frames/header.php"); ?>
<div id="container">
<div id="content">
<?php include("frames/left_bar.php"); ?>
<div id="main">

<h2>Install</h2>

For to use this tool you need these ports to be installed:
<ul>
<li><span class="path">net/acx100</span></li>
<li><span class="path">x11-toolkits/gtkdatabox2</span></li>
</ul>

<p>
The easiest way to install this program is just to download full package,
extract it somewhere and type in the extracted directory 'make install' as root user.
</p>
<p>
NOTE: Source distribution will not currently build because of the missed header.
You need to take this file from acx100 source tarball in case if you would like to build the program by yourself.
</p>
<p>
It is advisable to use full or binary package from this page unless acx100 port will provide headers.
</p>

<p>
To contact <a href="mailto:leoz@saunalahti.fi">mail me</a>.
</p>

</div>	
</div>
</div>
<?php include("frames/right_bar.php"); ?>
<?php include("frames/links_bar.php"); ?>
<div class="clearing"> </div>
<div id="footer">
	&copy; 2004 - 2005 Leonid Zolotarev. All rights reserved.
	<br/>
	$Id: install.php,v 1.1 2005-09-22 20:51:43 zoleo Exp $
</div>
</body>
</html>
