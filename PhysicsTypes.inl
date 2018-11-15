#ifndef VEC_TYPES
#define VEC_TYPES( a, b, c )
#endif

// a : type, b : identifier, c : debug output format
VEC_TYPES( float, f, "%.8f" )

#undef VEC_TYPES

// x : rows, y : columns
#ifndef MAT_TYPES
#define MAT_TYPES( X, Y )
#endif

MAT_TYPES( 2, 2 )
MAT_TYPES( 2, 3 )
MAT_TYPES( 2, 4 )
MAT_TYPES( 3, 2 )
MAT_TYPES( 3, 3 )
MAT_TYPES( 3, 4 )
MAT_TYPES( 4, 2 )
MAT_TYPES( 4, 3 )
MAT_TYPES( 4, 4 )

#undef MAT_TYPES

// x : rows, y : columns
#ifndef MAT_OP_TYPES
#define MAT_OP_TYPES( X, Y, Z )
#endif

MAT_OP_TYPES( 2, 2, 2 )
MAT_OP_TYPES( 2, 2, 3 )
MAT_OP_TYPES( 2, 2, 4 )
MAT_OP_TYPES( 2, 3, 2 )
MAT_OP_TYPES( 2, 3, 3 )
MAT_OP_TYPES( 2, 3, 4 )
MAT_OP_TYPES( 2, 4, 2 )
MAT_OP_TYPES( 2, 4, 3 )
MAT_OP_TYPES( 2, 4, 4 )

MAT_OP_TYPES( 3, 2, 2 )
MAT_OP_TYPES( 3, 2, 3 )
MAT_OP_TYPES( 3, 2, 4 )
MAT_OP_TYPES( 3, 3, 2 )
MAT_OP_TYPES( 3, 3, 3 )
MAT_OP_TYPES( 3, 3, 4 )
MAT_OP_TYPES( 3, 4, 2 )
MAT_OP_TYPES( 3, 4, 3 )
MAT_OP_TYPES( 3, 4, 4 )

MAT_OP_TYPES( 4, 2, 2 )
MAT_OP_TYPES( 4, 2, 3 )
MAT_OP_TYPES( 4, 2, 4 )
MAT_OP_TYPES( 4, 3, 2 )
MAT_OP_TYPES( 4, 3, 3 )
MAT_OP_TYPES( 4, 3, 4 )
MAT_OP_TYPES( 4, 4, 2 )
MAT_OP_TYPES( 4, 4, 3 )
MAT_OP_TYPES( 4, 4, 4 )

#undef MAT_OP_TYPES
