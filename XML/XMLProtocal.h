/*****************************************************************************
 * \File: XMLProtocal.h
 * \Date: 2018/02/13 13:15
 * \Copyright: (C) 1990-2015 sky-light.com.hk
 * \Author: lijiang
 *
 * \Brief: 
 *
 * \Version: 1.0.0.0
 *
 * \Note:
 *****************************************************************************/
#ifndef SKYNAT_XMLProtocal_H
#define SKYNAT_XMLProtocal_H

#include <stdint.h>

#include "tinyxml2.h"
using namespace tinyxml2;

class XMLProtocal : public tinyxml2::XMLDocument
{
public:
	 XMLProtocal();
	~XMLProtocal();
	virtual bool Open(const char * where, int where_size);
	virtual bool Close();
	virtual bool isGood();
public:
	static bool CheckChild(XMLNode * child);
	static bool GetNextElement(XMLNode ** child, char * key, char * value, int size);
	static bool GetNextElement(XMLNode ** child, char * key, int32_t * value);
	static bool HasChildElement(XMLElement * child, const char * name);
public:
	bool         m_good;
};

#endif //!SKYNAT_XMLProtocal_H