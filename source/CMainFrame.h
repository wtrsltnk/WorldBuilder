#ifndef CMAINFRAME_H
#define CMAINFRAME_H

#include <direct.h>
#include <strstream>
using namespace std;
#include "CWin.h"
#include "..\resource\resource.h"
#include "custommsg.h"
#include "CControlsManager.h"
#include "CDialogsManager.h"
#include "CCompileManager.h"
#include "tools\CGroupManager.h"
//#include "CSettings.h"

class CMainFrame : public CWin
{
private:
	CControlsManager			*m_pControlsManager;
	CDialogsManager				*m_pDialogsManager;
	CGroupManager				*m_pGroupManager;
	CCompileManager				*m_pCompileManager;

	char						m_pAppPath[MAX_PATH];
	int							newFollowUp;
	string						m_strDataname;
	string						m_strBatchname;
	bool						m_bChange;
	int							m_nX, m_nY;
	int							m_nWidth, m_nHeight;

	char						appPath[MAX_PATH];
public:
	CMainFrame();
	~CMainFrame();

	char *GetParameters( char * cmdline );
	void GetAppPath( char *lpCmdLine, char *dest );

	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	static LRESULT AboutProc(HWND, UINT, WPARAM, LPARAM);
};

#endif
