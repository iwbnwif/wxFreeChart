
 wxFreeChart ReadMe
 ------------------

 Website: http://wxcode.sourceforge.net/components/freechart
 Author: Moskvichev Andrey V.
 Version: 1.1
 Description:
 wxFreeChart is free charting library based on wxWidgets. It 
 designed with flexibility in mind, and has MCV design.
 Supported chart types are:
 - line/histogram charts base on xy coordinates
 - bar charts (vertical or horizontal)
 - stacked bar charts
 - layered bar charts
 - OHLC financial charts (bars or candlesticks)
 - pie charts
 - bubble charts
 

 Installation - win32
 --------------------

 When building on win32, you can use the makefiles in the BUILD folder using the
 WX_DIR, WX_DEBUG, WX_UNICODE and WX_SHARED to match your wxWidgets build.
 Examples:

   > nmake -fmakefile.vc WX_DIR=c:\path\to\my\wxWidgets WX_UNICODE=0/1 WX_DEBUG=0/1 WX_SHARED=0/1
   > make -fmakefile.bcc WX_DIR=c:\path\to\my\wxWidgets WX_UNICODE=0/1 WX_DEBUG=0/1 WX_SHARED=0/1



 Installation - unix
 -------------------

 When building on a Linux/GNU-based system, type

  cd build
  make -f GNUmakefile 
  
 to build against the default build of wxWidgets (the one listed as 'default'
 by wx-config --list). Type "./configure --help" for more info.



 ChangeLog
 ---------
 
 1.2: third version of wxFreeChart at wxCode
 		What's new:
 		 - added xy datasets support to OHLCPlot
 		 - axes draw when legend shown bug fixed
 		 - updated documentation
 		 - added time series and combined axis demos
 		 
 1.1: second version of wxFreeChart at wxCode
 		What's new:
 		 - many bugfixes
 		 - updated demos
 		 - major redesign
 		 - build system fixes
 

 1.0 - first version of wxFreeChart at wxCode

 Future plans:
 - Transparency for bubble charts, histogram charts.
 - Markers
 - Add levels/fractals/etc support to OHLCPlot. Make 
   OHLCPlot suitable for technical analysis applications.
 - Make antialiasing
 - Logorithmic axes
 - Make axis marks drawing more flexible.

 
 Known issues:
 - window scrolling bugs
 - compdateaxis bugs
 - axes sometimes drawn not correctly in case of Gantt charts
 - markers not implemented
 - Work with wxWidgets 2.6.x not tested.
 - I can test only wxMSW (on Windows XP, Windows Vista), and wxGTK (on Linux).
 - Antialiasing not implemented
 - Pie plots are very ugly, and must be cleaned up or rewritten.
 - Transparency not implemented. Needed for area/histogram charts with
   overlaying areas/histograms, etc.

 [optionally: Known bugs, Author's info, ... ]

 Author contact email: mab[at]smtp[dot]ru

