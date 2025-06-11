@echo off

REM Clear old breakpad repo
if exist deps\breakpad rmdir /s /q deps\breakpad

REM Clone Breakpad
git clone https://github.com/google/breakpad.git deps\breakpad
