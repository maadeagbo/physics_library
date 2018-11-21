#pragma once

#include <stdbool.h>
#include "PhysicsStructs.h"

float deg_to_rad( float deg );

float rad_to_deg( float rad );

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

bool equals_v2f( struct Vec2f lhs, struct Vec2f rhs );
bool equals_v3f( struct Vec3f lhs, struct Vec3f rhs );
bool equals_v4f( struct Vec4f lhs, struct Vec4f rhs );

float magnitude_v2f( struct Vec2f v2f );
float magnitude_v3f( struct Vec3f v3f );
float magnitude_v4f( struct Vec4f v4f );

struct Vec2f normalize_v2f( struct Vec2f v2 );
struct Vec3f normalize_v3f( struct Vec3f v3 );
struct Vec4f normalize_v4f( struct Vec4f v4 );

struct Vec2f mult_v2f( struct Vec2f v2, float s );
struct Vec3f mult_v3f( struct Vec3f v3, float s );
struct Vec4f mult_v4f( struct Vec4f v4, float s );

struct Vec2f add_v2f( struct Vec2f lhs, struct Vec2f rhs );
struct Vec3f add_v3f( struct Vec3f lhs, struct Vec3f rhs );
struct Vec4f add_v4f( struct Vec4f lhs, struct Vec4f rhs );

struct Vec2f sub_v2f( struct Vec2f lhs, struct Vec2f rhs );
struct Vec3f sub_v3f( struct Vec3f lhs, struct Vec3f rhs );
struct Vec4f sub_v4f( struct Vec4f lhs, struct Vec4f rhs );

float dot_v2f( struct Vec2f lhs, struct Vec2f rhs );
float dot_v3f( struct Vec3f lhs, struct Vec3f rhs );
float dot_v4f( struct Vec4f lhs, struct Vec4f rhs );

struct Vec3f cross_v3f( struct Vec3f u, struct Vec3f v );

//----------------------------------------------------------------
//----------------------------------------------------------------

#define IDENT_MAT( X, Y ) struct Mat##X##x##Y ident_m##X##x##Y();

IDENT_MAT( 2, 2 )
IDENT_MAT( 3, 3 )
IDENT_MAT( 4, 4 )

#define MULT_MAT( X, Y, Z )                                                  \
    struct Mat##X##x##Z mult_##X##x##Y##_##Y##x##Z( struct Mat##X##x##Y lhs, \
                                                    struct Mat##Y##x##Z rhs );

#define MAT_OP_TYPES( X, Y, Z ) MULT_MAT( X, Y, Z )
#include "PhysicsTypes.inl"

#define MULT_TRANSP( X, Y ) \
    struct Mat##Y##x##X transpose_##X##x##Y( struct Mat##X##x##Y m );

#define MAT_TYPES( X, Y ) MULT_TRANSP( X, Y )
#include "PhysicsTypes.inl"

#define MULT_SCALAR( X, Y ) \
    struct Mat##X##x##Y mult_##X##x##Y( struct Mat##X##x##Y m, float s );

#define MAT_TYPES( X, Y ) MULT_SCALAR( X, Y )
#include "PhysicsTypes.inl"

#define ADD_MAT( X, Y )                                         \
    struct Mat##X##x##Y add_##X##x##Y( struct Mat##X##x##Y lhs, \
                                       struct Mat##X##x##Y rhs );

#define MAT_TYPES( X, Y ) ADD_MAT( X, Y )
#include "PhysicsTypes.inl"

#define EQUALS_M( X, Y ) \
    bool equals_##X##x##Y( struct Mat##X##x##Y a, struct Mat##X##x##Y b );

#define MAT_TYPES( X, Y ) EQUALS_M( X, Y )
#include "PhysicsTypes.inl"

float determinant_2x2( struct Mat2x2 m );
float determinant_3x3( struct Mat3x3 m );
float determinant_4x4( struct Mat4x4 m );

struct Mat2x2 inverse_2x2( struct Mat2x2 m );
struct Mat3x3 inverse_3x3( struct Mat3x3 m );
struct Mat4x4 inverse_4x4( struct Mat4x4 m );

#define MULT_MAT_VEC( X, Y )                                   \
    struct Vec##X##f mult_##X##x##Y##v( struct Mat##X##x##Y m, \
                                        struct Vec##Y##f v );

#define MAT_TYPES( X, Y ) MULT_MAT_VEC( X, Y )
#include "PhysicsTypes.inl"

//----------------------------------------------------------------
//----------------------------------------------------------------

struct Quat quat_from_euler( float radian_pitch,
                             float radian_yaw,
                             float radian_roll );

// x : pitch, y : yaw, z : roll
struct Quat quat_from_euler_v( struct Vec3f v );

// x : pitch, y : yaw, z : roll
struct Vec3f quat_to_euler( struct Quat q );

struct Quat mult_q( struct Quat lhs, struct Quat rhs );

struct Vec3f mult_qv( struct Quat q, struct Vec3f v );

struct Mat4x4 quat_to_mat( struct Quat q );

struct Quat conjugate( struct Quat q );

float dot_q( struct Quat q1, struct Quat q2 );

//----------------------------------------------------------------
//----------------------------------------------------------------

#if _MSC_VER && !__INTEL_COMPILER

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
	struct Mat4x2  : mult_3x4_4x2 ) \
\
)(X, Y)

// clang-format on

#endif