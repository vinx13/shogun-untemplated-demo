#ifndef _VECTOR_EXPRESSION_H
#define _VECTOR_EXPRESSION_H

#include "exp.h"
#include <shogun/lib/DataType.h>
#include <shogun/lib/SGVector.h>

namespace shogun
{
	template <class E>
	class VectorExp
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

	template <typename E>
	Vector& Vector::operator=(const VectorExp<E>& exp)
	{
		*this = exp.self().eval();
		return *this;
	}

	template <typename E>
	Vector::Vector(const VectorExp<E>& exp) : m_data(nullptr)
	{
		*this = exp.self().eval();
	}

	class VectorRefExp : public VectorExp<VectorRefExp>
	{
	public:
		VectorRefExp(const Vector& vector) : vector(vector)
		{
		}

		EPrimitiveType ptype() const
		{
			return vector.ptype();
		}

		Vector eval() const
		{
			return vector;
		}

		template <typename T>
		SGVector<T> eval() const
		{
			return vector;
		}

		Vector vector;
	};

	template <class OP, class E1, class E2>
	class BinaryVectorExp : public VectorExp<BinaryVectorExp<OP, E1, E2>>
	{
	public:
		BinaryVectorExp(OP op, const E1& lhs, const E2& rhs)
		    : op(op), lhs(lhs), rhs(rhs)
		{
		}

		EPrimitiveType ptype() const
		{
			ASSERT(lhs.ptype() == rhs.ptype());
			return lhs.ptype();
		}

		Vector eval() const
		{
			SG_TYPE_SWITCH(ptype(), PType, { return Vector(eval<PType>()); });
		}

		template <typename T>
		SGVector<T> eval() const
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
