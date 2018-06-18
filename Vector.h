#ifndef VECTOR_H_
#define VECTOR_H_

#include "TypeTraits.h"
#include "helper.h"
#include <shogun/base/some.h>
#include <shogun/io/SGIO.h>
#include <shogun/lib/DataType.h>
#include <shogun/lib/SGVector.h>
#include <shogun/lib/common.h>

namespace shogun
{

	class VectorRefExp;

	template <typename E>
	class VectorExp;

	class Vector : public SGReferencedData
	{
	public:
		template <class T>
		using templated_type = SGVector<T>;

		explicit Vector(uint32_t len, EPrimitiveType ptype = PT_FLOAT64)
		    : SGReferencedData(true), m_ptype(ptype), m_vlen(len)
		{
			SG_TYPE_SWITCH(ptype, PType, { m_data = SG_CALLOC(PType, len); })
		}

		template <typename T>
		Vector(SGVector<T> vector)
		    : SGReferencedData(vector), m_vlen(vector.vlen)
		{
			m_data = static_cast<void*>(vector.vector);

			m_ptype = SGTypeTraits<T>::PRIMITIVE_TYPE;
		}

		Vector(const Vector& orig) : SGReferencedData(orig)
		{
			copy_data(orig);
		}

		/** Copy from vector expression */
		template <typename E>
		Vector(const VectorExp<E>& exp);

		/** Assign from vector expression */
		template <typename E>
		Vector& operator=(const VectorExp<E>& exp);

		Vector& operator=(const Vector& other)
		{
			SGReferencedData::operator=(other);
			return *this;
		}

		Vector(Vector&& orig) : SGReferencedData(orig)
		{
			copy_data(orig);
			orig.init_data();
		}

		Vector& operator=(Vector&& vector)
		{
			SGReferencedData::operator=(vector);
			return *this;
		}

		// TODO copy and assign from vector exp rvalue

		~Vector()
		{
			unref();
		}

		template <typename T>
		operator SGVector<T>() const
		{
			ASSERT(SGTypeTraits<T>::PRIMITIVE_TYPE == m_ptype);
			return SGVector<T>(static_cast<T*>(m_data), m_vlen, false);
		}

		EPrimitiveType ptype() const
		{
			return m_ptype;
		}

		virtual void init_data()
		{
			m_data = nullptr;
			m_vlen = 0;
			m_ptype = PT_FLOAT64;
		}

		virtual void copy_data(const SGReferencedData& orig)
		{
			const auto& vector = static_cast<const Vector&>(orig);
			m_data = vector.m_data;
			m_vlen = vector.m_vlen;
			m_ptype = vector.m_ptype;
		}

		virtual void free_data()
		{
			if (m_data)
				SG_FREE(m_data);
			m_data = 0;
			m_vlen = 0;
			m_ptype = PT_FLOAT64;
		}

		void display_vector(
		    const char* name = "vector", const char* prefix = "") const
		{
			SG_TYPE_SWITCH(m_ptype, PType, {
				SGVector<PType>(*this).display_vector(name, prefix);
			});
		}

		operator VectorRefExp();

	private:
		uint32_t m_vlen;
		EPrimitiveType m_ptype;
		void* m_data;
	};
}
#endif // VECTOR_H_
