/*	The NANDRAD data model library.
Copyright (c) 2012, Institut fuer Bauklimatik, TU Dresden, Germany

Written by
A. Nicolai		<andreas.nicolai -[at]- tu-dresden.de>
A. Paepcke		<anne.paepcke -[at]- tu-dresden.de>
St. Vogelsang	<stefan.vogelsang -[at]- tu-dresden.de>
All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
*/

#include "NANDRAD_Interface.h"
#include "NANDRAD_KeywordList.h"

#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <IBK_messages.h>

#include "NANDRAD_Constants.h"
#include "NANDRAD_Zone.h"

#include <tinyxml.h>

namespace NANDRAD {

Interface::Interface() :
	m_id(INVALID_ID),
	m_zoneRef(NULL)
{
}

void Interface::readXML(const TiXmlElement * element) {
#if 0
	const char * const FUNC_ID = "[Interface::readXML]";
	// read attributes
	try {
		const TiXmlAttribute * attrib = TiXmlAttribute::attributeByName(element, "displayName");
		if (attrib)
			m_displayName = attrib->Value();

		attrib = TiXmlAttribute::attributeByName(element, "location");
		if (!attrib)
			throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
				IBK::FormatString("Missing 'location' attribute.")
				), FUNC_ID);
		// check keyword
		if( ! KeywordList::KeywordExists("Interface::location_t",attrib->Value()) ) {
			throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
				IBK::FormatString("Unknown location attribute '%1'.").arg(attrib->Value())
				), FUNC_ID);
		}

		m_location = (location_t) KeywordList::Enumeration("Interface::location_t",attrib->Value());

		attrib = TiXmlAttribute::attributeByName(element, "id");
		if (!attrib)
			throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
				IBK::FormatString("Missing 'id' attribute.")
				), FUNC_ID);

		try {
			m_id = IBK::string2val<unsigned int>(attrib->Value());
			NANDRAD::IDGeneratorSingleton::instance().setNextFreeId( NANDRAD::IDGeneratorSingleton::IDS_Interface, m_id+1 );
		}
		// Error obtaining id number
		catch (IBK::Exception & ex) {
			throw IBK::Exception( ex, IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
				IBK::FormatString("Error reading 'id' attribute.")
				), FUNC_ID);
		}

		// read sub-elements
		for (const TiXmlElement * c = element->FirstChildElement(); c; c = c->NextSiblingElement()) {
			// determine data based on element name
			std::string cname = c->Value();
			if (cname == "ZoneID") {
				m_zoneId = IBK::string2val<unsigned int>(c->GetText());
			}
			// check for parameter names
			else if(KeywordList::KeywordExists("Interface::condition_t",cname)) {
				condition_t condition = (condition_t) KeywordList::Enumeration("Interface::condition_t",cname);
				// read parameter model
				switch(condition)
				{
					case IP_HEATCONDUCTION:
						m_heatConduction.readXML(c);
					break;
					case IP_SOLARABSORPTION:
						m_solarAbsorption.readXML(c);
					break;
					case IP_LONGWAVEEMISSION:
						m_longWaveEmission.readXML(c);
					break;
					case IP_VAPORDIFFUSION:
						m_vaporDiffusion.readXML(c);
						break;
					default:
					break;
				}
			}
			else {
				throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(c->Row()).arg(
									IBK::FormatString("Unknown XML tag with name '%1'.").arg(cname)
										), FUNC_ID);
			}
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception(ex, IBK::FormatString("Error reading 'Interface' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception(IBK::FormatString("%1\nError reading 'Interface' element.").arg(ex2.what()), FUNC_ID);
	}
#endif
}

void Interface::writeXML(TiXmlElement * parent, bool detailedOutput) const {
#if 0

	TiXmlElement * e = new TiXmlElement("Interface");
	parent->LinkEndChild(e);

	if(!m_displayName.empty())
		e->SetAttribute("displayName", m_displayName);

	e->SetAttribute("id", IBK::val2string<unsigned int>(m_id));
	e->SetAttribute("location", KeywordList::Keyword("Interface::location_t",m_location));

	// write all references
	TiXmlElement::appendSingleAttributeElement(e, "ZoneID", NULL, std::string(),IBK::val2string<unsigned int>(m_zoneId));

	// write all model parameters
	if( m_heatConduction.m_modelType != InterfaceHeatConduction::NUM_MT)
		m_heatConduction.writeXML(e, detailedOutput);
	if( m_solarAbsorption.m_modelType != InterfaceSolarAbsorption::NUM_MT)
		m_solarAbsorption.writeXML(e, detailedOutput);
	if( m_longWaveEmission.m_modelType != InterfaceLongWaveEmission::NUM_MT)
		m_longWaveEmission.writeXML(e, detailedOutput);
	if (m_vaporDiffusion.m_modelType != InterfaceVaporDiffusion::NUM_MT)
		m_vaporDiffusion.writeXML(e, detailedOutput);
#endif
}

void Interface::writeCommentsXML(TiXmlElement * parent) const {
#if 0
	// first add all comments
	for (std::set<std::string>::const_iterator it = m_comments.begin(); it != m_comments.end(); ++it)
		TiXmlComment::addComment(parent,*it);
	// add comments specifying the referenced zone
	if(!m_zoneDisplayName.empty()) {
		std::string referenceComment = std::string("Interface connecting wall surface '") +
								KeywordList::Keyword("Interface::location_t",m_location) +
								std::string("' with Zone '") +
								m_zoneDisplayName + std::string("'.");

		TiXmlComment::addComment(parent,referenceComment);
	}
#endif
}

} // namespace NANDRAD
