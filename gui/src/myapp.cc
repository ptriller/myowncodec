#include "myapp.h"
#include "VideoCanvas.h"
enum
{
	ID_Open = wxID_HIGHEST +1,
	ID_Play,
	ID_Stop
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Open,   MyFrame::OnOpen)
    EVT_MENU(ID_Play,   MyFrame::OnPlay)
    EVT_MENU(ID_Stop,   MyFrame::OnStop)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(VideoCanvas, wxPanel)
// catch paint events
EVT_PAINT(VideoCanvas::paintEvent)

wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Hello World", wxPoint(50, 50), wxSize(450, 340) );
    frame->Show( true );
    return true;
}
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
	wxInitAllImageHandlers();
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Open, "&Open Directory...",
                     "Open File for playing");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    videoPanel = new VideoCanvas(this);
    hbox1->Add(videoPanel,1, wxEXPAND);
    vbox->Add(hbox1, 1, wxEXPAND);
    hbox2->Add(new wxButton(this, ID_Play, "Play"));
    hbox2->Add(new wxButton(this, ID_Stop, "Stop"));
    vbox->Add(hbox2, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);
    SetSizer(vbox);
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to wxWidgets!" );
}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is a wxWidgets' Hello world sample",
                  "About Hello World", wxOK | wxICON_INFORMATION );
}


void MyFrame::OnOpen(wxCommandEvent& event) {
	wxDirDialog dlg(this, "Movie Directory");
	dlg.ShowModal();
}

void MyFrame::OnPlay(wxCommandEvent& event) {
}

void MyFrame::OnStop(wxCommandEvent& event) {
}


