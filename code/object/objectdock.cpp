/*
 * Created by Ian "Goober5000" Warfield for the Freespace2 Source Code Project.
 * You may not sell or otherwise commercially exploit the source or things you
 * create based on the source.
 *
 */ 

/*
 * $Logfile: /Freespace2/code/Object/ObjectDock.cpp $
 * $Revision: 2.1 $
 * $Date: 2005-01-11 21:38:49 $
 * $Author: Goober5000 $
 *
 * Implementation of new docking system
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.0  2004/12/30 16:35:00  Goober5000
 * Addition to CVS repository
 *
 */

#include "globalincs/pstypes.h"
#include "object/objectdock.h"
#include "object/object.h"
#include "math/bitarray.h"
#include "ship/ship.h"
#include "math/vecmat.h"
#include "mission/missionparse.h"




// helper prototypes

void dock_evaluate_tree(object *objp, dock_function_info *infop, void (*function)(object *, dock_function_info *), char *visited_bitstring);
void dock_move_docked_children_tree(object *objp, object *parent_objp);
void dock_count_total_docked_objects_helper(object *objp, dock_function_info *infop);
void dock_check_find_docked_object_helper(object *objp, dock_function_info *infop);
void dock_calc_docked_center_helper(object *objp, dock_function_info *infop);
void dock_calc_docked_center_of_mass_helper(object *objp, dock_function_info *infop);
void dock_calc_total_docked_mass_helper(object *objp, dock_function_info *infop);
void dock_calc_cross_sectional_radius_squared_perpendicular_to_line_helper(object *objp, dock_function_info *infop);
void dock_find_max_speed_helper(object *objp, dock_function_info *infop);
void dock_find_max_fspeed_helper(object *objp, dock_function_info *infop);


// management prototypes

bool dock_check_assume_hub();
object *dock_get_hub(object *objp);

void dock_add_instance(object *objp, int dockpoint, object *other_objp);
void dock_remove_instance(object *objp, object *other_objp);
dock_instance *dock_find_instance(object *objp, object *other_objp);
dock_instance *dock_find_instance(object *objp, int dockpoint);
int dock_count_instances(object *objp);



object *dock_get_first_docked_object(object *objp)
{
	// are we docked?
	if (!object_is_docked(objp))
		return NULL;

	return objp->dock_list->docked_objp;
}

bool dock_check_docked_one_on_one(object *objp)
{
	// we must be docked
	if (!object_is_docked(objp))
		return false;
	
	// our dock list must contain only one object
	if (objp->dock_list->next != NULL)
		return false;

	// the other guy's dock list must contain only one object
	if (dock_get_first_docked_object(objp)->dock_list->next != NULL)
		return false;

	// debug check to make sure that we're docked to each other
	Assert(objp == dock_get_first_docked_object(objp)->dock_list->docked_objp);
	
	// success
	return true;
}

int dock_count_direct_docked_objects(object *objp)
{
	return dock_count_instances(objp);
}

int dock_count_total_docked_objects(object *objp)
{
	dock_function_info dfi;

	dock_evaluate_all_docked_objects(objp, &dfi, dock_count_total_docked_objects_helper);

	return dfi.maintained_variables.int_value;
}

bool dock_check_find_direct_docked_object(object *objp, object *other_objp)
{
	return (dock_find_instance(objp, other_objp) != NULL);
}

bool dock_check_find_docked_object(object *objp, object *other_objp)
{
	dock_function_info dfi;
	dfi.parameter_variables.objp_value = other_objp;

	dock_evaluate_all_docked_objects(objp, &dfi, dock_check_find_docked_object_helper);

	return dfi.maintained_variables.bool_value;
}

object *dock_find_object_at_dockpoint(object *objp, int dockpoint)
{
	dock_instance *result = dock_find_instance(objp, dockpoint);
	
	if (result == NULL)
		return NULL;
	else
		return result->docked_objp;
}

