/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Source: /cvs/cvsroot/fs2open/fs2_open/code/parse/sexp.h,v $
 * $Revision: 2.58 $
 * $Author: Goober5000 $
 * $Date: 2004-03-05 09:02:09 $
 *
 * header for sexpression parsing
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.57  2004/01/20 22:20:41  Goober5000
 * bumped MAX_SEXP_NODES to 3000
 * --Goober5000
 *
 * Revision 2.56  2003/10/28 23:59:02  Goober5000
 * tweakage
 * --Goober5000
 *
 * Revision 2.55  2003/10/20 11:49:18  Goober5000
 * added min, max, and avg sexps
 * --Goober5000
 *
 * Revision 2.54  2003/09/13 06:02:07  Goober5000
 * clean rollback of all of argv's stuff
 * --Goober5000
 *
 * Revision 2.51  2003/09/05 05:06:32  Goober5000
 * merged num-ships-in-battle and num-ships-in-battle-team, making the
 * team argument optional
 * --Goober5000
 *
 * Revision 2.50  2003/09/05 04:39:55  Goober5000
 * merge of Phreak's and my sexp.h
 * --Goober5000
 *
 * Revision 2.49  2003/08/30 21:59:48  phreak
 * added num-ships-in-battle and num-ships-in-battle-team sexp
 *
 * Revision 2.48  2003/08/28 05:46:52  Goober5000
 * trying to commit
 * --Goober5000
 *
 * Revision 2.47  2003/08/27 02:04:54  Goober5000
 * added percent-ships-disarmed and percent-ships-disabled
 * --Goober5000
 *
 * Revision 2.46  2003/08/27 01:38:00  Goober5000
 * added is-ship-type, is-ship-class, lock-rotating-subsystem, and free-rotating-subsystem;
 * also fixed the argument and return values for various sexps so that they work
 * properly for negative numbers
 * --Goober5000
 *
 * Revision 2.45  2003/06/19 18:12:12  phreak
 * added turret-tagged-specific and turret-tagged-clear-specific sexps
 *
 * Revision 2.44  2003/05/24 16:47:58  phreak
 * added Sesquipedalian's kamikaze and not-kamikaze sexps
 *
 * Revision 2.43  2003/04/29 01:03:24  Goober5000
 * implemented the custom hitpoints mod
 * --Goober5000
 *
 * Revision 2.42  2003/04/05 20:47:58  Goober5000
 * gotta love those compiler errors ;)
 * fixed those and cleaned up conflicts with the missile-locked sexp
 * --Goober5000
 *
 * Revision 2.41  2003/04/05 20:17:23  sesquipedalian
 * Recommit of is-missile-locked.
 * I changed the sexp's category from non-campaign to training, so you may get a conflict with that.
 *
 * Revision 2.39  2003/03/30 07:27:33  Goober5000
 * resolved a nasty bug that caused some missions to crash
 * --Goober5000
 *
 * Revision 2.38  2003/03/30 04:34:38  Goober5000
 * preliminary work on ai facing sexp
 * --Goober5000
 *
 * Revision 2.37  2003/03/29 11:23:46  sesquipedalian
 * Aaaand nevermind...
 *
 * Revision 2.36  2003/03/29 08:52:59  sesquipedalian
 * Added is-missile-locked sexp
 *
 * Revision 2.35  2003/03/22 06:11:51  Goober5000
 * added play-sound-from-table, play-sound-from-file, and close-sound-from-file
 * --Goober5000
 *
 * Revision 2.34  2003/03/21 04:51:33  Goober5000
 * added get-relative-object-*, where * = x, y, and z; these sexps return the
 * world coordinates of a set of relative coordinates to an object; also, fixed many
 * places in sexp.cpp so that now sexps can accept other sexps as parameters,
 * wherease before they weren't able to
 * --Goober5000
 *
 * Revision 2.33  2003/03/20 09:17:16  Goober5000
 * implemented EMP as part of weapon-effect sexp
 * --Goober5000
 *
 * Revision 2.32  2003/03/20 04:27:10  Goober5000
 * extended sexps
 * --Goober5000
 *
 * Revision 2.31  2003/03/19 06:23:28  Goober5000
 * added warp-effect sexp
 * --Goober5000
 *
 * Revision 2.30  2003/03/18 08:44:05  Goober5000
 * added explosion-effect sexp and did some other minor housekeeping
 * --Goober5000
 *
 * Revision 2.29  2003/03/03 04:28:37  Goober5000
 * fixed the tech room bug!  yay!
 * --Goober5000
 *
 * Revision 2.28  2003/01/26 18:37:19  Goober5000
 * changed change-music to change-soundtrack
 * --Goober5000
 *
 * Revision 2.27  2003/01/25 04:17:39  Goober5000
 * added change-music sexp and bumped MAX_SOUNDTRACKS from 10 to 25
 * --Ian Warfield
 *
 * Revision 2.26  2003/01/21 17:24:16  Goober5000
 * fixed a few bugs in Bobboau's implementation of the glow sexps; also added
 * help for the sexps in sexp_tree
 * --Goober5000
 *
 * Revision 2.25  2003/01/20 05:40:50  bobboau
 * added several sExps for turning glow points and glow maps on and off
 *
 * Revision 2.24  2003/01/19 07:02:16  Goober5000
 * fixed a bunch of bugs - "no-subspace-drive" should now work properly for
 * all ships, and all ships who have their departure anchor set to a capital ship
 * should exit to that ship when told to depart
 * --Goober5000
 *
 * Revision 2.23  2003/01/10 04:14:19  Goober5000
 * I found these two beautiful functions in ship.cpp - ship_change_model
 * and change_ship_type - so I made them into sexps :)
 * --Goober5000
 *
 * Revision 2.22  2003/01/07 20:06:44  Goober5000
 * added ai-chase-any-except sexp
 * --Goober5000
 *
 * Revision 2.21  2003/01/03 21:58:07  Goober5000
 * Fixed some minor bugs, and added a primitive-sensors flag, where if a ship
 * has primitive sensors it can't target anything and objects don't appear
 * on radar if they're outside a certain range.  This range can be modified
 * via the sexp primitive-sensors-set-range.
 * --Goober5000
 *
 * Revision 2.20  2003/01/02 00:35:20  Goober5000
 * added don't-collide-invisible and collide-invisible sexps
 * --Goober5000
 *
 * Revision 2.19  2003/01/01 23:33:33  Goober5000
 * added ship-vaporize and ship-no-vaporize sexps
 * --Goober5000
 *
 * Revision 2.18  2002/12/31 07:26:40  Goober5000
 * added damaged-escort-priority-all sexp
 * --Goober5000
 *
 * Revision 2.17  2002/12/27 20:16:18  phreak
 * added damage-escort-list as a new sexp
 *
 * Revision 2.16  2002/12/27 02:57:51  Goober5000
 * removed the existing stealth sexps and replaced them with the following...
 * ship-stealthy
 * ship-unstealthy
 * is-ship-stealthy
 * friendly-stealth-invisible
 * friendly-stealth-visible
 * is-friendly-stealth-visible
 * --Goober5000
 *
 * Revision 2.15  2002/12/25 01:22:23  Goober5000
 * meh - changed is-cargo-x to is-cargo
 * --Goober5000
 *
 * Revision 2.14  2002/12/24 07:42:29  Goober5000
 * added change-ai-class and is-ai-class, and I think I may also have nailed the
 * is-iff bug; did some other bug hunting as well
 * --Goober5000
 *
 * Revision 2.13  2002/12/23 23:01:27  Goober5000
 * added set-cargo and is-cargo-x sexps
 * --Goober5000
 *
 * Revision 2.12  2002/12/23 05:18:52  Goober5000
 * Squashed some Volition bugs! :O Some of the sexps for dealing with more than
 * one ship would return after only dealing with the first ship.
 *
 * Also added the following sexps:
 * is-ship-stealthed
 * ship-force-stealth
 * ship-force-nostealth
 * ship-remove-stealth-forcing
 *
 * They toggle the stealth flag on and off.  If a ship is forced stealthy, it won't even
 * show up for friendly ships.
 * --Goober5000
 *
 * Revision 2.11  2002/12/22 21:12:22  Goober5000
 * added primaries-depleted and primary-ammo-pct sexps -- useful for ships with
 * ballistic primaries
 * --Goober5000
 *
 * Revision 2.10  2002/12/22 17:22:47  Goober5000
 * Subcategories implemented. :) So far all that's been done is the Change menu, but other
 * subcategorizations are possible.  Here are the instructions from sexp.h...
 * "Adding more subcategories is possible with the new code.  All that needs to be done is
 * to add a #define here (a number from 0x0000 to 0x00ff ORred with the category that it
 * goes under), some appropriate case statements in get_subcategory() (in sexp.cpp) that
 * will return the subcategory for each sexp that uses it, and the submenu name in the
 * op_submenu[] array in sexp_tree.cpp."
 *
 * Please note that I rearranged a whole bunch of sexps in the Operators[] array in sexp.cpp
 * in order to make the subcategories work better, so if you get a whole bunch of differences
 * or even conflicts, just ignore them. :)
 * --Goober5000
 *
 * Revision 2.9  2002/12/21 17:58:11  Goober5000
 * rearranged the sexp list and got the preliminary subcategories working - still need to work on the actual submenu
 * --Goober5000
 *
 * Revision 2.8  2002/12/17 02:21:42  Goober5000
 * cosmetic fixed; also OP_SET_SCANNED and OP_SET_UNSCANNED added in preparation for the set-scanned and set-unscanned sexp commit
 * --Goober5000
 *
 * Revision 2.7  2002/12/12 08:01:57  Goober5000
 * added distance-ship-subsystem sexp
 * ~Goober5000~
 *
 * Revision 2.6  2002/12/02 23:56:12  Goober5000
 * fixed misspelling
 *
 * Revision 2.5  2002/12/02 20:37:26  Goober5000
 * fixed misspelling of "category" as "catagory"
 *
 * Revision 2.4  2002/11/28 00:00:37  sesquipedalian
 * end-mission sexp added
 *
 * Revision 2.3  2002/10/29 22:41:48  sesquipedalian
 * no message
 *
 * Revision 2.2  2002/08/01 01:41:09  penguin
 * The big include file move
 *
 * Revision 2.1  2002/07/13 09:16:18  wmcoolmon
 * Added initial code for "ship-lights-on" and "ship-lights-off" SEXPs
 *
 * Revision 2.0  2002/06/03 04:02:27  penguin
 * Warpcore CVS sync
 *
 * Revision 1.1  2002/05/02 18:03:12  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 40    9/07/99 1:05a Andsager
 * Added team-score sexp for multi team vs team missions
 * 
 * 39    9/02/99 7:06p Dave
 * Bumped MAX_SEXP_NODES to 2200
 * 
 * 38    8/27/99 4:07p Andsager
 * Add is-ship-visible sexp.  Make ship-vanish sexp SINGLE player only
 * 
 * 37    8/24/99 4:25p Andsager
 * Add ship-vanish sexp
 * 
 * 36    8/16/99 10:04p Andsager
 * Add special-warp-dist and special-warpout-name sexp for Knossos device
 * warpout.
 * 
 * 35    8/09/99 2:00p Dave
 * 2 new sexpressions.
 * 
 * 34    8/02/99 4:26p Dave
 * Added 2 new sexpressions.
 * 
 * 33    7/28/99 1:36p Andsager
 * Modify cargo1 to include flag CARGO_NO_DEPLETE.  Add sexp
 * cargo-no-deplete (only for BIG / HUGE).  Modify ship struct to pack
 * better.
 * 
 * 32    7/24/99 4:56p Dave
 * Added 3 new sexpressions.
 * 
 * 31    7/21/99 8:10p Dave
 * First run of supernova effect.
 * 
 * 30    7/20/99 9:19p Andsager
 * Added facing waypoint sexp
 * 
 * 29    7/20/99 9:54a Andsager
 * Add subsys-set-random sexp
 * 
 * 28    7/15/99 9:20a Andsager
 * FS2_DEMO initial checkin
 * 
 * 27    7/13/99 3:37p Andsager
 * Add secondaries-depleted sexp
 * 
 * 26    7/08/99 12:06p Andsager
 * Add turret-tagged-only and turret-tagged-clear sexp.
 * 
 * 25    6/28/99 4:51p Andsager
 * Add ship-guardian sexp (does not allow ship to be killed)
 * 
 * 24    6/23/99 5:51p Andsager
 * Add waypoint-cap-speed.  Checkin stealth ai - inactive.
 * 
 * 23    6/16/99 10:21a Dave
 * Added send-message-list sexpression.
 * 
 * 22    6/01/99 8:35p Dave
 * Finished lockarm weapons. Added proper supercap weapons/damage. Added
 * awacs-set-radius sexpression.
 * 
 * 21    5/24/99 11:28a Dave
 * Sexpression for adding/removing ships from the hud escort list.
 * 
 * 20    4/28/99 9:33a Andsager
 * Add turret-free and turret-lock (and -all) sexp.  Stargger start time
 * of beam weapons beam-free and beam-free-all.
 * 
 * 19    4/26/99 2:14p Andsager
 * Add beam-protect-ship and beam-unprotect-ship sexp.
 * 
 * 18    4/23/99 9:45a Andsager
 * Modify rand_sexp to return the same value each time it is called on a
 * particular node.  This prevents random time delay defaulting to min.
 * 
 * 17    4/02/99 9:55a Dave
 * Added a few more options in the weapons.tbl for beam weapons. Attempt
 * at putting "pain" packets into multiplayer.
 * 
 * 16    3/20/99 3:46p Dave
 * Added support for model-based background nebulae. Added 3 new
 * sexpressions.
 * 
 * 15    3/04/99 6:09p Dave
 * Added in sexpressions for firing beams and checking for if a ship is
 * tagged.
 * 
 * 14    2/26/99 6:01p Andsager
 * Add sexp has-been-tagged-delay and cap-subsys-cargo-known-delay
 * 
 * 13    2/11/99 5:22p Andsager
 * Fixed bugs, generalized block Sexp_variables
 * 
 * 12    2/11/99 2:15p Andsager
 * Add ship explosion modification to FRED
 * 
 * 11    1/25/99 4:29p Andsager
 * Modify sexp_modify_variable() to handle type string. added quick out
 * for multiplayer_client
 * 
 * 10    1/25/99 8:15a Andsager
 * Format fix
 * 
 * 9     1/25/99 8:14a Andsager
 * Add sexp_modify_variable().  Changed syntax checking to allow, adding
 * operator return type ambiguous
 * 
 * 8     1/24/99 11:37p Dave
 * First full rev of beam weapons. Very customizable. Removed some bogus
 * Int3()'s in low level net code.
 * 
 * 7     1/20/99 9:37a Andsager
 * 
 * 6     1/19/99 3:57p Andsager
 * Round 2 of variables
 * 
 * 5     1/07/99 1:52p Andsager
 * Initial check in of Sexp_variables
 * 
 * 4     12/15/98 3:59p Dan
 * DA: bumped sexp nodes to 2000 for dan
 * 
 * 3     11/05/98 5:55p Dave
 * Big pass at reducing #includes
 * 
 * 2     10/07/98 10:53a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:50a Dave
 * 
 * 168   9/17/98 9:25p Dave
 * _really_ upped max sexp nodes to 1800.
 * 
 * 167   9/16/98 6:54p Dave
 * Upped  max sexpression nodes to 1800 (from 1600). Changed FRED to sort
 * the ship list box. Added code so that tracker stats are not stored with
 * only 1 player.
 * 
 * 166   9/16/98 10:42a Hoffoss
 * Added sexp node counting to fsm files for end user designers.
 * 
 * 165   4/25/98 7:40p Allender
 * fixd some small hotkey stuff.  Worked on turret orientation being
 * correct for multiplayer.  new sexpression called end-campaign will will
 * end the main campaign
 * 
 * 164   4/24/98 4:20p Hoffoss
 * Made the Cond operator an unlisted operator, as using this in Fred with
 * the sexp trees will cause them to be generated wrong, and then
 * FreeSpace would pay the price.
 * 
 * 163   4/23/98 5:50p Hoffoss
 * Added tracking of techroom database list info in pilot files, added
 * sexp to add more to list, made mouse usable on ship listing in tech
 * room.
 * 
 * 162   4/16/98 4:33p Hoffoss
 * Added support for detecting instructor terminating training due to
 * player shooting at him.
 * 
 * 161   4/15/98 12:58p Lawrance
 * increase MAX_SEXP_NODES for demo build, needed since training mission
 * was added
 * 
 * 160   4/14/98 5:46p Hoffoss
 * Added special-check operator.
 * 
 * 159   4/14/98 5:24p Hoffoss
 * Added a custom operator for training handling for Mike K.
 * 
 * 158   4/14/98 11:55a Allender
 * add end-of-campaign sexpression to allow for mission replay at the end
 * of campaigns
 * 
 * 157   4/09/98 4:32p Hoffoss
 * Fixed several bugs in debriefing.
 * 
 * 156   4/06/98 5:37p Hoffoss
 * Added sexp tree support to briefings in Fred.
 * 
 * 155   4/03/98 2:47p Allender
 * made directives act different when multiple waves of a wing take a long
 * time to reappear
 * 
 * 154   4/03/98 12:18a Allender
 * new sexpression to detect departed or destroyed.  optionally disallow
 * support ships.  Allow docking with escape pods 
 * 
 * 153   4/02/98 10:13p Lawrance
 * increase MAX_SEXP_NODES to 1600
 * 
 * 152   4/02/98 6:32p Lawrance
 * reduce MAX_SEXP_NODES if DEMO defined
 * 
 * 151   4/02/98 11:40a Lawrance
 * check for #ifdef DEMO instead of #ifdef DEMO_RELEASE
 * 
 * 150   4/01/98 8:30p Mike
 * Reduce MAX_SHIP_SUBOBJECTS and MAX_SEXP_NODES
 * 
 * 149   3/17/98 4:29p Allender
 * allow the warp broken sexpressions
 * 
 * 148   3/15/98 3:41p Allender
 * new sexpression to gauge whether a ship warped out in proximity of jump
 * node
 * 
 * 147   3/09/98 4:31p Allender
 * multiplayer secondary weapon changes.  red-alert and cargo-known-delay
 * sexpressions.  Add time cargo revealed to ship structure
 * 
 * 146   3/02/98 9:17p Allender
 * four new sexpressions:  ships-(in)vulnerable.
 * percent-ships-(destroyed/departed)
 * 
 * 145   2/26/98 10:07p Hoffoss
 * Rewrote state saving and restoring to fix bugs and simplify the code.
 * 
 * 144   2/19/98 4:54p Allender
 * new sexpression to make ships visible/invisible on players sensors
 * 
 * 143   2/10/98 8:58p Allender
 * added hull damage to set/repair/sabotage subsystem
 * 
 * 142   1/30/98 4:23p Hoffoss
 * Added operators for debriefing checking.
 * 
 * 141   1/23/98 4:09p Hoffoss
 * Added a new operator format type to allow ships that aren't player
 * ships.  Made sabotage, repair and set-subsys-strength utilize it.
 * 
 * 140   1/20/98 4:49p Allender
 * new sexpression to help AI fire huge secondary weapons
 * 
 * 139   1/07/98 2:08p Hoffoss
 * Moved do-nothing operator so it appears last in the category's list.
 * 
 * 138   1/07/98 2:02p Johnson
 * Added do-nothing to change category.
 * 
 * 137   1/07/98 1:48p Hoffoss
 * Put do-nothing operator into change category so designers can make use
 * of it.
 * 
 * 136   1/05/98 4:26p Allender
 * added sexpression to flash a hud gauge -- a training only operator
 * 
 * 135   1/02/98 4:41p Allender
 * new sexpressions (not allowed yet) for changing warp status of ships
 * 
 * 134   12/19/97 2:59p Allender
 * more stuff to get persistent ships/weapons across campaign missions
 * 
 * 133   12/19/97 12:43p Hoffoss
 * Changed code to allow counts in directives.
 * 
 * 132   12/19/97 12:03p Allender
 * Added GM_CAMPAIGN_MODE to indicate when player is in a campaign or not.
 * Started adding FreeSpace support for carrying of ship/weapon types
 * across missions in a campaign.
 * 
 */

