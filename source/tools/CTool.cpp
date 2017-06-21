#include "CTool.h"


////////////////////////////////////////////////////////
//CONSTRUCTOR / DESCRUCTOR
////////////////////////////////////////////////////////
CTool::CTool( string name, bool run )
{
	this->tlName = name;
	this->tlName = "No Call";
	this->tlDescription = "No Description";
	this->tlRun = run;
}

CTool::CTool( void )
{
	this->tlName = "No Name";
	this->tlName = "No Call";
	this->tlDescription = "No Description";
	this->tlRun = false;
}

CTool::~CTool( void )
{
}

////////////////////////////////////////////////////////
//Savefunctions
////////////////////////////////////////////////////////

bool CTool::save( string filename )
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

bool CTool::save( ofstream &output, int level )
{
	string tab;
	for ( int i = 0; i < level; i++ )
	{
		tab += '\t';
	}

	output << tab.c_str() << "<Tool>" << "\n";
	
	output << tab.c_str() << "\t" << "<ToolName>" << "\n";
	output << tab.c_str() << "\t\t\"" << this->getName().c_str() << "\"\n";
	output << tab.c_str() << "\t" << "</ToolName>" << "\n";
	
	output << tab.c_str() << "\t" << "<ToolCall>" << "\n";
	output << tab.c_str() << "\t\t\"" << this->getCall().c_str() << "\"\n";
	output << tab.c_str() << "\t" << "</ToolCall>" << "\n";
	
	output << tab.c_str() << "\t" << "<ToolDescription>" << "\n";
	output << tab.c_str() << "\t\t\"" << this->getDescription().c_str() << "\"\n";
	output << tab.c_str() << "\t" << "</ToolDescription>" << "\n";
	
	output << tab.c_str() << "\t" << "<ToolRun>" << "\n";
	if ( this->isRun() )
		output << tab.c_str() << "\t\t\"" << "true" << "\"\n";
	else
		output << tab.c_str() << "\t\t\"" << "false" << "\"\n";
	output << tab.c_str() << "\t" << "</ToolRun>" << "\n";

	for ( int j = 0; j < this->getCmdCount(); j++ )
		this->getCommand( j )->save( output, level+1 );

	output << tab.c_str() << "</Tool>" << "\n";
	return true;
}

bool CTool::load( string filename )
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

	if ( strcmp( xml.GetElementName(), "<Tool>" ) != 0 )
	{
		throw( "Wrong File" );
		return false;
	}

	xml.GetNextElement();
	this->load( &xml );

	return true;
}

bool CTool::load( CXMLParser *xml )
{
	CCommand *cmd;

	while ( stricmp( xml->GetElementName(), "</Tool>" ) != 0 )
	{
		if ( strcmp( xml->GetElementName(), "<ToolName>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				this->setName( trim(xml->GetData() ) );
			}
		}
		else if ( strcmp( xml->GetElementName(), "<ToolCall>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				this->setCall( trim(xml->GetData() ) );
			}
		}
		else if ( strcmp( xml->GetElementName(), "<ToolDescription>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				this->setDescription( trim(xml->GetData() ) );
			}
		}
		else if ( strcmp( xml->GetElementName(), "<ToolRun>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				if ( strcmp( xml->GetData(), "true" ) )
				{
					this->setRun( true );
				}
				else
				{
					this->setRun( false );
				}
			}
		}
		else if ( strcmp( xml->GetElementName(), "<Command>" ) == 0 )
		{
			cmd = new CCommand();
			cmd->load( xml );
			this->addCommand( cmd );
		}
		xml->GetNextElement();
	}
	return true;
}

////////////////////////////////////////////////////////
//ToolFunctions
////////////////////////////////////////////////////////

//////////////////////
//VECTOR Functions
//////////////////////
bool CTool::addCommand( CCommand *cmd )
{
	if ( cmd != NULL )
		commands.push_back( *cmd );
	else
		return false;
	return true;
}

bool CTool::remCommand( string name )
{
	if ( !commands.empty() )
	{
		for ( int i = 0; i < commands.size(); i++ )
			if ( strcmp( const_cast <char *> (commands[ i ].getName().c_str()), const_cast <char *> (name.c_str()) ) == 0 )
			{
				commands.erase( commands.begin() + i );
				return true;
			}
	}
	return false;
}

CCommand *CTool::getCommand( string name )
{
	if ( !commands.empty() )
	{
		for ( int i = 0; i < commands.size(); i++ )
			if ( strcmp( const_cast <char *> (commands[ i ].getName().c_str()), const_cast <char *> (name.c_str()) ) == 0 )
			{
				return &commands[ i ];
			}
	}
	return NULL;
}

CCommand *CTool::getCommand( int index )
{
	if ( !commands.empty() )
	{
		return &commands[ index ];
	}
	return NULL;
}

int CTool::getCmdCount( void )
{
	return commands.size();
}

//////////////////////
//GET/SET Functions
//////////////////////
string CTool::getName( void )
{
	return this->tlName;
}

void CTool::setName( string name )
{
	if ( strcmp( name.c_str(), "" ) != 0 )
		this->tlName = name;
	else
		this->tlName = "No Name";
}
string CTool::getCall( void )
{
	return this->tlCall;
}

void CTool::setCall( string call )
{
	if ( strcmp( call.c_str(), "" ) != 0 )
		this->tlCall = call;
	else
		this->tlCall = "No Call";
}

string CTool::getDescription( void )
{
	return this->tlDescription;
}
	
void CTool::setDescription( string description )
{
	if ( strcmp( description.c_str(), "" ) != 0 )
		this->tlDescription = description;
	else
		this->tlDescription = "No Description";
}

bool CTool::isRun( void )
{
	return this->tlRun;
}

void CTool::setRun( bool run )
{
	this->tlRun = run;
}


////////////////////////////////////////////////////////
//Command Functions
////////////////////////////////////////////////////////

//////////////////////
//GET/SET Functions
//////////////////////
string CTool::getCmdDescription( string cmdName )
{
	if ( getCommand( cmdName ) != NULL )
		return getCommand( cmdName )->getDescription();
	return "No Description:";
}

void CTool::setCmdDescription( string cmdName, string description )
{
	if ( getCommand( cmdName ) != NULL )
		getCommand( cmdName )->setDescription( description );
}

string CTool::getCmdCall( string cmdName )
{
	if ( getCommand( cmdName ) != NULL )
		return getCommand( cmdName )->getCall();
	return "No Call:";
}

void CTool::setCmdCall( string cmdName, string call )
{
	if ( getCommand( cmdName ) != NULL )
		getCommand( cmdName )->setCall( call );
}

string CTool::getCmdValue( string cmdName )
{
	if ( getCommand( cmdName ) != NULL )
		return getCommand( cmdName )->getValue();
	return "No Value:";
}

void CTool::setCmdValue( string cmdName, string value )
{
	if ( getCommand( cmdName ) != NULL )
		getCommand( cmdName )->setValue( value );
}


int CTool::getCmdType( string cmdName )
{
	if ( getCommand( cmdName ) != NULL )
		return getCommand( cmdName )->getType();
	return -1;
}

void CTool::setCmdType( string cmdName, int type )
{
	if ( getCommand( cmdName ) != NULL )
		getCommand( cmdName )->setType( type );
}