int dock_find_dockpoint_used_by_object(object *objp, object *other_objp)
{
	dock_instance *result = dock_find_instance(objp, other_objp);
	
	if (result == NULL)
		return -1;
	else
		return result->dockpoint_used;
}

void dock_calc_docked_center(vector *dest, object *objp)
{
	vm_vec_zero(dest);

	dock_function_info dfi;
	dfi.maintained_variables.vecp_value = dest;

	dock_evaluate_all_docked_objects(objp, &dfi, dock_calc_docked_center_helper);
	
	// overall center = sum of centers divided by sum of objects
	vm_vec_scale(dest, (1.0f / (float) dfi.maintained_variables.int_value));
}

void dock_calc_docked_center_of_mass(vector *dest, object *objp)
{
	vm_vec_zero(dest);

	dock_function_info dfi;
	dfi.maintained_variables.vecp_value = dest;

	dock_evaluate_all_docked_objects(objp, &dfi, dock_calc_docked_center_of_mass_helper);

	// overall center of mass = weighted sum of centers of mass divided by total mass
	vm_vec_scale(dest, (1.0f / dfi.maintained_variables.float_value));
}

float dock_calc_total_docked_mass(object *objp)
{
	dock_function_info dfi;
	
	dock_evaluate_all_docked_objects(objp, &dfi, dock_calc_total_docked_mass_helper);

	return dfi.maintained_variables.float_value;
}

float dock_calc_cross_sectional_radius_perpendicular_to_axis(object *objp, axis_type axis)
{
	vector local_line_start, local_line_end;
	vector world_line_start, world_line_end;
	dock_function_info dfi;

	// to calculate cross-sectional radius, we need a line that will be perpendicular to the cross-section

	vm_vec_zero(&local_line_start);
	vm_vec_zero(&local_line_end);
	switch(axis)
	{
		case X_AXIS:
			local_line_start.xyz.x = -2.0f * objp->radius;
			local_line_end.xyz.x = 2.0f * objp->radius;
			break;

		case Y_AXIS:
			local_line_start.xyz.y = -2.0f * objp->radius;
			local_line_end.xyz.y = 2.0f * objp->radius;
			break;

		case Z_AXIS:
			local_line_start.xyz.z = -2.0f * objp->radius;
			local_line_end.xyz.z = 2.0f * objp->radius;
			break;

		default:
			Int3();
			return 0.0f;
	}

	// rotate and move the endpoints to go through the axis of the actual object
	vm_vec_rotate(&world_line_start, &local_line_start, &objp->orient);
	vm_vec_rotate(&world_line_end, &local_line_end, &objp->orient);
	vm_vec_add2(&world_line_start, &objp->pos);
	vm_vec_add2(&world_line_end, &objp->pos);

	// now we have a line twice the length of an object going straight through it, 
	// centered at its position (although the length and center of the line don't
	// matter, as it's calculated as an endless line)

	// now determine the cross-sectional radius

	// set parameters and call function for the radius squared
	dfi.parameter_variables.vecp_value = &world_line_start;
	dfi.parameter_variables.vecp_value2 = &world_line_end;
	dock_evaluate_all_docked_objects(objp, &dfi, dock_calc_cross_sectional_radius_squared_perpendicular_to_line_helper);

	// the radius is the square root of our result
	return fl_sqrt(dfi.maintained_variables.float_value);
}

float dock_calc_docked_fspeed(object *objp)
{
	// *sigh*... the docked fspeed is simply the max fspeed of all docked objects
	dock_function_info dfi;
	dock_evaluate_all_docked_objects(objp, &dfi, dock_find_max_fspeed_helper);
	return dfi.maintained_variables.float_value;
}

float dock_calc_docked_speed(object *objp)
{
	// ditto with speed
	dock_function_info dfi;
	dock_evaluate_all_docked_objects(objp, &dfi, dock_find_max_speed_helper);
	return dfi.maintained_variables.float_value;
}


// functions to deal with all docked ships anywhere
// ---------------------------------------------------------------------------------------------------------------

