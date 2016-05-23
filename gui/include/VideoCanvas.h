#ifndef VIDEOCANVAS_H_
#define VIDEOCANVAS_H_
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <memory>

class VideoCanvas: public wxPanel {
public:
	VideoCanvas(wxFrame * parent);
	void setImage(const wxImage &image);
	void paintEvent(wxPaintEvent & evt);
	void paintNow();
	void render(wxDC& dc);
private:
	wxCriticalSection lock;
	wxImage image;
	wxBitmap resized;
	DECLARE_EVENT_TABLE()

};

#endif /* VIDEOCANVAS_H_ */
