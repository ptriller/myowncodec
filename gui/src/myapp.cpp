#include "myapp.h"
#include "VideoPlayer.h"
#include "bitmapcodec.h"
wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    register_bitmap_codec();
    (new VideoPlayer("Video Player"))->Show(true);
    return true;
}




