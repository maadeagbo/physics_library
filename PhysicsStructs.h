#pragma once

#ifdef _WIN32
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

#endif  // _WIN32

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

struct Quat
{
    union {
        struct
        {
            float i, j, k, real;
        };
        struct
        {
            float x, y, z, w;
        };
    };
};

struct DebugStr stringify_quat( struct Quat q );

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
