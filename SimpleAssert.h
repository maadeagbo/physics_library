#pragma once

// implementation based of: Learn C The Hard Way by Zed A Shaw

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#define clean_errno() ( errno == 0 ? "None" : strerror( errno ) )

#define log_error( M, ... )              \
    fprintf( stdout,                     \
             "%s:%d: errno: %s " M "\n", \
             __FILE__,                   \
             __LINE__,                   \
             clean_errno(),              \
             ##__VA_ARGS__ )

#define assertf( A, M, ... )           \
    if( !( A ) )                       \
    {                                  \
        log_error( M, ##__VA_ARGS__ ); \
        assert( A );                   \
    }
