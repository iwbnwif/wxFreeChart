/////////////////////////////////////////////////////////////////////////////
// Name:	titledemos.cpp
// Purpose: xy demos
// Author:	Andreas Kuechler
// Created:	2010/03/23
// Copyright:	(c) 2010 Andreas Kuechler
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"

#include <wx/xy/xyplot.h>
#include <wx/xy/xylinerenderer.h>
#include <wx/xy/xysimpledataset.h>
#include <wx/axis/logarithmicnumberaxis.h>

#include <wx/title.h>

#include <wx/datetime.h>


class TitleDemo1 : public ChartDemo
{
public:
  TitleDemo1()
  : ChartDemo(wxT("Title Demo 1 - simple title"))
  {
  }

  virtual Chart* Create()
  {
    Header* simpleTitle = new Header(GetName());
    return new Chart(new XYPlot(), simpleTitle);
  }
};

class TitleDemo2 : public ChartDemo
{
public:
  TitleDemo2()
  : ChartDemo(wxT("Title Demo 2 - header and footer"))
  {
  }

  virtual Chart* Create()
  {
    Header* header = new Header();
    Footer* footer = new Footer();

    TextElement bottomLeft(wxDateTime::Now().FormatDate(), wxALIGN_LEFT);
    TextElement topCenter(GetName(), wxALIGN_CENTER_HORIZONTAL);
    TextElement topRight(wxT("Some description"), wxALIGN_RIGHT);

    header->AddElement(topCenter);
    header->AddElement(topRight);
    footer->AddElement(bottomLeft);

    return new Chart(new XYPlot(), header, footer);
  }
};

class TitleDemo3 : public ChartDemo
{
public:
  TitleDemo3()
  : ChartDemo(wxT("Title Demo 3 - fancy headline"))
  {
  }

  virtual Chart* Create()
  {
    Header* header = new Header();
    Footer* footer = new Footer();


    TextElement topCenter(GetName(), wxALIGN_CENTER, wxFont(16, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_SLANT,
                            wxFONTWEIGHT_BOLD, true));
    topCenter.SetColour(wxColour(255, 128, 0));

    TextElement bottomCenter(wxT("Some huge text"), wxALIGN_CENTER, wxFont(20, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL,
                            wxFONTWEIGHT_LIGHT, false));
    bottomCenter.SetColour(wxTheColourDatabase->Find(wxT("RED")));

    header->AddElement(topCenter);
    footer->AddElement(bottomCenter);

    return new Chart(new XYPlot(), header, footer);
  }
};


ChartDemo *titleDemos[] = {
  new TitleDemo1(),
  new TitleDemo2(),
  new TitleDemo3(),
};
int titleDemosCount = WXSIZEOF(titleDemos);
