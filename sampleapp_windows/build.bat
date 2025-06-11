@echo off
echo Building RaygunBreakpad...

REM Check if Visual Studio build tools are available
where msbuild >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo Using MSBuild...
    msbuild RaygunBreakpad.sln /p:Configuration=Debug /p:Platform=x64
) else (
    echo MSBuild not found. Please run this from a Visual Studio Developer Command Prompt.
    echo.
    echo Alternative: Open RaygunBreakpad.sln in Visual Studio and build from there.
    echo.
    echo The project includes:
    echo - Main application source: main.cpp
    echo - Breakpad client sources from ..\deps\breakpad\src\client\windows\
    echo - Breakpad common sources from ..\deps\breakpad\src\common\windows\
    pause
)
