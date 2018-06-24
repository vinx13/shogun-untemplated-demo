#ifndef _MATRIX_EXPRESSION_H
#define _MATRIX_EXPRESSION_H

#include "exp.h"
#include "Matrix.h"
#include <shogun/lib/DataType.h>
#include <shogun/lib/SGVector.h>

namespace shogun
{
	template <typename E>
	class MatrixExp : public Exp<MatrixExp<E>>
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

		EPrimitiveType ptype() const
		{
			return self().ptype();
		}
	};

	class MatrixRefExp : public MatrixExp<MatrixRefExp>
	{
	public:
		MatrixRefExp(const Matrix& matrix) : matrix(matrix)
		{
		}

		EPrimitiveType ptype() const
		{
			return matrix.ptype();
		}

		Matrix eval() const
		{
			return matrix;
		}

		template <typename T>
		SGMatrix<T> eval() const
		{
			return matrix;
		}

		Matrix matrix;
	};

	template <typename OP, typename E1, typename E2>
	class BinaryMatrixExp : public MatrixExp<BinaryMatrixExp<OP, E1, E2>>
	{
	public:
		BinaryMatrixExp(OP op, const E1& lhs, const E2& rhs)
		    : op(op), lhs(lhs), rhs(rhs)
		{
		}

		EPrimitiveType ptype() const
		{
			ASSERT(lhs.ptype() == rhs.ptype());
			return lhs.ptype();
		}

		Matrix eval() const
		{
			SG_TYPE_SWITCH(ptype(), PType, { return Matrix(eval<PType>()); });
		}

		template <typename T>
		SGMatrix<T> eval() const
		{
			auto lhs_result = lhs.self().template eval<T>();
			auto rhs_result = rhs.self().template eval<T>();

			return op.template apply(lhs_result, rhs_result);
		}

	private:
		E1 lhs;
		E2 rhs;
		OP op;
	};
}

#endif
