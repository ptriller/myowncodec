#include <DirectoryReader.h>
#include "myapp.h"
#include "VideoCanvas.h"
#include "DirectoryReader.h"
#include "VideoPlayer.h"
#include <memory>

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    (new VideoPlayer("Video Player"))->Show(true);
    return true;
}




