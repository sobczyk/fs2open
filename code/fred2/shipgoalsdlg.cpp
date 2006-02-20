/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/fred2/ShipGoalsDlg.cpp $
 * $Revision: 1.2 $
 * $Date: 2006-02-20 02:13:07 $
 * $Author: Goober5000 $
 *
 * Initial orders editor dialog box handling code.  This dialog is used for both
 * ship and wing initial orders, and can support more if need be without modification.
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/01/19 02:27:32  Goober5000
 * import FRED2 back into fs2_open module
 * --Goober5000
 *
 * Revision 1.4  2005/08/23 07:28:02  Goober5000
 * grammar
 * --Goober5000
 *
 * Revision 1.3  2005/03/29 03:43:11  phreak
 * ai directory fixes as well as fixes for the new jump node code
 *
 * Revision 1.2  2002/08/15 01:06:34  penguin
 * Include filename reorg (to coordinate w/ fs2_open)
 *
 * Revision 1.1.1.1  2002/07/15 03:11:03  inquisitor
 * Initial FRED2 Checking
 *
 * 
 * 4     3/26/99 4:49p Dave
 * Made cruisers able to dock with stuff. Made docking points and paths
 * visible in fred.
 * 
 * 3     3/25/99 3:32p Johnson
 * HACK: Allow Mycerinus to dock
 * 
 * 2     10/07/98 6:28p Dave
 * Initial checkin. Renamed all relevant stuff to be Fred2 instead of
 * Fred. Globalized mission and campaign file extensions. Removed Silent
 * Threat specific code.
 * 
 * 1     10/07/98 3:01p Dave
 * 
 * 1     10/07/98 3:00p Dave
 * 
 * 57    7/06/98 5:12p Hoffoss
 * Fixed bug where 3-5th orders don't update data listing when object
 * changes.
 * 
 * 56    5/21/98 12:58a Hoffoss
 * Fixed warnings optimized build turned up.
 * 
 * 55    4/06/98 11:34a Hoffoss
 * Fixed bug caused by change in max ai goals.  Should be able to handle
 * anything from 0 to 10 ai goals now (i.e. it's more flexible now).
 * 
 * 54    11/05/97 4:43p Allender
 * reworked medal/rank system to read all data from tables.  Made Fred
 * read medals.tbl.  Changed ai-warp to ai-warp-out which doesn't require
 * waypoint for activation
 * 
 * 53    10/22/97 3:15p Hoffoss
 * Fixed ai-stay-still initial order to use waypoints instead of waypoint
 * paths.
 * 
 * 52    10/22/97 1:58p Hoffoss
 * Added support for AI_GOALS_PLAY_DEAD and changed AI_GOALS_STAY_STILL
 * for Fred.
 * 
 * 51    10/10/97 5:03p Allender
 * started work on ai-stay-still
 * 
 * 50    9/18/97 11:28a Duncan
 * Fixed bug with player objects having wrong name.
 * 
 * 49    9/16/97 9:41p Hoffoss
 * Changed Fred code around to stop using Parse_player structure for
 * player information, and use actual ships instead.
 * 
 * 48    9/09/97 3:39p Sandeep
 * warning level 4 bugs
 * 
 * 47    9/02/97 5:10p Johnson
 * Fixed bug with wing initial orders available to select from.
 * 
 * 46    8/26/97 4:18p Hoffoss
 * Added error checking to initial orders dialog when ok is clicked.
 * 
 * 45    8/19/97 11:59a Duncan
 * Fixed bug in initial orders set_item().
 * 
 * 44    8/16/97 4:51p Hoffoss
 * Fixed bugs with wing deletion and removing ships from a wing.
 * 
 * 43    8/15/97 5:14p Hoffoss
 * Completely changed around how initial orders dialog worked.  It's
 * pretty awesome now.
 * 
 * 42    8/14/97 7:07p Hoffoss
 * Changed "guard ship" to "guard", since it can be used with wings now as
 * well as ships.
 * 
 * 41    8/10/97 4:41p Hoffoss
 * Fixed bugs with docking initial order.
 * 
 * 40    8/05/97 10:10p Hoffoss
 * Made attack and guard orders handle both ships and wings as targets.
 * 
 * 39    8/01/97 12:21p Jasen
 * Fixed bug with docking order (in iinitial orders) where original dockee
 * was deleted, and so not found when looked up.
 * 
 * 38    7/30/97 12:31p Hoffoss
 * Made improvements to ship goals editor (initial orders) to disallow
 * illegal orders.
 * 
 * 37    7/25/97 4:30p Hoffoss
 * Changes to ship lookup to include player ships.
 * 
 * 36    7/24/97 4:55p Allender
 * added ai-evade-ship to fred and to Freespace
 * 
 * 35    7/22/97 3:40p Allender
 * Changed the way that attacking subsystem works (for initial orders).
 * The code was behaving two different ways.  Orders are now model
 * specific as per which subsystem to attack.
 * 
 * 34    7/17/97 4:23p Allender
 * ai-guard-wing now in both Fred and Freespace
 * 
 * 33    7/09/97 1:56p Jasen
 * Added new case to data mode checkunder save item. 
 * 
 * 32    6/11/97 2:13p Hoffoss
 * Fixed bug in initial order initialization, and made subsystem combo box
 * use ship specific subsystems.
 * 
 * 31    6/04/97 12:00a Allender
 * added disarm and disable as initial order options
 * 
 * 30    5/30/97 4:50p Hoffoss
 * Added code to allow marked ship editing of data in child dialogs of
 * ship editor dialog.
 * 
 * 29    5/07/97 1:32p Allender
 * fix bug from previous checkin where undock orders were not persistent
 * 
 * 28    5/07/97 1:08p Allender
 * make undock initial order only accept a priority
 * 
 * 27    4/03/97 3:18p Allender
 * 
 * 26    3/31/97 6:07p Hoffoss
 * Fixed several errors, including BG editor not graying fields, BG editor
 * not updating image when changed, Removed obsolete data from Weapon
 * editor, priority not being saved when missions saved, priority not
 * editable in initial orders editor.
 * 
 * 25    3/28/97 3:19p Hoffoss
 * Added chase-any goal to initial orders.
 * 
 * 24    3/21/97 4:04p Bernal
 * fixed crash when initial orders references illegal objects. (Jason)
 * 
 * 23    3/21/97 10:29a Hoffoss
 * forced negative priorities to 50
 * 
 * 22    3/19/97 4:53p Hoffoss
 * fixed bug with unused fields not being cleared.
 * 
 * 21    3/13/97 12:20p Hoffoss
 * fixed bug in docking point specification of initial orders dialog.
 * 
 * 20    3/10/97 6:43p Hoffoss
 * Standardized docking goal usage by fred to use names instead of
 * indexes.
 * 
 * 19    3/10/97 5:37p Hoffoss
 * fixed bug in dock goal selection.
 * 
 * 18    3/10/97 12:54p Hoffoss
 * Added drop down combo box to toolbar and fixed compiling errors Mark
 * (maybe Mike?) introduced to code.
 * 
 * 17    3/04/97 12:52p Allender
 * docking styff.  Added dock type to docking structure in model code.
 * Renamed structure member in ai_goals.  Temporary checkin.  (i.e.
 * rearming will use rearm dock points)
 * 
 * 16    3/03/97 4:32p Hoffoss
 * Initial orders supports new docking stuff Allender added.
 * 
 * 15    2/27/97 3:15p Allender
 * major wing structure enhancement.  simplified wing code.  All around
 * better wing support
 * 
 * 14    2/26/97 2:45p Hoffoss
 * Initial orders dialog now only allows 89 as a max on priority.
 * 
 * 13    2/21/97 5:34p Hoffoss
 * Added extensive modification detection and fixed a bug in initial
 * orders editor.
 * 
 * 12    2/17/97 5:28p Hoffoss
 * Checked RCS headers, added them were missing, changing description to
 * something better, etc where needed.
 *
 * $NoKeywords: $
 */

#include "stdafx.h"
#include "FRED.h"
#include "ShipGoalsDlg.h"
#include "object/object.h"
#include "globalincs/linklist.h"
#include "Management.h"
#include "ai/aigoals.h"
#include "FREDDoc.h"
#include "FREDView.h"

#define TYPE_PATH			0x1000
#define TYPE_SHIP			0x2000
#define TYPE_PLAYER		0x3000
#define TYPE_WING			0x4000
#define TYPE_WAYPOINT	0x5000
#define TYPE_MASK			0xf000
#define DATA_MASK			0x0fff

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ShipGoalsDlg dialog

ShipGoalsDlg::ShipGoalsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ShipGoalsDlg::IDD, pParent)
{
	int i;

	for (i=0; i<ED_MAX_GOALS; i++) {
		m_behavior[i] = -1;
		m_object[i] = -1;
		m_priority[i] = 0;
		m_subsys[i] = -1;
		m_dock2[i] = -1;
		m_data[i] = 0;
	}

	//{{AFX_DATA_INIT(ShipGoalsDlg)
	//}}AFX_DATA_INIT
	goalp = NULL;
	self_ship = self_wing = -1;
}

void ShipGoalsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ShipGoalsDlg)
	//}}AFX_DATA_MAP

	DDX_CBIndex(pDX, IDC_BEHAVIOR1, m_behavior[0]);
	DDX_CBIndex(pDX, IDC_BEHAVIOR2, m_behavior[1]);
	DDX_CBIndex(pDX, IDC_BEHAVIOR3, m_behavior[2]);
	DDX_CBIndex(pDX, IDC_BEHAVIOR4, m_behavior[3]);
	DDX_CBIndex(pDX, IDC_BEHAVIOR5, m_behavior[4]);
	DDX_CBIndex(pDX, IDC_BEHAVIOR6, m_behavior[5]);
	DDX_CBIndex(pDX, IDC_BEHAVIOR7, m_behavior[6]);
	DDX_CBIndex(pDX, IDC_BEHAVIOR8, m_behavior[7]);
	DDX_CBIndex(pDX, IDC_BEHAVIOR9, m_behavior[8]);
	DDX_CBIndex(pDX, IDC_BEHAVIOR10, m_behavior[9]);

	DDX_CBIndex(pDX, IDC_OBJECT1, m_object[0]);
	DDX_CBIndex(pDX, IDC_OBJECT2, m_object[1]);
	DDX_CBIndex(pDX, IDC_OBJECT3, m_object[2]);
	DDX_CBIndex(pDX, IDC_OBJECT4, m_object[3]);
	DDX_CBIndex(pDX, IDC_OBJECT5, m_object[4]);
	DDX_CBIndex(pDX, IDC_OBJECT6, m_object[5]);
	DDX_CBIndex(pDX, IDC_OBJECT7, m_object[6]);
	DDX_CBIndex(pDX, IDC_OBJECT8, m_object[7]);
	DDX_CBIndex(pDX, IDC_OBJECT9, m_object[8]);
	DDX_CBIndex(pDX, IDC_OBJECT10, m_object[9]);

	DDX_Text(pDX, IDC_PRIORITY1, m_priority[0]);
	DDV_MinMaxInt(pDX, m_priority[0], 0, 89);
	DDX_Text(pDX, IDC_PRIORITY2, m_priority[1]);
	DDV_MinMaxInt(pDX, m_priority[1], 0, 89);
	DDX_Text(pDX, IDC_PRIORITY3, m_priority[2]);
	DDV_MinMaxInt(pDX, m_priority[2], 0, 89);
	DDX_Text(pDX, IDC_PRIORITY4, m_priority[3]);
	DDV_MinMaxInt(pDX, m_priority[3], 0, 89);
	DDX_Text(pDX, IDC_PRIORITY5, m_priority[4]);
	DDV_MinMaxInt(pDX, m_priority[4], 0, 89);
	DDX_Text(pDX, IDC_PRIORITY6, m_priority[5]);
	DDV_MinMaxInt(pDX, m_priority[5], 0, 89);
	DDX_Text(pDX, IDC_PRIORITY7, m_priority[6]);
	DDV_MinMaxInt(pDX, m_priority[6], 0, 89);
	DDX_Text(pDX, IDC_PRIORITY8, m_priority[7]);
	DDV_MinMaxInt(pDX, m_priority[7], 0, 89);
	DDX_Text(pDX, IDC_PRIORITY9, m_priority[8]);
	DDV_MinMaxInt(pDX, m_priority[8], 0, 89);
	DDX_Text(pDX, IDC_PRIORITY10, m_priority[9]);
	DDV_MinMaxInt(pDX, m_priority[9], 0, 89);

	DDX_CBIndex(pDX, IDC_SUBSYSTEM1, m_subsys[0]);
	DDX_CBIndex(pDX, IDC_SUBSYSTEM2, m_subsys[1]);
	DDX_CBIndex(pDX, IDC_SUBSYSTEM3, m_subsys[2]);
	DDX_CBIndex(pDX, IDC_SUBSYSTEM4, m_subsys[3]);
	DDX_CBIndex(pDX, IDC_SUBSYSTEM5, m_subsys[4]);
	DDX_CBIndex(pDX, IDC_SUBSYSTEM6, m_subsys[5]);
	DDX_CBIndex(pDX, IDC_SUBSYSTEM7, m_subsys[6]);
	DDX_CBIndex(pDX, IDC_SUBSYSTEM8, m_subsys[7]);
	DDX_CBIndex(pDX, IDC_SUBSYSTEM9, m_subsys[8]);
	DDX_CBIndex(pDX, IDC_SUBSYSTEM10, m_subsys[9]);

	DDX_CBIndex(pDX, IDC_DOCK1, m_dock2[0]);
	DDX_CBIndex(pDX, IDC_DOCK2, m_dock2[1]);
	DDX_CBIndex(pDX, IDC_DOCK3, m_dock2[2]);
	DDX_CBIndex(pDX, IDC_DOCK4, m_dock2[3]);
	DDX_CBIndex(pDX, IDC_DOCK5, m_dock2[4]);
	DDX_CBIndex(pDX, IDC_DOCK6, m_dock2[5]);
	DDX_CBIndex(pDX, IDC_DOCK7, m_dock2[6]);
	DDX_CBIndex(pDX, IDC_DOCK8, m_dock2[7]);
	DDX_CBIndex(pDX, IDC_DOCK9, m_dock2[8]);
	DDX_CBIndex(pDX, IDC_DOCK10, m_dock2[9]);
}

