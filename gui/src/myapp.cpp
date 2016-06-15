#include "myapp.h"
#include "VideoPlayer.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    (new VideoPlayer("Video Player"))->Show(true);
    return true;
}




