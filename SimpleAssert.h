#pragma once

// implementation based of: Learn C The Hard Way by Zed A Shaw

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef _WIN32
#define SIMPLE_HALT() __debugbreak()
#else
#define SIMPLE_HALT() __builtin_trap();
#endif  // linux

#define clean_errno() ( errno == 0 ? "None" : strerror( errno ) )

#define log_error( M, ... )                   \
  fprintf( stderr,                            \
           "%s : %d\n  errno: %s\n  " M "\n", \
           __FILE__,                          \
           __LINE__,                          \
           clean_errno(),                     \
           ##__VA_ARGS__ )

#ifdef NDEBUG

#define assertf( A, M, ... )

#else

#define assertf( A, M, ... )       \
  if( !( A ) )                     \
  {                                \
    log_error( M, ##__VA_ARGS__ ); \
    SIMPLE_HALT();                 \
  }

#endif  // NDEBUG