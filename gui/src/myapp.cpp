#include <DirectoryReader.h>
#include "myapp.h"
#include "VideoCanvas.h"
#include "DirectoryReader.h"
#include "VideoPlayer.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    VideoPlayer *player = new VideoPlayer("Video Player");
    player->Show(true);
    return true;
}