#ifndef _SEXP_H
#define _SEXP_H

struct ship_subsys;

// bumped to 30 by Goober5000
#define	OPERATOR_LENGTH	30  // if this ever exceeds TOKEN_LENGTH, let JasonH know!
#define	TOKEN_LENGTH		32

#ifdef FS2_DEMO
	#define	MAX_SEXP_NODES	1600
#else
	#define	MAX_SEXP_NODES	3000	// Reduced from 2000 to 1200 by MK on 4/1/98.
											//	Most used nodes is 698 in sm1-10a.  Sandeep thinks that's the most complex mission.
											// AL 2-4-98: upped to 1600, btm03 ran out of sexps, since campaign took a bunch
											// DA 12/15 bumped up to 2000 - Dan ran out
											// DaveB 9/02/99 bumped to 2200
											// Goober5000 01/20/2004 bumped to 3000

#endif

#define MAX_SEXP_VARIABLES 100

#define	MAX_SEXP_TEXT	2000
#define	MAX_OPERATORS	1024  // Yes, this is used, but not by the Sexp code.

// Operator argument formats (data types of an argument)
#define	OPF_NONE				1		// argument cannot exist at this position if it's this
#define	OPF_NULL				2		// no value.  Can still be used for type matching, however
#define	OPF_BOOL				3
#define	OPF_NUMBER				4
#define	OPF_SHIP				5
#define	OPF_WING				6
#define	OPF_SUBSYSTEM			7
#define	OPF_POINT				8		// either a 3d point in space, or a waypoint name
#define	OPF_IFF					9
#define	OPF_AI_GOAL				10		// special to match ai goals
#define	OPF_DOCKER_POINT		11		// docking point on docker ship
#define	OPF_DOCKEE_POINT		12		// docking point on dockee ship
#define	OPF_MESSAGE				13		// the name (id) of a message in Messages[] array
#define	OPF_WHO_FROM			14		// who sent the message -- doesn't necessarily have to be a ship!!!
#define	OPF_PRIORITY			15		// priority for messages
#define	OPF_WAYPOINT_PATH		16		// name of a waypoint
#define	OPF_POSITIVE			17		// positive number or zero
#define	OPF_MISSION_NAME		18		// name of a mission for various mission related things
#define	OPF_SHIP_POINT			19		// a waypoint or a ship
#define	OPF_GOAL_NAME			20		// name of goal (or maybe event?) from a mission
#define	OPF_SHIP_WING			21		// either a ship or wing name (they don't conflict)
#define	OPF_SHIP_WING_POINT		22		// name of a ship, wing, or a point
#define	OPF_SHIP_TYPE			23		// type of ship (fighter/bomber/etc)
#define	OPF_KEYPRESS			24		// a default key
#define	OPF_EVENT_NAME			25		// name of an event
#define	OPF_AI_ORDER			26		// a squadmsg order player can give to a ship
#define	OPF_SKILL_LEVEL			27		// current skill level of the game
#define	OPF_MEDAL_NAME			28		// name of medals
#define	OPF_WEAPON_NAME			29		// name of a weapon
#define	OPF_SHIP_CLASS_NAME		30		// name of a ship class
#define	OPF_HUD_GAUGE_NAME		31		// name of HUD gauge
#define	OPF_HUGE_WEAPON			32		// name of a secondary bomb type weapon
#define	OPF_SHIP_NOT_PLAYER		33		// a ship, but not a player ship
#define	OPF_JUMP_NODE_NAME		34		// name of a jump node
#define	OPF_VARIABLE_NAME		35		// variable name
#define	OPF_AMBIGUOUS			36		// type used with variable
#define	OPF_AWACS_SUBSYSTEM		37		// an awacs subsystem
#define OPF_CARGO				38		// Goober5000 - a cargo string (currently used for set-cargo and is-cargo)
#define OPF_AI_CLASS			39		// Goober5000 - an AI class
#define OPF_SUPPORT_SHIP_CLASS	40		// Goober5000 - a support ship class
#define OPF_ARRIVAL_LOCATION	41		// Goober5000 - a ship arrival location
#define OPF_ARRIVAL_ANCHOR_ALL	42		// Goober5000 - all of a ship's possible arrival anchors
#define OPF_DEPARTURE_LOCATION	43		// Goober5000 - a ship departure location
#define OPF_SHIP_WITH_BAY		44		// Goober5000 - a ship with a fighter bay
#define OPF_SOUNDTRACK_NAME		45		// Goober5000 - the name of a music soundtrack
#define OPF_INTEL_NAME			46		// Goober5000 - the name of an intel entry in species.tbl
#define OPF_STRING				47		// Goober5000 - any old string
#define OPF_ROTATING_SUBSYSTEM	48		// Goober5000 - a rotating subsystem

