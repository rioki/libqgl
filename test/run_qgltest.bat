
set TARGET_DIR=%1
set SDL_DIR=%2
set SDL_IMAGE_DIR=%3
set SDL_TTF_DIR=%4
set GLEW_DIR=%6
set SIGC_DIR=%7

copy /Y "%SDL_DIR%\bin\*.dll" %TARGET_DIR%
copy /Y "%SDL_IMAGE_DIR%\bin\*.dll" %TARGET_DIR%
copy /Y "%SDL_TTF_DIR%\bin\*.dll" %TARGET_DIR%
copy /Y "%GLEW_DIR%\bin\*.dll" %TARGET_DIR%
copy /Y "%SIGC_DIR%\bin\*.dll" %TARGET_DIR%

%TARGET_DIR%\qgltest.exe
