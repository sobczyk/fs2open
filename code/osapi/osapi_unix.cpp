/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/OsApi/OsApi.cpp $
 * $Revision: 2.5 $
 * $Date: 2005-01-31 10:34:38 $
 * $Author: taylor $
 *
 * Low level Windows code
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.4  2004/07/26 16:11:41  Goober5000
 * fixored a problem when using the command-line compiler to compile everything under Windows
 * --Goober5000
 *
 * Revision 2.3  2004/03/05 09:02:08  Goober5000
 * Uber pass at reducing #includes
 * --Goober5000
 *
 * Revision 2.2  2002/08/01 01:41:09  penguin
 * The big include file move
 *
 * Revision 2.1  2002/07/07 19:55:59  penguin
 * Back-port to MSVC
 *
 * Revision 2.0  2002/06/03 04:10:40  penguin
 * Warpcore CVS sync
 *
 * Revision 1.3  2002/06/03 03:42:13  mharris
 * fAppActive is now set correctly; translate some keyboard scancodes
 * that appear to be different between SDL and Win32; combine KEYDOWN
 * and KEYUP events.
 *
 * Revision 1.2  2002/05/21 15:45:58  mharris
 * init outwnd in debug mode; added SDL support
 *
 * Revision 1.1  2002/05/16 00:47:21  mharris
 * New version of OsApi files for Unix variants.
 *
 * Revision 1.2  2002/05/09 13:52:01  mharris
 * debug_int3() calls abort()
 *
 * Revision 1.1  2002/05/02 18:03:12  mharris
 * Initial checkin - converted filenames and includes to lower case
 * 
 * 
 * 7     6/30/99 5:53p Dave
 * Put in new anti-camper code.
 * 
 * 6     6/03/99 6:37p Dave
 * More TNT fun. Made perspective bitmaps more flexible.
 * 
 * 5     6/02/99 6:18p Dave
 * Fixed TNT lockup problems! Wheeeee!
 * 
 * 4     12/18/98 1:13a Dave
 * Rough 1024x768 support for Direct3D. Proper detection and usage through
 * the launcher.
 * 
 * 3     10/09/98 2:57p Dave
 * Starting splitting up OS stuff.
 * 
 * 2     10/08/98 2:38p Dave
 * Cleanup up OsAPI code significantly. Removed old functions, centralized
 * registry functions.
 * 
 * 118   7/10/98 5:04p Dave
 * Fix connection speed bug on standalone server.
 * 
 * 117   5/24/98 2:28p Hoffoss
 * Because we never really care about if the left or the right shift or
 * alt key was used, but rather than either shift or alt was used, made
 * both map to the left one.  Solves some problems, causes none.
 * 
 * 116   5/18/98 9:22p John
 * Took out the annoying tab check.
 * 
 * 115   5/18/98 11:17a John
 * Fixed some bugs with software window and output window.
 * 
 * 114   5/16/98 2:20p John
 * Changed the os_suspend and resume to use a critical section to prevent
 * threads from executing rather than just suspending the thread.  Had to
 * make sure gr_close was called before os_close.
 * 
 * 113   5/15/98 4:49p John
 * 
 * 112   5/15/98 3:36p John
 * Fixed bug with new graphics window code and standalone server.  Made
 * hwndApp not be a global anymore.
 * 
 * 111   5/14/98 5:42p John
 * Revamped the whole window position/mouse code for the graphics windows.
 * 
 * 110   5/04/98 11:08p Hoffoss
 * Expanded on Force Feedback code, and moved it all into Joy_ff.cpp.
 * Updated references everywhere to it.
 *
 * $NoKeywords: $
 */

#ifndef WIN32	// Goober5000

#include <stdio.h>
#include <fcntl.h>
#include <stdarg.h>

#include "globalincs/pstypes.h"
#include "osapi/osapi.h"
#include "io/key.h"
#include "io/mouse.h"
#include "osapi/outwnd.h"
#include "io/joy.h"
#include "io/joy_ff.h"
#include "osapi/osregistry.h"
#include "graphics/2d.h"

// ----------------------------------------------------------------------------------------------------
// OSAPI DEFINES/VARS
//

// os-wide globals
static int			fAppActive = 1;
static char			szWinTitle[128];
static char			szWinClass[128];
//static int			WinX, WinY, WinW, WinH;
static int			Os_inited = 0;

static CRITICAL_SECTION Os_lock;

int Os_debugger_running = 0;

// ----------------------------------------------------------------------------------------------------
// OSAPI FORWARD DECLARATIONS
//

DWORD unix_process(DWORD lparam);

// called at shutdown. Makes sure all thread processing terminates.
void os_deinit();

// ----------------------------------------------------------------------------------------------------
// OSAPI FUNCTIONS
//