// Operand return types
#define	OPR_NUMBER		1	// returns number
#define	OPR_BOOL		2	// returns true/false value
#define	OPR_NULL		3	// doesn't return a value
#define	OPR_AI_GOAL		4	// is an ai operator (doesn't really return a value, but used for type matching)
#define	OPR_POSITIVE	5	// returns a non-negative number
#define	OPR_STRING		6	// not really a return type, but used for type matching.
#define	OPR_AMBIGUOUS	7	// not really a return type, but used for type matching.

#define	OP_INSERT_FLAG			0x8000
#define	OP_REPLACE_FLAG			0x4000
#define	OP_NONCAMPAIGN_FLAG		0x2000
#define	OP_CAMPAIGN_ONLY_FLAG	0x1000

// if we ever have more than 1024 (!)
// total sexps, we're going to have to
// figure out a different way of
// distinguishing between sexp identifier
// and sexp array index
#define	FIRST_OP				0x0400

// IMPORTANT: because of the way
// categories work, no category can
// have more than 256 sexps (mapped
// to 00 through ff) otherwise
// they'll overlap their category)
#define	OP_CATEGORY_OBJECTIVE	0x0400
#define	OP_CATEGORY_TIME		0x0500
#define	OP_CATEGORY_LOGICAL		0x0600
#define	OP_CATEGORY_ARITHMETIC	0x0700
#define	OP_CATEGORY_STATUS		0x0800
#define	OP_CATEGORY_CHANGE		0x0900
#define	OP_CATEGORY_CONDITIONAL	0x0a00
#define	OP_CATEGORY_AI			0x0b00  // used for AI goals
#define	OP_CATEGORY_TRAINING	0x0c00
#define	OP_CATEGORY_UNLISTED	0x0d00
#define	OP_CATEGORY_GOAL_EVENT	0x0f00	// final category can't be higher than 0x0f00,
										// to avoid overlap with flags above

