#include "PhysicsInterface.h"
#include <immintrin.h>

#define UNUSED_VAR( X ) (void)X

#ifdef _WIN32
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>

#define EPSILON_F FLT_EPSILON
#else
#include <math.h>
#define EPSILON_F __FLT_EPSILON__
#endif  // _WIN32

float deg_to_rad( float deg )
{
    return deg * (float)0.01745329251994329576923690768489;
}

float rad_to_deg( float rad )
{
    return rad * (float)57.295779513082320876798154814105;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

static bool equals_impl( const float dataA[],
                         const float dataB[],
                         uint32_t count )
{
    bool is_equal = true;
    for( uint32_t i = 0; i < count && is_equal; i++ )
        is_equal &= dataA[i] >= ( dataB[i] - EPSILON_F ) &&
                    dataA[i] <= ( dataB[i] + EPSILON_F );
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

// sourced from David Hammen :
// https://stackoverflow.com/questions/11667783/quaternion-and-normalization

static struct Quat normalize_quat( struct Quat q )
{
    float denom;
    double sq_mag = q.i * q.i + q.j * q.j + q.k * q.k + q.real * q.real;

    // check if quaternion needs to be normailzed
    // if so and if falls with a certain tolerance, use 1st order Pade approx,
    // else use sqrt

    if( fabs( 1.0 - sq_mag ) < 2.107342e-08 )
        denom = 2.f / ( 1.f + (float)sq_mag );
    else
        denom = 1.f / sqrtf( (float)sq_mag );

    struct Quat norm_q = {
        .i = q.i / denom,
        .j = q.j / denom,
        .k = q.k / denom,
        .real = q.real / denom,
    };

    return norm_q;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

struct Quat quat_from_euler( float radian_pitch,
                             float radian_yaw,
                             float radian_roll )
{
    // Calclations are based on NASA aerplane corrdinate space:
    // x: forward, y: right, z: downward
    // In order to fit my coordinate system, input has been shifted
    // My system is:
    // x: right, y: upward, z: forward

    float half_yaw = radian_roll * 0.5f;
    float half_pitch = radian_yaw * 0.5f;
    float half_roll = radian_pitch * 0.5f;

    float cos_y = cosf( half_yaw );
    float sin_y = sinf( half_yaw );
    float cos_p = cosf( half_pitch );
    float sin_p = sinf( half_pitch );
    float cos_r = cosf( half_roll );
    float sin_r = sinf( half_roll );

    return ( struct Quat ){
        cos_y * sin_r * cos_p - sin_y * cos_r * sin_p,
        cos_y * cos_r * sin_p + sin_y * sin_r * cos_p,
        sin_y * cos_r * cos_p - cos_y * sin_r * sin_p,
        cos_y * cos_r * cos_p + sin_y * sin_r * sin_p,
    };
}

struct Quat quat_from_euler_v( struct Vec3f v )
{
    // Calclations are based on NASA aerplane corrdinate space:
    // x: forward, y: right, z: downward
    // In order to fit my coordinate system, input has been shifted
    // My system is:
    // x: right, y: upward, z: forward

    float half_pitch = v.y * 0.5f;
    float half_yaw = v.z * 0.5f;
    float half_roll = v.x * 0.5f;

    float cos_y = cosf( half_yaw );
    float sin_y = sinf( half_yaw );
    float cos_p = cosf( half_pitch );
    float sin_p = sinf( half_pitch );
    float cos_r = cosf( half_roll );
    float sin_r = sinf( half_roll );

    return ( struct Quat ){
        cos_y * sin_r * cos_p - sin_y * cos_r * sin_p,
        cos_y * cos_r * sin_p + sin_y * sin_r * cos_p,
        sin_y * cos_r * cos_p - cos_y * sin_r * sin_p,
        cos_y * cos_r * cos_p + sin_y * sin_r * sin_p,
    };
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

struct Vec3f quat_to_euler( struct Quat q )
{
    q = normalize_quat( q );

    // test for gimbal lock in euler conversion
    float test_gimbal = q.x * q.y + q.z * q.w;

    if( test_gimbal > 0.499f )
    {
        return ( struct Vec3f ){
            (float)M_PI / 2.f, 2.f * atan2f( q.x, q.w ), 0.f};
    }
    else if( test_gimbal < -0.499f )
    {
        return ( struct Vec3f ){
            (float)M_PI / -2.f, -2.f * atan2f( q.x, q.w ), 0.f};
    }

    return ( struct Vec3f ){atan2f( 2.f * ( q.w * q.x + q.y * q.z ),
                                    1.f - 2.f * ( q.x * q.x + q.y * q.y ) ),
                            asinf( 2.f * ( q.w * q.y - q.z * q.x ) ),
                            atan2f( 2.f * ( q.w * q.z + q.x * q.y ),
                                    1.f - 2.f * ( q.y * q.y + q.z * q.z ) )};
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

struct Mat4x4 quat_to_mat( struct Quat q )
{
    // homogeneous expression ( non-unit quaternions will be a scalar multiple)

    q = normalize_quat( q );

    float qx2 = q.x * q.x;
    float qy2 = q.y * q.y;
    float qz2 = q.z * q.z;

    return ( struct Mat4x4 ){.data = {{1.f - 2.f * ( qy2 + qz2 ),
                                       2.f * ( q.x * q.y + q.w * q.z ),
                                       2.f * ( q.x * q.z - q.w * q.y ),
                                       0.f},
                                      {2.f * ( q.x * q.y - q.w * q.z ),
                                       1.f - 2.f * ( qx2 + qz2 ),
                                       2.f * ( q.w * q.x + q.y * q.z ),
                                       0.f},
                                      {2.f * ( q.w * q.y + q.x * q.z ),
                                       2.f * ( q.y * q.z - q.w * q.x ),
                                       1.f - 2.f * ( qx2 + qy2 ),
                                       0.f},
                                      {0.f, 0.f, 0.f, 1.f}}};
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

struct Quat mult_q( struct Quat lhs, struct Quat rhs )
{
    // this->x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
    // this->y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
    // this->z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
    struct Quat q = {
        .x = lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
        .y = lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
        .z = lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x,
        .w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
    };

    return normalize_quat( q );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

struct Vec3f mult_qv( struct Quat q, struct Vec3f v )
{
    // Implementation can be up to ~30% faster the q*v*q_conjugate

    q = normalize_quat( q );

    struct Vec3f q_vec = {.x = q.i, .y = q.j, .z = q.z};

    struct Vec3f t_vec = cross_v3f( mult_v3f( q_vec, 2.f ), v );

    return add_v3f( add_v3f( v, mult_v3f( t_vec, q.w ) ),
                    cross_v3f( q_vec, t_vec ) );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

struct Quat conjugate( struct Quat q )
{
    return ( struct Quat ){.i = -q.i, .j = -q.j, .k = -q.k, .real = q.real};
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

float dot_q( struct Quat q1, struct Quat q2 )
{
    q1 = normalize_quat( q1 );
    q2 = normalize_quat( q2 );

    return q1.i * q2.i + q1.j * q2.j + q1.k * q2.k + q1.real * q2.real;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#define IDENT_MAT_IMPL( X, Y )                                      \
    struct Mat##X##x##Y ident_m##X##x##Y()                          \
    {                                                               \
        struct Mat##X##x##Y m = {0};                                \
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

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

float determinant_2x2( struct Mat2x2 m )
{
    return m.data[0][0] * m.data[1][1] - m.data[1][0] * m.data[0][1];
}

float determinant_3x3( struct Mat3x3 m )
{
    return m.data[0][0] *
               ( m.data[1][1] * m.data[2][2] - m.data[2][1] * m.data[1][2] ) +
           m.data[1][0] *
               ( m.data[2][1] * m.data[0][2] - m.data[0][1] * m.data[2][2] ) +
           m.data[2][0] *
               ( m.data[0][1] * m.data[1][2] - m.data[1][1] * m.data[0][2] );
}

float determinant_4x4( struct Mat4x4 m )
{
    // Determinant logic uses scalar triple product and cofactor expansion

    float val_00 = m.data[1][1] * m.data[2][2] * m.data[3][3] -
                   m.data[1][1] * m.data[2][3] * m.data[3][2] -
                   m.data[2][1] * m.data[1][2] * m.data[3][3] +
                   m.data[2][1] * m.data[1][3] * m.data[3][2] +
                   m.data[3][1] * m.data[1][2] * m.data[2][3] -
                   m.data[3][1] * m.data[1][3] * m.data[2][2];

    float val_10 = -m.data[1][0] * m.data[2][2] * m.data[3][3] +
                   m.data[1][0] * m.data[2][3] * m.data[3][2] +
                   m.data[2][0] * m.data[1][2] * m.data[3][3] -
                   m.data[2][0] * m.data[1][3] * m.data[3][2] -
                   m.data[3][0] * m.data[1][2] * m.data[2][3] +
                   m.data[3][0] * m.data[1][3] * m.data[2][2];

    float val_20 = m.data[1][0] * m.data[2][1] * m.data[3][3] -
                   m.data[1][0] * m.data[2][3] * m.data[3][1] -
                   m.data[2][0] * m.data[1][1] * m.data[3][3] +
                   m.data[2][0] * m.data[1][3] * m.data[3][1] +
                   m.data[3][0] * m.data[1][1] * m.data[2][3] -
                   m.data[3][0] * m.data[1][3] * m.data[2][1];

    float val_30 = -m.data[1][0] * m.data[2][1] * m.data[3][2] +
                   m.data[1][0] * m.data[2][2] * m.data[3][1] +
                   m.data[2][0] * m.data[1][1] * m.data[3][2] -
                   m.data[2][0] * m.data[1][2] * m.data[3][1] -
                   m.data[3][0] * m.data[1][1] * m.data[2][2] +
                   m.data[3][0] * m.data[1][2] * m.data[2][1];

    return m.data[0][0] * val_00 + m.data[0][1] * val_10 +
           m.data[0][2] * val_20 + m.data[0][3] * val_30;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

struct Mat2x2 inverse_2x2( struct Mat2x2 m )
{
    float det = determinant_2x2( m );

    assertf( det > 0.f + EPSILON_F || det < 0.f + EPSILON_F,
             "Cannot calculate inverse on degerate matrix %s\n",
             stringify_m2x2( m ).buffer );

    struct Mat2x2 adjoint = {
        .data = {{m.data[1][1], -m.data[0][1]}, {-m.data[1][0], m.data[0][0]}}};
    return mult_2x2( adjoint, 1.f / det );
}

struct Mat3x3 inverse_3x3( struct Mat3x3 m )
{
    float det = determinant_3x3( m );

    assertf( det > 0.f + EPSILON_F || det < 0.f + EPSILON_F,
             "Cannot calculate inverse on degerate matrix %s\n",
             stringify_m3x3( m ).buffer );

    struct Mat3x3 adjoint = {
        .data = {{
                     m.data[1][1] * m.data[2][2] - m.data[2][1] * m.data[1][2],
                     m.data[2][1] * m.data[0][2] - m.data[0][1] * m.data[2][2],
                     m.data[0][1] * m.data[1][2] - m.data[1][1] * m.data[0][2],
                 },
                 {
                     m.data[2][0] * m.data[1][2] - m.data[1][0] * m.data[2][2],
                     m.data[0][0] * m.data[2][2] - m.data[2][0] * m.data[0][2],
                     m.data[1][0] * m.data[0][2] - m.data[0][0] * m.data[1][2],
                 },
                 {
                     m.data[1][0] * m.data[2][1] - m.data[2][0] * m.data[1][1],
                     m.data[2][0] * m.data[0][1] - m.data[0][0] * m.data[2][1],
                     m.data[0][0] * m.data[1][1] - m.data[1][0] * m.data[0][1],
                 }}};

    return mult_3x3( adjoint, 1.f / det );
}

struct Mat4x4 inverse_4x4( struct Mat4x4 m )
{
    // Solution uses cofactor expansion

    struct Mat4x4 adjoint = {0};

    adjoint.data[0][0] = m.data[1][1] * m.data[2][2] * m.data[3][3] -
                         m.data[1][1] * m.data[2][3] * m.data[3][2] -
                         m.data[2][1] * m.data[1][2] * m.data[3][3] +
                         m.data[2][1] * m.data[1][3] * m.data[3][2] +
                         m.data[3][1] * m.data[1][2] * m.data[2][3] -
                         m.data[3][1] * m.data[1][3] * m.data[2][2];

    adjoint.data[1][0] = -m.data[1][0] * m.data[2][2] * m.data[3][3] +
                         m.data[1][0] * m.data[2][3] * m.data[3][2] +
                         m.data[2][0] * m.data[1][2] * m.data[3][3] -
                         m.data[2][0] * m.data[1][3] * m.data[3][2] -
                         m.data[3][0] * m.data[1][2] * m.data[2][3] +
                         m.data[3][0] * m.data[1][3] * m.data[2][2];

    adjoint.data[2][0] = m.data[1][0] * m.data[2][1] * m.data[3][3] -
                         m.data[1][0] * m.data[2][3] * m.data[3][1] -
                         m.data[2][0] * m.data[1][1] * m.data[3][3] +
                         m.data[2][0] * m.data[1][3] * m.data[3][1] +
                         m.data[3][0] * m.data[1][1] * m.data[2][3] -
                         m.data[3][0] * m.data[1][3] * m.data[2][1];

    adjoint.data[3][0] = -m.data[1][0] * m.data[2][1] * m.data[3][2] +
                         m.data[1][0] * m.data[2][2] * m.data[3][1] +
                         m.data[2][0] * m.data[1][1] * m.data[3][2] -
                         m.data[2][0] * m.data[1][2] * m.data[3][1] -
                         m.data[3][0] * m.data[1][1] * m.data[2][2] +
                         m.data[3][0] * m.data[1][2] * m.data[2][1];

    float det =
        m.data[0][0] * adjoint.data[0][0] + m.data[0][1] * adjoint.data[1][0] +
        m.data[0][2] * adjoint.data[2][0] + m.data[0][3] * adjoint.data[3][0];

    assertf( det > 0.f + EPSILON_F || det < 0.f + EPSILON_F,
             "Cannot calculate inverse on degerate matrix %s\n",
             stringify_m4x4( m ).buffer );

    adjoint.data[0][1] = -m.data[0][1] * m.data[2][2] * m.data[3][3] +
                         m.data[0][1] * m.data[2][3] * m.data[3][2] +
                         m.data[2][1] * m.data[0][2] * m.data[3][3] -
                         m.data[2][1] * m.data[0][3] * m.data[3][2] -
                         m.data[3][1] * m.data[0][2] * m.data[2][3] +
                         m.data[3][1] * m.data[0][3] * m.data[2][2];

    adjoint.data[1][1] = m.data[0][0] * m.data[2][2] * m.data[3][3] -
                         m.data[0][0] * m.data[2][3] * m.data[3][2] -
                         m.data[2][0] * m.data[0][2] * m.data[3][3] +
                         m.data[2][0] * m.data[0][3] * m.data[3][2] +
                         m.data[3][0] * m.data[0][2] * m.data[2][3] -
                         m.data[3][0] * m.data[0][3] * m.data[2][2];

    adjoint.data[2][1] = -m.data[0][0] * m.data[2][1] * m.data[3][3] +
                         m.data[0][0] * m.data[2][3] * m.data[3][1] +
                         m.data[2][0] * m.data[0][1] * m.data[3][3] -
                         m.data[2][0] * m.data[0][3] * m.data[3][1] -
                         m.data[3][0] * m.data[0][1] * m.data[2][3] +
                         m.data[3][0] * m.data[0][3] * m.data[2][1];

    adjoint.data[3][1] = m.data[0][0] * m.data[2][1] * m.data[3][2] -
                         m.data[0][0] * m.data[2][2] * m.data[3][1] -
                         m.data[2][0] * m.data[0][1] * m.data[3][2] +
                         m.data[2][0] * m.data[0][2] * m.data[3][1] +
                         m.data[3][0] * m.data[0][1] * m.data[2][2] -
                         m.data[3][0] * m.data[0][2] * m.data[2][1];

    adjoint.data[0][2] = m.data[0][1] * m.data[1][2] * m.data[3][3] -
                         m.data[0][1] * m.data[1][3] * m.data[3][2] -
                         m.data[1][1] * m.data[0][2] * m.data[3][3] +
                         m.data[1][1] * m.data[0][3] * m.data[3][2] +
                         m.data[3][1] * m.data[0][2] * m.data[1][3] -
                         m.data[3][1] * m.data[0][3] * m.data[1][2];

    adjoint.data[1][2] = -m.data[0][0] * m.data[1][2] * m.data[3][3] +
                         m.data[0][0] * m.data[1][3] * m.data[3][2] +
                         m.data[1][0] * m.data[0][2] * m.data[3][3] -
                         m.data[1][0] * m.data[0][3] * m.data[3][2] -
                         m.data[3][0] * m.data[0][2] * m.data[1][3] +
                         m.data[3][0] * m.data[0][3] * m.data[1][2];

    adjoint.data[2][2] = m.data[0][0] * m.data[1][1] * m.data[3][3] -
                         m.data[0][0] * m.data[1][3] * m.data[3][1] -
                         m.data[1][0] * m.data[0][1] * m.data[3][3] +
                         m.data[1][0] * m.data[0][3] * m.data[3][1] +
                         m.data[3][0] * m.data[0][1] * m.data[1][3] -
                         m.data[3][0] * m.data[0][3] * m.data[1][1];

    adjoint.data[3][2] = -m.data[0][0] * m.data[1][1] * m.data[3][2] +
                         m.data[0][0] * m.data[1][2] * m.data[3][1] +
                         m.data[1][0] * m.data[0][1] * m.data[3][2] -
                         m.data[1][0] * m.data[0][2] * m.data[3][1] -
                         m.data[3][0] * m.data[0][1] * m.data[1][2] +
                         m.data[3][0] * m.data[0][2] * m.data[1][1];

    adjoint.data[0][3] = -m.data[0][1] * m.data[1][2] * m.data[2][3] +
                         m.data[0][1] * m.data[1][3] * m.data[2][2] +
                         m.data[1][1] * m.data[0][2] * m.data[2][3] -
                         m.data[1][1] * m.data[0][3] * m.data[2][2] -
                         m.data[2][1] * m.data[0][2] * m.data[1][3] +
                         m.data[2][1] * m.data[0][3] * m.data[1][2];

    adjoint.data[1][3] = m.data[0][0] * m.data[1][2] * m.data[2][3] -
                         m.data[0][0] * m.data[1][3] * m.data[2][2] -
                         m.data[1][0] * m.data[0][2] * m.data[2][3] +
                         m.data[1][0] * m.data[0][3] * m.data[2][2] +
                         m.data[2][0] * m.data[0][2] * m.data[1][3] -
                         m.data[2][0] * m.data[0][3] * m.data[1][2];

    adjoint.data[2][3] = -m.data[0][0] * m.data[1][1] * m.data[2][3] +
                         m.data[0][0] * m.data[1][3] * m.data[2][1] +
                         m.data[1][0] * m.data[0][1] * m.data[2][3] -
                         m.data[1][0] * m.data[0][3] * m.data[2][1] -
                         m.data[2][0] * m.data[0][1] * m.data[1][3] +
                         m.data[2][0] * m.data[0][3] * m.data[1][1];

    adjoint.data[3][3] = m.data[0][0] * m.data[1][1] * m.data[2][2] -
                         m.data[0][0] * m.data[1][2] * m.data[2][1] -
                         m.data[1][0] * m.data[0][1] * m.data[2][2] +
                         m.data[1][0] * m.data[0][2] * m.data[2][1] +
                         m.data[2][0] * m.data[0][1] * m.data[1][2] -
                         m.data[2][0] * m.data[0][2] * m.data[1][1];

    return mult_4x4( adjoint, 1.f / det );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

static bool equals_mat_impl( const float dataA[],
                             const float dataB[],
                             uint32_t row,
                             uint32_t column )
{
    // data is stored in column major order
    bool is_equal = true;

    for( uint32_t i = 0; i < column && is_equal; i++ )
        for( uint32_t j = 0; j < row && is_equal; j++ )
        {
            uint32_t idx = i * row + j;
            is_equal &= dataA[idx] >= ( dataB[idx] - EPSILON_F ) &&
                        dataA[idx] <= ( dataB[idx] + EPSILON_F );
        }

    return is_equal;
}

#define EQUALS_M_IMPL( X, Y )                                             \
    bool equals_##X##x##Y( struct Mat##X##x##Y a, struct Mat##X##x##Y b ) \
    {                                                                     \
        return equals_mat_impl( (float*)a.data, (float*)b.data, X, Y );   \
    }

#define MAT_TYPES( X, Y ) EQUALS_M_IMPL( X, Y )
#include "PhysicsTypes.inl"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

static void transpose_impl( float output[],
                            const float input[],
                            uint32_t row,
                            uint32_t col )
{
    // data is stored in column major order

    for( uint32_t i = 0; i < col; i++ )
        for( uint32_t j = 0; j < row; j++ )
            ( output + j * col )[i] = ( input + i * row )[j];
}

#define MULT_TRANSP_IMPL( X, Y )                                     \
    struct Mat##Y##x##X transpose_##X##x##Y( struct Mat##X##x##Y m ) \
    {                                                                \
        struct Mat##Y##x##X out = {0};                               \
        transpose_impl( (float*)out.data, (float*)m.data, X, Y );    \
        return out;                                                  \
    }

#define MAT_TYPES( X, Y ) MULT_TRANSP_IMPL( X, Y )
#include "PhysicsTypes.inl"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

static void scalar_mult_impl( float scalar,
                              float input[],
                              uint32_t row,
                              uint32_t col )
{
    // data is stored in column major order

    for( uint32_t i = 0; i < col; i++ )
        for( uint32_t j = 0; j < row; j++ ) input[i * row + j] *= scalar;
}

#define MULT_SCALAR_IMPL( X, Y )                                         \
    struct Mat##X##x##Y mult_##X##x##Y( struct Mat##X##x##Y m, float s ) \
    {                                                                    \
        scalar_mult_impl( s, (float*)m.data, X, Y );                     \
        return m;                                                        \
    }

#define MAT_TYPES( X, Y ) MULT_SCALAR_IMPL( X, Y )
#include "PhysicsTypes.inl"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

static void add_mat_impl( float output[],
                          const float dataA[],
                          const float dataB[],
                          uint32_t row,
                          uint32_t col )
{
    // data is stored in column major order

    for( uint32_t i = 0; i < col; i++ )
        for( uint32_t j = 0; j < row; j++ )
            output[i * row + j] = dataA[i * row + j] + dataB[i * row + j];
}

#define ADD_MAT_IMPL( X, Y )                                              \
    struct Mat##X##x##Y add_##X##x##Y( struct Mat##X##x##Y lhs,           \
                                       struct Mat##X##x##Y rhs )          \
    {                                                                     \
        struct Mat##X##x##Y out;                                          \
        add_mat_impl(                                                     \
            (float*)out.data, (float*)lhs.data, (float*)rhs.data, X, Y ); \
        return out;                                                       \
    }

#define MAT_TYPES( X, Y ) ADD_MAT_IMPL( X, Y )
#include "PhysicsTypes.inl"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// struct Mat3x2 mult_3x4_4x2( struct Mat3x4 lhs, struct Mat4x2 rhs )
// {
//     struct Mat3x2 m;

//     float out[2][3] = {0};
//     float lhs_trans[3][4] = {0};

//     transpose_impl( (float*)lhs_trans, (float*)lhs.data, 3, 4 );

//     for( uint32_t k = 0; k < 2; k++ )
//         for( uint32_t j = 0; j < 3; j++ )
//             for( uint32_t i = 0; i < 4; i++ )
//                 out[k][j] += lhs_trans[j][i] * rhs.data[k][i];

//     memcpy( m.data, out, sizeof( float ) * 3 * 2 );

//     return m;
// }

#define MULT_MAT_IMPL( X, Y, Z )                                              \
    struct Mat##X##x##Z mult_##X##x##Y##_##Y##x##Z( struct Mat##X##x##Y lhs,  \
                                                    struct Mat##Y##x##Z rhs ) \
    {                                                                         \
        struct Mat##X##x##Z m;                                                \
                                                                              \
        float out[Z][X] = {0};                                                \
        float lhs_trans[X][Y] = {0};                                          \
                                                                              \
        transpose_impl( (float*)lhs_trans, (float*)lhs.data, X, Y );          \
                                                                              \
        for( uint32_t k = 0; k < Z; k++ )                                     \
            for( uint32_t j = 0; j < X; j++ )                                 \
                for( uint32_t i = 0; i < Y; i++ )                             \
                    out[k][j] += lhs_trans[j][i] * rhs.data[k][i];            \
                                                                              \
        memcpy( m.data, out, sizeof( float ) * X * Z );                       \
                                                                              \
        return m;                                                             \
    }

#define MAT_OP_TYPES( X, Y, Z ) MULT_MAT_IMPL( X, Y, Z )
#include "PhysicsTypes.inl"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#define MULT_MAT_VEC_IMPL( X, Y )                                        \
    struct Vec##X##f mult_##X##x##Y##v( struct Mat##X##x##Y m,           \
                                        struct Vec##Y##f v )             \
    {                                                                    \
        struct Vec##X##f result = {0};                                   \
                                                                         \
        float trans_mat[X][Y] = {0};                                     \
        transpose_impl( (float*)trans_mat, (const float*)m.data, X, Y ); \
                                                                         \
        for( uint32_t i = 0; i < X; i++ )                                \
            for( uint32_t j = 0; j < Y; j++ )                            \
                result.data[i] += trans_mat[i][j] * v.data[j];           \
                                                                         \
        return result;                                                   \
    }

#define MAT_TYPES( X, Y ) MULT_MAT_VEC_IMPL( X, Y )
#include "PhysicsTypes.inl"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

struct Mat4x4 translate_4x4( struct Mat4x4 m, struct Vec3f v )
{
    return ( struct Mat4x4 ){{
        {m.data[0][0], m.data[0][1], m.data[0][2], m.data[0][3]},
        {m.data[1][0], m.data[1][1], m.data[1][2], m.data[1][3]},
        {m.data[2][0], m.data[2][1], m.data[2][2], m.data[2][3]},
        {m.data[3][0] + v.x,
         m.data[3][1] + v.y,
         m.data[3][2] + v.z,
         m.data[3][3]},
    }};
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

struct Mat4x4 scale_4x4( struct Mat4x4 m, struct Vec3f v )
{
    return ( struct Mat4x4 ){{
        {m.data[0][0] * v.x, m.data[0][1], m.data[0][2], m.data[0][3]},
        {m.data[1][0], m.data[1][1] * v.y, m.data[1][2], m.data[1][3]},
        {m.data[2][0], m.data[2][1], m.data[2][2] * v.z, m.data[2][3]},
        {m.data[3][0], m.data[3][1], m.data[3][2], m.data[3][3]},
    }};
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

struct Mat3x3 extract_3x3( struct Mat4x4 m )
{
    return ( struct Mat3x3 ){{
        {m.data[0][0], m.data[0][1], m.data[0][2]},
        {m.data[1][0], m.data[1][1], m.data[1][2]},
        {m.data[2][0], m.data[2][1], m.data[2][2]},
    }};
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

struct Mat4x4 perspective_right_reverse_z( float fovy, float scr_width, float scr_height, float near, float far )
{
    struct Mat4x4 output = ident_m4x4();

    float half_fov = fovy / 2.f; 
    float yscale = cosf( half_fov ) / sin( half_fov );

    output.data[0][0] = yscale * ( scr_width / scr_height );
    output.data[1][1] = yscale;
    output.data[2][2] = -far / ( near - far ) - 1.f;
    output.data[2][3] = -(far * near) / ( near - far );
    output.data[3][2] = -1.f;

    return output;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

struct Mat4x4 view_matrix(  struct Vec3f cam_pos, struct Vec3f cam_up, struct Vec3f cam_forward )
{
    struct Vec3f right = cross_v3f( cam_forward, cam_up );

    return (struct Mat4x4){{
        { right.x, right.y, right.z, 0.f },
        { cam_up.x, cam_up.y, cam_up.z, 0.f },
        { cam_forward.x, cam_forward.y, cam_forward.z, 0.f },
        { cam_pos.x, cam_pos.y, cam_pos.z, 1.f }
    }};
}