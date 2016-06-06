#include "VideoCanvas.h"
#include "VideoFrame.h"
#include "DirectoryReader.h"
#include <chrono>
enum {
    TIMER_ID = wxID_HIGHEST + 100
};
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
                EVT_TIMER(TIMER_ID, VideoCanvas::OnTimer)
wxEND_EVENT_TABLE()

VideoCanvas::VideoCanvas(wxWindow *parent) :
        timer(this, TIMER_ID), wxPanel(parent), image(new wxImage()) {
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
            dc.SetPen(wxPen(wxColour(255, 20, 147)));
            dc.DrawRectangle(wxPoint(0, 0), size);
        }
    }
}

void VideoCanvas::SetImage(VideoFrame *videoFrame) {
    {
        SectionLock section(lock);
        this->image.reset(new wxImage(videoFrame->width(),
                                      videoFrame->height(),
                                      videoFrame->buffer(0, 0), true));
        resized.reset(new wxBitmap());
    }
    paintNow();
}

using namespace std::chrono;


void VideoCanvas::OnTimer(wxTimerEvent &event) {
    if(!reader) {
        reader.reset(new DirectoryReader(std::string(directory)));
        nextFrame = reader->nextFrame();
    }
    long long int time =  duration_cast< milliseconds >(high_resolution_clock::now() - start).count();

    while(time > nextFrame->timestamp()) {
        frame.reset(nextFrame.release());
        nextFrame = reader->nextFrame();
        if(!nextFrame) {
            StartPlaying();
            return;
        }
    }
    if(frame) {
        SetImage(frame.get());
    } else {
        reader.reset(nullptr);
    }
}

void VideoCanvas::SetDirectory(const wxString &str) {
    StopPlaying();
    directory = str;
    reader.reset(nullptr);
}

void VideoCanvas::StartPlaying() {
    reader.reset(nullptr);
    start = high_resolution_clock::now();
    if(!timer.IsRunning() ) {
        timer.Start(10);
    }
}

void VideoCanvas::StopPlaying() {
    if(timer.IsRunning() ) {
        timer.Stop();
    }
}
