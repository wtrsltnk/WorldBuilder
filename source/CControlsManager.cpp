#include "CControlsManager.h"


/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////
CControlsManager::CControlsManager( HINSTANCE hInstance, 
								   HWND hParent,
								   CGroupManager *pGroupManager,
								   int nWidth, int nHeight )
{
	char szBuffer[ 255 ];
	this->m_hInstance = hInstance;
	this->m_hParent = hParent;
	this->m_pGroupManager = pGroupManager;
	this->nType = -1;

	m_pToolBar = new CToolBar( m_hInstance, m_hParent, IDC_TOOLBAR );
	m_pToolBar->create( IDB_TOOLBAR, 10, 24, 24 );
	LoadString( m_hInstance, IDS_BUILD_MAP, szBuffer, 255 );
	m_pToolBar->addButton( szBuffer, IDM_BUILD_MAP, 0 );
	LoadString( m_hInstance, IDS_BUILD_BATCH, szBuffer, 255 );
	m_pToolBar->addButton( szBuffer, IDM_BUILD_BATCH, 1 );
	LoadString( m_hInstance, IDS_BUILD_STARTHL, szBuffer, 255 );
	m_pToolBar->addButton( szBuffer, IDM_BUILD_STARTGAME, 2 );

	m_pToolBar->addSeperator();

	LoadString( m_hInstance, IDS_EDIT_NEW, szBuffer, 255 );
	m_pToolBar->addButton( szBuffer, IDM_EDIT_NEW, 3 );
	LoadString( m_hInstance, IDS_EDIT_EDIT, szBuffer, 255 );
	m_pToolBar->addButton( szBuffer, IDM_EDIT_EDIT, 4 );
	LoadString( m_hInstance, IDS_EDIT_DEL, szBuffer, 255 );
	m_pToolBar->addButton( szBuffer, IDM_EDIT_DEL, 5 );

	m_pStatusBar = new CStatusBar( m_hInstance, m_hParent, IDC_STATUSBAR );
	m_pStatusBar->create();
	m_pStatusBar->addItem( "No Selection", 125 );
	m_pStatusBar->addItem( "0", 75 );
	m_pStatusBar->addItem( "time", 82 );

	m_pTreeView = new CTreeView( m_hInstance, m_hParent, 0, 34, 200, nHeight - 34 - 20, IDC_TREEVIEW );
	m_pTreeView->create( WS_EX_STATICEDGE, TVS_SHOWSELALWAYS );
	m_pTreeView->setImageList( IDB_NODES, 16, 16, 10 );

	m_pLabel = new CLabel( m_hInstance, m_hParent, 205, 34, nWidth - 205, 145, IDC_LABEL );
	m_pLabel->create( WS_EX_STATICEDGE );
	m_pLabel->setText( szBuffer );
	m_pLabel->setFont( m_pStatusBar->getFont() );

	m_pReportView = new CReportView( m_hInstance, m_hParent, 205, 150 + 34, nWidth - 205, nHeight - 150 - 34 - 20, IDC_REPORTVIEW );
	m_pReportView->create( WS_EX_STATICEDGE, LVS_SHOWSELALWAYS | LVS_SINGLESEL );
	m_pReportView->setExStyle( LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );
	LoadString( m_hInstance, IDS_SELECTITEM, szBuffer, 255 );
	m_pReportView->addColumn( szBuffer, 0, 200 );
	m_pLabel->setText( szBuffer );

}

