/*
	CXMLParser.cpp
	Een zeer eenvoudige XML parser t.b.v. HI blok 1.4 
	Jan Verhoeven
	Hogeschool Windesheim
	Maart 2003
*/

#include "xmlparser.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>
#include <cstdio>
#include <iostream>
using namespace std;

CXMLParser::CXMLParser()				//	constructor
{
	m_size = 0;
	m_pos = 0;
	m_level = 0;
	m_element[0] = '\0';
	m_data[0] = '\0';
}

CXMLParser::~CXMLParser()				//	destructor
{
	//if (m_size > 0)
	//	delete [] m_buf;
}

void CXMLParser::SetXmlFile(char *FileName) throw()
{
	FILE *F;							//	het te lezen bestand
	size_t numread;						//	grootte
	struct _stat status;				//	info over bestand

	if (_stat( FileName, &status) != 0)
		throw("Xml invoerbestand is niet te benaderen");

	m_size = (int)status.st_size + 1;	//	vraag bestandsgrootte in bytes

	try
	{
	   m_buf = new char[m_size];		//	reserveer genoeg geheugen voor bestand
	} 
	catch(...)
	{
		throw("Te weinig vrij geheugen aanwezig");
	}

	F = fopen(FileName, "r+t");			//	open als input textfile
	if (F == NULL) 
	{
		m_size = 0;
		throw("Xml invoerbestand is niet te openen");
	}
	   
	//	lees het gehele bestand in het geheugen -> m_buf
	numread = fread( m_buf, sizeof( char ), m_size, F );
	m_buf[numread] = '\0';
	fclose(F);
}

bool CXMLParser::GetNextElement()
{
	bool result;
	int p = 0;
	m_element[0] = NULL;

	//	foutje: initialiseren van m_data
	for (int i=0; i<sizeof(m_data); i++)
		m_data[i] = '\0';

	while (m_pos < m_size && *m_buf != '<')		//	zoek tot '<'
	{
		m_buf++;
		m_pos++;
	}

	if (m_pos >= m_size)
		return false;							//	geen elementen meer

	while (m_pos < m_size && *m_buf != '>')		//	kopieeer tot '>'
	{
		m_element[p++] = *m_buf;
		m_buf++;
		m_pos++;
	}
	if (m_pos < m_size)							//	kopieeer het '>'
	{
		m_element[p++] = *m_buf;
		m_buf++;
		m_pos++;
	}
	m_element[p]= '\0';							//	sluit cstring af

	switch (m_element[1])						//	bepaal het type en de level
	{
		case '/':	m_type = _xml_closeTag;
					m_level--;
					break;
		case '?':	m_type = _xml_anotherTag;
					break;
		case '!':	m_type = _xml_commentTag;
					break;
		default:	m_type = _xml_openTag;
					m_level++;
	}

	result = m_pos < m_size;					//	al aan het eind?

	//	lees nu de bijbehorende data
	p=0;
	m_data[p] = '\0';

	while (m_pos < m_size && *m_buf <= ' ')		//	skip alle 'rare' karakters
	{
		m_buf++;
		m_pos++;
	}
	while (m_pos < m_size && *m_buf != '<')		//	kopieeer alles tot '<'
	{
		m_data[p] = *m_buf;
		m_buf++;
		m_pos++;
		p++;
	}
	while (m_data[p] == ' ')					//	trim trailing spaces
		p--;

	m_data[p] = '\0';


	return result;
}

char *CXMLParser::GetElementName()
{
	return m_element;
}

int CXMLParser::GetElementLevel()
{
	return m_level;
}

enum ElementType CXMLParser::GetElementType()
{
	return m_type;
}

bool CXMLParser::HasData()
{
	return strlen(m_data) > 0;
}

char *CXMLParser::GetData()
{
	return m_data;
}
