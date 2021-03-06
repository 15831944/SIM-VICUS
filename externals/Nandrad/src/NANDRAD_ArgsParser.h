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

#ifndef NANDRAD_ArgsParserH
#define NANDRAD_ArgsParserH

#include <IBK_SolverArgsParser.h>

namespace NANDRAD {

/*! Re-implementation of IBK::SolverArgsParser to add NANDRAD-specific options. */
class ArgsParser : public IBK::SolverArgsParser {
public:
	ArgsParser();

	virtual void printHelp(std::ostream & out) const override;
};

} // namespace NANDRAD

#endif // NANDRAD_ArgsParserH