// initialization/shutdown functions -----------------------------------------------

// detect users home directory
const char *detect_home(void)
{
	return (getenv("HOME"));
}

// If app_name is NULL or ommited, then TITLE is used
// for the app name, which is where registry keys are stored.
void os_init(char * wclass, char * title, char *app_name, char *version_string )
{
#ifndef NDEBUG
	outwnd_init(1);
#endif	

	// create default ini entries for the user
	if (os_config_read_string(NULL, NOX("VideocardFs2open"), NULL) == NULL)
		os_config_write_string(NULL, NOX("VideocardFs2open"), NOX("OGL -(640x480)x16 bit"));

	os_init_registry_stuff(Osreg_company_name, title, version_string);
	
	strcpy( szWinTitle, title );
	strcpy( szWinClass, wclass );	

	INITIALIZE_CRITICAL_SECTION( Os_lock );

	unix_process(0);

	// initialized
	Os_inited = 1;

	atexit(os_deinit);
}

// set the main window title
void os_set_title( char *title )
{
	strcpy( szWinTitle, title );

	SDL_WM_SetCaption( szWinTitle, NULL );
}

// call at program end
void os_cleanup()
{
#ifndef NDEBUG
	outwnd_close();
#endif
}


// window management -----------------------------------------------------------------

// Returns 1 if app is not the foreground app.
int os_foreground()
{
	return fAppActive;
}

// Returns the handle to the main window
/*uint os_get_window()
{
	// not used
	return 0;
}*/


// process management -----------------------------------------------------------------

// Sleeps for n milliseconds or until app becomes active.
void os_sleep(int ms)
{
	usleep(ms*1000);
}

// Used to stop message processing
void os_suspend()
{
	ENTER_CRITICAL_SECTION( Os_lock );	
}

// resume message processing
void os_resume()
{
	LEAVE_CRITICAL_SECTION( Os_lock );	
}


// ----------------------------------------------------------------------------------------------------
// OSAPI FORWARD DECLARATIONS
//

extern int SDLtoFS2[SDLK_LAST];

DWORD unix_process(DWORD lparam)
{
	SDL_Event event;

	while( SDL_PollEvent(&event) ) {
		switch(event.type) {
			case SDL_ACTIVEEVENT:
				if( (event.active.state & SDL_APPACTIVE) || (event.active.state & SDL_APPINPUTFOCUS) ) {
					fAppActive = event.active.gain;
					gr_activate(fAppActive);
				}
				break;

			case SDL_KEYDOWN:
			/*	if( (event.key.keysym.mod & KMOD_ALT) && (event.key.keysym.sym == SDLK_RETURN) ) {
					Gr_screen_mode_switch = 1;
					gr_activate(1);
					break;
				}*/

				/* these key combos are used in game so don't capture them here
				if( (event.key.keysym.mod & KMOD_CTRL) && (event.key.keysym.sym == SDLK_g) )
				{
					// DDOI - ignore grab changes when fullscreen
					if( !(SDL_GetVideoSurface()->flags & SDL_FULLSCREEN) )
					{
						if( SDL_WM_GrabInput(SDL_GRAB_QUERY)==SDL_GRAB_ON )
							SDL_WM_GrabInput(SDL_GRAB_OFF);
						else
							SDL_WM_GrabInput(SDL_GRAB_ON);
					}
					break;
				}

				if( (event.key.keysym.mod & KMOD_CTRL) && (event.key.keysym.sym == SDLK_z) ) {
					gr_activate(0);
					break;
				}
				*/

				if( SDLtoFS2[event.key.keysym.sym] ) {
					key_mark( SDLtoFS2[event.key.keysym.sym], 1, 0 );
				}
				break;

			case SDL_KEYUP:
			/*	if( (event.key.keysym.mod & KMOD_ALT) && (event.key.keysym.sym == SDLK_RETURN) ) {
					Gr_screen_mode_switch = 0;
					break;
				}*/

				if (SDLtoFS2[event.key.keysym.sym]) {
					key_mark (SDLtoFS2[event.key.keysym.sym], 0, 0);
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				if (event.button.button <= HIGHEST_MOUSE_BUTTON) {
					mouse_mark_button(event.button.button, event.button.state);
				}
				break;
		}
	}

#ifndef NO_JOYSTICK
	extern void joy_poll();
	joy_poll();
#endif

	return 0;
}


// called at shutdown. Makes sure all thread processing terminates.
void os_deinit()
{
	DELETE_CRITICAL_SECTION( Os_lock );

	SDL_Quit();
}

void os_poll()
{
	unix_process(0);
}

void debug_int3()
{
   abort();
}

#endif		// Goober5000 - #ifndef WIN32