BEGIN_MESSAGE_MAP(ShipGoalsDlg, CDialog)
	//{{AFX_MSG_MAP(ShipGoalsDlg)
	ON_CBN_SELCHANGE(IDC_BEHAVIOR1, OnSelchangeBehavior1)
	ON_CBN_SELCHANGE(IDC_BEHAVIOR2, OnSelchangeBehavior2)
	ON_CBN_SELCHANGE(IDC_BEHAVIOR3, OnSelchangeBehavior3)
	ON_CBN_SELCHANGE(IDC_BEHAVIOR4, OnSelchangeBehavior4)
	ON_CBN_SELCHANGE(IDC_BEHAVIOR5, OnSelchangeBehavior5)
	ON_CBN_SELCHANGE(IDC_BEHAVIOR6, OnSelchangeBehavior6)
	ON_CBN_SELCHANGE(IDC_BEHAVIOR7, OnSelchangeBehavior7)
	ON_CBN_SELCHANGE(IDC_BEHAVIOR8, OnSelchangeBehavior8)
	ON_CBN_SELCHANGE(IDC_BEHAVIOR9, OnSelchangeBehavior9)
	ON_CBN_SELCHANGE(IDC_BEHAVIOR10, OnSelchangeBehavior10)
	ON_CBN_SELCHANGE(IDC_OBJECT1, OnSelchangeObject1)
	ON_CBN_SELCHANGE(IDC_OBJECT2, OnSelchangeObject2)
	ON_CBN_SELCHANGE(IDC_OBJECT3, OnSelchangeObject3)
	ON_CBN_SELCHANGE(IDC_OBJECT4, OnSelchangeObject4)
	ON_CBN_SELCHANGE(IDC_OBJECT5, OnSelchangeObject5)
	ON_CBN_SELCHANGE(IDC_OBJECT6, OnSelchangeObject6)
	ON_CBN_SELCHANGE(IDC_OBJECT7, OnSelchangeObject7)
	ON_CBN_SELCHANGE(IDC_OBJECT8, OnSelchangeObject8)
	ON_CBN_SELCHANGE(IDC_OBJECT9, OnSelchangeObject9)
	ON_CBN_SELCHANGE(IDC_OBJECT10, OnSelchangeObject10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ShipGoalsDlg message handlers

BOOL ShipGoalsDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	return CDialog::Create(IDD, &Ship_editor_dialog);
}

