/*
 * Created by Ian "Goober5000" Warfield for the Freespace2 Source Code Project.
 * You may not sell or otherwise commercially exploit the source or things you
 * create based on the source.
 *
 */ 

/*
 * $Logfile: /Freespace2/code/wxFRED2/FREDFrame.h $
 * $Revision: 1.1 $
 * $Date: 2005-03-29 13:35:53 $
 * $Author: Goober5000 $
 *
 * FRED app frame
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.0  2005/03/29 07:55:19  Goober5000
 * Addition to CVS repository
 *
 */

#ifndef _FREDFRAME_H
#define _FREDFRAME_H

class FREDFrame : public wxFrame
{
	public:
		FREDFrame(const wxChar *title, int xpos, int ypos, int width, int height);
		~FREDFrame();

	private:
		// menubar
		wxMenuBar	*myMenuBar;

		// menus
		wxMenu		*myFileMenu;
		wxMenu		*myFileSaveFormatMenu;
		wxMenu		*myFileImportMenu;
		wxMenu		*myEditMenu;
		wxMenu		*myViewMenu;
		wxMenu		*myViewDisplayFilterMenu;
		wxMenu		*myViewViewpointMenu;
		wxMenu		*mySpeedMenu;
		wxMenu		*mySpeedMovementMenu;
		wxMenu		*mySpeedRotationMenu;
		wxMenu		*myEditorsMenu;
		wxMenu		*myGroupsMenu;
		wxMenu		*myGroupsSetGroupMenu;
		wxMenu		*myMiscMenu;
		wxMenu		*myHelpMenu;

		enum
		{
			MENU_FILE_NEW,
			MENU_FILE_OPEN,
			MENU_FILE_SAVE,
			MENU_FILE_SAVE_AS,
			MENU_FILE_REVERT,
			MENU_FILE_SAVE_FORMAT,
			MENU_FILE_SAVE_FORMAT_FS2_OPEN,
			MENU_FILE_SAVE_FORMAT_FS2_RETAIL,
			MENU_FILE_IMPORT,
			MENU_FILE_IMPORT_FREESPACE_1_MISSION,
			MENU_FILE_IMPORT_WEAPON_LOADOUTS,
			MENU_FILE_RUN_FREESPACE,
			MENU_FILE_RECENT_FILE_LIST,
			MENU_FILE_EXIT,

			MENU_EDIT_UNDO,
			MENU_EDIT_DELETE,
			MENU_EDIT_DELETE_WING,
			MENU_EDIT_DISABLE_UNDO,

			MENU_VIEW_TOOLBAR,
			MENU_VIEW_STATUS_BAR,
			MENU_VIEW_DISPLAY_FITER,
			MENU_VIEW_DISPLAY_FILTER_SHOW_SHIPS,
			MENU_VIEW_DISPLAY_FILTER_SHOW_PLAYER_STARTS,
			MENU_VIEW_DISPLAY_FILTER_SHOW_WAYPOINTS,
			MENU_VIEW_DISPLAY_FILTER_SHOW_FRIENDLY,
			MENU_VIEW_DISPLAY_FILTER_SHOW_HOSTILE,
			MENU_VIEW_HIDE_MARKED_OBJECTS,
			MENU_VIEW_SHOW_HIDDEN_OBJECTS,
			MENU_VIEW_SHOW_SHIP_MODELS,
			MENU_VIEW_SHOW_OUTLINES,
			MENU_VIEW_SHOW_SHIP_INFO,
			MENU_VIEW_SHOW_COORDINATES,
			MENU_VIEW_SHOW_GRID_POSITIONS,
			MENU_VIEW_SHOW_DISTANCES,
			MENU_VIEW_SHOW_MODEL_PATHS,
			MENU_VIEW_SHOW_MODEL_DOCK_POINTS,
			MENU_VIEW_SHOW_GRID,
			MENU_VIEW_SHOW_HORIZON,
			MENU_VIEW_DOUBLE_FINE_GRIDLINES,
			MENU_VIEW_ANTI_ALIASED_GRIDLINES,
			MENU_VIEW_SHOW_3D_COMPASS,
			MENU_VIEW_SHOW_BACKGROUND,
			MENU_VIEW_VIEWPOINT,
			MENU_VIEW_VIEWPOINT_CAMERA,
			MENU_VIEW_VIEWPOINT_CURRENT_SHIP,
			MENU_VIEW_SAVE_CAMERA_POS,
			MENU_VIEW_RESTORE_CAMERA_POS,
			MENU_VIEW_LIGHTING_FROM_SUNS,

