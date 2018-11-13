#include "PhysicsStructs.h"
#include <stdio.h>

#define STRINGIFY_VEC2_IMPLEMENT( ID, FORMAT )             \
    struct DebugStr stringify_v2##ID( struct Vec2##ID v2 ) \
    {                                                      \
        struct DebugStr out;                               \
        snprintf( out.buffer,                              \
                  128,                                     \
                  "<Vec2" #ID "> x:" FORMAT ", y:" FORMAT, \
                  v2.x,                                    \
                  v2.y );                                  \
        return out;                                        \
    }

#define STRINGIFY_VEC3_IMPLEMENT( ID, FORMAT )                           \
    struct DebugStr stringify_v3##ID( struct Vec3##ID v3 )               \
    {                                                                    \
        struct DebugStr out;                                             \
        snprintf( out.buffer,                                            \
                  128,                                                   \
                  "<Vec3" #ID "> x:" FORMAT ", y:" FORMAT ", z:" FORMAT, \
                  v3.x,                                                  \
                  v3.y,                                                  \
                  v3.z );                                                \
        return out;                                                      \
    }

#define STRINGIFY_VEC4_IMPLEMENT( ID, FORMAT )                          \
    struct DebugStr stringify_v4##ID( struct Vec4##ID v4 )              \
    {                                                                   \
        struct DebugStr out;                                            \
        snprintf( out.buffer,                                           \
                  128,                                                  \
                  "<Vec4" #ID "> x:" FORMAT ", y:" FORMAT ", z:" FORMAT \
                  ", w:" FORMAT,                                        \
                  v4.x,                                                 \
                  v4.y,                                                 \
                  v4.z,                                                 \
                  v4.w );                                               \
        return out;                                                     \
    }

#define VEC_TYPES( a, b, c )         \
    STRINGIFY_VEC2_IMPLEMENT( b, c ) \
    STRINGIFY_VEC3_IMPLEMENT( b, c ) \
    STRINGIFY_VEC4_IMPLEMENT( b, c )
#include "PhysicsTypes.inl"