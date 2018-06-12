#include "Vector.h"
#include "exp.h"

namespace shogun
{
	Vector::operator VectorRefExp()
	{
		return VectorRefExp(*this);
	}
}
