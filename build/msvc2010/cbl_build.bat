@echo off
call "%VS100COMNTOOLS%\vsvars32.bat"

SET ProgRoot=%ProgramFiles%
SET VLDLibDir=lib
IF NOT "%PROGRAMFILES(x86)%" == "" SET ProgRoot=%ProgramFiles(x86)%
IF NOT "%PROGRAMFILES(x86)%" == "" SET VLDLibDir=lib\Win32

@SET INCLUDE=%ProgRoot%\Visual Leak Detector\include;%INCLUDE%
@SET LIB=%ProgRoot%\Visual Leak Detector\%VLDLibDir%;%LIB%

msbuild /p:useenv=true cbl.vcxproj /p:Configuration=Debug /p:VCBuildAdditionalOptions=/useenv
msbuild /p:useenv=true cbl.vcxproj /p:Configuration=DebugLib /p:"VCBuildAdditionalOptions= /useenv"
msbuild /p:useenv=true cbl.vcxproj /p:Configuration=Release /p:"VCBuildAdditionalOptions= /useenv"
msbuild /p:useenv=true cbl.vcxproj /p:Configuration=ReleaseLib /p:"VCBuildAdditionalOptions= /useenv"
