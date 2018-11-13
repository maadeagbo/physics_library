#include "PhysicsInterface.h"
#include <math.h>

#define EQUALS_VEC_IMPL( VSIZE, VTYPE, ID )                                 \
    bool equals_v##VSIZE##ID( struct Vec##VSIZE##ID lhs,                    \
                              struct Vec##VSIZE##ID rhs )                   \
    {                                                                       \
        bool is_equal = true;                                               \
        for( uint32_t i = 0; i < VSIZE && is_equal; i++ )                   \
            is_equal &= lhs.data[i] >= ( rhs.data[i] - __FLT_EPSILON__ ) && \
                        lhs.data[i] <= ( rhs.data[i] + __FLT_EPSILON__ );   \
        return is_equal;                                                    \
    }

#define MAGNITUDE_VEC_IMPL( VSIZE, VTYPE, ID )                     \
    float magnitude_v##VSIZE##ID( struct Vec##VSIZE##ID v##VSIZE ) \
    {                                                              \
        float output = 0.f;                                        \
        for( uint32_t i = 0; i < VSIZE; i++ )                      \
            output += v##VSIZE.data[i] * v##VSIZE.data[i];         \
        return sqrtf( output );                                    \
    }

#define NORMALIZE_VEC_IMPL( VSIZE, VTYPE, ID )    \
    struct Vec##VSIZE##ID normalize_v##VSIZE##ID( \
        struct Vec##VSIZE##ID v##VSIZE )          \
    {                                             \
        struct Vec##VSIZE##ID v;                  \
                                                  \
        float mag = magnitude_v( v##VSIZE );      \
                                                  \
        for( uint32_t i = 0; i < VSIZE; i++ )     \
            v.data[i] = v##VSIZE.data[i] / mag;   \
        return v;                                 \
    }

#define MULT_VEC_IMPL( VSIZE, VTYPE, ID )                                    \
    struct Vec##VSIZE##ID mult_v##VSIZE##ID( struct Vec##VSIZE##ID v##VSIZE, \
                                             VTYPE                 s )       \
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

#define VEC_TYPES( a, b, c ) EQUALS_VEC_IMPL( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) EQUALS_VEC_IMPL( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) EQUALS_VEC_IMPL( 4, a, b )
#include "PhysicsTypes.inl"

#define VEC_TYPES( a, b, c ) MAGNITUDE_VEC_IMPL( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) MAGNITUDE_VEC_IMPL( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) MAGNITUDE_VEC_IMPL( 4, a, b )
#include "PhysicsTypes.inl"

#define VEC_TYPES( a, b, c ) NORMALIZE_VEC_IMPL( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) NORMALIZE_VEC_IMPL( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) NORMALIZE_VEC_IMPL( 4, a, b )
#include "PhysicsTypes.inl"

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
