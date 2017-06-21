#include "CGroup.h"


////////////////////////////////////////////////////////
//CONSTRUCTOR / DESCRUCTOR
////////////////////////////////////////////////////////
CGroup::CGroup( string name )
{
	this->grName = name;
	this->grDescription = "No Desciprtion";
	this->grGameName = "No Game";
	this->grBaseDir = "No Default Directory";
	this->grMapName = "No Map Name";
	this->grGameDir = "No Game Dir";
	this->grWadDrive = "c:";
	this->grGameRun = false;
	cmdCount = 0;
	toolCount = 0;
}

CGroup::CGroup( void )
{
	this->grName = "No Name";
	this->grDescription = "No Desciprtion";
	this->grGameName = "No Game";
	this->grBaseDir = "No Default Directory";
	this->grMapName = "No Map Name";
	this->grGameDir = "No Game Dir";
	this->grWadDrive = "c:";
	this->grGameRun = false;;

	cmdCount = 0;
	toolCount = 0;
}

CGroup::~CGroup( void )
{
}

////////////////////////////////////////////////////////
//Savefunctions
////////////////////////////////////////////////////////

bool CGroup::save( string filename )
{
	ofstream output;

// CONTROLE
	if ( stricmp(filename.c_str(), "") == 0 )
	{
		throw( "No file name specified !\n" );
		return false;
	}

	output.open((const char *)filename.c_str());
	if (output.fail())
	{
		throw( "Couldn't open this file\n" );
		return false;
	}

// SCHRIJVEN
	output << "<?xml version=\"1.0\" encoding=\"iso-8859-1\" ?>\n"
		<< "<!-- WorldBuilder Data Storage File -->\n";

	this->save( output, 0 );

// DONE
	output.close();
	return true;
}

bool CGroup::save( ofstream &output, int level )
{
	string tab;
	for ( int i = 0; i < level; i++ )
	{
		tab += '\t';
	}

	output << tab.c_str() << "<Group>" << "\n";

	output << tab.c_str() << "\t" << "<GroupName>" << "\n";
	output << tab.c_str() << "\t\t\"" << this->getName().c_str() << "\"\n";
	output << tab.c_str() << "\t" << "</GroupName>" << "\n";

	output << tab.c_str() << "\t" << "<GroupBaseDir>" << "\n";
	output << tab.c_str() << "\t\t\"" << this->getBaseDir().c_str() << "\"\n";
	output << tab.c_str() << "\t" << "</GroupBaseDir>" << "\n";

	output << tab.c_str() << "\t" << "<GroupMapName>" << "\n";
	output << tab.c_str() << "\t\t\"" << this->getMapName().c_str() << "\"\n";
	output << tab.c_str() << "\t" << "</GroupMapName>" << "\n";

	output << tab.c_str() << "\t" << "<GroupDescription>" << "\n";
	output << tab.c_str() << "\t\t\"" << this->getDescription().c_str() << "\"\n";
	output << tab.c_str() << "\t" << "</GroupDescription>" << "\n";

	output << tab.c_str() << "\t" << "<GroupGameName>" << "\n";
	output << tab.c_str() << "\t\t\"" << this->getGameName().c_str() << "\"\n";
	output << tab.c_str() << "\t" << "</GroupGameName>" << "\n";

	output << tab.c_str() << "\t" << "<GroupGameDir>" << "\n";
	output << tab.c_str() << "\t\t\"" << this->getGameDir().c_str() << "\"\n";
	output << tab.c_str() << "\t" << "</GroupGameDir>" << "\n";

	output << tab.c_str() << "\t" << "<GroupWadDrive>" << "\n";
	output << tab.c_str() << "\t\t\"" << this->getWadDrive().c_str() << "\"\n";
	output << tab.c_str() << "\t" << "</GroupWadDrive>" << "\n";

	output << tab.c_str() << "\t" << "<GroupGameRun>" << "\n";
	if ( this->isGameRun() )
		output << tab.c_str() << "\t\t\"" << "true" << "\"\n";
	else
		output << tab.c_str() << "\t\t\"" << "false" << "\"\n";
	output << tab.c_str() << "\t" << "</GroupGameRun>" << "\n";

	for ( int j = 0; j < this->getGameCmdCount(); j++ )
		this->getGameCommand( j )->save( output, level+1 );
	
	for ( int k = 0; k < this->getToolCount(); k++ )
		this->getTool( k )->save( output, level+1 );

	output << tab.c_str() << "</Group>" << "\n";
	return true;
}

