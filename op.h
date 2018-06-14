#include "Vector.h"
#include "exp.h"
#include <shogun/mathematics/linalg/LinalgNamespace.h>

namespace shogun
{

	struct VectorAdd
	{
		template <typename T>
		SGVector<T> apply(const SGVector<T>& a, const SGVector<T>& b) const
		{
			return linalg::add(a, b);
		}
	};

	template <typename E1, typename E2>
	auto add(const VectorExp<E1>& e1, const VectorExp<E2>& e2)
	{
		return BinaryVectorExp<VectorAdd, E1, E2>(
		    VectorAdd(), e1.self(), e2.self());
	}

	struct Dot
	{
		template <typename T>
		T apply(const SGVector<T>& a, const SGVector<T>& b) const
		{
			return linalg::dot(a, b);
		}
	};

	template <typename E1, typename E2>
	auto dot(const VectorExp<E1>& e1, const VectorExp<E2>& e2)
	{
		return BinaryScalarExp<Dot, E1, E2>(Dot(), e1.self(), e2.self());
	}
}
