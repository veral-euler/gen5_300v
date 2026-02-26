@echo off
setlocal EnableDelayedExpansion

:: ==============================================================================
::  build.bat — STM32 CMake Build Automation Script (Windows)
::  Usage: build.bat [option]
::
::  Options:
::    (none)       Configure (if needed) + build
::    clean        Wipe build\ and stop
::    flash        Build then flash via OpenOCD
::    size         Print memory usage of last build
::    help         Show this help message
:: ==============================================================================

:: ── Config ────────────────────────────────────────────────────────────────────
set BUILD_DIR=%~dp0PegasusBuild
set BUILD_TYPE=Debug
set JOBS=%NUMBER_OF_PROCESSORS%
:: ─────────────────────────────────────────────────────────────────────────────

:: Resolve script directory (always absolute)
set SCRIPT_DIR=%~dp0
:: Remove trailing backslash
if "%SCRIPT_DIR:~-1%"=="\" set SCRIPT_DIR=%SCRIPT_DIR:~0,-1%

:: Parse argument
set ARG=%1
if "%ARG%"=="" set ARG=build

if /I "%ARG%"=="build" goto :do_build
if /I "%ARG%"=="clean" goto :do_clean
if /I "%ARG%"=="flash" goto :do_flash
if /I "%ARG%"=="size"  goto :do_size
if /I "%ARG%"=="help"  goto :do_help
if /I "%ARG%"=="-h"    goto :do_help

call :error "Unknown option '%ARG%'. Run 'build.bat help' for usage."
goto :eof

:: ==============================================================================
:: CHECK DEPENDENCIES
:: ==============================================================================
:check_deps
    where cmake              >nul 2>&1
    if errorlevel 1 ( call :error "cmake not found. Install CMake and add it to PATH." & exit /B 1 )
    where arm-none-eabi-gcc  >nul 2>&1
    if errorlevel 1 ( call :error "arm-none-eabi-gcc not found. Install the ARM toolchain and add it to PATH." & exit /B 1 )
    where arm-none-eabi-size >nul 2>&1
    if errorlevel 1 ( call :error "arm-none-eabi-size not found. Install the ARM toolchain and add it to PATH." & exit /B 1 )

    :: Auto-detect generator: prefer Ninja, fall back to MinGW
    set GENERATOR=
    where ninja >nul 2>&1
    if not errorlevel 1 (
        set GENERATOR=Ninja
        call :info "Using generator: Ninja"
        goto :eof
    )
    where mingw32-make >nul 2>&1
    if not errorlevel 1 (
        set GENERATOR=MinGW Makefiles
        call :info "Using generator: MinGW Makefiles"
        goto :eof
    )
    where make >nul 2>&1
    if not errorlevel 1 (
        set GENERATOR=MinGW Makefiles
        call :info "Using generator: MinGW Makefiles (make)"
        goto :eof
    )
    call :error "No build tool found. Install Ninja or MinGW64 and add to PATH."
    exit /B 1

:: ==============================================================================
:: CONFIGURE
:: ==============================================================================
:configure
    if not exist "%BUILD_DIR%\CMakeCache.txt" (
        call :info "Configuring project (BUILD_TYPE=%BUILD_TYPE%, Generator=%GENERATOR%)..."
        cmake -S "%SCRIPT_DIR%" -B "%BUILD_DIR%" ^
              -G "%GENERATOR%"                   ^
              -DCMAKE_BUILD_TYPE=%BUILD_TYPE%     ^
              -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
        if errorlevel 1 (
            call :error "CMake configuration failed."
            exit /B 1
        )
        call :success "Configuration done."
    ) else (
        call :info "Build directory exists — skipping configure. Run 'build.bat clean' to reconfigure."
    )
    goto :eof

:: ==============================================================================
:: BUILD
:: ==============================================================================
:build
    call :info "Building with %JOBS% parallel jobs..."
    cmake --build "%BUILD_DIR%" --parallel %JOBS%
    if errorlevel 1 (
        call :error "Build failed. Check errors above."
        exit /B 1
    )
    call :success "Build succeeded!"
    goto :eof

:: ==============================================================================
:: ACTIONS
:: ==============================================================================
:do_build
    call :check_deps
    if errorlevel 1 exit /B 1
    call :configure
    if errorlevel 1 exit /B 1
    call :build
    goto :eof

:do_clean
    call :warn "Removing '%BUILD_DIR%'..."
    if exist "%BUILD_DIR%" (
        rmdir /S /Q "%BUILD_DIR%"
        call :success "Cleaned. Run 'build.bat' to configure and rebuild."
    ) else (
        call :warn "Build directory does not exist, nothing to clean."
    )
    goto :eof

:do_flash
    where openocd >nul 2>&1
    if errorlevel 1 ( call :error "OpenOCD not found. Install it and add it to PATH." & exit /B 1 )
    call :check_deps
    if errorlevel 1 exit /B 1
    call :configure
    if errorlevel 1 exit /B 1
    call :build
    if errorlevel 1 exit /B 1
    call :info "Flashing via OpenOCD..."
    cmake --build "%BUILD_DIR%" --target flash
    if errorlevel 1 ( call :error "Flashing failed." & exit /B 1 )
    call :success "Flashed successfully!"
    goto :eof

:do_size
    call :info "Searching for .elf files under '%SCRIPT_DIR%'..."
    set ELF=
    for /R "%SCRIPT_DIR%" %%F in (*.elf) do (
        if "!ELF!"=="" set ELF=%%F
    )
    if "!ELF!"=="" call :error "No .elf file found under '%SCRIPT_DIR%'. Build first."
    call :info "Found: !ELF!"
    arm-none-eabi-size --format=berkeley "!ELF!"
    goto :eof

:do_help
    echo.
    echo  Usage: build.bat [option]
    echo.
    echo    (none)    Configure if needed, then build
    echo    clean     Wipe build\ directory
    echo    flash     Build and flash via OpenOCD
    echo    size      Print memory usage of last build
    echo    help      Show this message
    echo.
    echo  Config (edit inside build.bat):
    echo    BUILD_DIR   = %BUILD_DIR%
    echo    BUILD_TYPE  = %BUILD_TYPE%
    echo    JOBS        = %JOBS%
    echo.
    goto :eof

:: ==============================================================================
:: HELPERS — Colored output using PowerShell
:: ==============================================================================
:info
    powershell -Command "Write-Host '[INFO]  %~1' -ForegroundColor Cyan"
    goto :eof

:success
    powershell -Command "Write-Host '[OK]    %~1' -ForegroundColor Green"
    goto :eof

:warn
    powershell -Command "Write-Host '[WARN]  %~1' -ForegroundColor Yellow"
    goto :eof

:error
    powershell -Command "Write-Host '[ERROR] %~1' -ForegroundColor Red"
    exit /B 1

:: ==============================================================================
:: END OF FILE
:: ==============================================================================