
 wxFreeChart Development Version ReadMe
 ======================================

Official Website: <a href="http://wxcode.sourceforge.net/components/freechart" target="_blank">wxCode</a>
Original Author: Moskvichev Andrey V.
 
**IMPORTANT**
This is a clone (not fork) from the pbfordev/wxFreeChart repository, which is itself a clone of the original sourceforge code.
 
This particular repository is under constant development for the next few months and may contain numerous bugs or fail to even compile at times. Also, the API may well change in the near future and at some point diverge from the original API.
 
Nonetheless, any bug reports, comments or discussions on the API are very welcome :)
 
Description
-----------
wxFreeChart is free powerful charting framework based on wxWidgets. 
It designed with flexibility in mind, and supports many types of charts with many different configurations.

Some reasonably up-to-date documentation can be found here: https://iwbnwif.github.io/freechart_docs/html/index.html

The currently supported chart types are:
- Line/histogram/area charts based on xy coordinates
- Bar charts (vertical or horizontal)
- Stacked bar charts
- Layered bar charts
- OHLC financial charts (bars or candlesticks)
- Pie charts
- Bubble charts
- Gantt charts 

Installation - win32
--------------------

When building on win32, you can use the makefiles in the BUILD folder using the
WX_DIR, WX_DEBUG, WX_UNICODE and WX_SHARED to match your wxWidgets build.
Examples:

  > nmake -fmakefile.vc WX_DIR=c:\path\to\my\wxWidgets WX_UNICODE=0/1 WX_DEBUG=0/1 WX_SHARED=0/1 WX_MONOLITHIC=0/1
  > make -fmakefile.bcc WX_DIR=c:\path\to\my\wxWidgets WX_UNICODE=0/1 WX_DEBUG=0/1 WX_SHARED=0/1 WX_MONOLITHIC=0/1

Installation - unix
-------------------

When building on a Linux/GNU-based system, type

  > ./configure
  > make

To build against the default build of wxWidgets (the one listed as 'default' by wx-config --list). Type "./configure --help" for more info.

ChangeLog (for original project)
--------------------------------

1.7:
What's new:
- OHLCSimpleDataset was added
- MovingAvarage for OHLC was added
- ~~Windows installer was added~~
- Label colourer was added, to make possible axes labels have different colours
- OHLCColourer was added, so it's now possible to draw bars/candlesticks in different colours (from indicator values, etc)
- ~~Mouse zoom/pan was added~~
- ~~Chart mouse events was added~~
- ~~Tooltips support was added~~
- ~~Crosshair was added~~
- Many bugfixes
- Many API impovements
- Julian date axes was added (thanks to Carsten Arnholm)
- Pie plots (thanks to Grgory Soutad)
- OHLC charts improvements (now it's possible to control bars/candlesticks color from various conditions (indicator values, etc))
- Dynamic charts performance optimization
- TimeSeriesDataset was added
- Graphics rendering improvements, added drawing wrapper, to use wxGraphicsContext
- Demos updated
- ~~Will be new website with example docs and forum~~

1.6:
What's new:
- wxChartSplitPanel was added, it works with multiple plots,and allows add/remove/resize them
- XYDynamicDataset was added (thanks to Mike Sazonov)
- Basic markers support has been added
- Updated documentation
- Website update

1.5:
What's new:
- Logarithmic axes added (thanks to Andreas Kuechler)
- Updated demo
- DLL export problems fixed
- Updated documentation

1.4:
What's new:
- Added methods to access axis-dataset links to AxisPlot and Axis
- XYLineRenderer and XYAreaRenderer bugfixes
- Added XYLineStepRenderer class
- Added initial combined axes support (see AxisShare class)

1.3: 
What's new:
- Antialiasing added
- Axis improvements (added vertical text for labels)
- API changes: int replaced with size_t for indexes  

1.2: Third version of wxFreeChart at wxCode
What's new:
- Added xy datasets support to OHLCPlot
- Added XYSimpleDataset, CategorySimpleDataset, GanttSimpleDataset classes
- Many refactoring changes
- Many bugfixes
- Updated documentation
- Added time series, multiple axis and combined axis demos

1.1: Second version of wxFreeChart at wxCode
What's new:
- Many bugfixes
- Updated demos
- Major redesign
- Build system fixes

1.0 - First version of wxFreeChart at wxCode

Future plans
------------
- Transparency for bubble charts, histogram charts
- Add levels/fractals/etc support to OHLCPlot. Make OHLCPlot suitable for technical analysis applications
- Make axis marks drawing more flexible
- Add zoom to plots
- Add interval axes
- Statistics charts
- Mouse events for chart item click, right/left up/down, drag, etc
- Pie plots improvements: 3D charts, using wxGL, more flexible legend drawing
- Make wxFreeChart to work on handheld wxWidgets ports
 
Known issues
------------
- Window scrolling bugs
- Compdateaxis bugs
- Antialiasing doesn't work correctly with wxSHORT_DASH pen styles (on wxGTK port)

Help project
------------
Unfortunately, I have not enough time to work on project. 
You can help project development in following ways:
- Test it and write bugreports/bugfixes, especially test on MacOSX and WINCE ports.
- Write additional code and contribute it to project.
- Donate to support project development, click PayPal (tm) Donate button on wxFreeChart web site. 
 
Credits
-------
Mike Sazonov - Testing, export bugfixes, XYDynamicDataset implementation, many interesting ideas.
Andreas Kuechler - Testing, logarithmic axes implementation, many interesting ideas.
Alan Yaniger - Testing, performance optimization, many bugfixes, many useful patches.
Carsten Arnholm - Julian axes and dataset implementation.
Grgory Soutad - Pie plots and category renderer.
Carsten Arnholm - Julian date axes
