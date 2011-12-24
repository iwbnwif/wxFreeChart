
 wxFreeChart ReadMe
 ------------------

 Website: http://wxcode.sourceforge.net/components/freechart
 Author: Moskvichev Andrey V.
 Version: 1.7
 Description:
 wxFreeChart is free powerful charting framework based on wxWidgets. 
 It designed with flexibility in mind, and supports many types of charts 
 with many different configurations.
 Supported chart types are:
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

  ./configure
  make
  
 to build against the default build of wxWidgets (the one listed as 'default'
 by wx-config --list). Type "./configure --help" for more info.



 ChangeLog
 ---------
 
 1.7: FIXIT it's upcoming release, here is plans
 		What's new:
 		 - Mouse zoom/pan was added
 		 - Chart mouse events was added
 		 - Tooltips support was added
 		 - Crosshair was added
 		 - Some minor bugs fixed
 		 - Many API impovements
 		 - Demos updated
 	
 1.6:
 		What's new:
 		 - wxChartSplitPanel was added, it works with multiple plots, 
 		   and allows add/remove/resize them
 		 - XYDynamicDataset was added (thanks to Mike Sazonov)
 		 - basic markers support has been added
 		 - updated documentation
 		 - website update
 		 
 1.5:
 		What's new:
 		 - logarithmic axes added (thanks to Andreas Kuechler)
 		 - updated demo
 		 - dll export problems fixed
 		 - updated documentation
 		 
 1.4:
 		What's new:
 		 - added methods to access axis-dataset links to AxisPlot and Axis
 		 - XYLineRenderer and XYAreaRenderer bugfixes
 		 - added XYLineStepRenderer class
 		 - added initial combined axes support (see AxisShare class)
 		 
 1.3: 
 		What's new:
 		 - antialiasing added
 		 - axis improvements (added vertical text for labels)
 		 - API changes: int replaced with size_t for indexes  
 		 
 1.2: third version of wxFreeChart at wxCode
 		What's new:
 		 - added xy datasets support to OHLCPlot
 		 - added XYSimpleDataset, CategorySimpleDataset, GanttSimpleDataset classes
 		 - many refactoring changes
 		 - many bugfixes
 		 - updated documentation
 		 - added time series, multiple axis and combined axis demos
 		 
 1.1: second version of wxFreeChart at wxCode
 		What's new:
 		 - many bugfixes
 		 - updated demos
 		 - major redesign
 		 - build system fixes
 

 1.0 - first version of wxFreeChart at wxCode

 Future plans:
 - Transparency for bubble charts, histogram charts
 - Add levels/fractals/etc support to OHLCPlot. Make 
   OHLCPlot suitable for technical analysis applications
 - Make axis marks drawing more flexible
 - Add zoom to plots
 - Add interval axes
 - Crosshair
 - Statistics charts
 - Mouse events for chart item click, right/left up/down, drag, etc
 - Pie plots 
 - Make wxFreeChart to work on handheld wxWidgets ports
 
 Known issues:
 - window scrolling bugs
 - compdateaxis bugs
 - Antialiasing doesn't work correctly with wxSHORT_DASH pen styles (on wxGTK port)
 - Pie plots are very ugly, and must be cleaned up or rewritten.

 Help project:
 Unfortunately, i have not enough time to work on project. 
 You can help project development in following ways:
 - Test it and write bugreports/bugfixes,
   especially test on MacOSX and WINCE ports.
 - Write additional code and contribute it to project.
 - Donate to support project development, 
   click PayPal (tm) Donate button on wxFreeChart web site. 
 
 Credits:
 	Mike Sazonov - testing, export bugfixes, XYDynamicDataset implementation, 
 					many interesting ideas.
 	
 	Andreas Kuechler - testing, logarithmic axes implementation, many interesting ideas.
 	
 	Alan Yaniger - testing, many bugfixes, many usefull patches.
 	
 	Carsten Arnholm - julian axes and dataset implementation.
 	
 	Grgory Soutad - pie plots and category renderer.
 	
 	
 Author contacts:
	email: mab[at]BitGriff[dot]com
	skype: mab_at_smtp_ru
