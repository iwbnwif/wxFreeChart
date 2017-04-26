/////////////////////////////////////////////////////////////////////////////
// Name:    demo.cpp
// Purpose: demo application implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2009 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "demo.h"

#include <wx/aboutdlg.h>

static wxString version = wxT("1.7");

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
    m_currentDemo = NULL;

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

        if (m_currentDemo != NULL)
            m_currentDemo->CleanUp();
        
        m_currentDemo = demoItem->GetDemo();

        m_chartPanel->SetChart(m_currentDemo->Create());
    }
}

//
// MainFrame
//

enum
{
    MENU_FILE_SAVE_AS_PNG = 101,
    MENU_FILE_ENABLE_ANTIALIAS,
};

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(MENU_FILE_SAVE_AS_PNG, MainFrame::OnSaveAsPNG)
    EVT_MENU(MENU_FILE_ENABLE_ANTIALIAS, MainFrame::OnEnableAntialias)
    EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
    EVT_MENU(wxID_EXIT, MainFrame::OnExit)
END_EVENT_TABLE()

MainFrame::MainFrame()
: wxFrame(NULL, wxID_ANY, wxString::Format(wxT("wxFreeChart demo %s"), version.c_str()), wxDefaultPosition, wxSize(800, 445))
{    
    m_mgr.SetManagedWindow(this);
    
    m_chartPanel = new wxChartPanel(this);
    m_mgr.AddPane(m_chartPanel,
            wxAuiPaneInfo().Center().BestSize(400, 400).CloseButton(false).Caption(wxT("chart")));

    ChartSelector *chartSelector = new ChartSelector(this, m_chartPanel, DemoCollection::Get());
    m_mgr.AddPane(chartSelector,
            wxAuiPaneInfo().Left().Caption(wxT("chart types")).MinSize(350, 400).BestSize(350, 400).CloseButton(false));

    m_mgr.Update();

    // Create main menu
    wxMenuBar *menuBar = new wxMenuBar();

    wxMenu *menuFile = new wxMenu();

    menuFile->Append(MENU_FILE_SAVE_AS_PNG, wxT("Save as PNG"));
    menuFile->AppendSeparator();

#ifdef wxUSE_GRAPHICS_CONTEXT
    menuFile->AppendCheckItem(MENU_FILE_ENABLE_ANTIALIAS, wxT("Enable antialiasing"));
    menuFile->Check(MENU_FILE_ENABLE_ANTIALIAS, true);
    m_chartPanel->SetAntialias(true);
    menuFile->AppendSeparator();
#endif

    menuFile->Append(wxID_EXIT, wxT("E&xit"));


    wxMenu *menuHelp = new wxMenu();
    menuHelp->Append(wxID_ABOUT, wxT("&About"));

    menuBar->Append(menuFile, wxT("&File"));
    menuBar->Append(menuHelp, wxT("&Help"));

    SetMenuBar(menuBar);

    Centre();
}

MainFrame::~MainFrame()
{
    m_mgr.UnInit();
}

void MainFrame::OnSaveAsPNG(wxCommandEvent &WXUNUSED(ev))
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
        wxLogError(wxT("No chart is chosen!"));
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
    about.SetVersion(version);
    about.SetDescription(wxT("This is wxFreeChart demo collection. It shows various chart types."));
    about.SetCopyright(wxT("Copyright (C) 2008-2012 Moskvichev Andrey V."));

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