#define	OP_CATEGORY_MASK		0x0f00	// 0000111100000000b


// The debug category is obsolete, so
// I removed it.  It originally took the
// place of OP_CATEGORY_CONDITIONAL,
// which was bumped (along with all the
// lower categories) so that FIRST_OP
// could be 0x0400.  This allows for
// 1024 possible sexps, as opposed to
// the 768 possible if the categories
// had not been bumped.
/*
#define	OP_CATEGORY_DEBUG		0x0a00
*/

// New subcategories! :) -- Goober5000
// Adding more subcategories is possible with the new code.  All that needs to be done is
// to add a #define here (a number from 0x0000 to 0x00ff ORred with the category that it
// goes under), some appropriate case statements in get_subcategory() (in sexp.cpp) that
// will return the subcategory for each sexp that uses it, and the submenu name in the
// op_submenu[] array in sexp_tree.cpp.
#define SUBCATEGORY_MASK									0x00ff
#define CHANGE_SUBCATEGORY_MESSAGING_AND_MISSION_GOALS		(0x0000 | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_AI_AND_IFF						(0x0001 | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_SUBSYSTEMS_AND_CARGO				(0x0002 | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_SHIP_STATUS						(0x0003 | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_BEAMS_AND_TURRETS				(0x0004 | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_MISSION_AND_CAMPAIGN				(0x0005 | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_SPECIAL							(0x0006 | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_MODELS_AND_TEXTURES				(0x0007 | OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_COORDINATE_MANIPULATION			(0x0008	| OP_CATEGORY_CHANGE)
#define CHANGE_SUBCATEGORY_MUSIC_AND_SOUND					(0x0009 | OP_CATEGORY_CHANGE)

#define	OP_PLUS									(0x0000 | OP_CATEGORY_ARITHMETIC)
#define	OP_MINUS								(0x0001 | OP_CATEGORY_ARITHMETIC)
#define	OP_MOD									(0x0002 | OP_CATEGORY_ARITHMETIC)
#define	OP_MUL									(0x0003 | OP_CATEGORY_ARITHMETIC)
#define	OP_DIV									(0x0004 | OP_CATEGORY_ARITHMETIC)
#define	OP_RAND									(0x0005 | OP_CATEGORY_ARITHMETIC)
#define OP_ABS									(0x0006	| OP_CATEGORY_ARITHMETIC)	// Goober5000
#define OP_MIN									(0x0007	| OP_CATEGORY_ARITHMETIC)	// Goober5000
#define OP_MAX									(0x0008	| OP_CATEGORY_ARITHMETIC)	// Goober5000
#define OP_AVG									(0x0009	| OP_CATEGORY_ARITHMETIC)	// Goober5000

#define	OP_TRUE									(0x0000 | OP_CATEGORY_LOGICAL)
#define	OP_FALSE									(0x0001 | OP_CATEGORY_LOGICAL)
#define	OP_AND									(0x0002 | OP_CATEGORY_LOGICAL)
#define	OP_AND_IN_SEQUENCE					(0x0003 | OP_CATEGORY_LOGICAL)
#define	OP_OR										(0x0004 | OP_CATEGORY_LOGICAL)
#define	OP_EQUALS								(0x0005 | OP_CATEGORY_LOGICAL)
#define	OP_GREATER_THAN						(0x0006 | OP_CATEGORY_LOGICAL)
#define	OP_LESS_THAN							(0x0007 | OP_CATEGORY_LOGICAL)
#define	OP_IS_IFF								(0x0008 | OP_CATEGORY_LOGICAL | OP_NONCAMPAIGN_FLAG)
#define	OP_HAS_TIME_ELAPSED					(0x0009 | OP_CATEGORY_LOGICAL | OP_NONCAMPAIGN_FLAG)
#define	OP_NOT									(0x000a | OP_CATEGORY_LOGICAL)

