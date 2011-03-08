#include "RestartShutdownLogout.h"
#include <stdio.h>

int main(void)
{
    OSStatus status = SendAppleEventToSystemProcess(kAESleep);
    if (status != noErr)
        printf("Computer wouldn't sleep: %d\n", (int)status);

    return status == noErr ? EXIT_SUCCESS : EXIT_FAILURE;
}
