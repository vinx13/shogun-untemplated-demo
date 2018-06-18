#include "Vector.h"
#include "exp.h"
#include "matrix_expression.h"
#include "scalar_expression.h"
#include "vector_expression.h"

#include <shogun/mathematics/linalg/LinalgNamespace.h>

namespace shogun
{

	struct VectorAdd
	{
	public:
		VectorAdd(double alpha, double beta): alpha(alpha), beta(beta) 
		{
		}

		template <typename T>
		SGVector<T> apply(const SGVector<T>& a, const SGVector<T>& b) const
		{
			return linalg::add(a, b, static_cast<T>(alpha), static_cast<T>(beta));
		}
	private:
		double alpha;
		double beta;
	};

	template <typename E1, typename E2>
	auto add(const VectorExp<E1>& e1, const VectorExp<E2>& e2, double alpha=1.0, double beta=1.0)
	{
		return BinaryVectorExp<VectorAdd, E1, E2>(
		    VectorAdd(alpha, beta), e1.self(), e2.self());
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