#define	OP_GOAL_INCOMPLETE					(0x0000 | OP_CATEGORY_GOAL_EVENT | OP_NONCAMPAIGN_FLAG)
#define	OP_GOAL_TRUE_DELAY					(0x0001 | OP_CATEGORY_GOAL_EVENT | OP_NONCAMPAIGN_FLAG)
#define	OP_GOAL_FALSE_DELAY					(0x0002 | OP_CATEGORY_GOAL_EVENT | OP_NONCAMPAIGN_FLAG)
#define	OP_EVENT_INCOMPLETE					(0x0003 | OP_CATEGORY_GOAL_EVENT | OP_NONCAMPAIGN_FLAG)
#define	OP_EVENT_TRUE_DELAY					(0x0004 | OP_CATEGORY_GOAL_EVENT | OP_NONCAMPAIGN_FLAG)
#define	OP_EVENT_FALSE_DELAY					(0x0005 | OP_CATEGORY_GOAL_EVENT | OP_NONCAMPAIGN_FLAG)
#define	OP_PREVIOUS_EVENT_TRUE				(0x0006 | OP_CATEGORY_GOAL_EVENT)
#define	OP_PREVIOUS_EVENT_FALSE				(0x0007 | OP_CATEGORY_GOAL_EVENT)
#define	OP_PREVIOUS_GOAL_TRUE				(0x0009 | OP_CATEGORY_GOAL_EVENT)
#define	OP_PREVIOUS_GOAL_FALSE				(0x000a | OP_CATEGORY_GOAL_EVENT)

#define	OP_IS_DESTROYED_DELAY				(0x0008 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define	OP_IS_SUBSYSTEM_DESTROYED_DELAY	(0x0009 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define	OP_IS_DISABLED_DELAY					(0x000a | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define	OP_IS_DISARMED_DELAY					(0x000b | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define	OP_HAS_DOCKED_DELAY					(0x000c | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define	OP_HAS_UNDOCKED_DELAY				(0x000d | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define	OP_HAS_ARRIVED_DELAY					(0x000e | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define	OP_HAS_DEPARTED_DELAY				(0x000f | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define	OP_WAYPOINTS_DONE_DELAY				(0x0011 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define	OP_SHIP_TYPE_DESTROYED				(0x0012 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define	OP_PERCENT_SHIPS_DEPARTED			(0x0013 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define	OP_PERCENT_SHIPS_DESTROYED			(0x0014 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define	OP_DEPART_NODE_DELAY					(0x0015 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define	OP_DESTROYED_DEPARTED_DELAY			(0x0016 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)
#define OP_PERCENT_SHIPS_DISARMED			(0x0017 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_PERCENT_SHIPS_DISABLED			(0x0018 | OP_CATEGORY_OBJECTIVE | OP_NONCAMPAIGN_FLAG)	// Goober5000

#define	OP_TIME_SHIP_DESTROYED				(0x0000 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)
#define	OP_TIME_SHIP_ARRIVED					(0x0001 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)
#define	OP_TIME_SHIP_DEPARTED				(0x0002 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)
#define	OP_TIME_WING_DESTROYED				(0x0003 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)
#define	OP_TIME_WING_ARRIVED					(0x0004 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)
#define	OP_TIME_WING_DEPARTED				(0x0005 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)
#define	OP_MISSION_TIME						(0x0006 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)
#define	OP_TIME_DOCKED							(0x0007 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)
#define	OP_TIME_UNDOCKED						(0x0008 | OP_CATEGORY_TIME | OP_NONCAMPAIGN_FLAG)

#define	OP_SHIELDS_LEFT						(0x0000 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_HITS_LEFT						(0x0001 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_HITS_LEFT_SUBSYSTEM				(0x0002 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_DISTANCE							(0x0003 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_DISTANCE_SUBSYSTEM				(0x0004 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define	OP_LAST_ORDER_TIME					(0x0005 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_NUM_PLAYERS						(0x0006 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_SKILL_LEVEL_AT_LEAST				(0x0007 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_WAS_PROMOTION_GRANTED			(0x0008 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_WAS_MEDAL_GRANTED				(0x0009 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_CARGO_KNOWN_DELAY				(0x000a | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_CAP_SUBSYS_CARGO_KNOWN_DELAY		(0x000b | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_HAS_BEEN_TAGGED_DELAY			(0x000c | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_IS_TAGGED						(0x000d | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_NUM_KILLS						(0x000e | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_NUM_TYPE_KILLS					(0x000f | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_NUM_CLASS_KILLS					(0x0010 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define  OP_SHIELD_RECHARGE_PCT				(0x0011 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define  OP_ENGINE_RECHARGE_PCT				(0x0012 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define  OP_WEAPON_RECHARGE_PCT				(0x0013 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_SHIELD_QUAD_LOW					(0x0014 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_SECONDARY_AMMO_PCT				(0x0015 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_IS_SECONDARY_SELECTED			(0x0016 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_IS_PRIMARY_SELECTED				(0x0017 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_SPECIAL_WARP_DISTANCE			(0x0018 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_IS_SHIP_VISIBLE					(0x0019 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define	OP_TEAM_SCORE						(0x001a | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)
#define OP_PRIMARY_AMMO_PCT					(0x001b | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_IS_SHIP_STEALTHY					(0x001c | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_IS_CARGO							(0x001d | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_IS_FRIENDLY_STEALTH_VISIBLE		(0x001e | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_GET_OBJECT_X						(0x001f	| OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_GET_OBJECT_Y						(0x0020	| OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_GET_OBJECT_Z						(0x0021	| OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_GET_OBJECT_RELATIVE_X			(0x0022 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_GET_OBJECT_RELATIVE_Y			(0x0023 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_GET_OBJECT_RELATIVE_Z			(0x0024 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_IS_AI_CLASS						(0x0025 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_IS_SHIP_TYPE						(0x0026 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_IS_SHIP_CLASS					(0x0027	| OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_NUM_SHIPS_IN_BATTLE				(0x0028 | OP_CATEGORY_STATUS | OP_NONCAMPAIGN_FLAG)	// phreak

// conditional sexpressions
#define OP_WHEN									(0x0000 | OP_CATEGORY_CONDITIONAL)