// universal two functions
// -----------------------

// evaluate a certain function for all docked objects
void dock_evaluate_all_docked_objects(object *objp, dock_function_info *infop, void (*function)(object *, dock_function_info *))
{
	Assert((objp != NULL) && (infop != NULL) && (function != NULL));

	// not docked?
	if (!object_is_docked(objp))
	{
		// call the function for just the one object
		function(objp, infop);
		return;
	}

	// we only have two objects docked
	if (dock_check_docked_one_on_one(objp))
	{
		// call the function for the first object, and return if instructed
		function(objp, infop);
		if (infop->early_return_condition) return;

		// call the function for the second object, and return if instructed
		function(objp->dock_list->docked_objp, infop);
		if (infop->early_return_condition) return;
	}

	// we have multiple objects docked and we're treating them as a hub
	else if (dock_check_assume_hub())
	{
		// get the hub
		object *hub_objp = dock_get_hub(objp);

		// call the function for the hub, and return if instructed
		function(hub_objp, infop);
		if (infop->early_return_condition) return;

		// iterate through all docked objects
		for (dock_instance *ptr = hub_objp->dock_list; ptr != NULL; ptr = ptr->next)
		{
			// call the function for this object, and return if instructed
			function(ptr->docked_objp, infop);
			if (infop->early_return_condition) return;
		}
	}

	// we have multiple objects docked and we must treat them as a tree
	else
	{
		// create a bit array to mark the objects we checked
		char visited_bitstring[MAX_OBJECTS >> 3 + 1];

		// clear it
		memset(visited_bitstring, 0, MAX_OBJECTS >> 3 + 1);

		// start evaluating the tree
		dock_evaluate_tree(objp, infop, function, visited_bitstring);
	}
}

void dock_evaluate_tree(object *objp, dock_function_info *infop, void (*function)(object *, dock_function_info *), char *visited_bitstring)
{
	// make sure we haven't visited this object already
	if (get_bit(visited_bitstring, OBJ_INDEX(objp)))
		return;

	// mark as visited
	set_bit(visited_bitstring, OBJ_INDEX(objp));

	// call the function for this object, and return if instructed
	function(objp, infop);
	if (infop->early_return_condition) return;

	// iterate through all docked objects
	for (dock_instance *ptr = objp->dock_list; ptr != NULL; ptr = ptr->next)
	{
		// start another tree with the docked object as the root, and return if instructed
		dock_evaluate_tree(ptr->docked_objp, infop, function, visited_bitstring);
		if (infop->early_return_condition) return;
	}
}

// special-case functions
// ----------------------

void dock_move_docked_objects(object *objp)
{
	if (objp->type != OBJ_SHIP)
		return;

	if (!object_is_docked(objp))
		return;

	// has this object (by extension, this group of docked objects) been handled already?
	if (objp->flags & OF_DOCKED_ALREADY_HANDLED)
		return;

	Assert((objp->instance >= 0) && (objp->instance < MAX_SHIPS));

	dock_function_info dfi;
	object *fastest_objp;

	// find the object with the highest max speed
	dock_evaluate_all_docked_objects(objp, &dfi, dock_find_max_speed_helper);
	fastest_objp = dfi.maintained_variables.objp_value;

	// if we have no max speed, just use the first one
	if (fastest_objp == NULL)
		fastest_objp = objp;
	
	// start a tree with that object as the parent... do NOT use the �berfunction for this,
	// because we must use a tree for the parent ancestry to work correctly

	// we don't need a bit array because OF_DOCKED_ALREADY_HANDLED takes care of it
	// and must persist for the entire game frame

	// start evaluating the tree, starting with the fastest object having no parent
	dock_move_docked_children_tree(fastest_objp, NULL);
}

