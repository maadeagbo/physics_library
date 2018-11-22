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

DebugStr stringify_v( Vec2f v2 );
DebugStr stringify_v( Vec3f v3 );
DebugStr stringify_v( Vec4f v4 );

bool operator==( const Vec2f& lhs, const Vec2f& rhs );
bool operator==( const Vec3f& lhs, const Vec3f& rhs );
bool operator==( const Vec4f& lhs, const Vec4f& rhs );

float magnitude_v( Vec2f v2f );
float magnitude_v( Vec3f v3f );
float magnitude_v( Vec4f v4f );

Vec2f normalize_v( Vec2f v2 );
Vec3f normalize_v( Vec3f v3 );
Vec4f normalize_v( Vec4f v4 );

Vec2f operator*( Vec2f lhs, float rhs );
Vec3f operator*( Vec3f lhs, float rhs );
Vec4f operator*( Vec4f lhs, float rhs );

Vec2f operator+( Vec2f lhs, const Vec2f& rhs );
Vec3f operator+( Vec3f lhs, const Vec3f& rhs );
Vec4f operator+( Vec4f lhs, const Vec4f& rhs );

Vec2f operator-( Vec2f lhs, const Vec2f& rhs );
Vec3f operator-( Vec3f lhs, const Vec3f& rhs );
Vec4f operator-( Vec4f lhs, const Vec4f& rhs );

float dot_v( Vec2f lhs, Vec2f rhs );
float dot_v( Vec3f lhs, Vec3f rhs );
float dot_v( Vec4f lhs, Vec4f rhs );

#define STRINGIFY_MAT_H( X, Y ) \
    DebugStr stringify( Mat##X##x##Y m );

#define MAT_TYPES( X, Y ) STRINGIFY_MAT_H( X, Y )
#include "PhysicsTypes.inl"

#define MULT_MAT_H( X, Y, Z )                                         \
    Mat##X##x##Z operator*( Mat##X##x##Y lhs, const Mat##Y##x##Z& rhs );

#define MAT_OP_TYPES( X, Y, Z ) MULT_MAT_H( X, Y, Z )
#include "PhysicsTypes.inl"

#define MULT_TRANSP_H( X, Y )                \
    Mat##Y##x##X transpose_m( Mat##X##x##Y m );

#define MAT_TYPES( X, Y ) MULT_TRANSP_H( X, Y )
#include "PhysicsTypes.inl"

#define MULT_SCALAR_H( X, Y )                             \
    Mat##X##x##Y operator*( Mat##X##x##Y m, const float s );

#define MAT_TYPES( X, Y ) MULT_SCALAR_H( X, Y )
#include "PhysicsTypes.inl"

#define ADD_MAT_H( X, Y )                                             \
    Mat##X##x##Y operator+( Mat##X##x##Y lhs, const Mat##X##x##Y& rhs );

#define MAT_TYPES( X, Y ) ADD_MAT_H( X, Y )
#include "PhysicsTypes.inl"

#define EQUALS_M_H( X, Y )                                        \
    bool operator==( const Mat##X##x##Y& a, const Mat##X##x##Y& b );

#define MAT_TYPES( X, Y ) EQUALS_M_H( X, Y )
#include "PhysicsTypes.inl"

float determinant_m( Mat2x2 m );
float determinant_m( Mat3x3 m );
float determinant_m( Mat4x4 m );

Mat2x2 inverse_m( Mat2x2 m );
Mat3x3 inverse_m( Mat3x3 m );
Mat4x4 inverse_m( Mat4x4 m );

#define MULT_MAT_VEC_H( X, Y )                              \
    Vec##X##f operator*( Mat##X##x##Y m, const Vec##Y##f& v );

#define MAT_TYPES( X, Y ) MULT_MAT_VEC_H( X, Y )
#include "PhysicsTypes.inl"