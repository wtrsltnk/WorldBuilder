#include "CCommand.h"


////////////////////////////////////////////////////////
//CONSTRUCTOR / DESCRUCTOR
////////////////////////////////////////////////////////
CCommand::CCommand( string name, string call )
{
	this->cmdName = name;
	this->cmdDescription = "No Description";
	this->cmdCall = call;
	this->cmdValue = "No Value";
	this->cmdType = TYPE_TEXT;
}

CCommand::CCommand( void )
{
	this->cmdName = "No Name";
	this->cmdDescription = "No Description";
	this->cmdCall = "No Call";
	this->cmdValue = "No Value";
	this->cmdType = TYPE_TEXT;
}

CCommand::~CCommand( void )
{
}

////////////////////////////////////////////////////////
//Savefunctions
////////////////////////////////////////////////////////

bool CCommand::save( string filename )
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

bool CCommand::save( ofstream &output, int level )
{
	string tab;
	char *temp;
	for ( int i = 0; i < level; i++ )
	{
		tab += '\t';
	}

	output << tab.c_str() << "<Command>" << "\n";

	output << tab.c_str() << "\t" << "<CommandName>" << "\n";
	output << tab.c_str() << "\t\"" << this->getName().c_str() << "\"\n";
	output << tab.c_str() << "\t" << "</CommandName>" << "\n";

	output << tab.c_str() << "\t" << "<CommandDescription>" << "\n";
	output << tab.c_str() << "\t\"" << this->getDescription().c_str() << "\"\n";
	output << tab.c_str() << "\t" << "</CommandDescription>" << "\n";

	output << tab.c_str() << "\t" << "<CommandCall>" << "\n";
	output << tab.c_str() << "\t\"" << this->getCall().c_str() << "\"\n";
	output << tab.c_str() << "\t" << "</CommandCall>" << "\n";

	output << tab.c_str() << "\t" << "<CommandValue>" << "\n";
	output << tab.c_str() << "\t\"" << this->getValue().c_str() << "\"\n";
	output << tab.c_str() << "\t" << "</CommandValue>" << "\n";

	output << tab.c_str() << "\t" << "<CommandType>" << "\n";
	temp = new char;
	itoa( this->getType(), temp, 10 );
	output << tab.c_str() << "\t\"" << temp << "\"\n";
	output << tab.c_str() << "\t" << "</CommandType>" << "\n";

	output << tab.c_str() << "</Command>" << "\n";
	return true;
}

bool CCommand::load( CXMLParser *xml )
{
	while ( stricmp( xml->GetElementName(), "</Command>" ) != 0 )
	{
		if ( strcmp( xml->GetElementName(), "<CommandName>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				this->setName( trim(xml->GetData() ) );
			}
		}
		else if ( strcmp( xml->GetElementName(), "<CommandDescription>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				this->setDescription( trim(xml->GetData() ) );
			}
		}
		else if ( strcmp( xml->GetElementName(), "<CommandCall>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				this->setCall( trim(xml->GetData() ) );
			}
		}
		else if ( strcmp( xml->GetElementName(), "<CommandValue>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				this->setValue( trim(xml->GetData() ) );
			}
		}
		else if ( strcmp( xml->GetElementName(), "<CommandType>" ) == 0 )
		{
			if ( xml->HasData() )
			{
				this->setType( atoi( const_cast <char*> (trim( xml->GetData() ).c_str()) ) );
			}
		}
		xml->GetNextElement();
	}
	return true;
}

bool CCommand::load( string filename )
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

	if ( strcmp( xml.GetElementName(), "<Command>" ) != 0 )
	{
		throw( "Wrong File" );
		return false;
	}

	xml.GetNextElement();
	this->load( &xml );

	return true;
}

//////////////////////
//GET/SET Functions
//////////////////////
string CCommand::getName( void )
{
	return this->cmdName;
}

void CCommand::setName( string name )
{
	if ( strcmp( name.c_str(), "" ) != 0 )
		this->cmdName = name;
	else
		this->cmdName = "No Name";
}

string CCommand::getDescription( void )
{
	return this->cmdDescription;
}
	
void CCommand::setDescription( string description )
{
	if ( strcmp( description.c_str(), "" ) != 0 )
		this->cmdDescription = description;
	else
		this->cmdDescription = "No Description";
}

string CCommand::getCall( void )
{
	return this->cmdCall;
}

void CCommand::setCall( string call )
{
	if ( strcmp( call.c_str(), "" ) != 0 )
		this->cmdCall = call;
	else
		this->cmdCall = "No Call";
}

string CCommand::getValue( void )
{
	return this->cmdValue;
}

void CCommand::setValue( string value )
{
	if ( strcmp( value.c_str(), "" ) != 0 )
		this->cmdValue = value;
	else
		this->cmdValue = "No Value";
}

int CCommand::getType( void )
{
	return this->cmdType;
}

void CCommand::setType( int type )
{
	this->cmdType = type;
}