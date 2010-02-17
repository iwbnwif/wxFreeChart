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
  
	<br/><?php write_h1("wxFreeChart can draw following chart types"); ?>
	<ol>
		<li>Line XY charts.</li>
		<li>Histogram XY charts.</li>
		<li>Area XY charts.</li>
		<li>Bar charts.</li>
		<li>Stacked bar charts.</li>
		<li>Layered bar charts.</li>
		<li>OHLC bars financial charts.</li>
		<li>OHLC candlesticks financial charts.</li>
		<li>Bubble charts.</li>
		<li>Gantt charts.</li>
	</ol>
	
	<br/><?php write_h1("Features"); ?>
	<ol>
		<li>Easy to use: you create chart with minimal coding, only few lines to create charts with different configurations.</li>
		<li>High flexibility: you can create different types of charts with many different configurations.</li>
		<li>Charts scrolling.</li>
		<li>Multiple axes with different locations (top, bottom, left, right).</li>
		<li>Legend with different locations.</li>
		<li>Composite axes.</li>
		<li>Data markers: point, line, range.</li>
		<li>Axes font, text color, grid lines, chart lines, chart background - everything can be changed.</li>
		<li>Various visual features, like: gradient areas, gradient bars, etc.</li>
		<li>All-in-one solution. The same approach for different chart types.</li>
		<li>Multiplots.</li>
		<li>Clean MCV design. You can use different renderers to draw charts content, with many different data sources.</li>
		<li>High performance.</li>
		<li>Dynamic charting: data change triggers chart redrawing. No additional coding is needed.</li>
		<li>Charts can be saved as images or printed.</li>
		<li>Full documented code.</li>
		<li>Step-by-step detailed examples.</li>
	</ol>
	
	<br/><?php write_h1("Screenshots"); ?>
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
    <?php writeScreenshotLink("markers1.png", ""); ?>
    <?php writeScreenshotLink("combaxis1.png", ""); ?>
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
	<ul>
		 <li>Transparency for bubble charts, histogram charts.</li>
		 <li>Interval axes.</li>
		 <li>Add levels/fractals/etc support to OHLCPlot. Make OHLCPlot suitable for technical analysis applications.</li>
		 <li>Make axis marks drawing more flexible.</li>
		 <li>Add zoom to plots.</li>
		 <li>Crosshair.</li>
		 <li>Pie plots.</li>
		 <li>Statistical plots.</li>
		 <li>Make wxFreeChart to work on handheld wxWidgets ports.</li>
	</ul>
	
  <p> To submit a feature request please look at <a href="../../support.php">wxCode support page</a>.</p>


	<br/><?php require("footer.inc.php"); ?>
</html>
