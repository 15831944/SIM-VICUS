/*	The Zeppelin graph algorithm library.
Copyright(c) 2010-2017, Institut fuer Bauklimatik, TU Dresden, Germany

Written by
A.Paepcke		<anne.paepcke - [at] - tu - dresden.de>
All rights reserved.

This library is free software; you can redistribute it and / or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU
Lesser General Public License for more details.
*/

#ifndef ZEPPELIN_DependencyObjectH
#define ZEPPELIN_DependencyObjectH

#include <algorithm>
#include <vector>
#include <set>

namespace ZEPPELIN {

/*! An abstract base class representing an dependency object within a dependency graph.
	The class DependencyGraph can be used to resolve the graph and evaluate
	order and detect cyclic clusters.
	This implementation provides the convenience function dependsOn()
	and manages dependencies internally.
	\sa DependencyGraph
*/
class DependencyObject {
public:
	/*! Defines a ordered vector of dependency objects (a sequence). */
	typedef std::vector<DependencyObject*>		DependencySequence;

	/*! Virtual destructor. */
	virtual ~DependencyObject() {}

	/*! Set backward connections. */
	void updateParents() {
		for (unsigned int i = 0; i < m_childs.size(); ++i) {
			m_childs[i]->setParent(*this);
		}
	}

	/*! Registers an object dependency. */
	void dependsOn(DependencyObject & o) {
		if (std::find(m_childs.begin(), m_childs.end(), &o) ==
			m_childs.end()) {
			m_childs.push_back(&o);
		}
	}

	/*! Registers an object dependency. */
	void dependsOn(const DependencyObject & o) {
		if (std::find(m_childs.begin(), m_childs.end(), &o) ==
			m_childs.end()) {
			m_childs.push_back(const_cast<DependencyObject*>(&o));
		}
	}

	/*! Clears list of dependend objects and parents. */
	void clear() {
		m_childs.clear();
		m_parents.clear();
	}

	/*! Returns set with models that we depend on.
		Re-implement this function if you have different implementation.
	*/
	virtual const DependencySequence & dependencies() const {
		return m_childs;
	}

	/*! Returns set with models that depend on us.
		Re-implement this function if you have different implementation.
	*/
	virtual const DependencySequence &  parents() const {
		return m_parents;
	}

	void setParentInChilds() {
		for (DependencyObject * o : m_childs)
			o->setParent(*this);
	}

protected:

	/*! Registers an object parent. */
	void setParent(DependencyObject & o) {
		if (std::find(m_parents.begin(), m_parents.end(), &o) ==
			m_parents.end()) {
			m_parents.push_back(&o);
		}
	}

	/*! Set containing models that we depend on. */
	DependencySequence m_childs;
	/*! Set containing models that depend on us. */
	DependencySequence m_parents;

}; // DependencyObject


inline bool operator==(const DependencyObject &obj1, const DependencyObject &obj2) {
	if (obj1.dependencies().size() != obj2.dependencies().size())
		return false;

	DependencyObject::DependencySequence::const_iterator deps1 = obj1.dependencies().begin();
	DependencyObject::DependencySequence::const_iterator deps2 = obj2.dependencies().begin();
	for (; deps1 != obj1.dependencies().end(); ++deps1, ++deps2) {
		if(*deps1 != *deps2)
			return false;
	}

	if (obj1.parents().size() != obj2.parents().size())
		return false;

	DependencyObject::DependencySequence::const_iterator pars1 = obj1.parents().begin();
	DependencyObject::DependencySequence::const_iterator pars2 = obj2.parents().begin();
	for (; pars1 != obj1.parents().end(); ++pars1, ++pars2) {
		if(*pars1 != *pars2)
			return false;
	}
	return true;
}

} // namespace ZEPPELIN

#endif // ZEPPELIN_DependencyObjectH