BOOL ShipGoalsDlg::OnInitDialog() 
{
	int i, j, z, valid[99];
	object *ptr;

	// set up pointers to all the combo boxes to simplify things a lot
	m_behavior_box[0] = (CComboBox *) GetDlgItem(IDC_BEHAVIOR1);
	m_behavior_box[1] = (CComboBox *) GetDlgItem(IDC_BEHAVIOR2);
	m_behavior_box[2] = (CComboBox *) GetDlgItem(IDC_BEHAVIOR3);
	m_behavior_box[3] = (CComboBox *) GetDlgItem(IDC_BEHAVIOR4);
	m_behavior_box[4] = (CComboBox *) GetDlgItem(IDC_BEHAVIOR5);
	m_behavior_box[5] = (CComboBox *) GetDlgItem(IDC_BEHAVIOR6);
	m_behavior_box[6] = (CComboBox *) GetDlgItem(IDC_BEHAVIOR7);
	m_behavior_box[7] = (CComboBox *) GetDlgItem(IDC_BEHAVIOR8);
	m_behavior_box[8] = (CComboBox *) GetDlgItem(IDC_BEHAVIOR9);
	m_behavior_box[9] = (CComboBox *) GetDlgItem(IDC_BEHAVIOR10);

	m_object_box[0] = (CComboBox *) GetDlgItem(IDC_OBJECT1);
	m_object_box[1] = (CComboBox *) GetDlgItem(IDC_OBJECT2);
	m_object_box[2] = (CComboBox *) GetDlgItem(IDC_OBJECT3);
	m_object_box[3] = (CComboBox *) GetDlgItem(IDC_OBJECT4);
	m_object_box[4] = (CComboBox *) GetDlgItem(IDC_OBJECT5);
	m_object_box[5] = (CComboBox *) GetDlgItem(IDC_OBJECT6);
	m_object_box[6] = (CComboBox *) GetDlgItem(IDC_OBJECT7);
	m_object_box[7] = (CComboBox *) GetDlgItem(IDC_OBJECT8);
	m_object_box[8] = (CComboBox *) GetDlgItem(IDC_OBJECT9);
	m_object_box[9] = (CComboBox *) GetDlgItem(IDC_OBJECT10);

	m_subsys_box[0] = (CComboBox *) GetDlgItem(IDC_SUBSYSTEM1);
	m_subsys_box[1] = (CComboBox *) GetDlgItem(IDC_SUBSYSTEM2);
	m_subsys_box[2] = (CComboBox *) GetDlgItem(IDC_SUBSYSTEM3);
	m_subsys_box[3] = (CComboBox *) GetDlgItem(IDC_SUBSYSTEM4);
	m_subsys_box[4] = (CComboBox *) GetDlgItem(IDC_SUBSYSTEM5);
	m_subsys_box[5] = (CComboBox *) GetDlgItem(IDC_SUBSYSTEM6);
	m_subsys_box[6] = (CComboBox *) GetDlgItem(IDC_SUBSYSTEM7);
	m_subsys_box[7] = (CComboBox *) GetDlgItem(IDC_SUBSYSTEM8);
	m_subsys_box[8] = (CComboBox *) GetDlgItem(IDC_SUBSYSTEM9);
	m_subsys_box[9] = (CComboBox *) GetDlgItem(IDC_SUBSYSTEM10);

	m_dock2_box[0] = (CComboBox *) GetDlgItem(IDC_DOCK1);
	m_dock2_box[1] = (CComboBox *) GetDlgItem(IDC_DOCK2);
	m_dock2_box[2] = (CComboBox *) GetDlgItem(IDC_DOCK3);
	m_dock2_box[3] = (CComboBox *) GetDlgItem(IDC_DOCK4);
	m_dock2_box[4] = (CComboBox *) GetDlgItem(IDC_DOCK5);
	m_dock2_box[5] = (CComboBox *) GetDlgItem(IDC_DOCK6);
	m_dock2_box[6] = (CComboBox *) GetDlgItem(IDC_DOCK7);
	m_dock2_box[7] = (CComboBox *) GetDlgItem(IDC_DOCK8);
	m_dock2_box[8] = (CComboBox *) GetDlgItem(IDC_DOCK9);
	m_dock2_box[9] = (CComboBox *) GetDlgItem(IDC_DOCK10);

	m_priority_box[0] = (CComboBox *) GetDlgItem(IDC_PRIORITY1);
	m_priority_box[1] = (CComboBox *) GetDlgItem(IDC_PRIORITY2);
	m_priority_box[2] = (CComboBox *) GetDlgItem(IDC_PRIORITY3);
	m_priority_box[3] = (CComboBox *) GetDlgItem(IDC_PRIORITY4);
	m_priority_box[4] = (CComboBox *) GetDlgItem(IDC_PRIORITY5);
	m_priority_box[5] = (CComboBox *) GetDlgItem(IDC_PRIORITY6);
	m_priority_box[6] = (CComboBox *) GetDlgItem(IDC_PRIORITY7);
	m_priority_box[7] = (CComboBox *) GetDlgItem(IDC_PRIORITY8);
	m_priority_box[8] = (CComboBox *) GetDlgItem(IDC_PRIORITY9);
	m_priority_box[9] = (CComboBox *) GetDlgItem(IDC_PRIORITY10);

	// start off with all goals available
	for (i=0; i<Ai_goal_list_size; i++)
		valid[i] = 1;

	// disallow orders if they aren't allowed because of ship type
	if (self_ship >= 0) {  // editing orders for just one ship
		for (i=0; i<Ai_goal_list_size; i++){
			if (!(ai_query_goal_valid(self_ship, Ai_goal_list[i].def))){
				valid[i] = 0;
			}
		}
	} else if (self_wing >= 0) {  // editing orders for just one wing
		for (i=0; i<Wings[self_wing].wave_count; i++){
			for (j=0; j<Ai_goal_list_size; j++){
				if (!ai_query_goal_valid(Wings[self_wing].ship_index[i], Ai_goal_list[j].def)){
					valid[j] = 0;
				}
			}
		}

		for (i=0; i<Ai_goal_list_size; i++){
			if (Ai_goal_list[i].def == AI_GOAL_DOCK){  // a whole wing can't dock with one object..
				valid[i] = 0;
			}
		}
	} else {  // editing orders for all marked ships
		ptr = GET_FIRST(&obj_used_list);
		while (ptr != END_OF_LIST(&obj_used_list)) {
			if ((ptr->type == OBJ_SHIP) && (ptr->flags & OF_MARKED)){
				for (i=0; i<Ai_goal_list_size; i++){
					if (!ai_query_goal_valid(ptr->instance, Ai_goal_list[i].def)){
						valid[i] = 0;
					}
				}
			}

			ptr = GET_NEXT(ptr);
		}
	}

	for (i=0; i<MAX_WAYPOINT_LISTS; i++){
		if (Waypoint_lists[i].count){
			break;
		}
	}

	if (i == MAX_WAYPOINT_LISTS){
		for (i=0; i<Ai_goal_list_size; i++){
			switch (Ai_goal_list[i].def) {
				case AI_GOAL_WAYPOINTS:
				case AI_GOAL_WAYPOINTS_ONCE:
				//case AI_GOAL_WARP:
					valid[i] = 0;
			}
		}
	}

	z = 0;
	ptr = GET_FIRST(&obj_used_list);
	while (ptr != END_OF_LIST(&obj_used_list)) {
		if ((ptr->type == OBJ_SHIP) || (ptr->type == OBJ_START)) {
			i = ptr->instance;

			if ((self_ship > 0) && (self_ship != i) && ship_docking_valid(self_ship, i)){
				z = 1;
			}
		}
		ptr = GET_NEXT(ptr);
	}

	if (!z){
		for (i=0; i<Ai_goal_list_size; i++){
			if (Ai_goal_list[i].def == AI_GOAL_DOCK){
				valid[i] = 0;
			}
		}
	}

	// initialize the behavior boxes (they remain constant) and initialize each goal's data
	for (i=0; i<ED_MAX_GOALS; i++) {
		m_behavior_box[i] -> ResetContent();
		z = m_behavior_box[i] -> AddString("None");
		m_behavior_box[i] -> SetItemData(z, (DWORD) AI_GOAL_NONE);
		for (j=0; j<Ai_goal_list_size; j++){
			if (valid[j]) {
				z = m_behavior_box[i] -> AddString(Ai_goal_list[j].name);
				m_behavior_box[i] -> SetItemData(z, (DWORD) Ai_goal_list[j].def);
			}
		}
	}

	if (self_ship >= 0){
		initialize(Ai_info[Ships[self_ship].ai_index].goals, self_ship);
	} else if (self_wing >= 0){
		initialize(Wings[self_wing].ai_goals);
	} else {
		initialize_multi();
	}

	for (i=0; i<ED_MAX_GOALS; i++){
		set_item(i, 1);
	}

	CDialog::OnInitDialog();

	// restrict spin controls to a range of 0 - 89
	((CSpinButtonCtrl *) GetDlgItem(IDC_SPIN1)) -> SetRange(0, 89);
	((CSpinButtonCtrl *) GetDlgItem(IDC_SPIN2)) -> SetRange(0, 89);
	((CSpinButtonCtrl *) GetDlgItem(IDC_SPIN3)) -> SetRange(0, 89);
	((CSpinButtonCtrl *) GetDlgItem(IDC_SPIN4)) -> SetRange(0, 89);
	((CSpinButtonCtrl *) GetDlgItem(IDC_SPIN5)) -> SetRange(0, 89);
	((CSpinButtonCtrl *) GetDlgItem(IDC_SPIN6)) -> SetRange(0, 89);
	((CSpinButtonCtrl *) GetDlgItem(IDC_SPIN7)) -> SetRange(0, 89);
	((CSpinButtonCtrl *) GetDlgItem(IDC_SPIN8)) -> SetRange(0, 89);
	((CSpinButtonCtrl *) GetDlgItem(IDC_SPIN9)) -> SetRange(0, 89);
	((CSpinButtonCtrl *) GetDlgItem(IDC_SPIN10)) -> SetRange(0, 89);

	return TRUE;
}

