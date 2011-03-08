#include "RestartShutdownLogout.h"
#include <stdio.h>

void usage(char *me)
{
    printf("Usage:\n"
           "\t%s shutdown|restart|sleep|logout\n", me);
    exit(EXIT_FAILURE);
}

int main(int c, char **v)
{
    char *command = NULL;
    if (c == 2) command = v[1];
    if (!command) usage(v[0]);

    AEEventID event = 0;
    if (strcmp(command, "shutdown") == 0) event = kAEShutDown;
    if (strcmp(command, "restart")  == 0) event = kAERestart;
    if (strcmp(command, "sleep")    == 0) event = kAESleep;
    if (strcmp(command, "logout")   == 0) event = kAEReallyLogOut;
    if (event == 0) usage(v[0]);

    OSStatus status = SendAppleEventToSystemProcess(event);
    if (status != noErr)
        printf("Computer wouldn't %s: %d\n", command, (int)status);

    return status == noErr ? EXIT_SUCCESS : EXIT_FAILURE;
}
