#pragma once

/*
	CXMLParser.h
	Een zeer eenvoudige XML parser t.b.v. HI blok 1.4 
	Jan Verhoeven
	Hogeschool Windesheim
	Maart 2003
*/

#ifndef _XMLPARSER_H_
#define _XMLPARSER_H_

enum ElementType {_xml_openTag, _xml_closeTag, _xml_commentTag, _xml_anotherTag};

class CXMLParser
{
private:
	char *m_buf;				//	bevat de gehele xmlfile
	int m_size;					//	grootte van m_buf
	char m_element[80];			//	het huidige element (naam)
	int m_level;				//	het huidige level
	enum ElementType m_type;	//	het huidige type v/h element
	int m_pos;					//	huidige positie in m_buf
	char m_data[800];			//	data v/h element
public:
	CXMLParser();
	~CXMLParser();
	void SetXmlFile(char *FileName) throw();
	bool GetNextElement();
	char *GetElementName();	
	int GetElementLevel();
	enum ElementType GetElementType();
	bool HasData();
	char *GetData();
};

#endif

