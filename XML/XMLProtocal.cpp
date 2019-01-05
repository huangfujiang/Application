
#include "XMLProtocal.h"


XMLProtocal::XMLProtocal()
	:m_good(false)
{

}

XMLProtocal::~XMLProtocal()
{
	Close();
}


bool XMLProtocal::HasChildElement(XMLElement * child, const char * name)
{
	if (strcmp(child->Value(), name) != 0 || child->FirstChild() == NULL)
		return false;

	return true;
}

bool XMLProtocal::CheckChild(XMLNode * child)
{
	if (NULL == child)
	{
		return false;
	}
	if (NULL == child->ToElement())
	{
		return false;
	}
	if (NULL == child->ToElement()->GetText())
	{
		return false;
	}
	return true;
}


bool XMLProtocal::GetNextElement(XMLNode ** child, char * key, char * value, int size)
{
	if (child == NULL || *child == NULL || key == NULL || value == NULL)
	{
		return false;
	}

	XMLNode *   pChild = *child;

	pChild = pChild->NextSiblingElement(key);
	if (!CheckChild(pChild))
	{
		return false;
	}
	if (strlen(pChild->ToElement()->GetText()) >= size)
	{
		return false;
	}
	strcpy(value, pChild->ToElement()->GetText());

	return true;
}


bool XMLProtocal::GetNextElement(XMLNode ** child, char * key, int32_t * value)
{
	if (child == NULL || *child == NULL || key == NULL || value == NULL)
	{
		return false;
	}

	XMLNode *   pChild = *child;

	pChild = pChild->NextSiblingElement(key);
	if (!CheckChild(pChild))
	{
		return false;
	}

	*value = atoi(pChild->ToElement()->GetText());

	return true;
}


bool XMLProtocal::isGood()
{
	return m_good;
}

bool XMLProtocal::Open(const char * where, int where_size)
{
	if (where == NULL || where_size <= 0)
		return false;

	if (XML_NO_ERROR != this->Parse(where, where_size))
	{
		m_good = false;
	}
	else
	{
		m_good = true;
	}

	return m_good;
}

bool XMLProtocal::Close()
{
	m_good = false;
	this->Clear();

	return true;
}