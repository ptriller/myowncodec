@ECHO OFF
cd "E:/devel/project/eclipse/myowncodec"
E:\devel\cmake-3.5.2-win32-x86\bin\cmake.exe -D "CMAKE_BUILD_TYPE:STRING=Debug" -D "CMAKE_ECLIPSE_EXECUTABLE:FILEPATH=E:/devel/eclipse/eclipse.exe" -D "CMAKE_ECLIPSE_VERSION:STRING=4.3 (Kepler)" -D "wxWidgets_ROOT_DIR:PATH=E:/devel/wxWidgets" -D "wxWidgets_LIB_DIR:PATH=E:/devel/wxWidgets/lib/gcc510TDM_x64_dll" -G "Eclipse CDT4 - MinGW Makefiles" "E:/devel/project/myowncodec" 

