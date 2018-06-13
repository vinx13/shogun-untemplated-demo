#ifndef EXP_H
#define EXP_H

#include "Vector.h"
#include <shogun/lib/DataType.h>
#include <shogun/lib/SGVector.h>

namespace shogun
{

	template <class Derived>
	class Exp
	{
	public:
		Derived& self()
		{
			return *static_cast<Derived*>(this);
		}

		const Derived& self() const
		{
			return *static_cast<const Derived*>(this);
		}

	private:
	};

	template <class Derived>
	class VectorExp
	{
	public:
		Derived& self()
		{
			return *static_cast<Derived*>(this);
		}

		const Derived& self() const
		{
			return *static_cast<const Derived*>(this);
		}

		EPrimitiveType ptype() const
		{
			return self().ptype();
		}

		Vector eval() const
		{
			return self().eval();
		}

		template <typename T>
		SGVector<T> eval() const
		{
			return self().template eval<T>();
		}

		// operator Vector()
		// {
		// 	return eval();
		// }
	};

	template <typename E>
	Vector& Vector::operator=(const VectorExp<E>& exp)
	{
		*this = exp.eval();
		return *this;
	}

	template <typename E>
	Vector::Vector(const VectorExp<E>& exp)
	{
		*this = exp.eval();
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
		BinaryVectorExp(const E1& lhs, const E2& rhs) : lhs(lhs), rhs(rhs)
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

			return OP::apply(lhs_result, rhs_result);
		}

	private:
		E1 lhs;
		E2 rhs;
	};
}
#endif