void dock_move_docked_children_tree(object *objp, object *parent_objp)
{
	// has this object been handled already?
	if (objp->flags & OF_DOCKED_ALREADY_HANDLED)
		return;

	// mark as handled
	objp->flags |= OF_DOCKED_ALREADY_HANDLED;

	// if parent_objp exists, move this object to align with it
	if (parent_objp != NULL)
	{
		extern void move_one_docked_object(object *objp, object *parent_objp);
		move_one_docked_object(objp, parent_objp);
	}

	// iterate through all docked objects
	for (dock_instance *ptr = objp->dock_list; ptr != NULL; ptr = ptr->next)
	{
		// start another tree with the docked object as the root and this object as the parent
		dock_move_docked_children_tree(ptr->docked_objp, objp);
	}
}


// helper functions
// ----------------

void dock_count_total_docked_objects_helper(object *objp, dock_function_info *infop)
{
	// increment count
	infop->maintained_variables.int_value++;
}

void dock_check_find_docked_object_helper(object *objp, dock_function_info *infop)
{
	// if object found, set to true and break
	if (infop->parameter_variables.objp_value == objp)
	{
		infop->maintained_variables.bool_value = true;
		infop->early_return_condition = true;
	}
}

void dock_calc_docked_center_helper(object *objp, dock_function_info *infop)
{
	// add object position and increment count
	vm_vec_add2(infop->maintained_variables.vecp_value, &objp->pos);
	infop->maintained_variables.int_value++;
}

void dock_calc_docked_center_of_mass_helper(object *objp, dock_function_info *infop)
{
	// add weighted object position and add mass
	vm_vec_scale_add2(infop->maintained_variables.vecp_value, &objp->pos, objp->phys_info.mass);
	infop->maintained_variables.float_value += objp->phys_info.mass;
}

void dock_calc_total_docked_mass_helper(object *objp, dock_function_info *infop)
{
	// add mass
	infop->maintained_variables.float_value += objp->phys_info.mass;
}