bool CGroup::load( CXMLParser *xml )
{
	CTool *tl;
	CCommand *cmd;

	while ( stricmp( xml->GetElementName(), "</Group>" ) != 0 )
	{
		if ( strcmp( xml->GetElementName(), "<GroupName>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				this->setName( trim(xml->GetData() ) );
			}
		}
		else if ( strcmp( xml->GetElementName(), "<GroupBaseDir>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				this->setBaseDir( trim(xml->GetData() ) );
			}
		}
		else if ( strcmp( xml->GetElementName(), "<GroupMapName>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				this->setMapName( trim(xml->GetData() ) );
			}
		}
		else if ( strcmp( xml->GetElementName(), "<GroupDesciption>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				this->setDescription( trim(xml->GetData() ) );
			}
		}
		else if ( strcmp( xml->GetElementName(), "<GroupGameName>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				this->setGameName( trim(xml->GetData() ) );
			}
		}
		else if ( strcmp( xml->GetElementName(), "<GroupGameDir>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				this->setGameDir( trim(xml->GetData() ) );
			}
		}
		else if ( strcmp( xml->GetElementName(), "<GroupWadDrive>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				this->setWadDrive( trim(xml->GetData() ) );
			}
		}
		else if ( strcmp( xml->GetElementName(), "<GroupMapName>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				this->setMapName( trim(xml->GetData() ) );
			}
		}
		else if ( strcmp( xml->GetElementName(), "<GroupGameRun>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				if ( strcmp( xml->GetData(), "true" ) )
				{
					this->setGameRun( true );
				}
				else
				{
					this->setGameRun( false );
				}
			}
		}
		else if ( strcmp( xml->GetElementName(), "<Command>" ) == 0 )
		{
			cmd = new CCommand();
			cmd->load( xml );
			this->addGameCommand( cmd );
		}
		else if ( strcmp( xml->GetElementName(), "<Tool>" ) == 0 )
		{
			tl = new CTool();
			tl->load( xml );
			this->addTool( tl );
		}
		xml->GetNextElement();
	}
	return true;
}

bool CGroup::load( string filename )
{
	CXMLParser xml;

	try
	{
		xml.SetXmlFile( const_cast <char *> (filename.c_str()) );
	}
	catch ( char * error )
	{
		throw( error );
		return false;
	}

	xml.GetNextElement();
	xml.GetNextElement();
	xml.GetNextElement();

	if ( strcmp( xml.GetElementName(), "<Group>" ) != 0 )
	{
		throw( "Wrong File" );
		return false;
	}

	xml.GetNextElement();
	this->load( &xml );

	return true;
}

////////////////////////////////////////////////////////
//Group Functions
////////////////////////////////////////////////////////

//////////////////////
//VECTOR Functions
//////////////////////
bool CGroup::addGameCommand( CCommand *cmd )
{
	if ( cmd != NULL )
		gameCommands.push_back( *cmd );
	else
		return false;

	cmdCount++;
	return true;
}

bool CGroup::remGameCommand( string name )
{
	if ( !gameCommands.empty() )
	{
		for ( int i = 0; i < gameCommands.size(); i++ )
			if ( strcmp( const_cast <char *> (gameCommands[ i ].getName().c_str()), const_cast <char *> (name.c_str()) ) == 0 )
			{
				gameCommands.erase( gameCommands.begin() + i );
				cmdCount--;
				return true;
			}
	}
	return false;
}