void ShipGoalsDlg::initialize_multi()
{
	int i, flag = 0;
	object *ptr;
	int behavior[ED_MAX_GOALS];
	int priority[ED_MAX_GOALS];
	int subsys[ED_MAX_GOALS];
	int dock2[ED_MAX_GOALS];
	int data[ED_MAX_GOALS];

	ptr = GET_FIRST(&obj_used_list);
	while (ptr != END_OF_LIST(&obj_used_list)) {
		if ((ptr->type == OBJ_SHIP) && (ptr->flags & OF_MARKED)) {
			initialize(Ai_info[Ships[ptr->instance].ai_index].goals, ptr->instance);
			if (!flag) {
				flag = 1;
				for (i=0; i<ED_MAX_GOALS; i++) {
					behavior[i] = m_behavior[i];
					priority[i] = m_priority[i];
					subsys[i] = m_subsys[i];
					dock2[i] = m_dock2[i];
					data[i] = m_data[i];
				}

			} else {
				for (i=0; i<ED_MAX_GOALS; i++) {
					if (behavior[i] != m_behavior[i]) {
						behavior[i] = -1;
						data[i] = -1;
					}

					if (data[i] != m_data[i]) {
						data[i] = -1;
						subsys[i] = -1;
						dock2[i] = -1;
					}

					if (priority[i] != m_priority[i]){
						priority[i] = -1;
					}
					if (subsys[i] != m_subsys[i]){
						subsys[i] = -1;
					}
					if (dock2[i] != m_dock2[i]){
						dock2[i] = -1;
					}
				}
			}
		}

		ptr = GET_NEXT(ptr);
	}

	goalp = NULL;
	for (i=0; i<ED_MAX_GOALS; i++) {
		m_behavior[i] = behavior[i];
		m_priority[i] = priority[i];
		m_subsys[i] = subsys[i];
		m_dock2[i] = dock2[i];
		m_data[i] = data[i];
	}
}

// perform one-time initialization of data from the goals struct.
void ShipGoalsDlg::initialize(ai_goal *goals, int ship)
{
	int i, item, num, inst, flag, mode;
	object *ptr;

	goalp = goals;
	for (item=0; item<ED_MAX_GOALS; item++) {
		flag = 1;
		m_data[item] = 0;
		m_priority[item] = 0;
		mode = AI_GOAL_NONE;
		
		if (item < MAX_AI_GOALS) {
			m_priority[item] = goalp[item].priority;
			mode = goalp[item].ai_mode;
		}

		if (m_priority[item] < 0 || m_priority[item] > 89){
			m_priority[item] = 50;
		}

		m_behavior[item] = 0;
		if (mode != AI_GOAL_NONE) {
			i = m_behavior_box[item] -> GetCount();
			while (i-- > 0){
				if (mode & (m_behavior_box[item]->GetItemData(i))) {
					m_behavior[item] = i;
					break;
				}
			}
		}

		switch (mode) {
			case AI_GOAL_NONE:
			case AI_GOAL_CHASE_ANY:
			case AI_GOAL_UNDOCK:
			case AI_GOAL_KEEP_SAFE_DISTANCE:
			case AI_GOAL_PLAY_DEAD:
			case AI_GOAL_WARP:
				continue;

			case AI_GOAL_STAY_STILL:
				flag = 9;  // target is a ship or a waypoint
				break;

			case AI_GOAL_CHASE:
			case AI_GOAL_GUARD:
			case AI_GOAL_DISABLE_SHIP:
			case AI_GOAL_DISARM_SHIP:
			case AI_GOAL_IGNORE:
			case AI_GOAL_IGNORE_NEW:
			case AI_GOAL_EVADE_SHIP:
			case AI_GOAL_STAY_NEAR_SHIP:
				break;

			case AI_GOAL_WAYPOINTS:
			case AI_GOAL_WAYPOINTS_ONCE:
				flag = 4;  // target is a waypoint
				break;

			case AI_GOAL_DESTROY_SUBSYSTEM:
				num = ship_name_lookup(goalp[item].ship_name, 1);
				if (num != -1)
					m_subsys[item] = ship_get_subsys_index(&Ships[num], goalp[item].docker.name, 1);

				break;

			case AI_GOAL_DOCK:
				m_subsys[item] = -1;
				num = get_docking_list(Ships[ship].modelnum);
				for (i=0; i<num; i++) {
					Assert(Docking_bay_list[i]);
					if (!stricmp(goalp[item].docker.name, Docking_bay_list[i])) {
						m_subsys[item] = i;
						break;
					}
				}

				break;

			case AI_GOAL_CHASE_WING:
			case AI_GOAL_GUARD_WING:
				flag = 2;  // target is a wing
				break;

			default:
				Assert(0);
		}

		if (flag & 0x1) {
			ptr = GET_FIRST(&obj_used_list);
			while (ptr != END_OF_LIST(&obj_used_list)) {
				if ((ptr->type == OBJ_SHIP) || (ptr->type == OBJ_START)) {
					inst = ptr->instance;
					if (ptr->type == OBJ_SHIP) {
						Assert(inst >= 0 && inst < MAX_SHIPS);
						if (!stricmp(goalp[item].ship_name, Ships[inst].ship_name)) {
							m_data[item] = inst | TYPE_SHIP;
							break;
						}

					} else {
						Assert(inst >= 0 && inst < MAX_SHIPS);
						if (!stricmp(goalp[item].ship_name, Ships[inst].ship_name)) {
							m_data[item] = inst | TYPE_PLAYER;
							break;
						}
					}
				}

				ptr = GET_NEXT(ptr);
			}
		}

		if (flag & 0x2) {
			for (i=0; i<MAX_WINGS; i++)
				if (Wings[i].wave_count) {
					if (!stricmp(goalp[item].ship_name, Wings[i].name)) {
						m_data[item] = i | TYPE_WING;
						break;
					}
				}
		}

		if (flag & 0x4) {  // data is a waypoint path name
			for (i=0; i<Num_waypoint_lists; i++)
				if (!stricmp(goalp[item].ship_name, Waypoint_lists[i].name)) {
					m_data[item] = i | TYPE_PATH;
					break;
				}
		}

		if (flag & 0x8) {  // data is a waypoint name
			i = waypoint_lookup(goalp[item].ship_name);
			if (i >= 0)
				m_data[item] = i | TYPE_WAYPOINT;
		}

		switch (mode) {
			case AI_GOAL_DOCK:
				m_dock2[item] = -1;
				if (m_data[item]) {
					num = get_docking_list(Ships[m_data[item] & DATA_MASK].modelnum);
					for (i=0; i<num; i++) {
						Assert(Docking_bay_list[i]);
						Assert(goalp[item].dockee.name);
						Assert(goalp[item].dockee.index != -1);
						if (!stricmp(goalp[item].dockee.name, Docking_bay_list[i])) {
							m_dock2[item] = i;
							break;
						}
					}
				}

				break;
		}

//		Assert(m_data[item]);
	}
}