// What we're doing here is finding the distances between each side of the object and the line, and then taking the
// maximum distance as the cross-sectional radius.  We're actually maintaining the square of the distance rather than
// the actual distance, as it's faster to calculate and it gives the same result in a greater-than or less-than
// comparison.  When we're done calculating everything for all objects (i.e. when we return to the parent function)
// we take the square root of the final value.
void dock_calc_cross_sectional_radius_squared_perpendicular_to_line_helper(object *objp, dock_function_info *infop)
{
	vector world_point, local_point, nearest;
	polymodel *pm;
	float dist_squared;

	// line parameters
	vector *line_start = infop->parameter_variables.vecp_value;
	vector *line_end = infop->parameter_variables.vecp_value2;

	// We must find world coordinates for each of the six endpoints on the three axes of the object.  I looked up
	// which axis is front/back, left/right, and up/down, but I'm not sure which endpoint is which.  It doesn't
	// matter, though, as all we need are the distances.

	// grab our model
	Assert(objp->type == OBJ_SHIP);
	pm = model_get(Ships[objp->instance].modelnum);


	// calculate position of right point (max x)
	vm_vec_zero(&local_point);
	local_point.xyz.x = pm->maxs.xyz.x;
	vm_vec_rotate(&world_point, &local_point, &objp->orient);
	vm_vec_add2(&world_point, &objp->pos);

	// calculate square of distance to line
	vm_vec_dist_squared_to_line(&world_point, line_start, line_end, &nearest, &dist_squared);
	
	// update with farthest distance squared
	if (dist_squared > infop->maintained_variables.float_value)
		infop->maintained_variables.float_value = dist_squared;
	

	// calculate position of left point (min x)
	vm_vec_zero(&local_point);
	local_point.xyz.x = pm->mins.xyz.x;
	vm_vec_rotate(&world_point, &local_point, &objp->orient);
	vm_vec_add2(&world_point, &objp->pos);

	// calculate square of distance to line
	vm_vec_dist_squared_to_line(&world_point, line_start, line_end, &nearest, &dist_squared);
	
	// update with farthest distance squared
	if (dist_squared > infop->maintained_variables.float_value)
		infop->maintained_variables.float_value = dist_squared;


	// calculate position of top point (max y)
	vm_vec_zero(&local_point);
	local_point.xyz.y = pm->maxs.xyz.y;
	vm_vec_rotate(&world_point, &local_point, &objp->orient);
	vm_vec_add2(&world_point, &objp->pos);

	// calculate square of distance to line
	vm_vec_dist_squared_to_line(&world_point, line_start, line_end, &nearest, &dist_squared);
	
	// update with farthest distance squared
	if (dist_squared > infop->maintained_variables.float_value)
		infop->maintained_variables.float_value = dist_squared;
	

	// calculate position of bottom point (min y)
	vm_vec_zero(&local_point);
	local_point.xyz.y = pm->mins.xyz.y;
	vm_vec_rotate(&world_point, &local_point, &objp->orient);
	vm_vec_add2(&world_point, &objp->pos);

	// calculate square of distance to line
	vm_vec_dist_squared_to_line(&world_point, line_start, line_end, &nearest, &dist_squared);
	
	// update with farthest distance squared
	if (dist_squared > infop->maintained_variables.float_value)
		infop->maintained_variables.float_value = dist_squared;
	
	
	// calculate position of front point (max z)
	vm_vec_zero(&local_point);
	local_point.xyz.z = pm->maxs.xyz.z;
	vm_vec_rotate(&world_point, &local_point, &objp->orient);
	vm_vec_add2(&world_point, &objp->pos);

	// calculate square of distance to line
	vm_vec_dist_squared_to_line(&world_point, line_start, line_end, &nearest, &dist_squared);
	
	// update with farthest distance squared
	if (dist_squared > infop->maintained_variables.float_value)
		infop->maintained_variables.float_value = dist_squared;
	

	// calculate position of back point (min z)
	vm_vec_zero(&local_point);
	local_point.xyz.z = pm->mins.xyz.z;
	vm_vec_rotate(&world_point, &local_point, &objp->orient);
	vm_vec_add2(&world_point, &objp->pos);

	// calculate square of distance to line
	vm_vec_dist_squared_to_line(&world_point, line_start, line_end, &nearest, &dist_squared);
	
	// update with farthest distance squared
	if (dist_squared > infop->maintained_variables.float_value)
		infop->maintained_variables.float_value = dist_squared;
}

void dock_find_max_fspeed_helper(object *objp, dock_function_info *infop)
{
	// check our fspeed against the running maximum
	if (objp->phys_info.fspeed > infop->maintained_variables.float_value)
	{
		infop->maintained_variables.float_value = objp->phys_info.fspeed;
		infop->maintained_variables.objp_value = objp;
	}
}

void dock_find_max_speed_helper(object *objp, dock_function_info *infop)
{
	// check our speed against the running maximum
	if (objp->phys_info.speed > infop->maintained_variables.float_value)
	{
		infop->maintained_variables.float_value = objp->phys_info.speed;
		infop->maintained_variables.objp_value = objp;
	}
}
// ---------------------------------------------------------------------------------------------------------------
// end of �ber code block ----------------------------------------------------------------------------------------

// dock management functions -------------------------------------------------------------------------------------
void dock_dock_objects(object *objp1, int dockpoint1, object *objp2, int dockpoint2)
{
#ifndef NDEBUG
	if ((dock_find_instance(objp1, objp2) != NULL) || (dock_find_instance(objp2, objp1) != NULL))
	{
		Error(LOCATION, "Trying to dock an object that's already docked!\n");
	}

	if ((dock_find_instance(objp1, dockpoint1) != NULL) || (dock_find_instance(objp2, dockpoint2) != NULL))
	{
		Error(LOCATION, "Trying to dock to a dockpoint that's in use!\n");
	}
#endif

	// put objects on each others' dock lists 
	dock_add_instance(objp1, dockpoint1, objp2);
	dock_add_instance(objp2, dockpoint2, objp1);
}