			MENU_SPEED_MOVEMENT,
			MENU_SPEED_MOVEMENT_X1,
			MENU_SPEED_MOVEMENT_X2,
			MENU_SPEED_MOVEMENT_X3,
			MENU_SPEED_MOVEMENT_X5,
			MENU_SPEED_MOVEMENT_X8,
			MENU_SPEED_MOVEMENT_X10,
			MENU_SPEED_MOVEMENT_X50,
			MENU_SPEED_MOVEMENT_X100,
			MENU_SPEED_ROTATION,
			MENU_SPEED_ROTATION_X1,
			MENU_SPEED_ROTATION_X5,
			MENU_SPEED_ROTATION_X12,
			MENU_SPEED_ROTATION_X25,
			MENU_SPEED_ROTATION_X50,

			MENU_EDITORS_SHIPS,
			MENU_EDITORS_WINGS,
			MENU_EDITORS_OBJECTS,
			MENU_EDITORS_WAYPOINT_PATHS,
			MENU_EDITORS_MISSION_OBJECTIVES,
			MENU_EDITORS_EVENTS,
			MENU_EDITORS_TEAM_LOADOUT,
			MENU_EDITORS_BACKGROUND,
			MENU_EDITORS_REINFORCEMENTS,
			MENU_EDITORS_ASTEROID_FIELD,
			MENU_EDITORS_MISSION_SPECS,
			MENU_EDITORS_BRIEFING,
			MENU_EDITORS_DEBRIEFING,
			MENU_EDITORS_SHIELD_SYSTEM,
			MENU_EDITORS_COMMAND_BRIEFING,
			MENU_EDITORS_SET_GLOBAL_SHIP_FLAGS,
			MENU_EDITORS_VOICE_ACTING_MANAGER,
			MENU_EDITORS_CAMPAIGN,

			MENU_GROUPS_GROUP_1,
			MENU_GROUPS_GROUP_2,
			MENU_GROUPS_GROUP_3,
			MENU_GROUPS_GROUP_4,
			MENU_GROUPS_GROUP_5,
			MENU_GROUPS_GROUP_6,
			MENU_GROUPS_GROUP_7,
			MENU_GROUPS_GROUP_8,
			MENU_GROUPS_GROUP_9,
			MENU_GROUPS_SET_GROUP,
			MENU_GROUPS_SET_GROUP_GROUP_1,
			MENU_GROUPS_SET_GROUP_GROUP_2,
			MENU_GROUPS_SET_GROUP_GROUP_3,
			MENU_GROUPS_SET_GROUP_GROUP_4,
			MENU_GROUPS_SET_GROUP_GROUP_5,
			MENU_GROUPS_SET_GROUP_GROUP_6,
			MENU_GROUPS_SET_GROUP_GROUP_7,
			MENU_GROUPS_SET_GROUP_GROUP_8,
			MENU_GROUPS_SET_GROUP_GROUP_9,

			MENU_MISC_LEVEL_OBJECT,
			MENU_MISC_ALIGN_OBJECT,
			MENU_MISC_MARK_WING,
			MENU_MISC_CONTROL_OBJECT,
			MENU_MISC_NEXT_OBJECT,
			MENU_MISC_PREVIOUS_OBJECT,
			MENU_MISC_ADJUST_GRID,
			MENU_MISC_NEXT_SUBSYSTEM,
			MENU_MISC_PREV_SUBSYSTEM,
			MENU_MISC_CANCEL_SUBSYSTEM,
			MENU_MISC_MISSION_STATISTICS,
			MENU_MISC_ERROR_CHECKER,

			MENU_HELP_HELP_TOPICS,
			MENU_HELP_ABOUT_FRED2,
			MENU_HELP_SHOW_SEXP_HELP
		};
};

#endif