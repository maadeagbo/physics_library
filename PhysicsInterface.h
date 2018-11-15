#pragma once

#include <stdbool.h>
#include "PhysicsStructs.h"

bool equals_v2f( struct Vec2f lhs, struct Vec2f rhs );
bool equals_v3f( struct Vec3f lhs, struct Vec3f rhs );
bool equals_v4f( struct Vec4f lhs, struct Vec4f rhs );

float magnitude_v2f( struct Vec2f v2f );
float magnitude_v3f( struct Vec3f v3f );
float magnitude_v4f( struct Vec4f v4f );

#define NORMALIZE_VEC( VSIZE, VTYPE, ID )         \
    struct Vec##VSIZE##ID normalize_v##VSIZE##ID( \
        struct Vec##VSIZE##ID v##VSIZE );

#define VEC_TYPES( a, b, c ) NORMALIZE_VEC( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) NORMALIZE_VEC( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) NORMALIZE_VEC( 4, a, b )
#include "PhysicsTypes.inl"

#define MULT_VEC( VSIZE, VTYPE, ID )                                         \
    struct Vec##VSIZE##ID mult_v##VSIZE##ID( struct Vec##VSIZE##ID v##VSIZE, \
                                             VTYPE s );

#define VEC_TYPES( a, b, c ) MULT_VEC( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) MULT_VEC( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) MULT_VEC( 4, a, b )
#include "PhysicsTypes.inl"

#define ADD_VEC( VSIZE, VTYPE, ID )                                    \
    struct Vec##VSIZE##ID add_v##VSIZE##ID( struct Vec##VSIZE##ID lhs, \
                                            struct Vec##VSIZE##ID rhs );

#define VEC_TYPES( a, b, c ) ADD_VEC( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) ADD_VEC( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) ADD_VEC( 4, a, b )
#include "PhysicsTypes.inl"

#define SUB_VEC( VSIZE, VTYPE, ID )                                    \
    struct Vec##VSIZE##ID sub_v##VSIZE##ID( struct Vec##VSIZE##ID lhs, \
                                            struct Vec##VSIZE##ID rhs );

#define VEC_TYPES( a, b, c ) SUB_VEC( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) SUB_VEC( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) SUB_VEC( 4, a, b )
#include "PhysicsTypes.inl"

#define DOT_VEC( VSIZE, VTYPE, ID )                    \
    float dot_v##VSIZE##ID( struct Vec##VSIZE##ID lhs, \
                            struct Vec##VSIZE##ID rhs );

#define VEC_TYPES( a, b, c ) DOT_VEC( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) DOT_VEC( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) DOT_VEC( 4, a, b )
#include "PhysicsTypes.inl"

struct Vec3f cross_v3f( struct Vec3f u, struct Vec3f v );

#define IDENT_MAT( X, Y ) struct Mat##X##x##Y ident_m##X##x##Y();

IDENT_MAT( 2, 2 )
IDENT_MAT( 3, 3 )
IDENT_MAT( 4, 4 )

#define MULT_MAT( X, Y, Z )                           \
    struct Mat##X##x##Z mult_m##X##x##Y##_m##Y##x##Z( \
        struct Mat##X##x##Y lhs, struct Mat##Y##x##Z rhs );

#define MAT_OP_TYPES( X, Y, Z ) MULT_MAT( X, Y, Z )
#include "PhysicsTypes.inl"

//----------------------------------------------------------------
//----------------------------------------------------------------

// clang-format off

#define equals_v(X, Y) \
_Generic((X), \
struct Vec2f    : equals_v2f,    \
struct Vec3f    : equals_v3f,    \
default         : equals_v4f     \
)(X, Y)

#define magnitude_v(X) \
_Generic((X), \
struct Vec2f    : magnitude_v2f,    \
struct Vec3f    : magnitude_v3f,    \
default         : magnitude_v4f     \
)(X)

#define normalize_v(X) \
_Generic((X), \
struct Vec2f    : normalize_v2f,    \
struct Vec3f    : normalize_v3f,    \
default         : normalize_v4f     \
)(X)

#define mult_v(X, Y) \
_Generic((X), \
struct Vec2f    : mult_v2f,   \
struct Vec3f    : mult_v3f,   \
default         : mult_v4f    \
)(X, Y)

#define add_v(X, Y) \
_Generic((X), \
struct Vec2f    : add_v2f,   \
struct Vec3f    : add_v3f,   \
default         : add_v4f    \
)(X, Y)

#define sub_v(X, Y) \
_Generic((X), \
struct Vec2f    : sub_v2f,   \
struct Vec3f    : sub_v3f,   \
default         : sub_v4f    \
)(X, Y)

#define dot_v(X, Y) \
_Generic((X), \
struct Vec2f    : dot_v2f,   \
struct Vec3f    : dot_v3f,   \
default         : dot_v4f    \
)(X, Y)

#define cross_v(X, Y) \
_Generic((X), \
default         : cross_v3f    \
)(X, Y)

#define mult_x(X, Y) \
_Generic((X), \
struct Mat3x4  : \
\
_Generic((Y), \
	struct Mat4x3  : mult_m3x4_m4x3 ) \
\
)(X, Y)

// clang-format on
