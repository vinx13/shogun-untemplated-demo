#ifndef MATRIX_H_
#define MATRIX_H_

#include "TypeTraits.h"
#include "helper.h"
#include <shogun/base/some.h>
#include <shogun/io/SGIO.h>
#include <shogun/lib/DataType.h>
#include <shogun/lib/SGMatrix.h>
#include <shogun/lib/common.h>

namespace shogun
{
	class Matrix: public SGReferencedData
	{
	public:
		explicit Vector(uint32_t num_rows, uint32_t num_cols, EPrimitiveType ptype = PT_FLOAT64)
			: SGReferencedData(true), m_ptype(ptype), m_num_rows(num_rows), m_num_cols(num_cols)
		{
			SG_TYPE_SWITCH(ptype, PType, { m_data = SG_CALLOC(PType, num_rows*num_cols); })
		}
		
		template <typename T>
		Matrix(SGMatrix<T> matrix)
		: SGReferencedData(matrix), m_num_rows(matrix.num_rows), m_num_cols(matrix.num_cols)
		{
			m_data = static_cast<void*>(matrix.matrix);
			m_ptype = SGTypeTraits<T>::PRIMITIVE_TYPE;
		}

		Matrix(const Matrix& orig) : SGReferencedData(orig)
		{
			copy_data(orig);
		}

		Matrix(Matrix&& orig) : SGReferencedData(orig)
		{
			copy_data(orig);
			orig.init_data();
		}

		Matrix& operator=(const Matrix& other)
		{
			SGReferencedData::operator=(other);
			return *this;
		}

		Matrix& operator=(Matrix&& other)
		{
			SGReferencedData::operator=(other);
			return *this;
		}
		
		template <typename T>
		operator SGMatrix<T>() const
		{
			ASSERT(SGTypeTraits<T>::PRIMITIVE_TYPE == m_ptype);
			return SGMatrix<T>(static_cast<T*>(m_data), m_num_rows, m_num_cols, false);
		}

		EPrimitiveType ptype() const
		{
			return m_ptype;
		}

		virtual void init_data()
		{
			m_data = nullptr;
			m_num_rows = 0;
			m_num_cols = 0;
			m_ptype = PT_FLOAT64;
		}

		virtual void copy_data(const SGReferencedData& orig)
		{
			const auto& matrix = static_cast<const Matrix&>(orig);
			m_data = matrix.m_data;
			m_num_rows = matrix.m_num_rows;
			m_num_cols = matrix.m_num_cols;
			m_ptype = matrix.m_ptype;
		}

		virtual void free_data()
		{
			if (m_data)
				SG_FREE(m_data);
			m_data = nullptr;
			m_num_rows = 0;
			m_num_cols = 0;
			m_ptype = PT_FLOAT64;
		}

	private:
		uint32_t m_num_rows;
		uint32_t m_num_cols;
		void* m_data;
	};
}