// sexpressions with side-effects
#define OP_CHANGE_IFF						(0x0000 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_REPAIR_SUBSYSTEM					(0x0001 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SABOTAGE_SUBSYSTEM				(0x0002 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SET_SUBSYSTEM_STRNGTH			(0x0003 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_PROTECT_SHIP						(0x0004 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SEND_MESSAGE						(0x0005 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SELF_DESTRUCT					(0x0006 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_CLEAR_GOALS						(0x0007 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_ADD_GOAL							(0x0008 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_INVALIDATE_GOAL					(0x0009 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_VALIDATE_GOAL					(0x000a | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SEND_RANDOM_MESSAGE				(0x000b | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TRANSFER_CARGO					(0x000c | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_EXCHANGE_CARGO					(0x000d | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_UNPROTECT_SHIP					(0x000e | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_GOOD_REARM_TIME					(0x0010 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_BAD_REARM_TIME					(0x0011 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_GRANT_PROMOTION					(0x0012 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_GRANT_MEDAL						(0x0013 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_ALLOW_SHIP						(0x0014 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_ALLOW_WEAPON						(0x0015 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_GOOD_SECONDARY_TIME				(0x0016 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_WARP_BROKEN						(0x0017 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_WARP_NOT_BROKEN					(0x0018 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_WARP_NEVER						(0x0019 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_WARP_ALLOWED						(0x0020 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SHIP_INVISIBLE					(0x0021 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SHIP_VISIBLE						(0x0022 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SHIP_INVULNERABLE				(0x0023 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SHIP_VULNERABLE					(0x0024 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_RED_ALERT						(0x0025 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TECH_ADD_SHIP					(0x0026 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TECH_ADD_WEAPON					(0x0027 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_END_CAMPAIGN						(0x0028 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_JETTISON_CARGO					(0x0029 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_MODIFY_VARIABLE					(0X0030 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_NOP								(0x0031 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_BEAM_FIRE						(0x0032 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_BEAM_FREE						(0x0033 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_BEAM_FREE_ALL					(0x0034 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_BEAM_LOCK						(0x0035 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_BEAM_LOCK_ALL					(0x0036 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_BEAM_PROTECT_SHIP				(0x0037 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_BEAM_UNPROTECT_SHIP				(0x0038 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TURRET_FREE						(0x0039 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TURRET_FREE_ALL					(0x0040 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TURRET_LOCK						(0x0041 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TURRET_LOCK_ALL					(0x0042 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_ADD_REMOVE_ESCORT				(0x0043 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_AWACS_SET_RADIUS					(0x0044 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SEND_MESSAGE_LIST				(0x0045 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_CAP_WAYPOINT_SPEED				(0x0046 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SHIP_GUARDIAN					(0x0047 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SHIP_NO_GUARDIAN					(0x0048 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TURRET_TAGGED_ONLY_ALL			(0x0049 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_TURRET_TAGGED_CLEAR_ALL			(0x0050 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SUBSYS_SET_RANDOM				(0x0051 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SUPERNOVA_START					(0x0052 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_CARGO_NO_DEPLETE					(0x0053 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SET_SPECIAL_WARPOUT_NAME			(0X0054 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SHIP_VANISH						(0X0055 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)
#define OP_SHIELDS_ON						(0x0058 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	//-Sesquipedalian
#define OP_SHIELDS_OFF						(0x0059 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	//-Sesquipedalian
#define OP_CHANGE_AI_LEVEL					(0x0060 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	//-Sesquipedalian
#define OP_END_MISSION						(0x0061 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) //-Sesquipedalian. replaces end-mission-delay, which did nothing
#define OP_SET_SCANNED						(0x0062 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_SET_UNSCANNED					(0x0063	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_SHIP_STEALTHY					(0x0064	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_SHIP_UNSTEALTHY					(0x0065	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_SET_CARGO						(0x0066	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_CHANGE_AI_CLASS					(0x0067 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_FRIENDLY_STEALTH_INVISIBLE		(0x0068	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_FRIENDLY_STEALTH_VISIBLE			(0x0069	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_DAMAGED_ESCORT_LIST				(0x006a | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) //phreak
#define OP_DAMAGED_ESCORT_LIST_ALL			(0x006b	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_SHIP_VAPORIZE					(0x006c	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_SHIP_NO_VAPORIZE					(0x006d	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_COLLIDE_INVISIBLE				(0x006e	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_DONT_COLLIDE_INVISIBLE			(0x006f	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_PRIMITIVE_SENSORS_SET_RANGE		(0x0070	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_CHANGE_SHIP_CLASS				(0x0071	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_CHANGE_SHIP_MODEL				(0x0072	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_SET_SUPPORT_SHIP					(0x0073 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_DEACTIVATE_GLOW_POINTS			(0x0074	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	//-Bobboau
#define OP_ACTIVATE_GLOW_POINTS				(0x0075	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	//-Bobboau
#define OP_DEACTIVATE_GLOW_MAPS				(0x0076	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	//-Bobboau
#define OP_ACTIVATE_GLOW_MAPS				(0x0077	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	//-Bobboau
#define OP_DEACTIVATE_GLOW_POINT_BANK		(0x0078	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	//-Bobboau
#define OP_ACTIVATE_GLOW_POINT_BANK			(0x0079	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	//-Bobboau
#define OP_CHANGE_SOUNDTRACK				(0x007a	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_TECH_ADD_INTEL					(0x007b	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_TECH_RESET_TO_DEFAULT			(0x007c	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_EXPLOSION_EFFECT					(0x007d | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_WARP_EFFECT						(0x007e | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_SET_SHIP_FACING					(0x007f | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_SET_SHIP_FACING_OBJECT			(0x0080 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_SET_SHIP_POSITION				(0x0081	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_PLAY_SOUND_FROM_TABLE			(0x0082	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_PLAY_SOUND_FROM_FILE				(0x0083	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_CLOSE_SOUND_FROM_FILE			(0x0084 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_TOGGLE_HUD						(0x0085	| OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_KAMIKAZE							(0x0086 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	//-Sesquipedalian
#define OP_NOT_KAMIKAZE						(0x0087 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	//-Sesquipedalian
#define OP_TURRET_TAGGED_SPECIFIC			(0x0088 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) //phreak
#define OP_TURRET_TAGGED_CLEAR_SPECIFIC		(0x0089 | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG) //phreak
#define OP_LOCK_ROTATING_SUBSYSTEM			(0x008a | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_FREE_ROTATING_SUBSYSTEM			(0x008b | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_PLAYER_USE_AI					(0x008c | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_PLAYER_NOT_USE_AI				(0x008d | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000
#define OP_FORCE_JUMP						(0x008e | OP_CATEGORY_CHANGE | OP_NONCAMPAIGN_FLAG)	// Goober5000

/* made obsolete by Goober5000
// debugging sexpressions
#define	OP_INT3									(0x0000 | OP_CATEGORY_DEBUG)
*/

// defined for AI goals
#define OP_AI_CHASE								(0x0000 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_DOCK								(0x0001 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_UNDOCK								(0x0002 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_WARP_OUT							(0x0003 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_WAYPOINTS							(0x0004 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_WAYPOINTS_ONCE					(0x0005 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_DESTROY_SUBSYS					(0x0006 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_DISABLE_SHIP						(0x0008 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_DISARM_SHIP						(0x0009 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_GUARD								(0x000a | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_CHASE_ANY							(0x000b | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_EVADE_SHIP						(0x000d | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_STAY_NEAR_SHIP					(0x000e | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_KEEP_SAFE_DISTANCE				(0x000f | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_IGNORE								(0x0010 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_STAY_STILL						(0x0011 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_PLAY_DEAD							(0x0012 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)
#define OP_AI_CHASE_ANY_EXCEPT					(0x0013 | OP_CATEGORY_AI | OP_NONCAMPAIGN_FLAG)	// Goober5000

#define OP_GOALS_ID								(0x0001 | OP_CATEGORY_UNLISTED)
#define OP_NEXT_MISSION							(0x0002 | OP_CATEGORY_UNLISTED)		// used in campaign files for branching
#define OP_IS_DESTROYED							(0x0003 | OP_CATEGORY_UNLISTED)
#define OP_IS_SUBSYSTEM_DESTROYED			(0x0004 | OP_CATEGORY_UNLISTED)
#define OP_IS_DISABLED							(0x0005 | OP_CATEGORY_UNLISTED)
#define OP_IS_DISARMED							(0x0006 | OP_CATEGORY_UNLISTED)
#define OP_HAS_DOCKED							(0x0007 | OP_CATEGORY_UNLISTED)
#define OP_HAS_UNDOCKED							(0x0008 | OP_CATEGORY_UNLISTED)
#define OP_HAS_ARRIVED							(0x0009 | OP_CATEGORY_UNLISTED)
#define OP_HAS_DEPARTED							(0x000a | OP_CATEGORY_UNLISTED)
#define OP_WAYPOINTS_DONE						(0x000b | OP_CATEGORY_UNLISTED)
#define OP_ADD_SHIP_GOAL						(0x000c | OP_CATEGORY_UNLISTED)
#define OP_CLEAR_SHIP_GOALS					(0x000d | OP_CATEGORY_UNLISTED)
#define OP_ADD_WING_GOAL						(0x000e | OP_CATEGORY_UNLISTED)
#define OP_CLEAR_WING_GOALS					(0x000f | OP_CATEGORY_UNLISTED)
#define OP_AI_CHASE_WING						(0x0010 | OP_CATEGORY_UNLISTED)
#define OP_AI_GUARD_WING						(0x0011 | OP_CATEGORY_UNLISTED)
#define OP_EVENT_TRUE							(0x0012 | OP_CATEGORY_UNLISTED)
#define OP_EVENT_FALSE							(0x0013 | OP_CATEGORY_UNLISTED)
#define OP_PREVIOUS_GOAL_INCOMPLETE			(0x0014 | OP_CATEGORY_UNLISTED)
#define OP_PREVIOUS_EVENT_INCOMPLETE		(0x0015 | OP_CATEGORY_UNLISTED)
#define OP_AI_WARP								(0x0016 | OP_CATEGORY_UNLISTED)
#define OP_IS_CARGO_KNOWN						(0x001c | OP_CATEGORY_UNLISTED)
#define OP_COND									(0x001e | OP_CATEGORY_UNLISTED)
#define OP_END_OF_CAMPAIGN						(0x001f | OP_CATEGORY_UNLISTED)

