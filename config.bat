@ECHO OFF
setlocal
PATH=%PATH%;E:/devel/mingw-tdm/bin
set curr_dir=%cd%
IF EXIST E:/devel/project/eclipse/myowncodec GOTO IS_THERE
echo Creating dir
MKDIR "E:/devel/project/eclipse/myowncodec"
:IS_THERE
cd /D "E:/devel/project/eclipse/myowncodec"
E:\devel\cmake-3.5.2-win32-x86\bin\cmake.exe -D "CMAKE_BUILD_TYPE:STRING=Debug"^
 -D "CMAKE_LIBRARY_PATH:PATH=E:/devel/libjpeg-turbo-gcc64/lib"^
 -D "wxWidgets_LIB_DIR:PATH=E:/devel/wxWidgets/lib/gcc510TDM_x64_dll"^
 -D "wxWidgets_ROOT_DIR:PATH=E:/devel/wxWidgets"^
 -G "Eclipse CDT4 - MinGW Makefiles"^
 -D "CMAKE_ECLIPSE_EXECUTABLE:FILEPATH=E:/devel/eclipse/eclipse.exe"^
 -D "CMAKE_ECLIPSE_VERSION:STRING=4.3 (Kepler)"^
 -D "JPEG_INCLUDE_DIR:PATH=E:\devel\libjpeg-turbo-gcc64\include"^
 "E:/devel/project/myowncodec" 
cd /D %curr_dir%
