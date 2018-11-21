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

//Vec2f mult_v( Vec2f v2, float s ) { mult_v2f( v2, s ); }
Vec2f operator*( Vec2f lhs, float rhs ) { return mult_v2f( lhs, rhs ); }
//Vec3f mult_v( Vec3f v3, float s ) { mult_v3f( v3, s ); }
Vec3f operator*( Vec3f lhs, float rhs ) { return mult_v3f( lhs, rhs ); }
//Vec4f mult_v( Vec4f v4, float s ) { mult_v4f( v4, s ); }
Vec4f operator*( Vec4f lhs, float rhs ) { return mult_v4f( lhs, rhs ); }

//Vec2f add_v( Vec2f lhs, Vec2f rhs ) { add_v2f(lhs, rhs); }
Vec2f operator+( Vec2f lhs, const Vec2f& rhs ) { return add_v2f(lhs, rhs); }
//Vec3f add_v( Vec3f lhs, Vec3f rhs ) { add_v3f(lhs, rhs); }
Vec3f operator+( Vec3f lhs, const Vec3f& rhs ) { return add_v3f(lhs, rhs); }
//Vec4f add_v( Vec4f lhs, Vec4f rhs ) { add_v4f(lhs, rhs); }
Vec4f operator+( Vec4f lhs, const Vec4f& rhs ) { return add_v4f(lhs, rhs); }

//Vec2f sub_v( Vec2f lhs, Vec2f rhs ) { sub_v2f(lhs, rhs); }
Vec2f operator-( Vec2f lhs, const Vec2f& rhs ) { return sub_v2f(lhs, rhs); }
//Vec3f sub_v( Vec3f lhs, Vec3f rhs ) { sub_v3f(lhs, rhs); }
Vec3f operator-( Vec3f lhs, const Vec3f& rhs ) { return sub_v3f(lhs, rhs); }
//Vec4f sub_v( Vec4f lhs, Vec4f rhs ) { sub_v4f(lhs, rhs); }
Vec4f operator-( Vec4f lhs, const Vec4f& rhs ) { return sub_v4f(lhs, rhs); }

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
    Mat##X##x##Z operator*( Mat##X##x##Y lhs, const Mat##Y##x##Z& rhs )  \
    { \
        mult_##X##x##Y##_##Y##x##Z( lhs, rhs ); \
    }

#define MAT_OP_TYPES( X, Y, Z ) MULT_MAT_CPP( X, Y, Z )
#include "PhysicsTypes.inl"

#define MULT_TRANSP_CPP( X, Y ) \
    Mat##Y##x##X transpose_m( Mat##X##x##Y m ) \
    { \
        return transpose_##X##x##Y( m ); \
    }

#define MAT_TYPES( X, Y ) MULT_TRANSP_CPP( X, Y )
#include "PhysicsTypes.inl"

#define MULT_SCALAR_CPP( X, Y ) \
    Mat##X##x##Y operator*( Mat##X##x##Y m, const float s ) \
    { \
        return mult_##X##x##Y( m, s ); \
    }

#define MAT_TYPES( X, Y ) MULT_SCALAR_CPP( X, Y )
#include "PhysicsTypes.inl"

#define ADD_MAT_CPP( X, Y ) \
    Mat##X##x##Y operator+( Mat##X##x##Y lhs, const Mat##X##x##Y& rhs ) \
    { \
        return add_##X##x##Y( lhs, rhs ); \
    }

#define MAT_TYPES( X, Y ) ADD_MAT_CPP( X, Y )
#include "PhysicsTypes.inl"

#define EQUALS_M_CPP( X, Y ) \
    bool operator==( const Mat##X##x##Y& a, const Mat##X##x##Y& b ) \
    { \
        return equals_##X##x##Y( a, b ); \
    }

#define MAT_TYPES( X, Y ) EQUALS_M_CPP( X, Y )
#include "PhysicsTypes.inl"

float determinant_m( Mat2x2 m ) { determinant_2x2( m ); }
float determinant_m( Mat3x3 m ) { determinant_3x3( m ); }
float determinant_m( Mat4x4 m ) { determinant_4x4( m ); }

Mat2x2 inverse_m( Mat2x2 m ) { inverse_2x2( m ); }
Mat3x3 inverse_m( Mat3x3 m ) { inverse_3x3( m ); }
Mat4x4 inverse_m( Mat4x4 m ) { inverse_4x4( m ); }

#define MULT_MAT_VEC_CPP( X, Y )                                   \
    Vec##X##f operator*( Mat##X##x##Y m, const Vec##Y##f& v ) \
    { \
        return mult_##X##x##Y##v( m, v ); \
    }

#define MAT_TYPES( X, Y ) MULT_MAT_VEC_CPP( X, Y )
#include "PhysicsTypes.inl"