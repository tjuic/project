#include <stdio.h>
#include <stdbool.h>
#include <string.h>
typedef struct Covidcase_struct {
   char date[50];
   char state[50];
   int  newPos;
   int  newTot;
   int  newDeath;
   int  currHos;
   int  currVent;
} Covidcase;
void SelectionSortPos (Covidcase covidState[], int size) {
   int i;
   int j;
   int indexSmallest;
   Covidcase temp;
   
   for (i = 0; i < size - 1; i++) {
      indexSmallest = i;
      for(j = i + 1; j < size; j++) {
         
         if (covidState[j].newPos < covidState[indexSmallest].newPos ) {
            indexSmallest = j;
         }
      }
      
      temp = covidState[i];
      covidState[i] = covidState[indexSmallest];
      covidState[indexSmallest] = temp;
   }
}
void printCaseData (Covidcase caseC) {
   printf("                   Date: %s\n", caseC.date);
   printf("                  State: %s\n", caseC.state);          
   printf("      New positive test: %d tests\n", caseC.newPos);
   printf("             Total test: %d cases\n", caseC.newTot);
   printf("              New death: %d deaths\n", caseC.newDeath);
   printf(" Currently hospitalized: %d cases\n", caseC.currHos);
   printf("Current on a ventilator: %d cases\n\n", caseC.currVent);
   return;
}   

void printStar (Covidcase covidState[], int totalPos) {
   int i;
   printf("%s: ", covidState[0].state);
   for(i = 0; i < totalPos/50000 ; i++) {
      printf("* ");
   }
   printf("\n");
}

int main() {
   
   FILE* inFile = NULL;
   //Covidcase covidCase[10000];     //unknow max data
   Covidcase inCoState[6000];
   int ns;
   char inputS[10];
   
   printf("COVID-19 cases of the US by states and territories\n");
   // printf("How many states or territories would you want to analyze, max of 56\n");
   // printf("(in alphabetical order):\n");        //i.e. CA): 
   // scanf("%d",&ns);
   
   printf("Which state or territory data you would wasnt to anlyze (i.e. CA):\n");
   scanf("%s",inputS);
   


   inFile = fopen("COVID19USdata_2020_2021.txt", "r");
   if(inFile == NULL) {
      printf("No Data Available.\n");
      return -1;  //file open error
   }
   // if(inFile == NULL) {
   //    printf("No Data Available.\n");
   //    return -1;  //file open error          //not needed, one file need
   // }

   char garbage[20];
   int garb;
   char trash[300];
   //fscanf(inFile, "%s %s %d %d %d %d %d", garbage, garbage, garb, garb, garb, garb, garb);
   fgets(trash,300,inFile);

   printf(". . . .\n");
   
   
   int i = 0;
   int j = 0;
   int newPos, newTot, newDeath, currHos, currVent;
   char date[20], state[20];
   char currS[20];
   int totalPos = 0;
   int totDea = 0;

   while(!feof(inFile)){
      // fscanf(inFile, "%s %s %d %d %d %d %d", covidCase[i].date, covidCase[i].state, &covidCase[i].newPos,
                             //&covidCase[i].newTot, &covidCase[i].newDeath, &covidCase[i].currHos, &covidCase[i].currVent);

      fscanf(inFile, "%s", date);
      fscanf(inFile, "%s", state);
      fscanf(inFile, "%d", &newPos);
      fscanf(inFile, "%d", &newTot);
      fscanf(inFile, "%d", &newDeath);
      fscanf(inFile, "%d", &currHos);
      fscanf(inFile, "%d", &currVent);

      if(strcmp(state, inputS) == 0) {
         //inCoState[j] = covidCase[i];

         strcpy(inCoState[i].date,date);
         strcpy(inCoState[i].state,state);
         inCoState[i].newPos = newPos;
         inCoState[i].newTot = newTot;
         inCoState[i].newDeath = newDeath;
         inCoState[i].currHos = currHos;
         inCoState[i].currVent = currVent;

        //  printf("                   Date: %s\n", inCoState[j].date);
        //  printf("                  State: %s\n", inCoState[j].state);         
        //  printf("      New positive test: %d tests\n", inCoState[j].newPos);
        //  printf("             Total test: %d cases\n", inCoState[j].newTot);
        //  printf("              New death: %d deaths\n", inCoState[j].newDeath);     //this only works
        //  printf(" Currently hospitalized: %d cases\n", inCoState[j].currHos);
        //  printf("Current on a ventilator: %d cases\n\n", inCoState[j].currVent);



         totalPos += inCoState[i].newPos;
         totDea += inCoState[i].newDeath;
         i++;
         //break;
      }
   }

   fclose(inFile);

   //printCaseData(inCoState);

   SelectionSortPos(inCoState,i);
   //printf("\n10 most increase case:\n");
   // for( i = 0; i < 3; i++) {
   //    printPlanetData(exoplanets[i]);  
   // }
   printf("\nDate with most positive case:\n");
   for( j = 0; j < 10; j++) {
      printCaseData(inCoState[i-j-1]);  
   }

   //       printf("                   Date: %s\n", inCoState[i-1].date);
   //       printf("                  State: %s\n", inCoState[i-1].state);       
   //       printf("      New positive test: %d tests\n", inCoState[i-1].newPos);
   //       printf("             Total test: %d cases\n", inCoState[i-1].newTot);
   //       printf("              New death: %d deaths\n", inCoState[i-1].newDeath);     //this only works
   //       printf(" Currently hospitalized: %d cases\n", inCoState[i-1].currHos);
   //       printf("Current on a ventilator: %d cases\n\n", inCoState[i-1].currVent);
   // printf("            Total case: %d\n",totalPos);
   // printf("           Total death: %d\n",totDea);



   printf("            Total case: %d\n",totalPos);
   printf("           Total death: %d\n",totDea);

    printStar(inCoState, totalPos);

   return 0;
}

