//
// Created by ptriller on 01.06.2016.
//

#ifndef MYOWNCODEC_VIDEOPLAYER_H
#define MYOWNCODEC_VIDEOPLAYER_H
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class VideoCanvas;

class VideoPlayer: public wxFrame {
public:
    VideoPlayer(const wxString &title, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);

    virtual ~VideoPlayer();

    void OnOpen(wxCommandEvent &event);
    void OnPlay(wxCommandEvent &event);
    void OnStop(wxCommandEvent &event);
    void OnClose(wxCloseEvent &event);

private:
    VideoCanvas *canvas;
    wxButton *openButton;
    wxButton *playButton;
    wxButton *stopButton;
    wxDECLARE_EVENT_TABLE();

};


#endif //MYOWNCODEC_VIDEOPLAYER_H
