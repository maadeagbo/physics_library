#include "PhysicsStructs.h"
#include "PhysicsInterface.h"
#include <stdio.h>
#include <string.h>

struct DebugStr stringify_v2f( struct Vec2f v2 )
{
  struct DebugStr out;
  snprintf( out.buffer, 
            256, 
            "<Vec2f> x:%.8f, y:%.8f",
			v2.x,
			v2.y );
  return out;
}

struct DebugStr stringify_v3f( struct Vec3f v3 )
{
  struct DebugStr out;
  snprintf( out.buffer,
            256,
			"<Vec3f> x:%.8f, y:%.8f, z:%.8f",
			v3.x,
			v3.y,
			v3.z );
  return out;
}

struct DebugStr stringify_v4f( struct Vec4f v4 )
{
  struct DebugStr out;
  snprintf( out.buffer,
            256,
            "<Vec4f> x:%.8f, y:%.8f, z:%.8f, w:%.8f",
            v4.x,
            v4.y,
            v4.z,
            v4.w );
  return out;
}

struct DebugStr stringify_quat( struct Quat q )
{
  struct DebugStr out;

  struct Vec3f euler = quat_to_euler( q );
  snprintf( out.buffer,
            256,
			"<Quat> i:%.8f, j:%.8f, k:%.8f, real:%.8f (euler: %.3f, %.3f, %.3f)",
			q.i,
			q.j,
			q.k,
			q.real,
			rad_to_deg( euler.x ),
			rad_to_deg( euler.y ),
			rad_to_deg( euler.z ) );
  return out;
}

#define STRINGIFY_MAT_IMPLEMENT( X, Y )                                       \
  struct DebugStr stringify_m##X##x##Y( struct Mat##X##x##Y m )               \
  {                                                                           \
    struct DebugStr out;                                                      \
    uint32_t offset = 0;                                                      \
    snprintf( out.buffer, 256, "<Mat%ux%u>", X, Y );                          \
    offset = (uint32_t)strnlen( out.buffer, 256 );                            \
                                                                              \
    for( uint32_t i = 0; i < X; i++ )                                         \
    {                                                                         \
      snprintf( out.buffer + offset, 256 - offset, "\n  " );                  \
      offset += 3;                                                            \
                                                                              \
      for( uint32_t j = 0; j < Y; j++ )                                       \
      {                                                                       \
        snprintf( out.buffer + offset, 256 - offset, " %.5f", m.data[j][i] ); \
        offset = (uint32_t)strnlen( out.buffer, 256 );                        \
      }                                                                       \
    }                                                                         \
    return out;                                                               \
  }

#define MAT_TYPES( X, Y ) STRINGIFY_MAT_IMPLEMENT( X, Y )
#include "PhysicsTypes.inl"