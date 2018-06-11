#ifndef HELPER_H
#define HELPER_H

#define SG_TYPE_SWITCH(type, PType, ...)                                       \
	switch (type)                                                              \
	{                                                                          \
	case PT_BOOL:                                                              \
	{                                                                          \
		typedef bool PType;                                                    \
		{                                                                      \
			__VA_ARGS__                                                        \
		}                                                                      \
		break;                                                                 \
	}                                                                          \
	case PT_CHAR:                                                              \
	{                                                                          \
		typedef char PType;                                                    \
		{                                                                      \
			__VA_ARGS__                                                        \
		}                                                                      \
		break;                                                                 \
	}                                                                          \
	case PT_INT8:                                                              \
	{                                                                          \
		typedef int8_t PType;                                                  \
		{                                                                      \
			__VA_ARGS__                                                        \
		}                                                                      \
		break;                                                                 \
	}                                                                          \
	case PT_UINT8:                                                             \
	{                                                                          \
		typedef uint8_t PType;                                                 \
		{                                                                      \
			__VA_ARGS__                                                        \
		}                                                                      \
		break;                                                                 \
	}                                                                          \
	case PT_INT16:                                                             \
	{                                                                          \
		typedef int16_t PType;                                                 \
		{                                                                      \
			__VA_ARGS__                                                        \
		}                                                                      \
		break;                                                                 \
	}                                                                          \
	case PT_UINT16:                                                            \
	{                                                                          \
		typedef uint16_t PType;                                                \
		{                                                                      \
			__VA_ARGS__                                                        \
		}                                                                      \
		break;                                                                 \
	}                                                                          \
	case PT_INT32:                                                             \
	{                                                                          \
		typedef int32_t PType;                                                 \
		{                                                                      \
			__VA_ARGS__                                                        \
		}                                                                      \
		break;                                                                 \
	}                                                                          \
	case PT_UINT32:                                                            \
	{                                                                          \
		typedef uint32_t PType;                                                \
		{                                                                      \
			__VA_ARGS__                                                        \
		}                                                                      \
		break;                                                                 \
	}                                                                          \
	case PT_INT64:                                                             \
	{                                                                          \
		typedef int64_t PType;                                                 \
		{                                                                      \
			__VA_ARGS__                                                        \
		}                                                                      \
		break;                                                                 \
	}                                                                          \
	case PT_UINT64:                                                            \
	{                                                                          \
		typedef uint64_t PType;                                                \
		{                                                                      \
			__VA_ARGS__                                                        \
		}                                                                      \
		break;                                                                 \
	}                                                                          \
	case PT_FLOAT32:                                                           \
	{                                                                          \
		typedef float32_t PType;                                               \
		{                                                                      \
			__VA_ARGS__                                                        \
		}                                                                      \
		break;                                                                 \
	}                                                                          \
	case PT_FLOAT64:                                                           \
	{                                                                          \
		typedef float64_t PType;                                               \
		{                                                                      \
			__VA_ARGS__                                                        \
		}                                                                      \
		break;                                                                 \
	}                                                                          \
	case PT_FLOATMAX:                                                          \
	{                                                                          \
		typedef floatmax_t PType;                                              \
		{                                                                      \
			__VA_ARGS__                                                        \
		}                                                                      \
	}                                                                          \
	default:                                                                   \
		ASSERT(0)                                                              \
		break;                                                                 \
	}

#endif
