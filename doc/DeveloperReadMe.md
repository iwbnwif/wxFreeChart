EVENTS
======
A while back, I asked on the forum for some help in understanding wxWidgets event mechanism. Thanks to T-Rex, Doublemax and
others I got a pretty good understanding and was able to put together some code fragments for a subscriber mechanism that
may come in useful here.

First, I created a thread - MyThread - as follows:

```
class MyThread : public wxThread
{
public:
    MyThread(wxFrame* parent)
    {
        m_pParent = parent;
    }
    
    MyThread(wxMessageQueue<wxVector<wxString> >* queue)
    {
        m_pParentQueue = queue;
    }
    
    virtual ExitCode Entry
    {
        for (int n = 0; n < 5000; n++)
        {
            this->Sleep(500);
            
            // Create some data to send.
            int row = rand() % 10;
            wxString value = (wxString::Format("%d", rand() % 100));

            // Create an event to send.
            wxCommandEvent* event = new wxCommandEvent(wxEVT_COMMAND_TEXT_UPDATED, NUMBER_UPDATE_ID);
            event->SetInt(row); 
            event->SetString(value);
            
            // Send the event to the main frame's event handler.
            wxQueueEvent(wxTheApp->GetTopWindow(), event);
        }
        return 0;  
    }

private:
    wxFrame* m_pParent;
    wxMessageQueue<wxVector<wxString> >* m_pParentQueue;
};
```

This just runs in the background and every 500ms sends an event to the main window's (MainFrame) wxEventHandler. In another 
version (you will see from the first ctor) I arranged it so the thread could send the event to any window's wxEventHandler.

The main window contains a wxGrid (pointed to by m_pGrid) and a ctor like this:

```
void MainFrame::OnNumberUpdate (wxCommandEvent& event)
{
    m_pGrid->SetCellValue (event.GetInt(), 0, event.GetString());
    event.Skip ();
}
```

ViewFrame has two methods bound to m_pSubscribe and m_pUnsubscribe clicks as follows:


```
void ViewFrame::OnSubscribe (wxCommandEvent& event)
{
    wxTheApp->Bind (wxEVT_COMMAND_TEXT_UPDATED, &ViewFrame::OnNumberUpdate, this, NUMBER_UPDATE_ID);
}

void ViewFrame::OnUnsubscribe (wxCommandEvent& event)
{
    wxTheApp->Unbind (wxEVT_COMMAND_TEXT_UPDATED, &ViewFrame::OnNumberUpdate, this, NUMBER_UPDATE_ID);
}
```

