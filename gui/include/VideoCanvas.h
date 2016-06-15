#ifndef VIDEOCANVAS_H_
#define VIDEOCANVAS_H_

#include <wx/wxprec.h>

#ifndef WX_PRECOMP

#include <wx/wx.h>

#endif

#include <memory>
#include <chrono>

class VideoFrame;
class PmfDecoder;

class VideoCanvas : public wxPanel {
public:
    VideoCanvas(wxWindow *parent);

    void SetImage(VideoFrame *videoFrame);

    void paintEvent(wxPaintEvent &evt);

    void paintNow();

    void render(wxDC &dc);

    void SetFile(const wxString &str);

    wxString GetFile() { return file; }

    void StartPlaying();

    void StopPlaying();

    void OnTimer(wxTimerEvent &event);

private:
    wxTimer timer;
    wxCriticalSection lock;
    std::unique_ptr<wxImage> image;
    std::unique_ptr<wxBitmap> resized;
    std::unique_ptr<VideoFrame> frame;
    std::unique_ptr<VideoFrame> nextFrame;
    std::unique_ptr<PmfDecoder> reader;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    wxString file;

DECLARE_EVENT_TABLE()

};

#endif /* VIDEOCANVAS_H_ */
