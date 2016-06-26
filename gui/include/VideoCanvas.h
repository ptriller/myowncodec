#ifndef VIDEOCANVAS_H_
#define VIDEOCANVAS_H_

#include <wx/wxprec.h>

#ifndef WX_PRECOMP

#include <wx/wx.h>

#endif

#include <memory>
#include <chrono>
#include "codecapi.h"


class VideoCanvas : public wxPanel {
public:
    VideoCanvas(wxWindow *parent);

    void SetImage(codec::VideoFrame *videoFrame);

    void paintEvent(wxPaintEvent &evt);

    void paintNow();

    void render(wxDC &dc);

    void SetSource(const wxString &str);

    wxString GetSource() { return source; }

    void StartPlaying();

    void StopPlaying();

    void OnTimer(wxTimerEvent &event);

private:
    wxTimer timer;
    wxCriticalSection lock;
    std::unique_ptr<wxImage> image;
    std::unique_ptr<wxBitmap> resized;
    std::unique_ptr<codec::VideoFrame> frame;
    std::unique_ptr<codec::VideoFrame> nextFrame;
    std::unique_ptr<codec::VideoStream> reader;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    wxString source;

DECLARE_EVENT_TABLE()

};

#endif /* VIDEOCANVAS_H_ */
