#pragma once

#include <stdbool.h>
#include "PhysicsStructs.h"

#define EQUALS_VEC( VSIZE, VTYPE, ID ) \
bool equals_v##VSIZE##ID( struct Vec##VSIZE##ID lhs, struct Vec##VSIZE##ID rhs );

#define VEC_TYPES( a, b, c ) EQUALS_VEC( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) EQUALS_VEC( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) EQUALS_VEC( 4, a, b )
#include "PhysicsTypes.inl"

#define MAGNITUDE_VEC( VSIZE, VTYPE, ID ) \
float magnitude_v##VSIZE##ID( struct Vec##VSIZE##ID v##VSIZE );

#define VEC_TYPES( a, b, c ) MAGNITUDE_VEC( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) MAGNITUDE_VEC( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) MAGNITUDE_VEC( 4, a, b )
#include "PhysicsTypes.inl"

#define NORMALIZE_VEC( VSIZE, VTYPE, ID ) \
struct Vec##VSIZE##ID normalize_v##VSIZE##ID( struct Vec##VSIZE##ID v##VSIZE );

#define VEC_TYPES( a, b, c ) NORMALIZE_VEC( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) NORMALIZE_VEC( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) NORMALIZE_VEC( 4, a, b )
#include "PhysicsTypes.inl"

#define MULT_VEC( VSIZE, VTYPE, ID ) \
struct Vec##VSIZE##ID mult_v##VSIZE##ID( struct Vec##VSIZE##ID v##VSIZE, VTYPE s );

#define VEC_TYPES( a, b, c ) MULT_VEC( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) MULT_VEC( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) MULT_VEC( 4, a, b )
#include "PhysicsTypes.inl"

#define ADD_VEC( VSIZE, VTYPE, ID ) \
struct Vec##VSIZE##ID add_v##VSIZE##ID( struct Vec##VSIZE##ID lhs, struct Vec##VSIZE##ID rhs );

#define VEC_TYPES( a, b, c ) ADD_VEC( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) ADD_VEC( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) ADD_VEC( 4, a, b )
#include "PhysicsTypes.inl"

#define SUB_VEC( VSIZE, VTYPE, ID ) \
struct Vec##VSIZE##ID sub_v##VSIZE##ID( struct Vec##VSIZE##ID lhs, struct Vec##VSIZE##ID rhs );

#define VEC_TYPES( a, b, c ) SUB_VEC( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) SUB_VEC( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) SUB_VEC( 4, a, b )
#include "PhysicsTypes.inl"

#define DOT_VEC( VSIZE, VTYPE, ID ) \
float dot_v##VSIZE##ID( struct Vec##VSIZE##ID lhs, struct Vec##VSIZE##ID rhs );

#define VEC_TYPES( a, b, c ) DOT_VEC( 2, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) DOT_VEC( 3, a, b )
#include "PhysicsTypes.inl"
#define VEC_TYPES( a, b, c ) DOT_VEC( 4, a, b )
#include "PhysicsTypes.inl"

#define CROSS_VEC( VSIZE, VTYPE, ID ) \
struct Vec##VSIZE##ID cross_v##VSIZE##ID( struct Vec##VSIZE##ID u, struct Vec##VSIZE##ID v );

#define VEC_TYPES( a, b, c ) CROSS_VEC( 3, a, b )
#include "PhysicsTypes.inl"

//----------------------------------------------------------------
//----------------------------------------------------------------

// clang-format off

#define equals_v(X, Y) \
_Generic((X), \
struct Vec2f    : equals_v2f,    \
struct Vec2i    : equals_v2i,    \
struct Vec2u    : equals_v2u,    \
struct Vec2i64  : equals_v2i64,  \
struct Vec2u64  : equals_v2u64,  \
struct Vec3f    : equals_v3f,    \
struct Vec3i    : equals_v3i,    \
struct Vec3u    : equals_v3u,    \
struct Vec3i64  : equals_v3i64,  \
struct Vec3u64  : equals_v3u64,  \
struct Vec4i    : equals_v4i,    \
struct Vec4u    : equals_v4u,    \
struct Vec4i64  : equals_v4i64,  \
struct Vec4u64  : equals_v4u64,  \
default         : equals_v4f     \
)(X, Y)

#define magnitude_v(X) \
_Generic((X), \
struct Vec2f    : magnitude_v2f,    \
struct Vec2i    : magnitude_v2i,    \
struct Vec2u    : magnitude_v2u,    \
struct Vec2i64  : magnitude_v2i64,  \
struct Vec2u64  : magnitude_v2u64,  \
struct Vec3f    : magnitude_v3f,    \
struct Vec3i    : magnitude_v3i,    \
struct Vec3u    : magnitude_v3u,    \
struct Vec3i64  : magnitude_v3i64,  \
struct Vec3u64  : magnitude_v3u64,  \
struct Vec4i    : magnitude_v4i,    \
struct Vec4u    : magnitude_v4u,    \
struct Vec4i64  : magnitude_v4i64,  \
struct Vec4u64  : magnitude_v4u64,  \
default         : magnitude_v4f     \
)(X)

