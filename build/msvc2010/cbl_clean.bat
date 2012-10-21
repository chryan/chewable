@echo off
call "%VS100COMNTOOLS%\vsvars32.bat"
msbuild /t:clean cbl.vcxproj /p:Configuration=Debug
msbuild /t:clean cbl.vcxproj /p:Configuration=DebugLib
msbuild /t:clean cbl.vcxproj /p:Configuration=Release
msbuild /t:clean cbl.vcxproj /p:Configuration=ReleaseLib
