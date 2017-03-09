

#include <stdio.h>
#include <pthread.h>

#define TOTAL_PIRATES 1000

struct cave
{
    int pearlsRemain;
    int pearlsMovedOver;
};

void *pirateA();
void *pirateB();
void *pirateC();
void *pirateD();


struct cave piratesNew;

int
main()
{

    piratesNew.pearlsRemain = TOTAL_PIRATES;
    piratesNew.pearlsMovedOver = 0;

     //Creating the thread variable, without this, the entire program will break.
    pthread_t tid;

    //Creating the threads for concurrency
    pthread_setconcurrency(4);

    while(piratesNew.pearlsRemain > 0)
    {
        pthread_create(&tid, NULL, (void *(*)(void *))pirateA, NULL);
        pthread_create(&tid, NULL, (void *(*)(void *))pirateB, NULL);
        pthread_create(&tid, NULL, (void *(*)(void *))pirateC, NULL);
	pthread_create(&tid, NULL, (void *(*)(void *))pirateD, NULL);
    }
    printf( "\nThe total pearls taken by four pirates is (total): %d \n", piratesNew.pearlsMovedOver);

    pthread_exit(0);
}


//Pirate A will take 1/10rd of the pearls each time.
void *pirateA()
{
    int pearlsMoveA = 0;


    if(piratesNew.pearlsRemain > 0)
    {
        pearlsMoveA = (piratesNew.pearlsRemain*10)/100;

        if((piratesNew.pearlsRemain*10)%100 > 0)
            pearlsMoveA = pearlsMoveA+1;

        printf( "\nPirate A has moved %d pearls", pearlsMoveA);
        piratesNew.pearlsRemain = (piratesNew.pearlsRemain - pearlsMoveA);
        piratesNew.pearlsMovedOver = (piratesNew.pearlsMovedOver + pearlsMoveA);
    }

}

//Pirate B will take 1/10th of the pearls each time
void *pirateB()
{
    int pearlsMoveB = 0;


    if(piratesNew.pearlsRemain > 0)
    {
        pearlsMoveB = (piratesNew.pearlsRemain*10)/100;

        if((piratesNew.pearlsRemain*10)%100 > 0)
            pearlsMoveB = pearlsMoveB+1;

        printf( "\nPirate B has moved %d pearls", pearlsMoveB);
        piratesNew.pearlsRemain = (piratesNew.pearlsRemain - pearlsMoveB);
        piratesNew.pearlsMovedOver = piratesNew.pearlsMovedOver + pearlsMoveB;
    }

}

//Pirate C will take 15/100 th of the pearls each time.
void *pirateC()
{
    int pearlsMoveC = 0;


    if(piratesNew.pearlsRemain > 0)
    {
        pearlsMoveC = (piratesNew.pearlsRemain*15)/100;

        if((piratesNew.pearlsRemain*15)%100 > 0)
            pearlsMoveC = pearlsMoveC+1;

        printf( "\nPirates C has taken %d pearls", pearlsMoveC);
        piratesNew.pearlsRemain = (piratesNew.pearlsRemain - pearlsMoveC);
        piratesNew.pearlsMovedOver = piratesNew.pearlsMovedOver + pearlsMoveC;
    }


}
//Pirate D will take 15/100 th of the pearls each time.
void *pirateD()
{
    int pearlsMoveD = 0;


    if(piratesNew.pearlsRemain > 0)
    {
         pearlsMoveD = (piratesNew.pearlsRemain*15)/100;

        if((piratesNew.pearlsRemain*15)%100 > 0)
            pearlsMoveD = pearlsMoveD+1;

        printf( "\nPirates D has taken %d pearls", pearlsMoveD);
        piratesNew.pearlsRemain = (piratesNew.pearlsRemain - pearlsMoveD);
        piratesNew.pearlsMovedOver = piratesNew.pearlsMovedOver + pearlsMoveD;
    }


}
