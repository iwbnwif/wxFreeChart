/////////////////////////////////////////////////////////////////////////////
// Name:	demo.cpp
// Purpose: demo application implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "demo.h"

#include <wx/aui/aui.h>

#include <wx/aboutdlg.h>

class DemoTreeItemData : public wxTreeItemData
{
public:
	DemoTreeItemData(ChartDemo *demo)
	{
		m_demo = demo;
	}

	virtual ~DemoTreeItemData()
	{
	}

	ChartDemo *GetDemo()
	{
		return m_demo;
	}

private:
	ChartDemo *m_demo;
};

//
// ChartSelector
//

BEGIN_EVENT_TABLE(ChartSelector, wxTreeCtrl)
	EVT_TREE_ITEM_ACTIVATED(wxID_ANY, ChartSelector::OnTreeItemActivated)
END_EVENT_TABLE()

ChartSelector::ChartSelector(wxWindow *parent, wxChartPanel *chartPanel, DemoCollection *demoCollection)
: wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
	m_chartPanel = chartPanel;

	// create tree items for chart demos
	wxTreeItemId root = AddRoot(wxT("Charts"));

	for (int nCat = 0; nCat < demoCollection->GetCategoryCount(); nCat++) {
		wxTreeItemId catId = AppendItem(root, demoCollection->GetCategory(nCat));

		for (int nDemo = 0; nDemo < demoCollection->GetCategoryDemoCount(nCat); nDemo++) {
			ChartDemo *demo = demoCollection->GetCategoryDemo(nCat, nDemo);

			AppendItem(catId, demo->GetName(), -1, -1, new DemoTreeItemData(demo));
		}
	}

	Expand(root);
}

ChartSelector::~ChartSelector()
{
}

void ChartSelector::OnTreeItemActivated(wxTreeEvent &ev)
{
	DemoTreeItemData *demoItem = dynamic_cast<DemoTreeItemData *>(ev.GetClientObject());

	if (demoItem != NULL) {
		ChartDemo *demo = demoItem->GetDemo();

		m_chartPanel->SetChart(demo->Create());
	}
}

//
// MainFrame
//

enum
{
	MENU_FILE_EXPORT_TO_PS = 101,
	MENU_FILE_EXPORT_TO_PNG,
	MENU_FILE_ENABLE_ANTIALIAS,
};

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(MENU_FILE_EXPORT_TO_PS, MainFrame::OnExportToPS)
	EVT_MENU(MENU_FILE_EXPORT_TO_PNG, MainFrame::OnExportToPNG)
	EVT_MENU(MENU_FILE_ENABLE_ANTIALIAS, MainFrame::OnEnableAntialias)
	EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
END_EVENT_TABLE()

MainFrame::MainFrame()
: wxFrame(NULL, wxID_ANY, wxT("wxFreeChart demo 1.3"), wxDefaultPosition, wxSize(800, 445))
{
	wxAuiManager *auiMan = new wxAuiManager(this);

	m_chartPanel = new wxChartPanel(this);
	auiMan->AddPane(m_chartPanel,
			wxAuiPaneInfo().Center().BestSize(400, 400).CloseButton(false).Caption(wxT("chart")));

	ChartSelector *chartSelector = new ChartSelector(this, m_chartPanel, DemoCollection::Get());
	auiMan->AddPane(chartSelector,
			wxAuiPaneInfo().Left().Caption(wxT("chart types")).MinSize(350, 400).BestSize(350, 400).CloseButton(false));

	auiMan->Update();

	Centre();

	// Create main menu
	wxMenuBar *menuBar = new wxMenuBar();

	wxMenu *menuFile = new wxMenu();

	menuFile->Append(MENU_FILE_EXPORT_TO_PNG, wxT("Export to PNG"));
	menuFile->AppendSeparator();
	menuFile->AppendCheckItem(MENU_FILE_ENABLE_ANTIALIAS, wxT("Enable antialiasing"));
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT, wxT("E&xit"));

	wxMenu *menuHelp = new wxMenu();
	menuHelp->Append(wxID_ABOUT, wxT("&About"));

	menuBar->Append(menuFile, wxT("&File"));
	menuBar->Append(menuHelp, wxT("&Help"));

	SetMenuBar(menuBar);
}

MainFrame::~MainFrame()
{
}

void MainFrame::OnExportToPS(wxCommandEvent &WXUNUSED(ev))
{
	// TODO not implemented
}

void MainFrame::OnExportToPNG(wxCommandEvent &WXUNUSED(ev))
{
	Chart *chart = m_chartPanel->GetChart();
	if (chart != NULL) {
		wxFileDialog dlg(this, wxT("Choose file..."), wxEmptyString, wxEmptyString,
				wxString(wxT("PNG files (*.png)|*.png")), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

		if (dlg.ShowModal() != wxID_OK)
			return ;

		wxBitmap bitmap = m_chartPanel->CopyBackbuffer();
		bitmap.ConvertToImage().SaveFile(dlg.GetPath(), wxBITMAP_TYPE_PNG);
	}
	else {
		wxLogError(wxT("No chart chosen!"));
	}
}

void MainFrame::OnEnableAntialias(wxCommandEvent &ev)
{
	m_chartPanel->SetAntialias(ev.IsChecked());
}

void MainFrame::OnAbout(wxCommandEvent &WXUNUSED(ev))
{
	wxAboutDialogInfo about;
	about.SetName(wxT("wxFreeChart demo"));
	about.SetVersion(wxT("1.3"));
	about.SetDescription(wxT("This is wxFreeChart demo collection. It shows various chart types."));
	about.SetCopyright(wxT("Copyright (C) 2008-2009 Moskvichev Andrey V."));

	wxAboutBox(about);
}


void MainFrame::OnExit(wxCommandEvent &WXUNUSED(ev))
{
	Close();
}

/**
 * Demo application.
 */
class DemoApp : public wxApp
{
public:
	bool OnInit()
	{
		wxInitAllImageHandlers();

		MainFrame *mainFrame = new MainFrame();
		SetTopWindow(mainFrame);
		mainFrame->Show(true);
		return true;
	}
};

IMPLEMENT_APP(DemoApp);
