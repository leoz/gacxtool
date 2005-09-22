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

<h2>Usage</h2>

<p>
GTK ACX Tool supports following command line arguments:
</p>

<p>
<b>gacxtool <i>&lt;interface&gt;</i></b>
<br/>
Interface name.
<br/>
Default value is 'acx0'.
</p>

<p>
<b>gacxtool -i <i>&lt;interface&gt;</i></b>
<br/>
Interface name.
<br/>
Default value is 'acx0'.
</p>

<p>
<b>gacxtool -b <i>&lt;bandwidth&gt;</i></b>
<br/>
This value is used for to set traffic history graph size.
<br/>
Default value is 256.
</p>

<p>
<b>gacxtool -d <i>&lt;delay&gt;</i></b>
<br/>
Number of timeouts before updating signal and traffic data.
<br/>
Default value is 1.
</p>

<p>
<b>gacxtool -h</b>
<br/>
Shows short help information.
</p>

<p>
<b>gacxtool -r</b>
<br/>
Switches off absolute values display in 'Signal' and 'Traffic' tabs.
<br/>
Default value is 'on'.
</p>

<p>
<b>gacxtool -v</b>
<br/>
Switches on console output.
<br/>
Default value is 'off'.
</p>

<p>
<b>gacxtool -t <i>&lt;timeout&gt;</i></b>
<br/>
Driver poll timeout in milliseconds.
<br/>
Default value is 100.
</p>

<p>
These arguments could be used in any combination.
<br/>
If your interface is <b>acx0</b> than you can use <b>gacxtool</b> without any arguments.
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
	$Id: usage.php,v 1.1 2005-09-22 20:51:43 zoleo Exp $
</div>
</body>
</html>
