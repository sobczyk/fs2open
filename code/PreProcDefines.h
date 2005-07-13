// Place all prepreprcoessor definitions that tuurn features on/off
// into this file.
// the purpose of this is to prevent what happens with FRED
// when DECALS_ENABLED was added to code.lib

/*
 * $Logfile: /Freespace2/code/PreProcDefines.h $
 * $Revision: 1.15 $
 * $Date: 2005-07-13 00:44:23 $
 * $Author: Goober5000 $
 *
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.14  2005/07/12 22:14:40  Goober5000
 * removed DECALS_ENABLED
 * --Goober5000
 *
 * Revision 1.13  2005/07/12 21:58:45  Goober5000
 * removed NO_LINKED_PRIMARY_PENALTY as it's better suited for difficulty.tbl or something similar
 * --Goober5000
 *
 * Revision 1.12  2005/04/24 12:44:25  taylor
 * make sure we don't build with speech support under Linux unless we specify it as a configure option
 *
 * Revision 1.11  2005/03/25 06:57:32  wmcoolmon
 * Big, massive, codebase commit. I have not removed the old ai files as the ones I uploaded aren't up-to-date (But should work with the rest of the codebase)
 *
 * Revision 1.10  2005/03/02 21:18:18  taylor
 * better support for Inferno builds (in PreProcDefines.h now, no networking support)
 * make sure NO_NETWORK builds are as friendly on Windows as it is on Linux/OSX
 * revert a timeout in Client.h back to the original value before Linux merge
 *
 * Revision 1.9  2005/02/04 10:12:29  taylor
 * merge with Linux/OSX tree - p0204
 *
 * Revision 1.8  2005/01/01 13:14:19  argv
 * Since Taylor's asteroid targeting code does not use the
 * TURRETS_SHOOT_ASTEROIDS #define, remove it from preprocdefines.h. We can
 * put it back from an old rev if people decide to use my code instead of his,
 * which seems unlikely.
 *
 * -- _argv[-1]
 *
 * Revision 1.7  2004/12/31 03:13:08  argv
 * I've just been informed that turrets do not shoot asteroids in the retail
 * game, and that this implementation causes them to shoot at the parent ship,
 * too. I'll deal with this later; in the mean time, use
 * "#define TURRETS_SHOOT_ASTEROIDS" to cause turrets to shoot asteroids.
 *
 * -- _argv[-1]
 *
 * Revision 1.6  2004/12/30 07:26:21  argv
 * Quick hack to remove the 50% rate-of-fire penalty when primary weapons are
 * linked. "#define NO_LINKED_PRIMARY_PENALTY" to enable this change; it's
 * disabled by default.
 *
 * -- _argv[-1]
 *
 * Revision 1.5  2004/12/05 22:01:11  bobboau
 * sevral feature additions that WCS wanted,
 * and the foundations of a submodel animation system,
 * the calls to the animation triggering code (exept the procesing code,
 * wich shouldn't do anything without the triggering code)
 * have been commented out.
 *
 * Revision 1.4  2004/10/31 21:23:08  taylor
 * #define if !#defined, add USE_DEVIL and FS2_SPEECH commented out
 *
 * Revision 1.3  2004/10/06 22:02:53  Kazan
 * interface corruption fix - thanks taylor (MAX_BITMAPS upped to 7000)
 *
 * Revision 1.2  2004/08/20 05:13:07  Kazan
 * wakka wakka - fix minor booboo
 *
 * Revision 1.1  2004/08/11 05:06:17  Kazan
 * added preprocdefines.h to prevent what happened with fred -- make sure to make all fred2 headers include this file as the _first_ include -- i have already modified fs2 files to do this
 *
 *
 */

#if !defined(_pre_proc_defs_h_)
#define _pre_proc_defs_h_

#ifndef HTL
#define HTL					1
#endif

#ifndef USE_OPENGL
#define USE_OPENGL			1
#endif

#ifndef ENABLE_AUTO_PILOT
#define ENABLE_AUTO_PILOT	1
#endif

#ifndef _REPORT_MEM_LEAKS
#define _REPORT_MEM_LEAKS	1
#endif

#ifndef SCP_UNIX
// this needs to be a configure option on Linux/OSX

#ifndef FS2_SPEECH
#define FS2_SPEECH			1
#endif

#endif

/*
#ifndef INF_BUILD
#define INF_BUILD			1
#ifndef NO_NETWORK // no networking with INF_BUILD
#define NO_NETWORK			1
#endif // NO_NETWORK
#endif // INF_BUILD
*/

// INF_BUILD error check...
#if defined(INF_BUILD) && !defined(NO_NETWORK)
#error "Networking *must* be disabled with Inferno builds, define NO_NETWORK"
#endif

#endif // _pre_proc_defs_h_