#define OP_KEY_PRESSED							(0x0000 | OP_CATEGORY_TRAINING)
#define OP_KEY_RESET								(0x0001 | OP_CATEGORY_TRAINING)
#define OP_TARGETED								(0x0002 | OP_CATEGORY_TRAINING)
#define OP_SPEED									(0x0003 | OP_CATEGORY_TRAINING)
#define OP_FACING									(0x0004 | OP_CATEGORY_TRAINING)
#define OP_ORDER									(0x0005 | OP_CATEGORY_TRAINING)
#define OP_WAYPOINT_MISSED						(0x0006 | OP_CATEGORY_TRAINING)
#define OP_PATH_FLOWN							(0x0007 | OP_CATEGORY_TRAINING)
#define OP_WAYPOINT_TWICE						(0x0008 | OP_CATEGORY_TRAINING)
#define OP_TRAINING_MSG							(0x0009 | OP_CATEGORY_TRAINING)
#define OP_FLASH_HUD_GAUGE						(0x000a | OP_CATEGORY_TRAINING)
#define OP_SPECIAL_CHECK						(0x000b | OP_CATEGORY_TRAINING)
#define OP_SECONDARIES_DEPLETED				(0x000c | OP_CATEGORY_TRAINING)
#define OP_FACING2								(0x000d | OP_CATEGORY_TRAINING)
#define OP_PRIMARIES_DEPLETED					(0x000e | OP_CATEGORY_TRAINING)	// Goober5000
#define OP_MISSILE_LOCKED						(0x000f | OP_CATEGORY_TRAINING)	// Sesquipedalian

#define OP_SET_TRAINING_CONTEXT_FLY_PATH	(0x0080 | OP_CATEGORY_TRAINING)
#define OP_SET_TRAINING_CONTEXT_SPEED		(0x0081 | OP_CATEGORY_TRAINING)

// defines for string constants
#define SEXP_HULL_STRING			"Hull"

// macros for accessing sexpression atoms
#define CAR(n)		(Sexp_nodes[n].first)
#define CDR(n)		(Sexp_nodes[n].rest)
#define CADR(n)	(Sexp_nodes[Sexp_nodes[n].rest].first)
// #define CTEXT(n)	(Sexp_nodes[n].text)
char *CTEXT(int n);

// added by Goober5000
#define CDDR(n)		CDR(CDR(n))
#define CDDDR(n)	CDR(CDDR(n))
#define CDDDDR(n)	CDR(CDDDR(n))
#define CADDR(n)	CAR(CDDR(n))
#define CADDDR(n)	CAR(CDDDR(n))
#define CADDDDR(n)	CAR(CDDDDR(n))

#define REF_TYPE_SHIP		1
#define REF_TYPE_WING		2
#define REF_TYPE_PLAYER		3
#define REF_TYPE_WAYPOINT	4
#define REF_TYPE_PATH		5	// waypoint path

#define SRC_SHIP_ARRIVAL	0x10000
#define SRC_SHIP_DEPARTURE	0x20000
#define SRC_WING_ARRIVAL	0x30000
#define SRC_WING_DEPARTURE	0x40000
#define SRC_EVENT				0x50000
#define SRC_MISSION_GOAL	0x60000
#define SRC_SHIP_ORDER		0x70000
#define SRC_WING_ORDER		0x80000
#define SRC_DEBRIEFING		0x90000
#define SRC_BRIEFING			0xa0000
#define SRC_UNKNOWN			0xffff0000
#define SRC_MASK				0xffff0000
#define SRC_DATA_MASK		0xffff

#define SEXP_MODE_GENERAL	0
#define SEXP_MODE_CAMPAIGN	1

// defines for type field of sexp nodes.  The actual type of the node will be stored in the lower
// two bytes of the field.  The upper two bytes will be used for flags (bleah...)
// Be sure not to conflict with type field of sexp_variable
#define SEXP_NOT_USED		0
#define SEXP_LIST				1
#define SEXP_ATOM				2

// flags for sexpressions -- masked onto the end of the type field
#define SEXP_FLAG_PERSISTENT				(1<<31)		// should this sexp node be persistant across missions
#define SEXP_FLAG_VARIABLE					(1<<30)

// sexp variable definitions
#define SEXP_VARIABLE_CHAR					('@')
// defines for type field of sexp_variable.  Be sure not to conflict with type field of sexp_node
#define SEXP_VARIABLE_NUMBER				(1<<4)	//	(0x0010)
#define SEXP_VARIABLE_STRING				(1<<5)	//	(0x0020)
#define SEXP_VARIABLE_UNKNOWN				(1<<6)	//	(0x0040)
#define SEXP_VARIABLE_NOT_USED				(1<<7)	//	(0x0080)

#define SEXP_VARIABLE_BLOCK					(1<<0)	//	(0x0001)
#define SEXP_VARIABLE_BLOCK_EXP				(1<<1)	//	(0x0002)
#define SEXP_VARIABLE_BLOCK_HIT				(1<<2)	//	(0x0004)
#define SEXP_VARIABLE_PLAYER_PERSISTENT		(1<<3)	//	(0x0008)

// Goober5000 - hopefully this should work and not conflict with anything
#define SEXP_VARIABLE_CAMPAIGN_PERSISTENT	(1<<29)	//	(0x0100)

#define BLOCK_EXP_SIZE					6
#define INNER_RAD							0
#define OUTER_RAD							1
#define DAMAGE								2
#define BLAST								3
#define PROPAGATE							4
#define SHOCK_SPEED						5

#define BLOCK_HIT_SIZE					2
#define SHIELD_STRENGTH					0
#define HULL_STRENGTH					1


#define SEXP_VARIABLE_SET				(0x0100)
#define SEXP_VARIABLE_MODIFIED		(0x0200)

#define SEXP_TYPE_MASK(t)	(t & 0x00ff)
#define SEXP_NODE_TYPE(n)	(Sexp_nodes[n].type & 0x00ff)

// defines for subtypes of atoms
#define SEXP_ATOM_LIST			0
#define SEXP_ATOM_OPERATOR		1
#define SEXP_ATOM_NUMBER		2
#define SEXP_ATOM_STRING		3

// defines to short circuit evaluation when possible. Also used when goals can't
// be satisfied yet because ship (or wing) hasn't been created yet.

#define SEXP_TRUE			1
#define SEXP_FALSE			0
// Goober5000: changed these to unlikely values, because now we have sexps using negative numbers
#define SEXP_KNOWN_FALSE	-32767	//-1
#define SEXP_KNOWN_TRUE		-32766	//-2
#define SEXP_UNKNOWN		-32765	//-3
#define SEXP_NAN			-32764	//-4	// not a number -- used when ships/wing part of boolean and haven't arrived yet
#define SEXP_NAN_FOREVER	-32763	//-5	// not a number and will never change -- used to falsify boolean sexpressions
#define SEXP_CANT_EVAL		-32762	//-6	// can't evaluate yet for whatever reason (acts like false)
#define SEXP_NUM_EVAL		-32761	//-7	// already completed an arithmetic operation and result is stored

// defines for check_sexp_syntax
#define SEXP_CHECK_NONOP_ARGS			-1			// non-operator has arguments
#define SEXP_CHECK_OP_EXPECTED		-2			// operator expected, but found data instead
#define SEXP_CHECK_UNKNOWN_OP			-3			// unrecognized operator
#define SEXP_CHECK_TYPE_MISMATCH		-4			// return type or data type mismatch
#define SEXP_CHECK_BAD_ARG_COUNT		-5			// argument count in incorrect
#define SEXP_CHECK_UNKNOWN_TYPE		-6			// unrecognized return type of data type