#define normalize_v(X) \
_Generic((X), \
struct Vec2f    : normalize_v2f,    \
struct Vec2i    : normalize_v2i,    \
struct Vec2u    : normalize_v2u,    \
struct Vec2i64  : normalize_v2i64,  \
struct Vec2u64  : normalize_v2u64,  \
struct Vec3f    : normalize_v3f,    \
struct Vec3i    : normalize_v3i,    \
struct Vec3u    : normalize_v3u,    \
struct Vec3i64  : normalize_v3i64,  \
struct Vec3u64  : normalize_v3u64,  \
struct Vec4i    : normalize_v4i,    \
struct Vec4u    : normalize_v4u,    \
struct Vec4i64  : normalize_v4i64,  \
struct Vec4u64  : normalize_v4u64,  \
default         : normalize_v4f     \
)(X)

#define mult_v(X, Y) \
_Generic((X), \
struct Vec2u64  : mult_v2u64, \
struct Vec2u    : mult_v2u,   \
struct Vec2i64  : mult_v2i64, \
struct Vec2i    : mult_v2i,   \
struct Vec2f    : mult_v2f,   \
struct Vec3u64  : mult_v3u64, \
struct Vec3u    : mult_v3u,   \
struct Vec3i64  : mult_v3i64, \
struct Vec3i    : mult_v3i,   \
struct Vec3f    : mult_v3f,   \
struct Vec4u64  : mult_v4u64, \
struct Vec4u    : mult_v4u,   \
struct Vec4i64  : mult_v4i64, \
struct Vec4i    : mult_v4i,   \
default         : mult_v4f    \
)(X, Y)

#define add_v(X, Y) \
_Generic((X), \
struct Vec2u64  : add_v2u64, \
struct Vec2u    : add_v2u,   \
struct Vec2i64  : add_v2i64, \
struct Vec2i    : add_v2i,   \
struct Vec2f    : add_v2f,   \
struct Vec3u64  : add_v3u64, \
struct Vec3u    : add_v3u,   \
struct Vec3i64  : add_v3i64, \
struct Vec3i    : add_v3i,   \
struct Vec3f    : add_v3f,   \
struct Vec4u64  : add_v4u64, \
struct Vec4u    : add_v4u,   \
struct Vec4i64  : add_v4i64, \
struct Vec4i    : add_v4i,   \
default         : add_v4f    \
)(X, Y)

#define sub_v(X, Y) \
_Generic((X), \
struct Vec2u64  : sub_v2u64, \
struct Vec2u    : sub_v2u,   \
struct Vec2i64  : sub_v2i64, \
struct Vec2i    : sub_v2i,   \
struct Vec2f    : sub_v2f,   \
struct Vec3u64  : sub_v3u64, \
struct Vec3u    : sub_v3u,   \
struct Vec3i64  : sub_v3i64, \
struct Vec3i    : sub_v3i,   \
struct Vec3f    : sub_v3f,   \
struct Vec4u64  : sub_v4u64, \
struct Vec4u    : sub_v4u,   \
struct Vec4i64  : sub_v4i64, \
struct Vec4i    : sub_v4i,   \
default         : sub_v4f    \
)(X, Y)

#define dot_v(X, Y) \
_Generic((X), \
struct Vec2u64  : dot_v2u64, \
struct Vec2u    : dot_v2u,   \
struct Vec2i64  : dot_v2i64, \
struct Vec2i    : dot_v2i,   \
struct Vec2f    : dot_v2f,   \
struct Vec3u64  : dot_v3u64, \
struct Vec3u    : dot_v3u,   \
struct Vec3i64  : dot_v3i64, \
struct Vec3i    : dot_v3i,   \
struct Vec3f    : dot_v3f,   \
struct Vec4u64  : dot_v4u64, \
struct Vec4u    : dot_v4u,   \
struct Vec4i64  : dot_v4i64, \
struct Vec4i    : dot_v4i,   \
default         : dot_v4f    \
)(X, Y)

#define cross_v(X, Y) \
_Generic((X), \
struct Vec3u64  : cross_v3u64, \
struct Vec3u    : cross_v3u,   \
struct Vec3i64  : cross_v3i64, \
struct Vec3i    : cross_v3i,   \
default         : cross_v3f    \
)(X, Y)

// clang-format on

/*

#define mult(X, Y) \
_Generic((X), \
struct Vec3u64  : _Generic((Y), uint64_t : mult_v3u64),  \
struct Vec3u    : _Generic((Y), uint32_t : mult_v3u),    \
struct Vec3i64  : _Generic((Y), int64_t  : mult_v3i64),  \
struct Vec3i    : _Generic((Y), int32_t  : mult_v3i),    \
struct Vec3f    : _Generic((Y), float    : mult_v3f),    \
)(X, Y)

float magnitude_sq_v2( struct Vec2 v2 );
float magnitude_sq_v3( struct Vec3 v3 );
float magnitude_sq_v4( struct Vec4 v4 );
*/