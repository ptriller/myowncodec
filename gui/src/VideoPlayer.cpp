//
// Created by ptriller on 01.06.2016.
//

#include "VideoPlayer.h"
#include "VideoCanvas.h"
enum {
    ID_Play = wxID_HIGHEST + 300,
    ID_Stop,
    ID_Open
};

wxBEGIN_EVENT_TABLE(VideoPlayer, wxFrame)
    EVT_BUTTON(ID_Open, VideoPlayer::OnOpen)
    EVT_BUTTON(ID_Stop, VideoPlayer::OnStop)
    EVT_BUTTON(ID_Play, VideoPlayer::OnPlay)
    EVT_CLOSE(VideoPlayer::OnClose)
wxEND_EVENT_TABLE()

VideoPlayer::~VideoPlayer() { }

VideoPlayer::VideoPlayer(const wxString &title, const wxPoint &pos, const wxSize &size)
        :wxFrame(nullptr, wxID_ANY, title, pos, size ) {
    wxPanel *panel = new wxPanel(this);
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hboxTop = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hboxBottom= new wxBoxSizer(wxHORIZONTAL);
    canvas = new VideoCanvas(panel);
    hboxTop->Add(canvas, 1, wxEXPAND);
    vbox->Add(hboxTop, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT);
    vbox->AddSpacer(5);
    openButton = new wxButton(panel, ID_Open, wxT("Open"));
    hboxBottom->Add(openButton);
    playButton = new wxButton(panel, ID_Play, wxT("Play"));
    playButton->Disable();
    hboxBottom->Add(playButton);
    stopButton = new wxButton(panel, ID_Stop, wxT("Stop"));
    stopButton->Disable();
    hboxBottom->Add(stopButton);
    vbox->Add(hboxBottom, 0, wxBOTTOM | wxCENTER);
    panel->SetSizer(vbox);
    CreateStatusBar();
}

void VideoPlayer::OnOpen(wxCommandEvent &) {
    wxDirDialog dirDialog(nullptr, wxT("Select Video Data Folder"), canvas->GetSource(),
                          wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if(dirDialog.ShowModal() == wxID_OK) {
        canvas->SetSource(dirDialog.GetPath());
        playButton->Enable(true);
    }
}

void VideoPlayer::OnPlay(wxCommandEvent &) {
    openButton->Disable();
    stopButton->Enable();
    playButton->Disable();
    canvas->StartPlaying();
}

void VideoPlayer::OnStop(wxCommandEvent &) {
    canvas->StopPlaying();
    openButton->Enable();
    stopButton->Disable();
    playButton->Enable();

}

void VideoPlayer::OnClose(wxCloseEvent &) {
    Destroy();
}
