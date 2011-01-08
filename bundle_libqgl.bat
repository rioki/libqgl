
set QGL_VERSION=0.0.0

set BUNDLE_DIR=..\libqgl-%QGL_VERSION%

rmdir /s /q %BUNDLE_DIR%

mkdir %BUNDLE_DIR%
mkdir %BUNDLE_DIR%\bin
mkdir %BUNDLE_DIR%\include
mkdir %BUNDLE_DIR%\include\qgl
mkdir %BUNDLE_DIR%\lib

copy include\qgl\*.h %BUNDLE_DIR%\include\qgl
copy bin\Release\*.a %BUNDLE_DIR%\lib

copy bin\Release\libqgl.dll %BUNDLE_DIR%\bin
rem copy the rest
