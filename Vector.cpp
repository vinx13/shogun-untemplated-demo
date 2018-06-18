#include "Vector.h"
#include "vector_expression.h"

namespace shogun
{
	Vector::operator VectorRefExp()
	{
		return VectorRefExp(*this);
	}
}
