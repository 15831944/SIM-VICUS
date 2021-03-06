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

#ifndef NANDRAD_DailyCycleH
#define NANDRAD_DailyCycleH

#include <string>
#include <vector>

#include <IBK_Parameter.h>
#include "NANDRAD_LinearSplineParameter.h"
#include "NANDRAD_Interval.h"

class TiXmlElement;

namespace NANDRAD {

/*!	\brief Declaration for class DailyCycle

	A daily cycle provides the values of a scheduled quantity for the period of one day.
	It uses a vector of intervals to specify time and values of the scheduled quantity.
	Usually more than one quantities are defined within one interval.

	The interval definition defines a time interval per default. The last interval of one
	daily cycle does not need a time definition - it lasts until the end of day. The m_para
	section of the interval provides information about the interval time, the m_genericParaConst
	section provides the scheduled parameters with a constant value for each interval.

	Alternatively scheduled quantities may directly be defined as a linear spline parameter. Use
	the time in hours (for one complete day) as x-values and the hourly values of the quantity
	as y-values for the spline.
*/
class DailyCycle {
public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	/*! Reads the data from the xml element.
		Throws an IBK::Exception if a syntax error occurs.
	*/
	void readXML(const TiXmlElement * element);

	/*! Appends the element to the parent xml element.
		Throws an IBK::Exception in case of invalid data.
	*/
	void writeXML(TiXmlElement * parent) const;

	/*! Converts for interals or hourly values to a linear splin for a given quantity:
		Returns an empty linear spline if quantity is undefined.*/
	void createLinearSpline(const std::string &quantityName, IBK::LinearSpline &spline) const;

	/*! Checks input intervals and throws an IBK::Exception if
		some interval definition does not match definition rules. */
	void checkIntervalDefinition() const;

	/*! return the interval end in seconds for given interval index, if needed, parameters are conmputed on the fly. */
	double	intervalEndInSeconds( unsigned int intervalIndex ) const;


	/*! Compares this instance with another by value and returns true if they differ. */
	bool operator!=(const DailyCycle & other) const;

	/*! Compares this instance with another by value and returns true if they are the same. */
	bool operator==(const DailyCycle & other) const { return ! operator!=(other); }

	// *** PUBLIC MEMBER VARIABLES ***

	/*! Parameter definition inside each schedule interval.*/
	std::vector<Interval>				m_intervals;

	/*! Alternatively read hourly values into a linear spline. */
	std::vector<LinearSplineParameter>	m_hourlyValues;
};

} // namespace NANDRAD

#endif // DailyCycleH
