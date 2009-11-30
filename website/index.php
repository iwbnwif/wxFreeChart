<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<?php
  ////////////////////////////////////////////////////////////////////////////////////////////
  // Author: Moskvichev Andrey V.
  // Creation date: 10/11/2008
  // RCS-ID: $Id: index.php,v 1.7 2005/09/01 22:26:16 frm Exp $
  // Notes: the index page of the website of this component
  ////////////////////////////////////////////////////////////////////////////////////////////
?>

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en-AU">
	<?php
      $compname = "wxFreeChart";
      $subdir = "freechart";
      require("compwebsite.inc.php");
  ?>

	<!-- NOTE on the write_h1() php function:
	 - first arg: the label of the h1 tag
	 - second arg: the ID of the h1 tag (defaults to "")
	 - third arg: if TRUE the TOP link is added; if FALSE it is omitted (defaults to TRUE)
	 use FALSE as third arg for the first h1 tag of the page since it must
	 not have the TOP link...
  -->

	<br/><?php write_h1("Screenshots"); ?>
	<p>Description</p>
  <div class="center">
    <?php writeScreenshotLink("bars1.png", ""); ?>
    <?php writeScreenshotLink("bars2.png", ""); ?>
    <?php writeScreenshotLink("bars3.png", ""); ?>
    <?php writeScreenshotLink("bars4.png", ""); ?>
    <?php writeScreenshotLink("bubble1.png", ""); ?>
    <?php writeScreenshotLink("gantt1.png", ""); ?>
    <?php writeScreenshotLink("gantt2.png", ""); ?>
    <?php writeScreenshotLink("multaxis1.png", ""); ?>
    <?php writeScreenshotLink("ohlc1.png", ""); ?>
    <?php writeScreenshotLink("xy1.png", ""); ?>
    <?php writeScreenshotLink("xy2.png", ""); ?>
    <?php writeScreenshotLink("xy3.png", ""); ?>
  </div>


  <!-- NOTE TO THE DOCUMENTATION: for uploading you component docs in the website,
       see the ReadMe.txt file at wxCode\template... -->
  <br/><?php write_h1("Documentation"); ?>
  <p>The documentation for this component is available online
  <a href="../../docs/freechart/">here</a>.</p>

	<br/><?php write_h1("Support project"); ?>
	<p>Donate to support project development</p><br/>
	<form action="https://www.paypal.com/cgi-bin/webscr" method="post">
<input type="hidden" name="cmd" value="_s-xclick">
<input type="hidden" name="hosted_button_id" value="10094632">
<input type="image" src="https://www.paypal.com/en_US/i/btn/btn_donateCC_LG.gif" border="0" name="submit" alt="PayPal - The safer, easier way to pay online!">
<img alt="" border="0" src="https://www.paypal.com/ru_RU/i/scr/pixel.gif" width="1" height="1">
</form>
	

	<br/><?php write_h1("Known bugs"); ?>
  <p>None. To submit a bug report please look at <a href="../../support.php">wxCode support page</a>.</p>


	<br/><?php write_h1("Future enhancements"); ?>
  <p>None. To submit a feature request please look at <a href="../../support.php">wxCode support page</a>.</p>


	<br/><?php require("footer.inc.php"); ?>
</html>
