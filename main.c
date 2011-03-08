#include "RestartShutdownLogout.h"
#include <stdio.h>

int main(void)
{
    OSStatus status = SendAppleEventToSystemProcess(kAESleep);
    if (status != noErr)
        printf("Computer wouldn't sleep: %d\n", status);

    return status == noErr;
}
