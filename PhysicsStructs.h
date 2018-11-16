#pragma once

#ifdef __WIN32

#pragma warning( disable : 4201 )  // unnamed union
#pragma warning( disable : 4204 )  // struct initializer
#pragma warning( disable : 4505 )  // unreferenced local function
#pragma warning( disable : 4204 )  // nonstandard extension used : non-constant
                                   // aggregate initializer
#elif __llvm__

#pragma clang diagnostic ignored "-Wmissing-braces"              // for {{}}
#pragma clang diagnostic ignored "-Wmissing-field-initializers"  // for { 0 }

#else

#pragma GCC diagnostic ignored "-Wmissing-braces"

#endif

#include <inttypes.h>
#include "SimpleAssert.h"

struct DebugStr
{
    char buffer[256];
};

struct Vec2f
{
    union {
        struct
        {
            float x, y;
        };
        float data[2];
    };
};

struct Vec3f
{
    union {
        struct
        {
            float x, y, z;
        };
        float data[3];
    };
};

struct Vec4f
{
    union {
        struct
        {
            float x, y, z, w;
        };
        float data[4];
    };
};

struct DebugStr stringify_v2f( struct Vec2f v2 );
struct DebugStr stringify_v3f( struct Vec3f v3 );
struct DebugStr stringify_v4f( struct Vec4f v4 );

#define MAT_LAYOUT( X, Y ) \
    struct Mat##X##x##Y    \
    {                      \
        float data[Y][X];  \
    }

#define STRINGIFY_MAT( X, Y ) \
    struct DebugStr stringify_m##X##x##Y( struct Mat##X##x##Y m )

#define MAT_TYPES( X, Y ) \
    MAT_LAYOUT( X, Y );   \
    STRINGIFY_MAT( X, Y );
#include "PhysicsTypes.inl"

// clang-format off

#define stringify(X) _Generic((X),	\
struct Mat2x2   : stringify_m2x2,   \
struct Mat2x3   : stringify_m2x3,   \
struct Mat2x4   : stringify_m2x4,   \
struct Mat3x2   : stringify_m3x2,   \
struct Mat3x3   : stringify_m3x3,   \
struct Mat3x4   : stringify_m3x4,   \
struct Mat4x2   : stringify_m4x2,   \
struct Mat4x3   : stringify_m4x3,   \
struct Mat4x4   : stringify_m4x4,   \
struct Vec2f    : stringify_v2f,    \
struct Vec3f    : stringify_v3f,    \
default         : stringify_v4f     \
)(X)

// clang-format on