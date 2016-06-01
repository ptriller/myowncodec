#ifndef VIDEOCANVAS_H_
#define VIDEOCANVAS_H_

#include <wx/wxprec.h>

#ifndef WX_PRECOMP

#include <wx/wx.h>

#endif

#include <memory>
#include <chrono>

class VideoFrame;
class DirectoryReader;

class VideoCanvas : public wxPanel {
public:
    VideoCanvas(wxWindow *parent);

    void SetImage(VideoFrame *videoFrame);

    void paintEvent(wxPaintEvent &evt);

    void paintNow();

    void render(wxDC &dc);

    void SetDirectory(const wxString &str);

    wxString GetDirectory() { return directory; }

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
    std::unique_ptr<DirectoryReader> reader;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    wxString directory;

DECLARE_EVENT_TABLE()

};

#endif /* VIDEOCANVAS_H_ */
