#ifndef EXP_H
#define EXP_H

#include "Vector.h"
#include <shogun/lib/DataType.h>
#include <shogun/lib/SGVector.h>

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

	private:
	};

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
	Vector::Vector(const VectorExp<E>& exp)
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
		    : lhs(lhs), rhs(rhs)
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

	template <typename E>
	class ScalarExp : public Exp<ScalarExp<E>>
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

		// conversion to any integral type: float v = scalarExp

		// FIXME: why this can't compile?
		// template <typename T,
		// typename=std::enable_if_t<std::is_integral<T>::value>>

		// this doesn't work either
		// template< typename T, std::enable_if_t<std::is_integral<T>::value>* =
		// nullptr>
		template <typename T>
		operator T() const
		{
			// ASSERT(self().ptype() == SGTypeTraits<T>::PRIMITIVE_TYPE);
			// return self().template eval<T>();

			// do we allow implicit conversion?
			T result;
			SG_TYPE_SWITCH(self().ptype(), PType, {
				result = static_cast<T>(self().template eval<PType>());
			});

			return result;
		}
	};

	template <typename OP, typename E1, typename E2>
	class BinaryScalarExp : public ScalarExp<BinaryScalarExp<OP, E1, E2>>
	{
	public:
		BinaryScalarExp(OP op, const E1& lhs, const E2& rhs)
		    : lhs(lhs), rhs(rhs)
		{
		}

		EPrimitiveType ptype() const
		{
			ASSERT(lhs.ptype() == rhs.ptype());
			return lhs.ptype();
		}

		template <typename T>
		T eval() const
		{
			return op.template apply<T>(lhs.eval<T>(), rhs.eval<T>());
		}

	private:
		E1 lhs;
		E2 rhs;
		OP op;
	};
}
#endif
