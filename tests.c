//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "PhysicsStructs.h"
#include "PhysicsInterface.h"

#define TEST_EPS 0.000001f

int main( int argc, char const* argv[] )
{
    (void)argc;
    (void)argv;

    printf( "Running math/physics library tests...\n" );

    fputs( "\nVector creation\n", stdout );

    printf( "-- Test #1:: %s\n",
            stringify_v2f( ( struct Vec2f ){.x = 1.f} ).buffer );

    printf( "-- Test #2:: %s\n",
            stringify_v3f( ( struct Vec3f ){.y = 1.f} ).buffer );

    printf( "-- Test #3:: %s\n",
            stringify_v4f( ( struct Vec4f ){.z = 1.f} ).buffer );

    printf( "-- Test #4:: %s\n",
            stringify_v4f( ( struct Vec4f ){.data = {[2] = 0.5f}} ).buffer );

    fputs( "\nInterface API tests\n", stdout );

    struct Vec3f test_vectors[] = {
        {.x = 1.f}, {.y = 0.2f, .z = 0.8f}, {.x = 0.1f, .y = 0.4f, .z = 0.5f}};
    const uint32_t test_vectors_count =
        sizeof( test_vectors ) / sizeof( struct Vec3f );

    for( uint32_t i = 0; i < test_vectors_count; i++ )
    {
        printf(
            "-- Test #%u:: %s\n", i, stringify_v3f( test_vectors[i] ).buffer );

        printf( "     Magnitude:: %.5f\n", magnitude_v3f( test_vectors[i] ) );
        printf( "     Normalize:: %s\n",
                stringify_v3f( normalize_v3f( test_vectors[i] ) ).buffer );

        float mag_norm = magnitude_v3f( normalize_v3f( test_vectors[i] ) );
        printf( "     Magnitude (normalized):: %.5f\n", mag_norm );

        assertf( mag_norm > 1.f - TEST_EPS && mag_norm < 1.f + TEST_EPS,
                 "Invalid magnitude (%.5f) for normalized vector",
                 mag_norm );

        // Start testing algebraic identities

        struct Vec3f other = {.x = 0.5f, .y = 1.3f, .z = -3.f};
        struct Vec3f new_val = mult_v3f( test_vectors[i], 5.f );

        struct Vec3f val1 = add_v3f( new_val, test_vectors[i] );
        struct Vec3f val2 = add_v3f( test_vectors[i], new_val );

        assertf( equals_v3f( val1, val2 ),
                 "Algebraic identity #1 error::\n  %s\n != %s\n",
                 stringify_v3f( val1 ).buffer,
                 stringify_v3f( val2 ).buffer );

        val1 = add_v3f( add_v3f( test_vectors[i], other ), new_val );
        val2 = add_v3f( test_vectors[i], add_v3f( new_val, other ) );

        assertf( equals_v3f( val1, val2 ),
                 "Algebraic identity #2 error::\n  %s\n != %s\n",
                 stringify_v3f( val1 ).buffer,
                 stringify_v3f( val2 ).buffer );

        val1 = sub_v3f( test_vectors[i], new_val );
        val2 = add_v3f( test_vectors[i], mult_v3f( new_val, -1.f ) );

        assertf( equals_v3f( val1, val2 ),
                 "Algebraic identity #3 error::\n  %s\n != %s\n",
                 stringify_v3f( val1 ).buffer,
                 stringify_v3f( val2 ).buffer );

        val2 = mult_v3f( mult_v3f( new_val, -1.f ), -1.f );

        assertf( equals_v3f( new_val, val2 ),
                 "Algebraic identity #4 error::\n  %s\n != %s\n",
                 stringify_v3f( val1 ).buffer,
                 stringify_v3f( val2 ).buffer );

        val1 = ( struct Vec3f ){.x = 0.f};
        val2 = add_v3f( new_val, mult_v3f( new_val, -1.f ) );

        assertf( equals_v3f( val1, val2 ),
                 "Algebraic identity #5 error::\n  %s\n != %s\n",
                 stringify_v3f( val1 ).buffer,
                 stringify_v3f( val2 ).buffer );

        val1 = add_v3f( new_val, ( struct Vec3f ){.x = 0.f} );
        val2 = add_v3f( ( struct Vec3f ){.x = 0.f}, new_val );

        assertf( equals_v3f( val1, val2 ),
                 "Algebraic identity #6 error::\n  %s\n != %s\n",
                 stringify_v3f( val1 ).buffer,
                 stringify_v3f( val2 ).buffer );

        val1 = ( struct Vec3f ){.x = i * 0.8f, .y = i * 0.45f, .z = 1.f};
        val2 = ( struct Vec3f ){.x = i * 0.34f, .y = i * 0.15f, .z = 1.f};

        float mag1 = magnitude_v3f( val1 );

        assertf( dot_v3f( val1, val1 ) >= ( mag1 * mag1 - TEST_EPS ) &&
                     dot_v3f( val1, val1 ) <= ( mag1 * mag1 + TEST_EPS ),
                 "Algebraic identity #7 error:: %.5f != %.5f\n",
                 dot_v3f( val1, val1 ),
                 mag1 * mag1 );

        mag1 = dot_v3f( val2, val1 );
        float mag2 = dot_v3f( val1, val2 );

        assertf( mag1 >= ( mag2 - TEST_EPS ) && mag1 <= ( mag2 + TEST_EPS ),
                 "Algebraic identity #8 error:: %.5f != %.5f\n",
                 mag1,
                 mag2 );

        mag1 = dot_v3f( val1, add_v3f( val2, other ) );
        mag2 = dot_v3f( val1, val2 ) + dot_v3f( val1, other );

        assertf( mag1 >= ( mag2 - TEST_EPS ) && mag1 <= ( mag2 + TEST_EPS ),
                 "Algebraic identity #9 error:: %.5f != %.5f\n",
                 mag1,
                 mag2 );

        mag1 = dot_v3f( mult_v3f( val1, 2.f ), mult_v3f( val2, 4.f ) );
        mag2 = dot_v3f( val1, val2 ) * 2.f * 4.f;

        assertf( mag1 >= ( mag2 - TEST_EPS ) && mag1 <= ( mag2 + TEST_EPS ),
                 "Algebraic identity #10 error:: %.5f != %.5f\n",
                 mag1,
                 mag2 );

        other = cross_v3f( val1, val2 );
        new_val = mult_v3f( cross_v3f( val2, val1 ), -1.f );

        assertf( equals_v3f( other, new_val ),
                 "Algebraic identity #11 error::\n  %s\n != %s\n",
                 stringify_v3f( other ).buffer,
                 stringify_v3f( new_val ).buffer );

        new_val = cross_v3f( val1, val1 );

        assertf( equals_v3f( new_val, ( struct Vec3f ){0.f} ),
                 "Algebraic identity #12 error::\n  %s\n",
                 stringify_v3f( new_val ).buffer );

        other = cross_v3f( val1, ( struct Vec3f ){0.f} );
        new_val = cross_v3f( ( struct Vec3f ){0.f}, val1 );

        assertf( equals_v3f( other, new_val ) &&
                     equals_v3f( other, ( struct Vec3f ){0.f} ),
                 "Algebraic identity #13 error::\n  %s\n != %s\n",
                 stringify_v3f( other ).buffer,
                 stringify_v3f( new_val ).buffer );

        mag1 = dot_v3f( val1, cross_v3f( val1, val2 ) );
        mag2 = dot_v3f( val2, cross_v3f( val1, val2 ) );

        assertf( mag1 >= ( mag2 - TEST_EPS ) && mag1 <= ( mag2 + TEST_EPS ) &&
                     mag1 >= -TEST_EPS && mag1 <= TEST_EPS,
                 "Algebraic identity #14 error::\n  %.5f != %.5f",
                 mag1,
                 mag2 );

        other = mult_v3f( val2, 3.5f );
        mag1 = dot_v3f( val1, cross_v3f( other, val2 ) );
        mag2 = dot_v3f( val2, cross_v3f( val1, other ) );

        assertf( mag1 >= ( mag2 - TEST_EPS ) && mag1 <= ( mag2 + TEST_EPS ),
                 "Algebraic identity #15 error::\n  %.5f != %.5f",
                 mag1,
                 mag2 );
    }

    fputs( "\nMatrix creation\n\n", stdout );

    struct Mat4x2 test_mat = ( struct Mat4x2 ){.data[0][1] = 0.3f};
    test_mat.data[1][0] = 0.6f;
    test_mat.data[0][3] = 1.f;

    printf( "-- Test #1\n%s\n", stringify_m4x2( test_mat ).buffer );
    printf( "-- Test #1 (transpose)\n%s\n",
            stringify_m2x4( transpose_4x2( test_mat ) ).buffer );
    printf( "-- Test #1 (scalar multiply: 5.f)\n%s\n",
            stringify_m4x2( mult_4x2( test_mat, 5.f ) ).buffer );

    printf( "-- Test #2\n%s\n", stringify_m2x2( ident_m2x2() ).buffer );

    printf( "-- Test #3\n%s\n", stringify_m3x3( ident_m3x3() ).buffer );

    printf( "-- Test #4\n%s\n", stringify_m4x4( ident_m4x4() ).buffer );

    printf( "-- Test #5 (addition)\n%s\n",
            stringify_m4x4( add_4x4( ident_m4x4(), ident_m4x4() ) ).buffer );

    printf( "-- Test #5 (subtraction)\n%s\n",
            stringify_m4x4(
                add_4x4( ident_m4x4(), mult_4x4( ident_m4x4(), -5.f ) ) )
                .buffer );

    fputs( "\nMatrix multiply\n\n", stdout );

    srand( (unsigned)time( 0 ) );

    struct Mat3x4 m34 = {0.f};
    struct Mat4x2 m42 = {0.f};

    for( uint32_t i = 0; i < 4; i++ )
        for( uint32_t j = 0; j < 3; j++ )
            m34.data[i][j] = (float)rand() / (float)RAND_MAX;

    for( uint32_t i = 0; i < 4; i++ )
        for( uint32_t j = 0; j < 2; j++ )
            m42.data[j][i] = (float)rand() / (float)RAND_MAX;

    printf( "-- Matrix A:: %s\n", stringify_m3x4( m34 ).buffer );
    printf( "-- Matrix B:: %s\n", stringify_m4x2( m42 ).buffer );

    printf( "-- Multiplication Result\n%s\n",
            stringify_m3x2( mult_3x4_4x2( m34, m42 ) ).buffer );

    fputs( "\nMatrix inversion & determinant\n", stdout );

    {
        struct Mat2x2 m22;

        for( uint32_t i = 0; i < 2; i++ )
            for( uint32_t j = 0; j < 2; j++ )
                m22.data[j][i] = (float)rand() / (float)RAND_MAX;

        printf( "-- Normal 2x2 \n%s\n", stringify_m2x2( m22 ).buffer );

        printf( "-- Normal 2x2 determinant : %.5f\n", determinant_2x2( m22 ) );

        struct Mat2x2 inv_m22 = inverse_2x2( m22 );
        printf( "-- Inverted 2x2 \n%s\n", stringify_m2x2( inv_m22 ).buffer );

        printf( "-- \nInversion test #1\n%s\n",
                stringify_m2x2( mult_2x2_2x2( m22, inv_m22 ) ).buffer );
    }

    {
        struct Mat3x3 m33;

        for( uint32_t i = 0; i < 3; i++ )
            for( uint32_t j = 0; j < 3; j++ )
                m33.data[j][i] = (float)rand() / (float)RAND_MAX;

        printf( "\n-- Normal 3x3 \n%s\n", stringify_m3x3( m33 ).buffer );

        printf( "-- Normal 3x3 determinant : %.5f\n", determinant_3x3( m33 ) );

        struct Mat3x3 inv_m33 = inverse_3x3( m33 );
        printf( "-- Inverted 3x3 \n%s\n", stringify_m3x3( inv_m33 ).buffer );

        printf( "-- \nInversion test #2\n%s\n",
                stringify_m3x3( mult_3x3_3x3( m33, inv_m33 ) ).buffer );
    }

    {
        struct Mat4x4 m44;

        for( uint32_t i = 0; i < 4; i++ )
            for( uint32_t j = 0; j < 4; j++ )
                m44.data[j][i] = (float)rand() / (float)RAND_MAX;

        printf( "\n-- Normal 4x4 \n%s\n", stringify_m4x4( m44 ).buffer );

        printf( "-- Normal 4x4 determinant : %.5f\n", determinant_4x4( m44 ) );

        struct Mat4x4 inv_m44 = inverse_4x4( m44 );
        printf( "-- Inverted 4x4 \n%s\n", stringify_m4x4( inv_m44 ).buffer );

        printf( "-- \nInversion test #3\n%s\n",
                stringify_m4x4( mult_4x4_4x4( m44, inv_m44 ) ).buffer );
    }

    {
        struct Mat3x4 m34 = {0};
        m34.data[0][0] = 1.f;
        m34.data[1][0] = 1.f;
        m34.data[1][1] = 1.f;
        m34.data[2][2] = 1.f;

        struct Vec4f v4 = {.x = 4.f, .y = 3.f, .z = 2.f, .w = 1.f};
        struct Vec3f result = mult_3x4v( m34, v4 );
        printf( "\nMatrix 3x4 vector multiply\nv: %s\nm: %s\nanswer: %s\n",
                stringify_v4f( v4 ).buffer,
                stringify_m3x4( m34 ).buffer,
                stringify_v3f( result ).buffer );
    }

    {
        struct Mat4x4 m44 = ident_m4x4();
        m44.data[0][3] = 1.f;

        struct Vec4f v4 = {.x = 4.f, .y = 3.f, .z = 2.f, .w = 1.f};
        struct Vec4f result = mult_4x4v( m44, v4 );
        printf( "\nMatrix 4x4 vector multiply\nv: %s\nm: %s\nanswer: %s\n",
                stringify_v4f( v4 ).buffer,
                stringify_m4x4( m44 ).buffer,
                stringify_v4f( result ).buffer );
    }

    fputs( "\nQuaternions\n", stdout );

    {
        struct Quat q = quat_from_euler( deg_to_rad( -90.f ), 0.f, 0.f );
        q = mult_q( q, q );
        struct Vec3f v = {.z = 1.f};

        printf( "\nRotating vector \n%s\nby\n%s\n::\n%s\n",
                stringify_v3f( v ).buffer,
                stringify_quat( q ).buffer,
                stringify_v3f( mult_qv( q, v ) ).buffer );
    }

    {
        struct Quat q1 = quat_from_euler( deg_to_rad( -90.f ), 0.f, 0.f );
        struct Quat q2 = quat_from_euler( 0.f, deg_to_rad( -30.f ), 0.f );
        struct Quat q = mult_q( q1, q2 );

        printf( "\nRotating \n%s\nby\n%s\n::\n%s\n",
                stringify_quat( q1 ).buffer,
                stringify_quat( q2 ).buffer,
                stringify_quat( q ).buffer );
    }

    {
        struct Quat q2 = quat_from_euler( deg_to_rad( -90.f ), 0.f, 0.f );
        struct Quat q1 = quat_from_euler( 0.f, deg_to_rad( -30.f ), 0.f );
        struct Quat q = mult_q( q1, q2 );

        printf( "\nRotating \n%s\nby\n%s\n::\n%s\n",
                stringify_quat( q1 ).buffer,
                stringify_quat( q2 ).buffer,
                stringify_quat( q ).buffer );
    }

    {
        struct Quat q1 =
            quat_from_euler( 0.f, deg_to_rad( 15.f ), deg_to_rad( -50.f ) );
        struct Quat q2 = quat_from_euler( 0.f, deg_to_rad( -30.f ), 0.f );
        struct Quat q = mult_q( q1, q2 );

        printf( "\nRotating \n%s\nby\n%s\n::\n%s\n",
                stringify_quat( q1 ).buffer,
                stringify_quat( q2 ).buffer,
                stringify_quat( q ).buffer );
    }

    return 0;
}
