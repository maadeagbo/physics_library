#include "PhysicsInterface.h"
#include <math.h>
#include <immintrin.h>

#define UNUSED_VAR( X ) (void)X

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

static void normalize_impl( float data[], float mag, uint32_t count )
{
    for( uint32_t i = 0; i < count; i++ ) data[i] = data[i] / mag;
}

struct Vec2f normalize_v2f( struct Vec2f v2 )
{
    struct Vec2f v = {v2.x, v2.y};
    normalize_impl( v.data, magnitude_impl( v.data, 2 ), 2 );
    return v;
}

struct Vec3f normalize_v3f( struct Vec3f v3 )
{
    struct Vec3f v = {v3.x, v3.y, v3.z};
    normalize_impl( v.data, magnitude_impl( v.data, 3 ), 3 );
    return v;
}

struct Vec4f normalize_v4f( struct Vec4f v4 )
{
    struct Vec4f v = {v4.x, v4.y, v4.z, v4.w};
    normalize_impl( v.data, magnitude_impl( v.data, 4 ), 4 );
    return v;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

static void mult_impl( float data[], uint32_t count, float scalar )
{
    for( uint32_t i = 0; i < count; i++ ) data[i] = data[i] * scalar;
}

struct Vec2f mult_v2f( struct Vec2f v2, float s )
{
    struct Vec2f v = {v2.x, v2.y};
    mult_impl( v.data, 2, s );
    return v;
}

struct Vec3f mult_v3f( struct Vec3f v3, float s )
{
    struct Vec3f v = {v3.x, v3.y, v3.z};
    mult_impl( v.data, 3, s );
    return v;
}

struct Vec4f mult_v4f( struct Vec4f v4, float s )
{
    struct Vec4f v = {v4.x, v4.y, v4.z, v4.w};
    mult_impl( v.data, 4, s );
    return v;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

static void add_impl( float output[],
                      const float lhs[],
                      const float rhs[],
                      uint32_t count )
{
    for( uint32_t i = 0; i < count; i++ ) output[i] = lhs[i] + rhs[i];
}

struct Vec2f add_v2f( struct Vec2f lhs, struct Vec2f rhs )
{
    struct Vec2f v;
    add_impl( v.data, lhs.data, rhs.data, 2 );
    return v;
}

struct Vec3f add_v3f( struct Vec3f lhs, struct Vec3f rhs )
{
    struct Vec3f v;
    add_impl( v.data, lhs.data, rhs.data, 3 );
    return v;
}

struct Vec4f add_v4f( struct Vec4f lhs, struct Vec4f rhs )
{
    struct Vec4f v;
    add_impl( v.data, lhs.data, rhs.data, 4 );
    return v;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

static void sub_impl( float output[],
                      const float lhs[],
                      const float rhs[],
                      uint32_t count )
{
    for( uint32_t i = 0; i < count; i++ ) output[i] = lhs[i] - rhs[i];
}

struct Vec2f sub_v2f( struct Vec2f lhs, struct Vec2f rhs )
{
    struct Vec2f v;
    sub_impl( v.data, lhs.data, rhs.data, 2 );
    return v;
}

struct Vec3f sub_v3f( struct Vec3f lhs, struct Vec3f rhs )
{
    struct Vec3f v;
    sub_impl( v.data, lhs.data, rhs.data, 3 );
    return v;
}

struct Vec4f sub_v4f( struct Vec4f lhs, struct Vec4f rhs )
{
    struct Vec4f v;
    sub_impl( v.data, lhs.data, rhs.data, 4 );
    return v;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

static float dot_impl( const float dataA[],
                       const float dataB[],
                       uint32_t count )
{
    float output = 0.f;
    for( uint32_t i = 0; i < count; i++ ) output += dataA[i] * dataB[i];
    return output;
}

float dot_v2f( struct Vec2f lhs, struct Vec2f rhs )
{
    return dot_impl( lhs.data, rhs.data, 2 );
}

float dot_v3f( struct Vec3f lhs, struct Vec3f rhs )
{
    return dot_impl( lhs.data, rhs.data, 3 );
}

float dot_v4f( struct Vec4f lhs, struct Vec4f rhs )
{
    return dot_impl( lhs.data, rhs.data, 4 );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

struct Vec3f cross_v3f( struct Vec3f u, struct Vec3f v )
{
    return ( struct Vec3f ){.x = u.y * v.z - u.z * v.y,
                            .y = ( u.x * v.z - u.z * v.x ) * -1.f,
                            .z = u.x * v.y - u.y * v.x};
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

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
