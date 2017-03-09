#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int Frames = 0,
    refSlength = 0;


struct FrameMFU{// MFU
   int num;
   int tm;
   int f;
};
struct FrameLFU{// LFU
   int num;
   int tm;
   int f;
};

struct FrameElement{// LRU
   int num;
   int tm;
};
struct FrameOptimal{// Optimal
   int num;
   int dist;
};

//Function declarations
void getInput();
void getInputRefStream(int []);
void lru(int []);
void optimal(int []);
void MFU(int []);
void LFU(int []);
int getFrequency(int,int[]);
int main(){

   getInput();
   int refStream[refSlength];
   getInputRefStream(refStream);
   MFU(refStream);
   LFU(refStream);
   lru(refStream);
   optimal(refStream);

   return 0;
}


void getInput(){
   while(1){
      printf("Enter a number(1-8) of frames:");
      scanf("%d", &Frames);

      if(Frames >= 1 && Frames <=8)
         break;
      else
         printf(" Entered Invalid number of frames. Try again.\n\n");
   }

   while(1){
      printf("Enter the length (1 - 30) of reference string to generate:");
      scanf("%d", &refSlength);

      if(refSlength >= 1 && refSlength <= 30)
         break;
      else
         printf("Invalid number of reference(s) to generate. Please retry.\n\n");
	}
}

/*
 * This function takes input stream from the user.
 */
void getInputRefStream(int refStream[]){
   printf("\n Enter reference stream separated with space:\n");

   int i;

   for(i = 0; i < refSlength; i++){
      scanf("%d", &refStream[i]);

   }
   printf("you have entered the below reference stream\n");
 for(i = 0; i < refSlength; i++){

      printf("%d ", refStream[i]);
 }
   printf("\n\n");
}
//the Most Frequently Used page
 //replacement algorithm.

void MFU(int refStream[]){
   int refPtr = 0,
       i,
       frameSize = 0,//keep check if frame is full
       foundFrame,
       numFault = 0,
       clock = 0;

   struct FrameMFU frameSet[Frames];

   printf("\n MFU Algorithm \n");

   while(refPtr < refSlength){
      foundFrame = 0;//boolean
      if(refPtr == 0){//first reference #
         frameSet[frameSize].num = refStream[refPtr];
         frameSet[frameSize].tm = clock++;//get current time
         frameSet[frameSize].f=getFrequency(refPtr,refStream);
         frameSize++;
         numFault++;
         printf("Ref# *%d Not found\n", refStream[refPtr]);
      }
      else{//all other reference #
         for(i = 0; i < frameSize; i++){
            if(frameSet[i].num == refStream[refPtr]){
               foundFrame = 1;
               frameSet[i].tm = clock++;
               frameSet[i].f=getFrequency(refPtr,refStream);
               printf("Ref# %d Found\n", refStream[refPtr]);
               break;
            }
         }

         if(!foundFrame){
            if(frameSize < Frames){
               frameSet[frameSize].num = refStream[refPtr];
               frameSet[frameSize].tm = clock++;
               frameSet[frameSize].f=getFrequency(refPtr,refStream);
               frameSize++;
            }
            else{
                    int mostFrequent=frameSet[0].f;
                    int clk=frameSet[0].tm,index=0;
                for(i = 0; i < Frames; i++){
                  if(frameSet[i].f>mostFrequent){
                     mostFrequent=frameSet[i].f;
                     clk=frameSet[i].tm;
                     index=i;
                    }
                    else if(frameSet[i].f==mostFrequent)
                    {
                        if(frameSet[i].tm<clk)
                        {
                            mostFrequent=frameSet[i].f;
                            clk=frameSet[i].tm;
                            index=i;
                        }
                    }
               }
               frameSet[index].num = refStream[refPtr];
               frameSet[index].tm = clock++;
               frameSet[index].f=getFrequency(refPtr,refStream);

            }

            numFault++;
            printf("Ref# *%d Not Found\n", refStream[refPtr]);

         }
      }

      refPtr++;

      for(i = 0; i < Frames; ++i){
         if(i < frameSize)
            printf("[%d]", frameSet[i].num);
         else
            printf("[ ]");
      }
      printf("\n\n");
   }

   printf("Number of page fault for MFU: %d\n", numFault);
}

//
 //least Frequently Used page
 // replacement algorithm.
 //
