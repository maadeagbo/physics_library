#include <stdio.h>
#include <stdbool.h>
#include "PhysicsStructs.h"
#include "PhysicsInterface.h"

#define TEST_EPS 0.000001f

int main( int argc, char const* argv[] )
{
    printf( "Running math/physics library tests...\n" );

    fputs( "\nVector creation\n", stdout );

    printf( "-- Test #1:: %s\n",
            stringify( ( struct Vec2f ){.x = 1.f} ).buffer );

    printf( "-- Test #2:: %s\n",
            stringify( ( struct Vec3f ){.y = 1.f} ).buffer );

    printf( "-- Test #3:: %s\n",
            stringify( ( struct Vec4f ){.z = 1.f} ).buffer );

    printf( "-- Test #4:: %s\n",
            stringify( ( struct Vec4f ){.data = {[2] = 0.5f}} ).buffer );

    fputs( "\nInterface API tests\n", stdout );

    struct Vec3f test_vectors[] = {
        {.x = 1.f}, {.y = 0.2f, .z = 0.8f}, {.x = 0.1f, .y = 0.4f, .z = 0.5f}};
    const uint32_t test_vectors_count =
        sizeof( test_vectors ) / sizeof( struct Vec3f );

    for( uint32_t i = 0; i < test_vectors_count; i++ )
    {
        printf( "-- Test #%u:: %s\n", i, stringify( test_vectors[i] ).buffer );

        printf( "     Magnitude:: %.5f\n", magnitude_v( test_vectors[i] ) );
        printf( "     Normalize:: %s\n",
                stringify( normalize_v( test_vectors[i] ) ).buffer );

        float mag_norm = magnitude_v( normalize_v( test_vectors[i] ) );
        printf( "     Magnitude (normalized):: %.5f\n", mag_norm );

        assertf( mag_norm > 1.f - TEST_EPS && mag_norm < 1.f + TEST_EPS,
                 "Invalid magnitude (%.5f) for normalized vector",
                 mag_norm );

        // Start testing algebraic identities

        struct Vec3f other = {.x = 0.5f, .y = 1.3f, .z = -3.f};
        struct Vec3f new_val = mult_v( test_vectors[i], 5.f );

        struct Vec3f val1 = add_v( new_val, test_vectors[i] );
        struct Vec3f val2 = add_v( test_vectors[i], new_val );

        assertf( equals_v( val1, val2 ),
                 "Algebraic identity #1 error::\n  %s\n != %s\n",
                 stringify( val1 ).buffer,
                 stringify( val2 ).buffer );

        val1 = add_v( add_v( test_vectors[i], other ), new_val );
        val2 = add_v( test_vectors[i], add_v( new_val, other ) );

        assertf( equals_v( val1, val2 ),
                 "Algebraic identity #2 error::\n  %s\n != %s\n",
                 stringify( val1 ).buffer,
                 stringify( val2 ).buffer );

        val1 = sub_v( test_vectors[i], new_val );
        val2 = add_v( test_vectors[i], mult_v( new_val, -1.f ) );

        assertf( equals_v( val1, val2 ),
                 "Algebraic identity #3 error::\n  %s\n != %s\n",
                 stringify( val1 ).buffer,
                 stringify( val2 ).buffer );

        val2 = mult_v( mult_v( new_val, -1.f ), -1.f );

        assertf( equals_v( new_val, val2 ),
                 "Algebraic identity #4 error::\n  %s\n != %s\n",
                 stringify( val1 ).buffer,
                 stringify( val2 ).buffer );

        val1 = ( struct Vec3f ){.x = 0.f};
        val2 = add_v( new_val, mult_v( new_val, -1.f ) );

        assertf( equals_v( val1, val2 ),
                 "Algebraic identity #5 error::\n  %s\n != %s\n",
                 stringify( val1 ).buffer,
                 stringify( val2 ).buffer );

        val1 = add_v( new_val, ( struct Vec3f ){.x = 0.f} );
        val2 = add_v( ( struct Vec3f ){.x = 0.f}, new_val );

        assertf( equals_v( val1, val2 ),
                 "Algebraic identity #6 error::\n  %s\n != %s\n",
                 stringify( val1 ).buffer,
                 stringify( val2 ).buffer );

        val1 = ( struct Vec3f ){.x = i * 0.8f, .y = i * 0.45f, .z = 1.f};
        val2 = ( struct Vec3f ){.x = i * 0.34f, .y = i * 0.15f, .z = 1.f};

        float mag1 = magnitude_v( val1 );

        assertf( dot_v( val1, val1 ) >= ( mag1 * mag1 - TEST_EPS ) &&
                     dot_v( val1, val1 ) <= ( mag1 * mag1 + TEST_EPS ),
                 "Algebraic identity #7 error:: %.5f != %.5f\n",
                 dot_v( val1, val1 ),
                 mag1 * mag1 );

        mag1 = dot_v( val2, val1 );
        float mag2 = dot_v( val1, val2 );

        assertf( mag1 >= ( mag2 - TEST_EPS ) && mag1 <= ( mag2 + TEST_EPS ),
                 "Algebraic identity #8 error:: %.5f != %.5f\n",
                 mag1,
                 mag2 );

        mag1 = dot_v( val1, add_v( val2, other ) );
        mag2 = dot_v( val1, val2 ) + dot_v( val1, other );

        assertf( mag1 >= ( mag2 - TEST_EPS ) && mag1 <= ( mag2 + TEST_EPS ),
                 "Algebraic identity #9 error:: %.5f != %.5f\n",
                 mag1,
                 mag2 );

        mag1 = dot_v( mult_v( val1, 2.f ), mult_v( val2, 4.f ) );
        mag2 = dot_v( val1, val2 ) * 2.f * 4.f;

        assertf( mag1 >= ( mag2 - TEST_EPS ) && mag1 <= ( mag2 + TEST_EPS ),
                 "Algebraic identity #10 error:: %.5f != %.5f\n",
                 mag1,
                 mag2 );

        other = cross_v( val1, val2 );
        new_val = mult_v( cross_v( val2, val1 ), -1.f );

        assertf( equals_v( other, new_val ),
                 "Algebraic identity #11 error::\n  %s\n != %s\n",
                 stringify( other ).buffer,
                 stringify( new_val ).buffer );

        new_val = cross_v( val1, val1 );

        assertf( equals_v( new_val, ( struct Vec3f ){0.f} ),
                 "Algebraic identity #12 error::\n  %s\n",
                 stringify( new_val ).buffer );

        other = cross_v( val1, ( struct Vec3f ){0.f} );
        new_val = cross_v( ( struct Vec3f ){0.f}, val1 );

        assertf( equals_v( other, new_val ) &&
                     equals_v( other, ( struct Vec3f ){0.f} ),
                 "Algebraic identity #13 error::\n  %s\n != %s\n",
                 stringify( other ).buffer,
                 stringify( new_val ).buffer );

        mag1 = dot_v( val1, cross_v( val1, val2 ) );
        mag2 = dot_v( val2, cross_v( val1, val2 ) );

        assertf( mag1 >= ( mag2 - TEST_EPS ) && mag1 <= ( mag2 + TEST_EPS ) &&
                     mag1 >= -TEST_EPS && mag1 <= TEST_EPS,
                 "Algebraic identity #14 error::\n  %.5f != %.5f",
                 mag1,
                 mag2 );

        other = mult_v( val2, 3.5f );
        mag1 = dot_v( val1, cross_v( other, val2 ) );
        mag2 = dot_v( val2, cross_v( val1, other ) );

        assertf( mag1 >= ( mag2 - TEST_EPS ) && mag1 <= ( mag2 + TEST_EPS ),
                 "Algebraic identity #15 error::\n  %.5f != %.5f",
                 mag1,
                 mag2 );
    }

    return 0;
}
