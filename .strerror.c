#include <stdio.h>
#include <string.h>
 
int main()
{
   int errnum;
 
   for( errnum=0; errnum<39; errnum++ )
     printf( "strerror(%d) = %s\n", errnum, strerror( errnum ) );
 
   return 0;
}
