#ifndef VIDEOCANVAS_H_
#define VIDEOCANVAS_H_

#include <wx/wxprec.h>

#ifndef WX_PRECOMP

#include <wx/wx.h>

#endif

#include <memory>

class VideoFrame;

class VideoCanvas : public wxPanel {
public:
    VideoCanvas(wxFrame *parent);

    void setImage(VideoFrame *videoFrame);

    void paintEvent(wxPaintEvent &evt);

    void paintNow();

    void render(wxDC &dc);

private:
    wxCriticalSection lock;
    std::unique_ptr<wxImage> image;
    std::unique_ptr<wxBitmap> resized;
    std::unique_ptr<VideoFrame> frame;
DECLARE_EVENT_TABLE()

};

#endif /* VIDEOCANVAS_H_ */
