/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Ship/AiBig.h $
 * $Revision: 1.2 $
 * $Date: 2005-04-05 05:53:13 $
 * $Author: taylor $
 *
 * Header file for AI code related to large ships
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2005/03/25 06:45:12  wmcoolmon
 * Initial AI code move commit - note that aigoals.cpp has some escape characters in it, I'm not sure if this is really a problem.
 *
 * Revision 2.2  2004/08/11 05:06:34  Kazan
 * added preprocdefines.h to prevent what happened with fred -- make sure to make all fred2 headers include this file as the _first_ include -- i have already modified fs2 files to do this
 *
 * Revision 2.1  2004/03/05 09:01:51  Goober5000
 * Uber pass at reducing #includes
 * --Goober5000
 *
 * Revision 2.0  2002/06/03 04:02:28  penguin
 * Warpcore CVS sync
 *
 * Revision 1.1  2002/05/02 18:03:12  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 2     10/07/98 10:53a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:51a Dave
 * 
 * 13    4/29/98 5:01p Mike
 * Large overhaul in how turrets fire.
 * 
 * 12    4/27/98 11:59p Mike
 * Intermediate checkin.  Getting big ship turrets firing at big ships to
 * use pick_big_attack_point.
 * 
 * 11    3/21/98 3:36p Mike
 * Fix/optimize attacking of big ships.
 * 
 * 10    1/29/98 1:39p Mike
 * Better heat seeking homing on big ships.
 * 
 * 9     1/22/98 5:14p Lawrance
 * clean up ai_big code, clear path info when stop attacking a subsystem
 * 
 * 8     1/06/98 6:58p Lawrance
 * Attack turrets (sometimes) when fired upon while attacking a ship.
 * 
 * 7     12/15/97 7:16p Lawrance
 * improving subsystem attacking
 * 
 * 6     12/01/97 5:11p Lawrance
 * make strafe mode more effective... slow down when approaching and use
 * afterburner in avoids
 * 
 * 5     10/30/97 9:17p Lawrance
 * work on getting AIM_STRAFE working well with disable/disarm, try to
 * balance
 * 
 * 4     10/30/97 12:32a Lawrance
 * further work on AIM_STRAFE
 * 
 * 3     10/29/97 6:24p Lawrance
 * extern ai_strafe()
 * 
 * 2     10/26/97 3:24p Lawrance
 * split off large ship ai code into AiBig.cpp
 *
 * $NoKeywords: $
 */

#include "PreProcDefines.h"
#ifndef __AIBIG_H__
#define __AIBIG_H__

struct object;
struct ai_info;
struct vec3d;
struct ship_subsys;

void	ai_big_ship(object *objp);
void	ai_big_chase();
void	ai_big_subsys_path_cleanup(ai_info *aip);

// strafe functions
void	ai_big_strafe();
int	ai_big_maybe_enter_strafe_mode(object *objp, int weapon_objnum, int consider_target_only=0);
void	ai_big_strafe_maybe_attack_turret(object *ship_objp, object *weapon_objp);
void ai_big_pick_attack_point(object *objp, object *attacker_objp, vec3d *attack_point, float fov=1.0f);
void ai_big_pick_attack_point_turret(object *objp, ship_subsys *ssp, vec3d *gpos, vec3d *gvec, vec3d *attack_point, float weapon_travel_dist, float fov=1.0f);


#endif

