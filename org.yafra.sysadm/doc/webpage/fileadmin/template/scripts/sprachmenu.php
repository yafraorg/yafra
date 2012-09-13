<?php

/***************************************************************
*  Copyright notice
*
*  (c) 1999-2002 Kasper Skårhøj (kasper@typo3.com)
*  All rights reserved
*
*  This script is part of the Typo3 project. The Typo3 project is
*  free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  The GNU General Public License can be found at
*  http://www.gnu.org/copyleft/gpl.html.
*  A copy is found in the textfile GPL.txt and important notices to the license
*  from the author is found in LICENSE.txt distributed with these scripts.
*
*
*  This script is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  This copyright notice MUST APPEAR in all copies of the script!
***************************************************************/
/**
 * sprachmenu.php
 *
 * THIS IS AN EXAMPLE designed to work with the official Typo3 Quickstart
 *
 * @author	Patrik Bitzer <kaepten@c-dev.ch>
 */



 // First, select all pages_language_overlay records on the current page. Each represents a possibility for a language.
$query = "SELECT * FROM pages_language_overlay WHERE pid=".$GLOBALS["TSFE"]->id.$GLOBALS["TSFE"]->sys_page->enableFields("pages_language_overlay")." GROUP BY sys_language_uid";

$res = mysql(TYPO3_db,$query);
$langArr=array();
while($row=mysql_fetch_assoc($res))	{
	$langArr[$row["sys_language_uid"]]=$row["title"];
}

$flags = array();
if ($GLOBALS["TSFE"]->sys_language_uid==0) {
// ENGLISH default - show choice german
$flags[] = '<a href="index.php?id='.$GLOBALS["TSFE"]->id.'&L=2" target=_top>DE</a>';
} elseif ($GLOBALS["TSFE"]->sys_language_uid==2) {
// german selected - show ENGLISH
$flags[] = '<a href="index.php?id='.$GLOBALS["TSFE"]->id.'&L=0" target=_top>EN</a>';
}

// Macht die Ausgabe. Das Menü transferitert die page-id und die "L" variable zur Sprachsteuerung
$content = implode("",$flags);

?>