void dock_undock_objects(object *objp1, object *objp2)
{
#ifndef NDEBUG
	if ((dock_find_instance(objp1, objp2) == NULL) || (dock_find_instance(objp2, objp1) == NULL))
	{
		Error(LOCATION, "Trying to undock an object that isn't docked!\n");
	}
#endif

	// remove objects from each others' dock lists
	dock_remove_instance(objp1, objp2);
	dock_remove_instance(objp2, objp1);
}

// dock list functions -------------------------------------------------------------------------------------------
bool dock_check_assume_hub()
{
	// There are several ways of handling ships to other ships.  Level 1, the simplest, is the one-docker, one-dockee
	// model used in retail FS2.  Level 2 is the hub model, where we stipulate that any given set of docked ships
	// includes one ship to which all other ships are docked.  No ship except for the hub ship can be docked to more than
	// one ship.  Level 3 is the daisy-chain model, where you can string ships along and make a rooted tree.
	//
	// The new code can handle level 3 ship formations, but it requires more overhead than level 2 or level 1.  (Whether
	// the additional overhead is significant or not has not been determined.)  In the vast majority of cases, level 3
	// is not needed.  So this function is provided to allow the code to optimize itself for level 2, should level 1
	// evaluation fail.

	// Assume level 2 optimization unless the mission specifies level 3.
	return !(The_mission.flags & MISSION_FLAG_ALLOW_DOCK_TREES);
}

object *dock_get_hub(object *objp)
{
	Assert(dock_check_assume_hub() && object_is_docked(objp));

	// if our dock list contains only one object, it must be the hub
	if (objp->dock_list->next == NULL)
	{
		return dock_get_first_docked_object(objp);
	}
	// otherwise we are the hub
	else
	{
		return objp;
	}
}

void dock_add_instance(object *objp, int dockpoint, object *other_objp)
{
	dock_instance *item;

	// create item
	item = (dock_instance *) malloc(sizeof(dock_instance));
	item->dockpoint_used = dockpoint;
	item->docked_objp = other_objp;

	// prepend item to existing list
	item->next = objp->dock_list;
	objp->dock_list = item;
}

void dock_remove_instance(object *objp, object *other_objp)
{
	int found = 0;
	dock_instance *prev_ptr, *ptr;
	
	prev_ptr = NULL;
	ptr = objp->dock_list;

	// iterate until item found
	while (ptr != NULL)
	{
		// if found, exit loop
		if (ptr->docked_objp == other_objp)
		{
			found = 1;
			break;
		}

		// iterate
		prev_ptr = ptr;
		ptr = ptr->next;
	}

	// delete if found
	if (found)
	{
		// special case... found at beginning of list
		if (prev_ptr == NULL)
		{
			objp->dock_list = ptr->next;
		}
		// normal case
		else
		{
			prev_ptr->next = ptr->next;
		}

		// delete it
		free(ptr);
	}
}

dock_instance *dock_find_instance(object *objp, object *other_objp)
{
	dock_instance *ptr = objp->dock_list;

	// iterate until item found
	while (ptr != NULL)
	{
		// if found, return it
		if (ptr->docked_objp == other_objp)
			return ptr;

		// iterate
		ptr = ptr->next;
	}

	// not found
	return NULL;
}

dock_instance *dock_find_instance(object *objp, int dockpoint)
{
	dock_instance *ptr = objp->dock_list;

	// iterate until item found
	while (ptr != NULL)
	{
		// if found, return it
		if (ptr->dockpoint_used == dockpoint)
			return ptr;

		// iterate
		ptr = ptr->next;
	}

	// not found
	return NULL;
}

int dock_count_instances(object *objp)
{
	int total_count = 0;

	// count all instances in the list
	dock_instance *ptr = objp->dock_list;
	while (ptr != NULL)
	{
		// incrememnt for this object
		total_count++;

		// iterate
		ptr = ptr->next;
	}

	// done
	return total_count;
}
