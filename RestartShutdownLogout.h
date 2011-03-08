#if !defined(__DTSSampleCode_RestartShutdown__)
#define __DTSSampleCode_RestartShutdown__ 1

#if defined(__MWERKS__)
	#include <Carbon.h>
#else
	#include <Carbon/Carbon.h>
#endif

#if defined(__cplusplus)
extern "C" {
#endif
/*****************************************************
 * SendAppleEventToSystemProcess
 *****************************************************
 * Purpose:  This function will passed-on the Apple Event to the system process.  
 *
 * Parameters:
 *
 *     EventToSend    An AEEventID.  On calling SendAppleEventToSystemProcess
 *         this argument describes which event to send to the
 *        system process.  For use with this sample there is really three events listed below:
 *         	kAERestart will cause system to restart. (OSX and OS9)
 *         	kAEShutDown will cause system to shutdown. (OSX and OS9)
 *         	kAEReallyLogout will cause system to logout. (OSX only)
 *
 *     <Function Result>     A integer return value.
 *                 See result codes listed below.
 *         Result Codes:
 *        Zero    	Success.  Event was successfully sent.
 *        non-Zero    	See MacErrors.h for description of system defined errors.
 *****************************************************/
OSStatus SendAppleEventToSystemProcess(AEEventID EventToSend);

#if defined(__cplusplus)
}
#endif

#endif