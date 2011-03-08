#include "RestartShutdownLogout.h"
#include <stdio.h>

/*****************************************************
 * Main
 *****************************************************
 * Purpose:  Demonstrating the SendEventToSystem functions.
 *****************************************************/
int main(void)
{
    OSStatus error = noErr;
    
    //sending sleep event to system
    error = SendAppleEventToSystemProcess(kAESleep);
    if (error != noErr)
        printf("Computer wouldn't sleep: %d\n", status);

    return status == noErr;
}
