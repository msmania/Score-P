#include <stdlib.h>

#include "bar.h"

#include <foo.h>

void
fn_2( void )
{
    struct some_struct* s;
    s = fn_1_new();
    fn_3_set( s, 123 );
    int a = fn_2_get( s );
    ( void )a;
    free( s );
}
