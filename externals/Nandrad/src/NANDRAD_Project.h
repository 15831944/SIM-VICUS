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

#ifndef NANDRAD_ProjectH
#define NANDRAD_ProjectH

class TiXmlElement;

#include <string>
#include <vector>
#include <map>

#include "NANDRAD_Zone.h"
#include "NANDRAD_ConstructionInstance.h"
#include "NANDRAD_ProjectInfo.h"
#include "NANDRAD_SimulationParameter.h"
#include "NANDRAD_SolverParameter.h"
#include "NANDRAD_Schedules.h"
#include "NANDRAD_Outputs.h"
#include "NANDRAD_Location.h"
#include "NANDRAD_SpaceType.h"
#include "NANDRAD_Zone.h"

namespace NANDRAD {

/*! Contains all input data that describes a room with walls, floor, ceiling, usage, HVAC etc.
	The room description references constructions, window and shading types from the database.
*/
class Project {
public:
	// *** PUBLIC MEMBER FUNCTIONS ***

	/*! Reads the project data from an XML file.
		\param filename  The full path to the project file.
	*/
	void readXML(const IBK::Path & filename);

	/*! Writes the project file to an XML file.
		\param filename  The full path to the project file.
	*/
	void writeXML(const IBK::Path & filename) const;

	/*! Sets all connections and reference names. */
	void resolveReferenceNames();

	/*! All constructions with same boundary conditions and construction type are merged into one
		since the results will be the same for all constructions.
		For each merged construction, a new construction is added to the end of the construction list.
		All merged constructions are removed (this ensured, that any remaining reference to a merged
		construction will trigger an error).
		The cross sections of all constructions are summed together to make up the final cross section of
		the merged construction.

		A data table is created with information on merged constructions:
		- new merged construction ID
		- vector of merged construction IDs and their areas

		\warning This algorithmus may not be suitable for calculations that involve view factors and
		long wave radiation exchange. Hence, do not call this function for such models!

		Embedded objects that reference one of the merge constructions will be modified to reference
		the merge construction instead. A mapping table is created that lists those changes:
		- embedded object ID
		- old construction instance ID
		- new merged construction instance ID
	*/
	void mergeSameConstructions();

	/*! Returns the point ids for active areas which are connected to the given wall point id. */
	std::vector< unsigned int > activeAreaPointIds( const unsigned int pointId ) const;

	/*! Comments about the project. */
	ProjectInfo										m_projectInfo;

	/*! Contains mapping of directory placeholders and absolute directory paths. */
	std::map<std::string, IBK::Path>				m_placeholders;

	/*! All active and constant thermal zones.*/
	std::map< unsigned int, Zone>					m_zones;

	/*! All construction instances refernce a construction and a thermal zone
		(key is construction instance ID, value is the construction instance definition). */
	std::map< unsigned int, ConstructionInstance>	m_constructionInstances;

	/*! Simulation settings: all global parameters.*/
	SimulationParameter								m_simulationParameter;

	/*! Solver settings: error tolerances and convergence coefficients*/
	SolverParameter									m_solverParameter;

	/*! Location of the building and climate data. */
	Location										m_location;

	/*! Space type properties.*/
	std::map< unsigned int, SpaceType>				m_spaceTypes;

	/*! References to all schedules.*/
	Schedules										m_schedules;

	/*! References to Output specifications.*/
	Outputs											m_outputs;

	/*! References to object lists.*/
	std::vector<ObjectList>							m_objectLists;

private:

	void readDirectoryPlaceholdersXML(const TiXmlElement * element);
	void writeDirectoryPlaceholdersXML(TiXmlElement * parent) const;

	void readDataBaseXML(const TiXmlElement * element);
	void writeDataBaseXML(TiXmlElement * parent) const;

	void writeZonesXML(TiXmlElement * parent) const;
	void writeConstructionInstancesXML(TiXmlElement * parent) const;

	void readGeometriesXML( const TiXmlElement * parent );
	void writeGeometriesXML(TiXmlElement * parent) const;


	/*!	Checks whether all construction types and materials have a unique ID number.
	*/
	void checkDatabaseIDs();
};


} // namespace NANDRAD

#endif // ProjectH