CCommand *CGroup::getGameCommand( string name )
{
	if ( !gameCommands.empty() )
	{
		for ( int i = 0; i < gameCommands.size(); i++ )
		{
			if ( strcmp( const_cast <char *> (gameCommands[ i ].getName().c_str()), const_cast <char *> (name.c_str()) ) == 0 )
			{
				return &gameCommands[ i ];
			}
		}
	}
	return NULL;
}

CCommand *CGroup::getGameCommand( int index )
{
	if ( !gameCommands.empty() )
	{
		return &gameCommands[ index ];
	}
	return NULL;
}

int CGroup::getGameCmdCount( void )
{
	return cmdCount;
}

bool CGroup::addTool( CTool *tool )
{
	if ( tool != NULL )
		tools.push_back( *tool );
	else
		return false;

	toolCount++;
	return true;
}

bool CGroup::remTool( string name )
{
	if ( !tools.empty() )
	{
		for ( int i = 0; i < tools.size(); i++ )
			if ( strcmp( const_cast <char *> (tools[ i ].getName().c_str()), const_cast <char *> (name.c_str()) ) == 0 )
			{
				tools.erase( tools.begin() + i );
				toolCount--;
				return true;
			}
	}
	return false;
}

CTool *CGroup::getTool( string name )
{
	if ( !tools.empty() )
	{
		for ( int i = 0; i < tools.size(); i++ )
		{
			if ( strcmp( const_cast <char *> (tools[ i ].getName().c_str()), const_cast <char *> (name.c_str()) ) == 0 )
			{
				return &tools[ i ];
			}
		}
	}
	return NULL;
}

CTool *CGroup::getTool( int index )
{
	if ( !tools.empty() )
	{
		return &tools[ index ];
	}
	return NULL;
}

int CGroup::getToolCount( void )
{
	return toolCount;
}

//////////////////////
//GET/SET Functions
//////////////////////
string CGroup::getName( void )
{
	return this->grName;
}

void CGroup::setName( string name )
{
	if ( strcmp( name.c_str(), "" ) != 0 )
		this->grName = name;
	else
		this->grName = "No Name";
}

string CGroup::getBaseDir( void )
{
	return this->grBaseDir;
}

void CGroup::setBaseDir( string basedir )
{
	if ( strcmp( basedir.c_str(), "" ) != 0 )
		this->grBaseDir = basedir;
	else
		this->grBaseDir = "No Default Directory";
}

string CGroup::getMapName( void )
{
	return this->grMapName;
}

void CGroup::setMapName( string mapname )
{
	if ( strcmp( mapname.c_str(), "" ) != 0 )
		this->grMapName = mapname;
	else
		this->grMapName = "No Map Name";
}

string CGroup::getDescription( void )
{
	return this->grDescription;
}
	
void CGroup::setDescription( string description )
{
	if ( strcmp( description.c_str(), "" ) != 0 )
		this->grDescription = description;
	else
		this->grDescription = "No Desciprtion";
}

string CGroup::getGameName( void )
{
	return this->grGameName;
}
	
void CGroup::setGameName( string gamename )
{
	if ( strcmp( gamename.c_str(), "" ) != 0 )
		this->grGameName = gamename;
	else
		this->grGameName = "No Game";
}

string CGroup::getGameDir( void )
{
	return this->grGameDir;
}
	
void CGroup::setGameDir( string gamedir )
{
	if ( strcmp( gamedir.c_str(), "" ) != 0 )
		this->grGameDir = gamedir;
	else
		this->grGameDir = "No Game Dir";
}

string CGroup::getWadDrive( void )
{
	return this->grWadDrive;
}
	
void CGroup::setWadDrive( string waddrive )
{
	if ( strcmp( waddrive.c_str(), "" ) != 0 )
		this->grWadDrive = waddrive;
	else
		this->grWadDrive = "No Wad Drive";
}