void ShipGoalsDlg::set_item(int item, int init)
{
	int i, t, z, num, inst, mode;
	object *ptr;

	if (init)
		m_object[item] = -1;

	if (item >= MAX_AI_GOALS)
		m_behavior_box[item] -> EnableWindow(FALSE);
	
	Assert(item >= 0 && item < ED_MAX_GOALS);
	m_object_box[item] -> ResetContent();
	if (m_behavior[item] < 1) {
		m_object_box[item] -> EnableWindow(FALSE);
		m_subsys_box[item] -> EnableWindow(FALSE);
		m_dock2_box[item] -> EnableWindow(FALSE);
		m_priority_box[item] -> EnableWindow(FALSE);
		m_subsys[item] = -1;
		m_dock2[item] = -1;
		return;
	}

	mode = m_behavior_box[item] -> GetItemData(m_behavior[item]);
	m_priority_box[item] -> EnableWindow(TRUE);
	if ((mode == AI_GOAL_CHASE_ANY) || (mode == AI_GOAL_UNDOCK) || (mode == AI_GOAL_KEEP_SAFE_DISTANCE) || (mode == AI_GOAL_PLAY_DEAD) || (mode == AI_GOAL_WARP) ) {
		m_object_box[item] -> EnableWindow(FALSE);
		m_subsys_box[item] -> EnableWindow(FALSE);
		m_dock2_box[item] -> EnableWindow(FALSE);
		m_subsys[item] = -1;
		m_dock2[item] = -1;
		return;
	}

	m_object_box[item] -> EnableWindow(TRUE);

	switch (mode) {
		case AI_GOAL_WAYPOINTS:
		case AI_GOAL_WAYPOINTS_ONCE:
		//case AI_GOAL_WARP:
			for (i=0; i<MAX_WAYPOINT_LISTS; i++)
				if (Waypoint_lists[i].count) {
					z = m_object_box[item] -> AddString(Waypoint_lists[i].name);
					m_object_box[item] -> SetItemData(z, i | TYPE_PATH);
					if (init && (m_data[item] == (i | TYPE_PATH)))
						m_object[item] = z;
				}

			break;

		case AI_GOAL_STAY_STILL:
			ptr = GET_FIRST(&obj_used_list);
			while (ptr != END_OF_LIST(&obj_used_list)) {
				if (ptr->type == OBJ_WAYPOINT) {
					t = TYPE_SHIP;
					z = m_object_box[item] -> AddString(object_name(OBJ_INDEX(ptr)));
					m_object_box[item] -> SetItemData(z, OBJ_INDEX(ptr) | TYPE_WAYPOINT);
					if (init && (m_data[item] == (OBJ_INDEX(ptr) | TYPE_WAYPOINT)))
						m_object[item] = z;
				}

				ptr = GET_NEXT(ptr);
			}

			break;
	}

	switch (mode) {
		case AI_GOAL_DESTROY_SUBSYSTEM:
		case AI_GOAL_CHASE | AI_GOAL_CHASE_WING:
		case AI_GOAL_DOCK:
		case AI_GOAL_GUARD | AI_GOAL_GUARD_WING:
		case AI_GOAL_DISABLE_SHIP:
		case AI_GOAL_DISARM_SHIP:
		case AI_GOAL_EVADE_SHIP:
		case AI_GOAL_IGNORE:
		case AI_GOAL_IGNORE_NEW:
		case AI_GOAL_STAY_NEAR_SHIP:
		case AI_GOAL_STAY_STILL:
			ptr = GET_FIRST(&obj_used_list);
			while (ptr != END_OF_LIST(&obj_used_list)) {
				if (ptr->type == OBJ_SHIP || ptr->type == OBJ_START) {
					inst = ptr->instance;
					if (ptr->type == OBJ_SHIP)
						t = TYPE_SHIP;
					else
						t = TYPE_PLAYER;

					Assert(inst >= 0 && inst < MAX_SHIPS);
					// remove all marked ships from list
					if (!goalp && (ptr->flags & OF_MARKED))
						inst = -1;

					// when docking, remove invalid dock targets
					else if (mode == AI_GOAL_DOCK) {
						if (self_ship < 0 || !ship_docking_valid(self_ship, inst))
							inst = -1;
					}

					// disallow ship being its own target
					if (inst >= 0 && inst != self_ship) {
						z = m_object_box[item] -> AddString(Ships[inst].ship_name);
						m_object_box[item] -> SetItemData(z, inst | t);
						if (init && (m_data[item] == (inst | t)))
							m_object[item] = z;
					}
				}

				ptr = GET_NEXT(ptr);
			}

			break;
	}

	switch (mode) {
		case AI_GOAL_CHASE | AI_GOAL_CHASE_WING:
		case AI_GOAL_GUARD | AI_GOAL_GUARD_WING:
			for (i=0; i<MAX_WINGS; i++)
				if (Wings[i].wave_count && i != self_wing) {
					z = m_object_box[item] -> AddString(Wings[i].name);
					m_object_box[item] -> SetItemData(z, i | TYPE_WING);
					if (init && (m_data[item] == (i | TYPE_WING)))
						m_object[item] = z;
				}

			break;
	}

	if (mode == AI_GOAL_DESTROY_SUBSYSTEM) {
		m_subsys_box[item] -> EnableWindow(TRUE);
		m_dock2_box[item] -> EnableWindow(FALSE);
		m_dock2[item] = -1;
		set_object(item);
		if (!m_behavior[item])
			set_item(item, init);

	} else if (mode == AI_GOAL_DOCK) {
		num = get_docking_list(Ships[cur_ship].modelnum);
		m_subsys_box[item] -> EnableWindow(TRUE);
		m_subsys_box[item] -> ResetContent();
		for (i=0; i<num; i++) {
			Assert(Docking_bay_list[i]);
			z = m_subsys_box[item] -> AddString(Docking_bay_list[i]);
			m_subsys_box[item] -> SetItemDataPtr(z, Docking_bay_list[i]);
		}

		set_object(item);
		if (!m_behavior[item])
			set_item(item, init);

	} else {
		m_subsys_box[item] -> EnableWindow(FALSE);
		m_dock2_box[item] -> EnableWindow(FALSE);
		m_subsys[item] = -1;
		m_dock2[item] = -1;
	}
}

