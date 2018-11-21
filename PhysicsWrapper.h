#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "PhysicsStructs.h"
#include "PhysicsInterface.h"

#ifdef __cplusplus
}
#endif

DebugStr stringify_v( Vec2f v2 ) { return stringify_v2f( v2 ); }
DebugStr stringify_v( Vec3f v3 ) { return stringify_v3f( v3 ); }
DebugStr stringify_v( Vec4f v4 ) { return stringify_v4f( v4 ); }

bool equals_v( Vec2f lhs, Vec2f rhs ) { equals_v2f(lhs, rhs); }
bool equals_v( Vec3f lhs, Vec3f rhs ) { equals_v3f(lhs, rhs); }
bool equals_v( Vec4f lhs, Vec4f rhs ) { equals_v4f(lhs, rhs); }

float magnitude_v( Vec2f v2f ) { magnitude_v2f( v2f ); }
float magnitude_v( Vec3f v3f ) { magnitude_v3f( v3f ); }
float magnitude_v( Vec4f v4f ) { magnitude_v4f( v4f ); }

Vec2f normalize_v( Vec2f v2 ) { normalize_v2f( v2 ); }
Vec3f normalize_v( Vec3f v3 ) { normalize_v3f( v3 ); }
Vec4f normalize_v( Vec4f v4 ) { normalize_v4f( v4 ); }

Vec2f mult_v( Vec2f v2, float s ) { mult_v2f( v2, s ); }
Vec3f mult_v( Vec3f v3, float s ) { mult_v3f( v3, s ); }
Vec4f mult_v( Vec4f v4, float s ) { mult_v4f( v4, s ); }

Vec2f add_v( Vec2f lhs, Vec2f rhs ) { add_v2f(lhs, rhs); }
Vec3f add_v( Vec3f lhs, Vec3f rhs ) { add_v3f(lhs, rhs); }
Vec4f add_v( Vec4f lhs, Vec4f rhs ) { add_v4f(lhs, rhs); }

Vec2f sub_v( Vec2f lhs, Vec2f rhs ) { sub_v2f(lhs, rhs); }
Vec3f sub_v( Vec3f lhs, Vec3f rhs ) { sub_v3f(lhs, rhs); }
Vec4f sub_v( Vec4f lhs, Vec4f rhs ) { sub_v4f(lhs, rhs); }

float dot_v( Vec2f lhs, Vec2f rhs ) { dot_v2f(lhs, rhs); }
float dot_v( Vec3f lhs, Vec3f rhs ) { dot_v3f(lhs, rhs); }
float dot_v( Vec4f lhs, Vec4f rhs ) { dot_v4f(lhs, rhs); }

#define STRINGIFY_MAT_CPP( X, Y ) \
    DebugStr stringify( Mat##X##x##Y m ) \
    { \
        return stringify_m##X##x##Y( m ); \
    }

#define MAT_TYPES( X, Y ) STRINGIFY_MAT_CPP( X, Y )
#include "PhysicsTypes.inl"

#define MULT_MAT_CPP( X, Y, Z )  \
    Mat##X##x##Z mult_m( Mat##X##x##Y lhs, Mat##Y##x##Z rhs )  \
    { \
        mult_##X##x##Y##_##Y##x##Z( lhs, rhs ); \
    }

#define MAT_OP_TYPES( X, Y, Z ) MULT_MAT_CPP( X, Y, Z )
#include "PhysicsTypes.inl"
