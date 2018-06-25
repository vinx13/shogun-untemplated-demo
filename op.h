#include "Vector.h"
#include "exp.h"
#include "matrix_expression.h"
#include "scalar_expression.h"
#include "vector_expression.h"

#include <shogun/mathematics/linalg/LinalgNamespace.h>

namespace shogun
{
	template <typename T>
	auto forward_exp(T&& e)
	{
		return std::forward<T>(e);
	}

	auto forward_exp(Vector& e)
	{
		return VectorRefExp(e);
	}

	auto forward_exp(const Vector& e)
	{
		return VectorRefExp(e);
	}

	// Vector Add: an example showing passing Vector without explicitly casting
	// to VectorRefExp
	struct VectorAdd
	{
	public:
		VectorAdd(double alpha, double beta): alpha(alpha), beta(beta) 
		{
		}

		template <typename T>
		SGVector<T> apply(const SGVector<T>& a, const SGVector<T>& b) const
		{
			return linalg::add(
			    a, b, static_cast<T>(alpha),
			    static_cast<T>(beta)); // should we have T alpha, beta so that
			                           // we can avoid casting here?
		}
		template <typename T>
		void apply(
		    const SGVector<T>& a, const SGVector<T>& b, SGVector<T>& dst) const
		{
			return linalg::add(
			    a, b, dst, static_cast<T>(alpha), static_cast<T>(beta));
		}

	private:
		double alpha;
		double beta;
	};

	template <typename E1, typename E2>
	auto add_impl(
	    const VectorExp<E1>& e1, const VectorExp<E2>& e2, double alpha = 1.0,
	    double beta = 1.0)
	{
		return BinaryVectorExp<VectorAdd, E1, E2>(
		    VectorAdd(alpha, beta), e1.self(), e2.self());
	}

	template <typename... Args>
	auto add(Args&&... args) -> decltype(add_impl(forward_exp(args)...))
	{
		return add_impl(forward_exp(args)...);
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

	// a example of multiple output that looks bad
	template <typename E1>
	void eigen_solver(
	    const MatrixExp<E1>& matrix, Vector& eigenvalues, Matrix& eigenmatrix)
	{
		// SG_TYPE_SWITCH(matrix.ptype(), PType, {
		// can't use SG_TYPE_SWITCH, because it switches over all types while
		// eigen_solver<bool> is undefined
		switch (matrix.ptype())
		{
		case PT_FLOAT64:
			typedef float64_t PType;
			SGVector<PType> eigenvalues_ = eigenvalues;
			SGMatrix<PType> eigenmatrix_ = eigenmatrix;
			linalg::eigen_solver(
			    matrix.self().template eval<PType>(), eigenvalues_,
			    eigenmatrix_);
			eigenvalues = eigenvalues_;
			eigenmatrix = eigenmatrix_;
			// TODO: other cases
		}
	}
}