#define SEXP_CHECK_INVALID_NUM					-101		// number is not valid
#define SEXP_CHECK_INVALID_SHIP					-102		// invalid ship name
#define SEXP_CHECK_INVALID_WING					-103		// invalid wing name
#define SEXP_CHECK_INVALID_SUBSYS				-104		// invalid subsystem
#define SEXP_CHECK_INVALID_IFF					-105		// invalid iff string
#define SEXP_CHECK_INVALID_POINT					-106		// invalid point
#define SEXP_CHECK_NEGATIVE_NUM					-107		// negative number wasn't allowed
#define SEXP_CHECK_INVALID_SHIP_WING			-108	// invalid ship/wing
#define SEXP_CHECK_INVALID_SHIP_TYPE			-109	// invalid ship type
#define SEXP_CHECK_UNKNOWN_MESSAGE				-110	// invalid message
#define SEXP_CHECK_INVALID_PRIORITY				-111	// invalid priority for a message
#define SEXP_CHECK_INVALID_MISSION_NAME		-112	// invalid mission name
#define SEXP_CHECK_INVALID_GOAL_NAME			-113	// invalid goal name
#define SEXP_CHECK_INVALID_LEVEL					-114	// mission level too high in campaign
#define SEXP_CHECK_INVALID_MSG_SOURCE			-115	// invalid 'who-from' for a message being sent
#define SEXP_CHECK_INVALID_DOCKER_POINT		-116
#define SEXP_CHECK_INVALID_DOCKEE_POINT		-117
#define SEXP_CHECK_ORDER_NOT_ALLOWED			-118	// ship goal (order) isn't allowed for given ship
#define SEXP_CHECK_DOCKING_NOT_ALLOWED			-119
#define SEXP_CHECK_NUM_RANGE_INVALID			-120
#define SEXP_CHECK_INVALID_EVENT_NAME			-121
#define SEXP_CHECK_INVALID_SKILL_LEVEL			-122
#define SEXP_CHECK_INVALID_MEDAL_NAME			-123
#define SEXP_CHECK_INVALID_WEAPON_NAME			-124
#define SEXP_CHECK_INVALID_SHIP_CLASS_NAME	-125
#define SEXP_CHECK_INVALID_GAUGE_NAME			-126
#define SEXP_CHECK_INVALID_JUMP_NODE			-127
#define SEXP_CHECK_INVALID_VARIABLE				-128
#define SEXP_CHECK_INVALID_AI_CLASS				-129
#define SEXP_CHECK_UNKNOWN_ERROR				-130
#define SEXP_CHECK_INVALID_SUPPORT_SHIP_CLASS	-131
#define SEXP_CHECK_INVALID_SHIP_WITH_BAY		-132
#define SEXP_CHECK_INVALID_ARRIVAL_LOCATION		-133
#define SEXP_CHECK_INVALID_DEPARTURE_LOCATION	-134
#define SEXP_CHECK_INVALID_ARRIVAL_ANCHOR_ALL	-135
#define SEXP_CHECK_INVALID_SOUNDTRACK_NAME		-136
#define SEXP_CHECK_INVALID_INTEL_NAME			-137

#define TRAINING_CONTEXT_SPEED		(1<<0)
#define TRAINING_CONTEXT_FLY_PATH	(1<<1)

// numbers used in special_training_check() function
#define SPECIAL_CHECK_TRAINING_FAILURE	2000

typedef struct sexp_ai_goal_link {
	int ai_goal;
	int op_code;
} sexp_ai_goal_link;

typedef struct sexp_oper {
	char	*text;
	int	value;
	int	min, max;
} sexp_oper;

typedef struct sexp_node {
	char	text[TOKEN_LENGTH];
	int	type;						// atom, list, or not used
	int	subtype;					// type of atom or list?
	int	first;					// if first parameter is sexp, index into Sexp_nodes
	int	rest;						// index into Sexp_nodes of rest of parameters
	int	value;					// known to be true, known to be false, or not known
} sexp_node;

typedef struct sexp_variable {
	int		type;
	char	text[TOKEN_LENGTH];
	char	variable_name[TOKEN_LENGTH];
} sexp_variable;

// next define used to eventually mark a directive as satisfied even though there may be more
// waves for a wing.  bascially a hack for the directives display.
#define DIRECTIVE_WING_ZERO		-999

extern sexp_oper Operators[];
extern sexp_node Sexp_nodes[MAX_SEXP_NODES];
extern sexp_variable Sexp_variables[MAX_SEXP_VARIABLES];
extern int Num_operators;
extern int Locked_sexp_true, Locked_sexp_false;
extern int Directive_count;
extern int Sexp_useful_number;  // a variable to pass useful info in from external modules
extern char *Sexp_string;
extern int Training_context;
extern int Training_context_speed_min;
extern int Training_context_speed_max;
extern int Training_context_speed_set;
extern int Training_context_speed_timestamp;
extern int Training_context_path;
extern int Training_context_goal_waypoint;
extern int Training_context_at_waypoint;
extern float Training_context_distance;
extern int Players_target;
extern int Players_mlocked;
extern ship_subsys *Players_targeted_subsys;
extern int Players_target_timestamp;
extern int Players_mlocked_timestamp;
extern int Sexp_clipboard;  // used by Fred

extern void init_sexp();
extern int alloc_sexp(char *text, int type, int subtype, int first, int rest);
extern int find_free_sexp();
extern int free_one_sexp(int num);
extern int free_sexp(int num);
extern int free_sexp2(int num);
extern int dup_sexp_chain(int node);
extern int cmp_sexp_chains(int node1, int node2);
extern int find_sexp_list(int num);
extern int find_parent_operator(int num);
extern int is_sexp_top_level( int node );
extern int identify_operator(char *token);
extern int find_operator(char *token);
extern int query_sexp_args_count(int index);
extern int check_sexp_syntax(int index, int return_type = OPR_BOOL, int recursive = 0, int *bindex = 0 /*NULL*/, int mode = 0);
extern int get_sexp_main(void);	//	Returns start node
extern int stuff_sexp_variable_list();
extern int eval_sexp(int index);
extern int query_operator_return_type(int op);
extern int query_operator_argument_type(int op, int argnum);
extern void update_sexp_references(char *old_name, char *new_name);
extern void update_sexp_references(char *old_name, char *new_name, int format);
extern int query_referenced_in_sexp(int mode, char *name, int *node);
extern int verify_vector(char *text);
extern void skip_white(char **str);
extern int validate_float(char **str);
extern int build_sexp_string(int cur_node, int level, int mode);
extern int sexp_query_type_match(int opf, int opr);
extern char *sexp_error_message(int num);
extern int count_free_sexp_nodes();

// functions to change the attributes of an sexpression tree to persistent or not persistent
extern void sexp_unmark_persistent( int n );
extern void sexp_mark_persistent( int n );
extern int waypoint_lookup(char *name);
extern int verify_sexp_tree(int node);
extern int query_sexp_ai_goal_valid(int sexp_ai_goal, int ship);
int query_node_in_sexp(int node, int sexp);
void flush_sexp_tree(int node);

// sexp_variable
void sexp_modify_variable(int);
void sexp_modify_variable(char *text, int index);
int get_index_sexp_variable_name(const char* temp_name);
int sexp_variable_count();
int sexp_campaign_persistent_variable_count();	// Goober5000
void sexp_variable_delete(int index);
void sexp_variable_sort();
void sexp_fred_modify_variable(const char *text, const char *var_name, int index, int type);
int sexp_add_variable(const char *text, const char *var_name, int type, int index=-1);
int sexp_variable_allocate_block(const char* block_name, int block_type);
void sexp_variable_condense_block();
void sexp_variable_block_free(const char *ship_name, int start_index, int block_type);

// menu and category stuff
extern int get_subcategory(int sexp_id);

// Goober5000
extern void sexp_music_close();

#endif
