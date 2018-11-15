#include "PhysicsInterface.h"
#include <math.h>
#include <immintrin.h>

#define UNUSED_VAR( X ) (void)X

static bool equals_impl( const float dataA[],
                         const float dataB[],
                         uint32_t count )
{
    bool is_equal = true;
    for( uint32_t i = 0; i < count && is_equal; i++ )
        is_equal &= dataA[i] >= ( dataB[i] - __FLT_EPSILON__ ) &&
                    dataA[i] <= ( dataB[i] + __FLT_EPSILON__ );
    return is_equal;
}

bool equals_v2f( struct Vec2f lhs, struct Vec2f rhs )
{
    return equals_impl( lhs.data, rhs.data, 2 );
}

bool equals_v3f( struct Vec3f lhs, struct Vec3f rhs )
{
    return equals_impl( lhs.data, rhs.data, 3 );
}

bool equals_v4f( struct Vec4f lhs, struct Vec4f rhs )
{
    return equals_impl( lhs.data, rhs.data, 4 );
}

static float magnitude_impl( const float data[], uint32_t count )
{
    float output = 0.f;
    for( uint32_t i = 0; i < count; i++ ) output += data[i] * data[i];
    return sqrtf( output );
}

float magnitude_v2f( struct Vec2f v2f )
{
    return magnitude_impl( v2f.data, 2 );
}

float magnitude_v3f( struct Vec3f v3f )
{
    return magnitude_impl( v3f.data, 3 );
}

float magnitude_v4f( struct Vec4f v4f )
{
    return magnitude_impl( v4f.data, 4 );
}

static void normalize_impl( float data[], float mag, uint32_t count )
{
    for( uint32_t i = 0; i < count; i++ ) data[i] = data[i] / mag;
}

struct Vec2f normalize_v2f( struct Vec2f v2 )
{
	struct Vec2f v = { v2.x, v2.y };
	normalize_impl( v.data, magnitude_impl( v.data, 2), 2 );
	return v;
}

struct Vec3f normalize_v3f( struct Vec3f v3 )
{
	struct Vec3f v = { v3.x, v3.y, v3.z };
	normalize_impl( v.data, magnitude_impl( v.data, 3 ), 3 );
	return v;
}

struct Vec4f normalize_v4f( struct Vec4f v4 )
{
	struct Vec4f v = { v4.x, v4.y, v4.z, v4.z };
	normalize_impl( v.data, magnitude_impl( v.data, 4 ), 4 );
	return v;
}

#define MULT_VEC_IMPL( VSIZE, VTYPE, ID )                                    \
    struct Vec##VSIZE##ID mult_v##VSIZE##ID( struct Vec##VSIZE##ID v##VSIZE, \
                                             VTYPE s )                       \
    {                                                                        \
        struct Vec##VSIZE##ID v;                                             \
        for( uint32_t i = 0; i < VSIZE; i++ )                                \
            v.data[i] = v##VSIZE.data[i] * s;                                \
        return v;                                                            \
    }

#define ADD_VEC_IMPL( VSIZE, VTYPE, ID )                                \
    struct Vec##VSIZE##ID add_v##VSIZE##ID( struct Vec##VSIZE##ID lhs,  \
                                            struct Vec##VSIZE##ID rhs ) \
    {                                                                   \
        struct Vec##VSIZE##ID v;                                        \
        for( uint32_t i = 0; i < VSIZE; i++ )                           \
            v.data[i] = lhs.data[i] + rhs.data[i];                      \
        return v;                                                       \
    }

#define SUB_VEC_IMPL( VSIZE, VTYPE, ID )                                \
    struct Vec##VSIZE##ID sub_v##VSIZE##ID( struct Vec##VSIZE##ID lhs,  \
                                            struct Vec##VSIZE##ID rhs ) \
    {                                                                   \
        struct Vec##VSIZE##ID v;                                        \
        for( uint32_t i = 0; i < VSIZE; i++ )                           \
            v.data[i] = lhs.data[i] - rhs.data[i];                      \
        return v;                                                       \
    }

#define DOT_VEC_IMPL( VSIZE, VTYPE, ID )                \
    float dot_v##VSIZE##ID( struct Vec##VSIZE##ID lhs,  \
                            struct Vec##VSIZE##ID rhs ) \
    {                                                   \
        float output = 0.f;                             \
        for( uint32_t i = 0; i < VSIZE; i++ )           \
            output += lhs.data[i] * rhs.data[i];        \
        return output;                                  \
    }

#define CROSS_VEC_IMPL( VSIZE, VTYPE, ID )                              \
    struct Vec##VSIZE##ID cross_v##VSIZE##ID( struct Vec##VSIZE##ID u,  \
                                              struct Vec##VSIZE##ID v ) \
    {                                                                   \
        return ( struct Vec##VSIZE##ID ){                               \
            .x = u.y * v.z - u.z * v.y,                                 \
            .y = ( u.x * v.z - u.z * v.x ) * -1.f,                      \
            .z = u.x* v.y - u.y* v.x};                                  \
    }

#define VEC_TYPES( a, b, c ) MULT_VEC_IMPL( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) MULT_VEC_IMPL( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) MULT_VEC_IMPL( 4, a, b )
#include "PhysicsTypes.inl"

#define VEC_TYPES( a, b, c ) ADD_VEC_IMPL( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) ADD_VEC_IMPL( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) ADD_VEC_IMPL( 4, a, b )
#include "PhysicsTypes.inl"

#define VEC_TYPES( a, b, c ) SUB_VEC_IMPL( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) SUB_VEC_IMPL( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) SUB_VEC_IMPL( 4, a, b )
#include "PhysicsTypes.inl"

#define VEC_TYPES( a, b, c ) DOT_VEC_IMPL( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) DOT_VEC_IMPL( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) DOT_VEC_IMPL( 4, a, b )
#include "PhysicsTypes.inl"

#define VEC_TYPES( a, b, c ) CROSS_VEC_IMPL( 3, a, b )
#include "PhysicsTypes.inl"

#define IDENT_MAT_IMPL( X, Y )                                      \
    struct Mat##X##x##Y ident_m##X##x##Y()                          \
    {                                                               \
        struct Mat##X##x##Y m = {};                                 \
                                                                    \
        uint32_t max_val = X < Y ? X : Y;                           \
                                                                    \
        for( uint32_t i = 0; i < max_val; i++ ) m.data[i][i] = 1.f; \
                                                                    \
        return m;                                                   \
    }

IDENT_MAT_IMPL( 2, 2 )
IDENT_MAT_IMPL( 3, 3 )
IDENT_MAT_IMPL( 4, 4 )

struct Mat3x3 mult_m3x4_m4x3( struct Mat3x4 lhs, struct Mat4x3 rhs )
{
    UNUSED_VAR( lhs );
    UNUSED_VAR( rhs );

    struct Mat3x3 m = ident_m3x3();

    // int mask = 0xf1;

    //

    return m;
}
