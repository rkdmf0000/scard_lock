@echo off
title RUN_APPLICATION FOR SCARD_LOCK


goto check_process_by_name

:check_process_by_name
for /F %%d in ( 'tasklist' ) do (
    if %%d == scard_lock.exe (
    echo "Service is alive"
    echo "STOPPED!"
    timeout 2 > NUL
    exit
    )
)
goto startup

:startup
mkdir "%appdata%/scard_lock"
start "Scard locking service" /D "%appdata%/scard_lock" /REALTIME /B scard_lock.exe
exit