void ShipGoalsDlg::OnSelchangeBehavior1() 
{
	UpdateData(TRUE);
	m_object[0] = 0;
	m_subsys[0] = m_dock2[0] = 0;
	set_item(0);
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeBehavior2() 
{
	UpdateData(TRUE);
	m_object[1] = 0;
	set_item(1);
	m_subsys[1] = m_dock2[1] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeBehavior3() 
{
	UpdateData(TRUE);
	m_object[2] = 0;
	set_item(2);
	m_subsys[2] = m_dock2[2] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeBehavior4() 
{
	UpdateData(TRUE);
	m_object[3] = 0;
	set_item(3);
	m_subsys[3] = m_dock2[3] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeBehavior5() 
{
	UpdateData(TRUE);
	m_object[4] = 0;
	set_item(4);
	m_subsys[4] = m_dock2[4] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeBehavior6() 
{
	UpdateData(TRUE);
	m_object[5] = 0;
	set_item(5);
	m_subsys[5] = m_dock2[5] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeBehavior7() 
{
	UpdateData(TRUE);
	m_object[6] = 0;
	set_item(6);
	m_subsys[6] = m_dock2[6] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeBehavior8() 
{
	UpdateData(TRUE);
	m_object[7] = 0;
	set_item(7);
	m_subsys[7] = m_dock2[7] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeBehavior9() 
{
	UpdateData(TRUE);
	m_object[8] = 0;
	set_item(8);
	m_subsys[8] = m_dock2[8] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeBehavior10() 
{
	UpdateData(TRUE);
	m_object[9] = 0;
	set_item(9);
	m_subsys[9] = m_dock2[9] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::update()
{
	int i;

	if (goalp) {
		for (i=0; i<ED_MAX_GOALS; i++)
			update_item(i);

		verify_orders();

	} else {
		object *ptr;

		ptr = GET_FIRST(&obj_used_list);
		while (ptr != END_OF_LIST(&obj_used_list)) {
			if ((ptr->type == OBJ_SHIP) && (ptr->flags & OF_MARKED)) {
				goalp = Ai_info[Ships[ptr->instance].ai_index].goals;
				for (i=0; i<ED_MAX_GOALS; i++)
					update_item(i, 1);
			}

			ptr = GET_NEXT(ptr);
		}

		ptr = GET_FIRST(&obj_used_list);
		while (ptr != END_OF_LIST(&obj_used_list)) {
			if ((ptr->type == OBJ_SHIP) && (ptr->flags & OF_MARKED)) {
				self_ship = ptr->instance;
				goalp = Ai_info[Ships[self_ship].ai_index].goals;
				verify_orders(self_ship);
			}

			ptr = GET_NEXT(ptr);
		}
	}
}

int ShipGoalsDlg::verify_orders(int ship)
{
	char *str, buf[2048];

	if ((str = error_check_initial_orders(goalp, self_ship, self_wing))!=NULL) {
		if (*str == '!')
			return 1;
		else if (*str == '*')
			str++;

		if (ship >= 0)
			sprintf(buf, "Initial orders error for ship \"%s\"\n\n%s", Ships[ship].ship_name, str);
		else
			strcpy(buf, str);

		if (MessageBox(buf, "Error", MB_OKCANCEL | MB_ICONEXCLAMATION) != IDOK)
			return 1;
	}

	return 0;
}

void ShipGoalsDlg::update_item(int item, int multi)
{
	char *docker, *dockee, *subsys;
	int mode;
	char buf[512], save[80];

	if (item >= MAX_AI_GOALS)
		return;

	if (!multi || m_priority[item] >= 0)
		goalp[item].priority = m_priority[item];

	if (m_behavior[item] < 0) {
		if (multi)
			return;
		else
			m_behavior[item] = 0;
	}

	mode = m_behavior_box[item] -> GetItemData(m_behavior[item]);
	switch (mode) {
		case AI_GOAL_NONE:
		case AI_GOAL_CHASE_ANY:
		case AI_GOAL_UNDOCK:
		case AI_GOAL_KEEP_SAFE_DISTANCE:
		case AI_GOAL_PLAY_DEAD:
		case AI_GOAL_WARP:
			MODIFY(goalp[item].ai_mode, mode);
			return;

		case AI_GOAL_WAYPOINTS:
		case AI_GOAL_WAYPOINTS_ONCE:
		case AI_GOAL_DISABLE_SHIP:
		case AI_GOAL_DISARM_SHIP:
		case AI_GOAL_IGNORE:
		case AI_GOAL_IGNORE_NEW:
		case AI_GOAL_EVADE_SHIP:
		case AI_GOAL_STAY_NEAR_SHIP:
		case AI_GOAL_STAY_STILL:
			break;

		case AI_GOAL_DESTROY_SUBSYSTEM:
			subsys = NULL;
			if (!multi || (m_data[item] && (m_subsys[item] >= 0)))
				subsys = (char *) m_subsys_box[item]->GetItemDataPtr(m_subsys[item]);
				//MODIFY(goalp[item].ai_submode, m_subsys[item] + 1);

			if (!subsys) {
				sprintf(buf, "Order #%d doesn't have valid subsystem name.  Order will be removed", item + 1);
				MessageBox(buf, "Notice");
				MODIFY(goalp[item].ai_mode, AI_GOAL_NONE);
				return;

			} else {
				if (!goalp[item].docker.name || (goalp[item].docker.name && !stricmp(goalp[item].docker.name, subsys)))
					set_modified();

				goalp[item].docker.name = subsys;
			}

			break;

		case AI_GOAL_CHASE | AI_GOAL_CHASE_WING:
			switch (m_data[item] & TYPE_MASK) {
				case TYPE_SHIP:
				case TYPE_PLAYER:
					mode = AI_GOAL_CHASE;
					break;

				case TYPE_WING:
					mode = AI_GOAL_CHASE_WING;
					break;
			}

			break;

		case AI_GOAL_DOCK:
			docker = NULL;
			if (!multi || (m_data[item] && (m_subsys[item] >= 0)))
				docker = (char *) m_subsys_box[item] -> GetItemDataPtr(m_subsys[item]);

			dockee = NULL;
			if (!multi || (m_data[item] && (m_dock2[item] >= 0)))
				dockee = (char *) m_dock2_box[item] -> GetItemDataPtr(m_dock2[item]);

			if (docker == (char *) 0xffffffff)
				docker = NULL;
			if (dockee == (char *) 0xffffffff)
				dockee = NULL;

			if (!docker || !dockee) {
				sprintf(buf, "Order #%d doesn't have valid docking points.  Order will be removed", item + 1);
				MessageBox(buf, "Notice");
				MODIFY(goalp[item].ai_mode, AI_GOAL_NONE);
				return;

			} else {
				if (!goalp[item].docker.name)
					set_modified();
				else if (!stricmp(goalp[item].docker.name, docker))
					set_modified();

				if (!goalp[item].dockee.name)
					set_modified();
				else if (!stricmp(goalp[item].dockee.name, dockee))
					set_modified();

				goalp[item].docker.name = docker;
				goalp[item].dockee.name = dockee;
			}

			break;

		case AI_GOAL_GUARD | AI_GOAL_GUARD_WING:
			switch (m_data[item] & TYPE_MASK) {
				case TYPE_SHIP:
				case TYPE_PLAYER:
					mode = AI_GOAL_GUARD;
					break;

				case TYPE_WING:
					mode = AI_GOAL_GUARD_WING;
					break;
			}

			break;

		default:
			Warning(LOCATION, "Unknown AI_GOAL type 0x%x", mode);
			MODIFY(goalp[item].ai_mode, AI_GOAL_NONE);
			return;
	}

	MODIFY(goalp[item].ai_mode, mode);

	*save = 0;
	if (goalp[item].ship_name)
		strcpy(save, goalp[item].ship_name);

	switch (m_data[item] & TYPE_MASK) {
		int not_used;

		case TYPE_SHIP:
		case TYPE_PLAYER:
			goalp[item].ship_name = ai_get_goal_ship_name(Ships[m_data[item] & DATA_MASK].ship_name, &not_used);
			break;

		case TYPE_WING:
			goalp[item].ship_name = ai_get_goal_ship_name(Wings[m_data[item] & DATA_MASK].name, &not_used);
			break;

		case TYPE_PATH:
			goalp[item].ship_name = ai_get_goal_ship_name(Waypoint_lists[m_data[item] & DATA_MASK].name, &not_used);
			break;

		case TYPE_WAYPOINT:
			goalp[item].ship_name = ai_get_goal_ship_name(object_name(m_data[item] & DATA_MASK), &not_used);
			break;

		case 0:
		case -1:
		case (-1 & TYPE_MASK):
			if (multi)
				return;

			sprintf(buf, "Order #%d doesn't have a valid target.  Order will be removed", item + 1);
			MessageBox(buf, "Notice");
			MODIFY(goalp[item].ai_mode, AI_GOAL_NONE);
			return;

		default:
			Assert(0);
	}

	if (stricmp(save, goalp[item].ship_name))
		set_modified();
}

void ShipGoalsDlg::OnOK()
{
	int i, mode;

	UpdateData(TRUE);

	for (i=0; i<ED_MAX_GOALS; i++) {
		mode = m_behavior_box[i] -> GetItemData(m_behavior[i]);
		if ((mode != AI_GOAL_NONE) && (mode != AI_GOAL_CHASE_ANY) && (mode != AI_GOAL_UNDOCK) && (mode != AI_GOAL_KEEP_SAFE_DISTANCE) && (mode != AI_GOAL_PLAY_DEAD) && (mode != AI_GOAL_WARP) ) {
			if (!m_object_box[i] -> GetCount())  // no valid objects?
				m_behavior[i] = 0;
			else
				m_data[i] = m_object_box[i] -> GetItemData(m_object[i]);
		}
	}

	update();
	CDialog::OnOK();
}

void ShipGoalsDlg::OnSelchangeObject1() 
{
	UpdateData(TRUE);
	set_object(0);
	m_subsys[0] = m_dock2[0] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeObject2() 
{
	UpdateData(TRUE);
	set_object(1);
	m_subsys[1] = m_dock2[1] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeObject3() 
{
	UpdateData(TRUE);
	set_object(2);
	m_subsys[2] = m_dock2[2] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeObject4() 
{
	UpdateData(TRUE);
	set_object(3);
	m_subsys[3] = m_dock2[3] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeObject5() 
{
	UpdateData(TRUE);
	set_object(4);
	m_subsys[4] = m_dock2[4] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeObject6()
{
	UpdateData(TRUE);
	set_object(5);
	m_subsys[5] = m_dock2[5] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeObject7()
{
	UpdateData(TRUE);
	set_object(6);
	m_subsys[6] = m_dock2[6] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeObject8() 
{
	UpdateData(TRUE);
	set_object(7);
	m_subsys[7] = m_dock2[7] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeObject9() 
{
	UpdateData(TRUE);
	set_object(8);
	m_subsys[8] = m_dock2[8] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::OnSelchangeObject10() 
{
	UpdateData(TRUE);
	set_object(9);
	m_subsys[9] = m_dock2[9] = 0;
	UpdateData(FALSE);
}

void ShipGoalsDlg::set_object(int item)
{
	char *str;
	int i = 0, z, num, not_used, mode;
	ship_subsys *subsys;

	if (m_behavior[item] > 0) {
		mode = m_behavior_box[item] -> GetItemData(m_behavior[item]);
		if (!m_object_box[item] -> GetCount())
			m_behavior[item] = m_data[item] = 0;
		else
			m_data[item] = m_object_box[item] -> GetItemData(m_object[item]);

		if ((mode == AI_GOAL_DOCK) && (m_data[item] >= 0)) {
			num = get_docking_list(Ships[m_data[item] & DATA_MASK].modelnum);
			m_dock2_box[item] -> EnableWindow(TRUE);
			m_dock2_box[item] -> ResetContent();
			for (i=0; i<num; i++) {
				Assert(Docking_bay_list[i]);
				z = m_dock2_box[item] -> AddString(Docking_bay_list[i]);
				str = ai_get_goal_ship_name(Docking_bay_list[i], &not_used);
				m_dock2_box[item] -> SetItemDataPtr(z, str);
			}

		} else if ((mode == AI_GOAL_DESTROY_SUBSYSTEM) && (m_data[item] >= 0)) {
			if (((m_data[item] & TYPE_MASK) == TYPE_SHIP) || ((m_data[item] & TYPE_MASK) == TYPE_PLAYER)) {
				i = m_data[item] & DATA_MASK;

			} else
				Int3();

			m_subsys_box[item] -> ResetContent();
			subsys = GET_FIRST(&Ships[i].subsys_list);
			z = 0;
			while (subsys != END_OF_LIST(&Ships[i].subsys_list)) {
				m_subsys_box[item]->AddString(subsys->system_info->subobj_name);
				m_subsys_box[item]->SetItemDataPtr(z, subsys->system_info->subobj_name);
				z++;
				subsys = GET_NEXT(subsys);
			}
		}
	}
}
