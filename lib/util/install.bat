@echo off
@rem
@rem Install lib util and include files
@rem

@rem make the destination directories
@rem
@rem Copy public include files
xcopy unistd.h %DEVROOT%\include /V /Y

@rem Copy library
xcopy Debug\libUtil.lib %DEVROOT%\lib /V /Y