bool CGroup::isGameRun( void )
{
	return this->grGameRun;
}

void CGroup::setGameRun( bool run )
{
	this->grGameRun = run;
}



////////////////////////////////////////////////////////
//Tool Functions
////////////////////////////////////////////////////////

//////////////////////
//VECTOR Functions
//////////////////////
bool CGroup::addTlCommand( string tlName, CCommand *cmd )
{
	if ( getTool( tlName ) != NULL )
		return getTool( tlName )->addCommand( cmd );
	return false;
}

bool CGroup::remTlCommand( string tlName, string name )
{
	if ( getTool( tlName ) != NULL )
		return getTool( tlName )->remCommand( name );
	return false;
}

CCommand *CGroup::getTlCommand( string tlName, string name )
{
	if ( getTool( tlName ) != NULL )
		return getTool( tlName )->getCommand( name );
	return NULL;
}

int CGroup::getTlCmdCount( string tlName )
{
	if ( getTool( tlName ) != NULL )
		return getTool( tlName )->getCmdCount();
	return 0;
}

//////////////////////
//GET/SET Functions
//////////////////////
string CGroup::getTlName( string tlName )
{
	if ( getTool( tlName ) != NULL )
		return getTool( tlName )->getName();
	return "No Name:";
}

void CGroup::setTlName( string tlName, string name )
{
	if ( getTool( tlName ) != NULL )
		getTool( tlName )->setName( name );
}

string CGroup::getTlCall( string tlName )
{
	if ( getTool( tlName ) != NULL )
		return getTool( tlName )->getCall();
	return "No Call:";
}

void CGroup::setTlCall( string tlName, string call )
{
	if ( getTool( tlName ) != NULL )
		getTool( tlName )->setCall( call );
}

string CGroup::getTlDescription( string tlName )
{
	if ( getTool( tlName ) != NULL )
		return getTool( tlName )->getDescription();
	return "NoDescription:";
}
	
void CGroup::setTlDescription( string tlName, string description )
{
	if ( getTool( tlName ) != NULL )
		getTool( tlName )->setDescription( description );
}

bool CGroup::isTlRun( string tlName )
{
	if ( getTool( tlName ) != NULL )
		return getTool( tlName )->isRun();
	return false;
}

void CGroup::setTlRun( string tlName, bool run )
{
	if ( getTool( tlName ) != NULL )
		getTool( tlName )->setRun( run );
}


////////////////////////////////////////////////////////
//Command Functions
////////////////////////////////////////////////////////

//////////////////////
//GET/SET Functions
//////////////////////
string CGroup::getCmdDescription( string tlName, string cmdName )
{
	if ( getTool( tlName ) != NULL )
		return getTool( tlName )->getCmdDescription( cmdName );
	return "No Description:";
}

void CGroup::setCmdDescription( string tlName, string cmdName, string description )
{
	getTool( tlName )->setCmdDescription( cmdName, description );
}

string CGroup::getCmdCall( string tlName, string cmdName )
{
	if ( getTool( tlName ) != NULL )
		return getTool( tlName )->getCmdCall( cmdName );
	return "No Call:";
}

void CGroup::setCmdCall( string tlName, string cmdName, string call )
{
	getTool( tlName )->setCmdCall( cmdName, call );
}

string CGroup::getCmdValue( string tlName, string cmdName )
{
	if ( getTool( tlName ) != NULL )
		return getTool( tlName )->getCmdValue( cmdName );
	return "No Value:";
}

void CGroup::setCmdValue( string tlName, string cmdName, string value )
{
	getTool( tlName )->setCmdValue( cmdName, value );
}


int CGroup::getCmdType( string tlName, string cmdName )
{
	if ( getTool( tlName ) != NULL )
		return getTool( tlName )->getCmdType( cmdName );
	return -1;
}

void CGroup::setCmdType( string tlName, string cmdName, int type )
{
	getTool( tlName )->setCmdType( cmdName, type );
}
