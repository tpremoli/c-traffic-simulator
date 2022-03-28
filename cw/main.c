#include <runSimulations.h>

int main()
{
   float leftFlow;
   float rightFlow;
   int leftTime;
   int rightTime;

   printf("Input left traffic flow (float range 0-1):");
   if (scanf("%f",&leftFlow) != 1  || leftFlow > 1 || leftFlow < 0)
   {
      printf("Incorrect input!\n");
      return EXIT_FAILURE;
   }
   printf("Input right traffic flow (float range 0-1):");
   if (scanf("%f",&rightFlow) != 1  || rightFlow > 1 || rightFlow < 0)
   {
      printf("Incorrect input!\n");
      return EXIT_FAILURE;
   }
   printf("Input left traffic light time (int > 0):");
   if (scanf("%d",&leftTime) != 1  || leftTime < 0)
   {
      printf("Incorrect input!\n");
      return EXIT_FAILURE;
   }
   printf("Input right traffic light time (int > 0):");
   if (scanf("%d",&rightTime) != 1  || rightTime < 0)
   {
      printf("Incorrect input!\n");
      return EXIT_FAILURE;
   }
   runSimulations(leftFlow, rightFlow, leftTime, rightTime);

   return 0;
}

