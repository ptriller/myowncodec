@ECHO OFF
set curr_dir=%cd%
cd /D "E:/devel/project/mingw-eclipse/myowncodec"
E:\devel\cmake-3.5.2-win32-x86\bin\cmake.exe -D "CMAKE_BUILD_TYPE:STRING=Debug"^
 -D "LibJpegTurbo_INCLUDE_DIR:PATH=E:/devel/libjpeg-turbo-gcc64/include"^
 -D "LibJpegTurbo_LIBRARY_DIR:PATH=E:/devel/libjpeg-turbo-gcc64/lib"^
 -D "wxWidgets_LIB_DIR:PATH=E:/devel/wxWidgets/lib/gcc510TDM_x64_dll"^
 -D "wxWidgets_ROOT_DIR:PATH=E:/devel/wxWidgets"^
 -G "Eclipse CDT4 - MinGW Makefiles"^
 -D "CMAKE_ECLIPSE_EXECUTABLE:FILEPATH=E:/devel/eclipse/eclipse.exe"^
 -D "CMAKE_ECLIPSE_VERSION:STRING=4.3 (Kepler)"^
 "E:/devel/project/myowncodec" 
cd /D %curr_dir%
