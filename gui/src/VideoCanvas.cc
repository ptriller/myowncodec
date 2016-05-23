#include "VideoCanvas.h"

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

VideoCanvas::VideoCanvas(wxFrame * parent) :
		wxPanel(parent) {
	image.LoadFile("/home/ptriller/projects/sandbox/myowncodec/gui/testme.jpg",
			wxBITMAP_TYPE_JPEG);
	SetBackgroundColour(wxColour(255, 0, 0));
}

void VideoCanvas::paintEvent(wxPaintEvent & evt) {
	wxPaintDC dc(this);
	render(dc);
}

void VideoCanvas::paintNow() {
	wxClientDC dc(this);
	render(dc);
}

void VideoCanvas::render(wxDC& dc) {
	int width, height;
	const wxSize size = dc.GetSize();
	{
		SectionLock section(lock);
		if (size.GetWidth() > 0 && size.GetHeight() > 0 && image.IsOk()) {
			if (!resized.IsOk() || size.GetWidth() != resized.GetWidth()
					|| size.GetHeight() != resized.GetHeight()) {
				resized = image.Scale(size.GetWidth(), size.GetHeight());
			}
			dc.DrawBitmap(resized, 0, 0, false);
		} else {
			dc.SetBrush(wxBrush(wxColour(255, 20, 147)));
			dc.DrawRectangle(wxPoint(0, 0), size);
		}
	}
}

void VideoCanvas::setImage(const wxImage &image) {
	{
		SectionLock section(lock);
		this->image = image;
		resized = wxBitmap();
	}
	paintNow();
}

