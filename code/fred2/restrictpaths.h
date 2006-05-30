/*
 *
 */

/*
 * $Logfile: $
 * $Revision: 1.1 $
 * $Date: 2006-05-30 05:58:59 $
 * $Author: Goober5000 $
 *
 * Code for restricting arrival/departure to specific bays
 *
 * $Log: not supported by cvs2svn $
 *
 * $NoKeywords: $
 */

#include "model/model.h"
#include "parse/parselo.h"

/////////////////////////////////////////////////////////////////////////////
// restrict_paths dialog

class restrict_paths : public CDialog
{
// Construction
public:	
	restrict_paths(CWnd* pParent = NULL);   // standard constructor

	// parameters for the dialog
	int	m_ship_class;
	bool m_arrival;


// Dialog Data
	//{{AFX_DATA(restrict_paths)
	enum { IDD = IDD_RESTRICT_PATHS };
	CCheckListBox		m_path_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(restrict_paths)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(restrict_paths)
	virtual BOOL OnInitDialog();
	void OnCancel();	
	void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	// model info
	polymodel *m_model;
	int m_num_paths;

	// data for check box list
	struct {
		char name[MAX_NAME_LEN];
		bool allowed;
	} m_ship_bay_data[MAX_SHIP_BAY_PATHS];

	// regenerate all controls
	void reset_controls();
};
