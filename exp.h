#ifndef EXP_H
#define EXP_H

#include "Vector.h"

namespace shogun
{
	template <class E>
	class Exp
	{
	public:
		E& self()
		{
			return *static_cast<E*>(this);
		}

		const E& self() const
		{
			return *static_cast<const E*>(this);
		}
	};
}

#endif
