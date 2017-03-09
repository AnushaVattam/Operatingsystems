#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main ()
{
   char stocknames[20][30];
   float stockvalues[20];
   int length, i;
   int count = 0;
   char TempStockName[30];
   float TempStockValue;
   
   length = scanf ( "%s %f", TempStockName, &TempStockValue );

   while ( length == 2 )
   {
      strcpy ( stocknames[count], TempStockName );
      stockvalues[count] = TempStockValue;

      count++;

      length = scanf ( "%s %f", TempStockName, &TempStockValue );
   }

   printf ( "\n" );

   for ( i = 0; i < count; i++ )
   {
      if ( stockvalues[i] < 10 )
         printf ( "%s\n", stocknames[i] );
   }

   exit ( 0 );
}
