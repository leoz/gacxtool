<div id="contents">
<ul>
<?php 
$contents = array(
	'index.php' => 'News',
	'about.php' => 'About',
	'roadmap.php' => 'Roadmap',
	'shots.php' => 'Screen Shots',
	'download.php' => 'Download',
	'install.php' => 'Install',
	'usage.php' => 'Usage',
	'links.php' => 'Links',
	'http://sourceforge.net/projects/gacxtool/' => 'Summary'
);
function get_page_link($page, $name)
{
	if ($page == basename($_SERVER['PHP_SELF']))
		return "<li><b>$name</b></li>";
	else
		return "<li><a href=$page>$name</a></li>";
}
foreach ($contents as $key=>$value)
{
	echo get_page_link($key, $value);
}
?>
</ul>
</div>
