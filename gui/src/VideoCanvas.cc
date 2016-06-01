#include "VideoCanvas.h"
#include "VideoFrame.h"
namespace {
    class SectionLock {
    public:
        SectionLock(wxCriticalSection &lock) :
                lock(lock) {
            lock.Enter();

        }

        ~SectionLock() {
            lock.Leave();
        }

    private:
        wxCriticalSection &lock;
    };
}

wxDEFINE_EVENT(UPDATE_IMAGE_EVENT, wxCommandEvent);

wxBEGIN_EVENT_TABLE(VideoCanvas, wxPanel)
                EVT_PAINT(VideoCanvas::paintEvent)
wxEND_EVENT_TABLE()

VideoCanvas::VideoCanvas(wxFrame *parent) :
        wxPanel(parent), image(new wxImage()) {
    SetBackgroundColour(wxColour(255, 0, 0));
}

void VideoCanvas::paintEvent(wxPaintEvent &evt) {
    wxPaintDC dc(this);
    render(dc);
}

void VideoCanvas::paintNow() {
    wxClientDC dc(this);
    render(dc);
}

void VideoCanvas::render(wxDC &dc) {
    const wxSize size = dc.GetSize();
    {
        SectionLock section(lock);
        if (size.GetWidth() > 0 && size.GetHeight() > 0 && image->IsOk()) {
            if (!resized->IsOk() || size.GetWidth() != resized->GetWidth()
                || size.GetHeight() != resized->GetHeight()) {
                resized.reset(new wxBitmap(image->Scale(size.GetWidth(), size.GetHeight())));
            }
            dc.DrawBitmap(*resized, 0, 0, false);
        } else {
            dc.SetBrush(wxBrush(wxColour(255, 20, 147)));
            dc.DrawRectangle(wxPoint(0, 0), size);
        }
    }
}

void VideoCanvas::setImage(VideoFrame *videoFrame) {
    {
        SectionLock section(lock);
        this->image.reset(new wxImage(videoFrame->width(),
                                      videoFrame->height(),
                                      videoFrame->buffer(0,0), true));
        this->frame.reset(videoFrame);
        resized.reset(new wxBitmap());
    }
    paintNow();
}

