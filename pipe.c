#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main ()
{
   int fd[2];
   int pid;
   pipe ( fd );
   pid = fork();

   if ( pid > 0 )
   { // parent
      close ( 1 );
      dup ( fd[1] );
      close ( fd[1] );
      close ( fd[0] );

      execlp ( "./find", "./find", NULL );
   }
   else if ( pid == 0 )
   { // child
      close ( 0 );
      dup ( fd[0] );
      close ( fd[0] );
      close ( fd[1] );

      execlp ( "./sort", "./sort", NULL );
   }
   else
   {
      perror ( "An error has occured in the fork." );
      exit ( 1 );
   }
   exit ( 0 );
}
