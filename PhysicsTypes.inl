#ifndef VEC_TYPES
#define VEC_TYPES( a, b, c )
#endif

// a : type, b : identifier, c : debug output format
VEC_TYPES( float, f, "%.8f" )
VEC_TYPES( int32_t, i, "%d" )
VEC_TYPES( uint32_t, u, "%u" )
VEC_TYPES( int64_t, i64, "%" PRId64 )
VEC_TYPES( uint64_t, u64, "%" PRIu64 )

#undef VEC_TYPES

// x : rows, y : columns
#ifndef MAT_TYPES
#define MAT_TYPES( x, y )
#endif

MAT_TYPES( 2, 2 )

#undef MAT_TYPES
