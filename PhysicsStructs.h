#pragma once

#ifdef __WIN32
#pragma warning( disable : 4201 )  // unnamed union
#pragma warning( disable : 4204 )  // struct initializer
#pragma warning( disable : 4505 )  // unreferenced local function
#pragma warning( disable : 4204 )  // nonstandard extension used : non-constant
                                   // aggregate initializer
#elif __llvm__
#pragma clang diagnostic ignored "-Wmissing-braces"
#endif

#include <inttypes.h>
#include "SimpleAssert.h"

#define VEC2_LAYOUT( TYPE, ID ) \
    struct Vec2##ID             \
    {                           \
        union {                 \
            struct              \
            {                   \
                TYPE x, y;      \
            };                  \
            TYPE data[2];       \
        };                      \
    }

#define VEC3_LAYOUT( TYPE, ID ) \
    struct Vec3##ID             \
    {                           \
        union {                 \
            struct              \
            {                   \
                TYPE x, y, z;   \
            };                  \
            TYPE data[3];       \
        };                      \
    }

#define VEC4_LAYOUT( TYPE, ID )  \
    struct Vec4##ID              \
    {                            \
        union {                  \
            struct               \
            {                    \
                TYPE x, y, z, w; \
            };                   \
            TYPE data[4];        \
        };                       \
    }

#define MAT_LAYOUT( X, Y ) \
struct Mat##Xx##Y \
{ \
	float data[Y][X]; \
}

struct DebugStr
{
    char buffer[128];
};

#define STRINGIFY_VEC2( ID ) \
    struct DebugStr stringify_v2##ID( struct Vec2##ID v2 )

#define STRINGIFY_VEC3( ID ) \
    struct DebugStr stringify_v3##ID( struct Vec3##ID v3 )

#define STRINGIFY_VEC4( ID ) \
    struct DebugStr stringify_v4##ID( struct Vec4##ID v4 )

#define VEC_TYPES( a, b, c ) \
    VEC2_LAYOUT( a, b );     \
    STRINGIFY_VEC2( b );     \
    VEC3_LAYOUT( a, b );     \
    STRINGIFY_VEC3( b );     \
    VEC4_LAYOUT( a, b );     \
    STRINGIFY_VEC4( b );
#include "PhysicsTypes.inl"

#define MAT_TYPES( X, Y ) MAT_LAYOUT( X, Y );
#include "PhysicsTypes.inl"

#define STRINGIFY_MAT( X, Y ) \
    struct DebugStr stringify_m##Xx##Y( struct Mat##Xx##Y m )

// clang-format off

#define stringify(X)                \
_Generic((X),					    \
struct Vec2f    : stringify_v2f,    \
struct Vec2i    : stringify_v2i,    \
struct Vec2u    : stringify_v2u,    \
struct Vec2i64  : stringify_v2i64,  \
struct Vec2u64  : stringify_v2u64,  \
struct Vec3f    : stringify_v3f,    \
struct Vec3i    : stringify_v3i,    \
struct Vec3u    : stringify_v3u,    \
struct Vec3i64  : stringify_v3i64,  \
struct Vec3u64  : stringify_v3u64,  \
struct Vec4i    : stringify_v4i,    \
struct Vec4u    : stringify_v4u,    \
struct Vec4i64  : stringify_v4i64,  \
struct Vec4u64  : stringify_v4u64,  \
default         : stringify_v4f     \
)(X)

// clang-format on