void LFU(int refStream[]){
   int refPtr = 0,
       i,
       frameSize = 0,
       foundFrame,
       numFault = 0,
       clock = 0;

   struct FrameLFU frameSet[Frames];

   printf("\n LFU Algorithm \n");

   while(refPtr < refSlength){
      foundFrame = 0;
      if(refPtr == 0){
         frameSet[frameSize].num = refStream[refPtr];
         frameSet[frameSize].tm = clock++;
         frameSet[frameSize].f=getFrequency(refPtr,refStream);
         frameSize++;
         numFault++;
         printf("Ref# *%d Not found\n", refStream[refPtr]);
      }
      else{
         for(i = 0; i < frameSize; i++){
            if(frameSet[i].num == refStream[refPtr]){
               foundFrame = 1;
               frameSet[i].tm = clock++;
               frameSet[i].f=getFrequency(refPtr,refStream);
               printf("Ref# %d Found\n", refStream[refPtr]);
               break;
            }
         }

         if(!foundFrame){
            if(frameSize < Frames){
               frameSet[frameSize].num = refStream[refPtr];
               frameSet[frameSize].tm = clock++;
               frameSet[frameSize].f=getFrequency(refPtr,refStream);
               frameSize++;
            }
            else{
                    int leastFrequent=frameSet[0].f;
                    int clk=frameSet[0].tm,index=0;
                for(i = 0; i < Frames; i++){
                  if(frameSet[i].f<leastFrequent){
                     leastFrequent=frameSet[i].f;
                     clk=frameSet[i].tm;
                     index=i;
                    }
                    else if(frameSet[i].f==leastFrequent)
                    {
                        if(frameSet[i].tm<clk)
                        {
                            leastFrequent=frameSet[i].f;
                            clk=frameSet[i].tm;
                            index=i;
                        }
                    }
               }
               frameSet[index].num = refStream[refPtr];
               frameSet[index].tm = clock++;
               frameSet[index].f=getFrequency(refPtr,refStream);

            }

            numFault++;
            printf("Ref# *%d Not Found\n", refStream[refPtr]);

         }
      }

      refPtr++;

      for(i = 0; i < Frames; ++i){
         if(i < frameSize)
            printf("[%d]", frameSet[i].num);
         else
            printf("[ ]");
      }
      printf("\n\n");
   }

   printf(" page faults of LFU: %d\n", numFault);
}


//optimal algorithm

void optimal(int refStream[]){
   int refPtr = 0,
	   i,
	   k,
	   frameSize = 0,
	   foundFrame,
	   numFault = 0;

   struct FrameOptimal frame[Frames];

   printf("\n Optimal Algorithm \n");

   while(refPtr < refSlength){
      foundFrame = 0;

      if(refPtr == 0){
         frame[0].num = refStream[refPtr];
         frame[0].dist = 0;
         ++frameSize;
         ++numFault;
         foundFrame = 1;
         printf("Ref# *%d Not Found\n", refStream[refPtr]);
      }
      else{
         for(i = 0; i < frameSize; ++i){
            if(frame[i].num == refStream[refPtr]){
               foundFrame = 1;
               printf("Ref# %d Found\n", refStream[refPtr]);
            }
         }
      }

      if(!foundFrame){
         if(frameSize < Frames){
            frame[frameSize].num = refStream[refPtr];
            frame[frameSize].dist = 0;
            ++frameSize;

         }
         else if(frameSize == Frames){
            if((refPtr + 1) < refSlength){
               for(i = 0; i < frameSize; ++i){
                  for(k = (refPtr + 1); k < refSlength; ++k){
                     if(frame[i].num == refStream[k]){
                        frame[i].dist = k;
                        break;
                     }
                     else
                        frame[i].dist = refSlength;
                  }
               }
            }

            int temp = 0;
            for(i = 1; i < frameSize; ++i){
               if(frame[temp].dist < frame[i].dist)
                  temp = i;
            }

            frame[temp].num = refStream[refPtr];
         }

         ++numFault;
         printf("Ref# *%d  Not Found\n", refStream[refPtr]);
      }

      ++refPtr;


      for(i = 0; i < Frames; ++i){
         if(i < frameSize)
            printf("[%d]", frame[i].num);
         else
            printf("[ ]");
      }
      printf("\n\n");
   }

   printf("page faults of Optimal: %d\n", numFault);
}

 //Least Recently Used page

void lru(int refStream[]){
   int refPtr = 0,
       i,
       frameSize = 0,
       foundFrame,
       numFault = 0,
       clock = 0;

   struct FrameElement frame[Frames];

   printf("\n LRU Algorithm \n");

   while(refPtr < refSlength){
      foundFrame = 0;

      if(refPtr == 0){
         frame[frameSize].num = refStream[refPtr];
         frame[frameSize].tm = clock++;
         frameSize++;
         numFault++;
         printf("Ref# *%d Not found \n", refStream[refPtr]);
      }
      else{
         for(i = 0; i < frameSize; i++){
            if(frame[i].num == refStream[refPtr]){
               foundFrame = 1;
               frame[i].tm = clock++;
               printf("Ref# %d Found\n", refStream[refPtr]);
               break;
            }
         }

         if(!foundFrame){
            if(frameSize < Frames){
               frame[frameSize].num = refStream[refPtr];
               frame[frameSize].tm = clock++;
               frameSize++;
            }
            else{
               struct FrameElement temp = frame[0];
               int replace = 0;

               for(i = 1; i < frameSize; ++i){
                  if(temp.tm > frame[i].tm){
                     temp = frame[i];
                     replace = i;
                  }
               }
               frame[replace].num = refStream[refPtr];
               frame[replace].tm = clock++;
            }

            numFault++;
            printf("Ref# *%d Not Found\n", refStream[refPtr]);

         }
      }

      refPtr++;
      for(i = 0; i < Frames; i++){
         if(i < frameSize)
            printf("[%d]", frame[i].num);
         else
            printf("[ ]");
      }
      printf("\n\n");
   }

   printf("Number of page fault of LRU: %d\n", numFault);
}




int getFrequency(int refPtr,int refStream[])
{
    int f=0,i;
    for(i=0;i<=refPtr;i++)
    {
        if(refStream[i]==refStream[refPtr])
        {
            f=f+1;
        }
    }
    return f;
}
