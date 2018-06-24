#ifndef _SG_TYPE_TRAITS_H
#define _SG_TYPE_TRAITS_H

#include <shogun/lib/DataType.h>

namespace shogun
{

	template <typename>
	struct SGTypeTraits
	{
	};

	template <>
	struct SGTypeTraits<bool>
	{
		static const auto PRIMITIVE_TYPE = PT_BOOL;
	};

	template <>
	struct SGTypeTraits<char>
	{
		static const auto PRIMITIVE_TYPE = PT_CHAR;
	};

	template <>
	struct SGTypeTraits<int8_t>
	{
		static const auto PRIMITIVE_TYPE = PT_INT8;
	};

	template <>
	struct SGTypeTraits<uint8_t>
	{
		static const auto PRIMITIVE_TYPE = PT_UINT8;
	};

	template <>
	struct SGTypeTraits<int16_t>
	{
		static const auto PRIMITIVE_TYPE = PT_INT16;
	};

	template <>
	struct SGTypeTraits<uint16_t>
	{
		static const auto PRIMITIVE_TYPE = PT_UINT16;
	};

	template <>
	struct SGTypeTraits<int32_t>
	{
		static const auto PRIMITIVE_TYPE = PT_INT32;
	};
	template <>
	struct SGTypeTraits<uint32_t>
	{
		static const auto PRIMITIVE_TYPE = PT_UINT32;
	};
	template <>
	struct SGTypeTraits<int64_t>
	{
		static const auto PRIMITIVE_TYPE = PT_INT64;
	};
	template <>
	struct SGTypeTraits<uint64_t>
	{
		static const auto PRIMITIVE_TYPE = PT_UINT64;
	};

	template <>
	struct SGTypeTraits<float32_t>
	{
		static const auto PRIMITIVE_TYPE = PT_FLOAT32;
	};

	template <>
	struct SGTypeTraits<float64_t>
	{
		static const auto PRIMITIVE_TYPE = PT_FLOAT64;
	};

	template <>
	struct SGTypeTraits<floatmax_t>
	{
		static const auto PRIMITIVE_TYPE = PT_FLOATMAX;
	};

	template <>
	struct SGTypeTraits<complex128_t>
	{
		static const auto PRIMITIVE_TYPE = PT_COMPLEX128;
	};

	class SGObject;
	template <>
	struct SGTypeTraits<SGObject>
	{
		static const auto PRIMITIVE_TYPE = PT_SGOBJECT;
	};
}

#endif
