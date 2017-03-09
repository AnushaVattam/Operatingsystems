#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lessThan ( char first[], char second[] );
void swap ( char arr[20][30], int first, int second );

main()
{
   char names[20][30];
   char name[30];
   int length, i, j, k;
   int count = 0;

   length = scanf ( "%s", name );

   while ( length == 1 )
   {
      strcpy ( names[count], name );
      count++;

      length = scanf ( "%s", name );
   }

   for ( i = 1; i < count; i++ ) // insertion sort!
   {

      for ( j = i - 1; j >= 0; j-- )
      {
         if ( lessThan ( names[j + 1], names[j] ) )
            swap ( names, j + 1, j );
         else
            break;
      }
   }

   printf ( "\n" );

   for ( i = 0; i < count; i++ )
      printf ( "%s\n", names[i] );

   exit ( 0 );
}

int lessThan ( char first[], char second[] )
{
   int i;
   int less = 0;

   for ( i = 0; i < 29; i++ )
   {
      if ( ( first[i] | 0x20 ) < ( second[i] | 0x20 ) )
      {
         less = 1;
         break;
      }
      else if ( ( first[i] | 0x20 ) > ( second[i] | 0x20 ) )
         break;
      else 
      {	// each is the same letter, checking for upper with lower
         if ( first[i] > second[i] ) // lowercase has higher value
         {
            less = 1;
            break;
         }
         else if ( first[i] < second[i] )
            break;
      }
   }

   return less;
}

void swap ( char arr[20][30], int first, int second )
{
   char temp[30];

   strcpy ( temp, arr[first] );
   strcpy ( arr[first], arr[second] );
   strcpy ( arr[second], temp );
}
