// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <memory>
class MyApp: public wxApp {
public:
	virtual bool OnInit();
};

class MyFrame: public wxFrame {
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnPlay(wxCommandEvent& event);
	void OnStop(wxCommandEvent& event);

	wxPanel *videoPanel;
	wxDECLARE_EVENT_TABLE();
};
