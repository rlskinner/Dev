@echo off
@rem
@rem Install include files
@rem

@rem make the destination directories
xcopy UnixCompat.h %DEVROOT%\include /V