CControlsManager::~CControlsManager( void )
{
	delete m_pTreeView;
	delete m_pReportView;
	delete m_pLabel;
	delete m_pStatusBar;
	delete m_pToolBar;
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

void CControlsManager::resize( WPARAM wParam, LPARAM lParam )
{
	m_pToolBar->resize( wParam, lParam );
	m_pStatusBar->resize( wParam, lParam );

	int nWidth = LOWORD(lParam);
	int nHeight = HIWORD(lParam);

	m_pTreeView->resize( 0, 34, 200, nHeight - 34 - 20 );
	m_pLabel->resize( 205, 34, nWidth - 205, 145 );
	m_pReportView->resize( 205, 150 + 34, nWidth - 205, nHeight - 150 - 34 - 20 );
}

void CControlsManager::setPointer( CGroupManager *pGroupManager )
{
	this->m_pGroupManager = pGroupManager;
}

void CControlsManager::updateTreeView( void )
{
	HTREEITEM	hGroup,hTool, hCommand;
	CGroup		*pGroup;
	CTool		*pTool;
	CCommand	*pCommand;

	string		gr, tl, cmd;
	int			type;

	gr = this->getTVGroup();
	tl = this->getTVTool();
	cmd = this->getTVCommand();
	type = this->getTVSelectedType();

	m_pTreeView->reset();

	for ( int i = 0; i < m_pGroupManager->getGroupCount(); i++ )
	{
		pGroup = m_pGroupManager->getGroup( i );
		if ( pGroup != NULL )
		{
			hGroup = m_pTreeView->addItem( pGroup->getName(), TVGN_ROOT, 0 );
			for ( int j = 0; j < pGroup->getToolCount(); j++ )
			{
				pTool = pGroup->getTool( j );
				if ( pTool != NULL )
				{
					hTool = m_pTreeView->addItem( pTool->getName(), hGroup, 2 );
					if ( strcmp( const_cast <char*>(pGroup->getName().c_str()), const_cast <char*>(gr.c_str()) ) == 0 )
						m_pTreeView->expand( hGroup );
					for ( int k = 0; k < pTool->getCmdCount(); k++ )
					{
						pCommand = pTool->getCommand( k );
						if ( pCommand != NULL )
						{
							if ( strcmp( const_cast <char*>(pTool->getName().c_str()), const_cast <char*>(tl.c_str()) ) == 0 )
								m_pTreeView->expand( hTool );
							hCommand = m_pTreeView->addItem( pCommand->getName(), hTool, 4 );
						}
					}
				}
			}
			/*
			for ( j = 0; j < pGroup->getGameCmdCount(); j++ )
			{
				pCommand = pGroup->getGameCommand( j );
					if ( pCommand != NULL )
					{
						hCommand = m_pTreeView->addItem( pCommand->getName(), hGroup, 4 );
					}
			}
			*/
		}
	}
}

HTREEITEM CControlsManager::addItem( string str, HTREEITEM hParent, int iImage )
{
	return m_pTreeView->addItem( str, hParent, iImage );
}


void CControlsManager::SelectGroup( string group )
{
	CGroup		*pGroup;
	char		szBuffer[ 255 ];

	//group ophalen
	pGroup = m_pGroupManager->getGroup( group );

	//headers laden
	m_pReportView->reset();
	LoadString( m_hInstance, IDS_HEADER_NAME, szBuffer, 255 );
	m_pReportView->addColumn( szBuffer, 0, 250 );
	LoadString( m_hInstance, IDS_HEADER_DESCRIPTION, szBuffer, 255 );
	m_pReportView->addColumn( szBuffer, 1, 250 );

	if ( pGroup != NULL )
	{
        int i;
		//alle tools op het scherm zetten
        for ( i = 0; i < pGroup->getToolCount(); i++ )
		{
			m_pReportView->addItem( pGroup->getTool( i )->getName(), i, 0 );
			m_pReportView->addSubItem( pGroup->getTool( i )->getDescription(), i, 1 );
		}

		//alle gamecommands op het scherm
		for ( int j = i; j < pGroup->getGameCmdCount()+i; j++ )
		{
			m_pReportView->addItem( pGroup->getGameCommand( j - i )->getName(), i, 0 );
			m_pReportView->addSubItem( pGroup->getGameCommand( j - i )->getDescription(), i, 1 );
		}

		//alle info in het info veld
		strstream strsN, strsM, strsD, strsG, strsT, strsGN, strsGD;

		LoadString( m_hInstance, IDS_INFO_NAME, szBuffer, 255 );
		strsN << szBuffer << "\t" << pGroup->getName() << "\n" << ends;
		m_pLabel->setText( strsN.str() );
		delete strsN.str();

		LoadString( m_hInstance, IDS_INFO_MAP, szBuffer, 255 );
		strsM << szBuffer << "\t" << pGroup->getMapName() << "\n" << ends;
		m_pLabel->addText( strsM.str() );
		delete strsM.str();

		LoadString( m_hInstance, IDS_INFO_DESCRIPTION, szBuffer, 255 );
		strsD << szBuffer << "\t" << pGroup->getDescription() << "\n" << ends;
		m_pLabel->addText( strsD.str() );
		delete strsD.str();

		LoadString( m_hInstance, IDS_INFO_GAME, szBuffer, 255 );
		strsGN << szBuffer << "\t" << pGroup->getGameName() << "\n" << ends;
		m_pLabel->addText( strsGN.str() );
		delete strsGN.str();

		LoadString( m_hInstance, IDS_INFO_GAME_DIR, szBuffer, 255 );
		strsGD << szBuffer << "\t" << pGroup->getGameDir() << "\n" << ends;
		m_pLabel->addText( strsGD.str() );
		delete strsGD.str();

		LoadString( m_hInstance, IDS_INFO_TOOLCOUNT, szBuffer, 255 );
		strsT << szBuffer << "\t" << pGroup->getToolCount() << "\n" << ends;
		m_pLabel->addText( strsT.str() );
		delete strsT.str();

		LoadString( m_hInstance, IDS_INFO_GAMECMDCOUNT, szBuffer, 255 );
		strsG << szBuffer << "\t" << pGroup->getGameCmdCount() << "\n" << ends;
		m_pLabel->addText( strsG.str() );
		delete strsG.str();
	}
}

void CControlsManager::SelectTool( string group, string tool )
{
	CTool		*pTool;
	char		szBuffer[ 255 ];

	//tool ophalen
	pTool = m_pGroupManager->getGrTool( group, tool );

	//headers laden
	m_pReportView->reset();
	LoadString( m_hInstance, IDS_HEADER_NAME, szBuffer, 255 );
	m_pReportView->addColumn( szBuffer, 0, 250 );
	LoadString( m_hInstance, IDS_HEADER_DESCRIPTION, szBuffer, 255 );
	m_pReportView->addColumn( szBuffer, 1, 250 );

	if ( pTool != NULL )
	{
		//alle commands op het scherm zetten
		for ( int i = 0; i < pTool->getCmdCount(); i++ )
		{
			m_pReportView->addItem( pTool->getCommand( i )->getName(), i, 0 );
			m_pReportView->addSubItem( pTool->getCommand( i )->getDescription(), i, 1 );
		}

		//alle info in het info veld
		strstream strsN, strsD, strsG, strsT, strsC;

		LoadString( m_hInstance, IDS_INFO_NAME, szBuffer, 255 );
		strsN << szBuffer << "\t" << pTool->getName() << "\n" << ends;
		m_pLabel->setText( strsN.str() );
		delete strsN.str();

		LoadString( m_hInstance, IDS_INFO_CALL, szBuffer, 255 );
		strsC << szBuffer << "\t" << pTool->getCall() << "\n" << ends;
		m_pLabel->addText( strsC.str() );
		delete strsC.str();

		LoadString( m_hInstance, IDS_INFO_DESCRIPTION, szBuffer, 255 );
		strsD << szBuffer << "\t" << pTool->getDescription() << "\n" << ends;
		m_pLabel->addText( strsD.str() );
		delete strsD.str();

		LoadString( m_hInstance, IDS_INFO_CMDCOUNT, szBuffer, 255 );
		strsG << szBuffer << "\t" << pTool->getCmdCount() << "\n" << ends;
		m_pLabel->addText( strsG.str() );
		delete strsG.str();

		if ( pTool->isRun() )
		{
			LoadString( m_hInstance, IDS_INFO_RUN, szBuffer, 255 );
			m_pLabel->addText( "\n-" );
			m_pLabel->addText( szBuffer );
		}
	}
}

void CControlsManager::SelectCommand( string group, string tool, string command )
{
	CCommand	*pCommand;
	char		szBuffer[ 255 ];

	//command ophalen
	pCommand = m_pGroupManager->getTlCommand( group, tool, command );

	//headers laden
	m_pReportView->reset();
	LoadString( m_hInstance, IDS_HEADER_ITEM, szBuffer, 255 );
	m_pReportView->addColumn( szBuffer, 0, 250 );
	LoadString( m_hInstance, IDS_HEADER_VALUE, szBuffer, 255 );
	m_pReportView->addColumn( szBuffer, 1, 250 );

	if ( pCommand != NULL )
	{
		//alle mogelijke schit op het scherm zetten
		for ( int i = 0; i < 5; i++ )
		{
			LoadString( m_hInstance, IDS_ITEM_NAME + i, szBuffer, 255 );
			m_pReportView->addItem( szBuffer, i, 0 );
		}

		//zet de waarde er bij
		m_pReportView->addSubItem( pCommand->getName(), 0, 1 );
		m_pReportView->addSubItem( pCommand->getCall(), 1, 1 );
		m_pReportView->addSubItem( pCommand->getDescription(), 2, 1 );
		m_pReportView->addSubItem( pCommand->getValue(), 3, 1 );
		switch ( pCommand->getType() )
		{
		case TYPE_TEXT:
			m_pReportView->addSubItem( "TEXT", 4, 1 );
			break;
		case TYPE_BOOL:
			m_pReportView->addSubItem( "TRUE/FALSE", 4, 1 );
			break;
		case TYPE_INT:
			m_pReportView->addSubItem( "NUMBER", 4, 1 );
			break;
		}

		//alle info in het info veld
		strstream strsN, strsD, strsG, strsV, strsT;

		LoadString( m_hInstance, IDS_INFO_NAME, szBuffer, 255 );
		strsN << szBuffer << "\t" << pCommand->getName() << "\n" << ends;
		m_pLabel->setText( strsN.str() );
		delete strsN.str();

		LoadString( m_hInstance, IDS_INFO_CALL, szBuffer, 255 );
		strsG << szBuffer << "\t" << pCommand->getCall() << "\n" << ends;
		m_pLabel->addText( strsG.str() );
		delete strsG.str();

		LoadString( m_hInstance, IDS_INFO_DESCRIPTION, szBuffer, 255 );
		strsD << szBuffer << "\t" << pCommand->getDescription() << "\n" << ends;
		m_pLabel->addText( strsD.str() );
		delete strsD.str();

		LoadString( m_hInstance, IDS_INFO_VALUE, szBuffer, 255 );
		strsV << szBuffer << "\t" << pCommand->getValue() << "\n" << ends;
		m_pLabel->addText( strsV.str() );
		delete strsV.str();

		LoadString( m_hInstance, IDS_INFO_TYPE, szBuffer, 255 );
		switch ( pCommand->getType() )
		{
		case TYPE_TEXT:
			strsT << szBuffer << "\tTEXT\n" << ends;
			break;
		case TYPE_INT:
			strsT << szBuffer << "\tNUMBER\n" << ends;
			break;
		case TYPE_BOOL:
			strsT << szBuffer << "\tTRUE/FALSE\n" << ends;
			break;
		}
		
		m_pLabel->addText( strsT.str() );
		delete strsT.str();
	}
}

void CControlsManager::TVSelectionChanged( void )
{
	HTREEITEM		sel, parent, group, tool, command;

	sel = m_pTreeView->getSelection();
	group = m_pTreeView->getParent( sel );
	m_pLabel->setText( "" );
	if ( group == TVGN_ROOT )
	{
		SelectGroup( m_pTreeView->getItemText( sel ) );
		nType = 0;
	}
	else
	{
		parent = m_pTreeView->getParent( sel );
		tool = m_pTreeView->getParent( parent );
		if ( tool == TVGN_ROOT )
		{
			group = m_pTreeView->getParent( sel );
			SelectTool( m_pTreeView->getItemText( group ),
				m_pTreeView->getItemText( sel ) );
			nType = 1;
		}
		else
		{
			command = m_pTreeView->getParent( sel );
			group = m_pTreeView->getParent( command );
			SelectCommand( m_pTreeView->getItemText( group ),
				m_pTreeView->getItemText( command ),
				m_pTreeView->getItemText( sel ) );
			nType = 2;
		}
	}
}

void CControlsManager::RVSelectionChanged( void )
{
	if  ( 
		m_pReportView->getSelectedIndex() 
		>= 
		m_pGroupManager->getGroup( this->getTVGroup() )->getToolCount()
		)
	{
		nType = 3;
	}
}

int CControlsManager::getTVSelectedType( void )
{
	return nType;
}

void CControlsManager::timeChanged( void )
{
	struct tm *newtime;
	long ltime;

	time( &ltime );										//haal de tijd op
	newtime = localtime( &ltime );

	m_pStatusBar->setItemText( asctime ( newtime ), 3 );
}

void CControlsManager::setTVinST( void )
{
	string selGroup = getTVGroup();
	m_pStatusBar->setItemText( getTVSelectedItem(), 1 );

	char *temp;
	temp = new char;
	switch ( getTVSelectedType() )
	{
	case 0:
		itoa( m_pGroupManager->getGroup( selGroup )->getToolCount(), temp, 10 );
		break;
	case 1:
		itoa( m_pGroupManager->getGrTool( selGroup, getTVTool() )->getCmdCount(), temp, 10 );
		break;
	default:
        temp[0] = '0';
		break;
	}
	m_pStatusBar->setItemText( temp, 2 );
}

string CControlsManager::getTVSelectedItem( void )
{
	return m_pTreeView->getItemText( m_pTreeView->getSelection() );
}

string CControlsManager::getRVSelectedItem( void )
{
	return m_pReportView->getItemText( m_pReportView->getSelectedIndex() );
}

int CControlsManager::getRVSelectedIndex( void )
{
	return m_pReportView->getSelectedIndex();
}

string CControlsManager::getTVGroup( void )
{
	switch ( getTVSelectedType() )
	{
	case 0:
		return getTVSelectedItem();
		break;
	case 1:
		return m_pTreeView->getItemText( m_pTreeView->getParent( m_pTreeView->getSelection() ) );
		break;
	case 2:
		return m_pTreeView->getItemText( m_pTreeView->getParent( m_pTreeView->getParent( m_pTreeView->getSelection() ) ) );
		break;
	default:
		return "";
		break;
	}
}

string CControlsManager::getTVTool( void )
{
	switch ( getTVSelectedType() )
	{
	case 0:
		return "";
		break;
	case 1:
		return getTVSelectedItem();
		break;
	case 2:
		return m_pTreeView->getItemText( m_pTreeView->getParent( m_pTreeView->getSelection() ) );
		break;
	default:
		return "";
		break;
	}
}

string CControlsManager::getTVCommand( void )
{
	switch ( getTVSelectedType() )
	{
	case 0:
		return "";
		break;
	case 1:
		return "";
		break;
	case 2:
		return m_pTreeView->getItemText( m_pTreeView->getSelection() );
		break;
	default:
		return "";
		break;
	}
}
