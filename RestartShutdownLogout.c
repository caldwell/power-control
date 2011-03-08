/*
	File:		RestartShutdownLogout.c
	
	Description:	This program implements a simple API which allows developers to
                        programatically cause restart, shutdown, logout.  
					
	Author:		Chad Jones (chadj@apple.com)

	Copyright: 	© Copyright 2003 Apple Computer, Inc. All rights reserved.
	
	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc.
				("Apple") in consideration of your agreement to the following terms, and your
				use, installation, modification or redistribution of this Apple software
				constitutes acceptance of these terms.  If you do not agree with these terms,
				please do not use, install, modify or redistribute this Apple software.

				In consideration of your agreement to abide by the following terms, and subject
				to these terms, Apple grants you a personal, non-exclusive license, under Apple’s
				copyrights in this original Apple software (the "Apple Software"), to use,
				reproduce, modify and redistribute the Apple Software, with or without
				modifications, in source and/or binary forms; provided that if you redistribute
				the Apple Software in its entirety and without modifications, you must retain
				this notice and the following text and disclaimers in all such redistributions of
				the Apple Software.  Neither the name, trademarks, service marks or logos of
				Apple Computer, Inc. may be used to endorse or promote products derived from the
				Apple Software without specific prior written permission from Apple.  Except as
				expressly stated in this notice, no other rights or licenses, express or implied,
				are granted by Apple herein, including but not limited to any patent rights that
				may be infringed by your derivative works or by other works in which the Apple
				Software may be incorporated.

				The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO
				WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED
				WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
				PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN
				COMBINATION WITH YOUR PRODUCTS.

				IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR
				CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
				GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
				ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION
				OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT
				(INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN
				ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
				
	Change History (most recent first): 
*/
#include "RestartShutdownLogout.h"

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
OSStatus SendAppleEventToSystemProcess(AEEventID EventToSend)
{
    // --- Allocating local variables --- //
    AEAddressDesc targetDesc;
    static const ProcessSerialNumber kPSNOfSystemProcess = { 0, kSystemProcess };
    AppleEvent eventReply = {typeNull, NULL};
    AppleEvent appleEventToSend = {typeNull, NULL};
    
    OSStatus error = noErr;

    /* Now that we have the Apple Event we need to target the system process
     * we need to target the system process.  This is done with a call to
     * AECreateDesc.  Note on OS9 the "system process" is the Finder.  On OSX 
     * the "system process" is loginwindow.  Both "system processes" handle the 
     * events correctly and cause the expected results.
     * First Argument: The process targetting method.
     *      Here we are targetting by process serial number.
     * Second Argument: The actual data used to target the process.
     *      In this case of course we are using the process serial number of
     *      the process being targeted.  Here the system process is being
     *      targetted.  We target the system process by the constant
     *      kSystemProcess here already input into the "psn" argument being passed.
     * Third Argument: Size of the data used to target the process.  Of course
     *      this case we have the size of the ProcessSerialNumber argument
     *      being passed.
     * Forth Argument: On return from AECreateDesc this parameter will hold a 
     *      a AEDescriptor.  The AEDescriptor describes the targetted process.
     *      This will be used to send an Apple Event to the target process.
     *      Note we have to dispose of descriptor.
     * Return Value: Error representing success or failure of the process.
     */
    error = AECreateDesc(typeProcessSerialNumber, &kPSNOfSystemProcess, 
                        sizeof(kPSNOfSystemProcess), &targetDesc);

    if (error != noErr) //Failure occurred in targetting the process.
    {
        return(error); //Return error indicating error creating descriptor
    }

    /* Now that we have the descriptor which targets the system process we need
     * to create an Apple Event to send to the system process.
     * First Argument: The Apple Event class to send.  In this case all the
     *      possible events we may send are from the CoreEventClass.  Thus pass
     *      kCoreEventClass as the Apple Event class.
     * Second Argument: The actual Apple Event to send to the system.  This
     *      will either be kAERestart, kAEShutdown or the logout event.
     *      Which event is chosen is based on the input argument to this function.
     * Third Argument: A AEDescriptor describing the target process.  Here we
     *      pass the Apple Event descriptor we recently created.
     * Forth Argument: The return ID to use. Here we want auto
     *      generated return ID.
     * Fifth Argument: The transaction ID to use.  Here we want
     *      AnyTransactionID.
     * Sixth Argument: On return this argument holds the Apple Event to be sent.
     * Return Value: Error representing success or failure of the process.
     *      This is system error returned.
     */
    error = AECreateAppleEvent(kCoreEventClass, EventToSend,
                     &targetDesc, kAutoGenerateReturnID,
                     kAnyTransactionID, &appleEventToSend);

    //disposing of the Apple Event descriptor since we are done with it.
    AEDisposeDesc(&targetDesc);

    if (error != noErr) //Failure occurred in creating the Apple Event.
    {
        return(error); //Return error indicating error creating Apple Event.
    }

    /* Now that we have the Apple Event to send we will send it.
     * First Argument: The Apple Event to send.  In this case the Apple Event
     *      we created earlier.
     * Second Argument: The reply to the Apple Event.  We don't use the
     *      reply but get the result back from the call.
     * Third Argument: The reply type.  In this case we don't want any reply to
     *      the Apple Event.  Thus, we pass kAENoReply.
     * Forth Argument: The priority of the event to send.  Here we want
     *      normal priority (kAENormalPriority).
     * Fifth Argument: The timeout value to use.  Here we want default value
     *      so use kAEDefaultTimeout.
     * Sixth Argument: Idle proc to use.  We pass null since we don't need this.
     * Seventh Argument: Filter proc to use.  We pass null since we don't need this.
     * Return Value: Error representing success or failure of the process.
     *      This is system error returned.
     */
    error = AESend(&appleEventToSend, &eventReply, kAENoReply,
             kAENormalPriority, kAEDefaultTimeout,
             NULL, NULL);

    //disposing of the Apple Event since we are done with it.
    AEDisposeDesc(&appleEventToSend);

    if (error != noErr) 
    {
    	return(error); 
    }

    //disposing of the Apple Event reply since we are done with it.
    AEDisposeDesc(&eventReply);
    
    return(error); //if this is noErr then we are successful
}
