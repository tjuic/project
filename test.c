#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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
   
   for (i = 0; i < size - 1; i++) {    //one more than the size
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

void printStar (char covidState[20], int totalPos) {
   int i;
   printf("%s: ", covidState);
   for(i = 0; i < totalPos/50000 ; i++) {
      printf("* ");
   }
   printf(" %d",totalPos);
   printf("\n");
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

int main() {
   
   
   FILE* inFile = NULL;
   Covidcase inCoState[400];
   
   int ns;
   char inputS[10];
   char trash[300];
   int i = 0;
   int j = 0;
   int totalPos = 0;
   int newPos, newTot, newDeath, currHos, currVent;
   char date[20], state[20], currS[20];

   printf("COVID-19 cases of the US by states and territories\n\n");
   printf("Covid cases by state and terrotories (* represent a 50000 cases): \n");

   inFile = fopen("COVID19USdata_2020_2021.txt", "r");

   fgets(trash,300,inFile);

   for(i = 0; i < 55; i++) {

      fscanf(inFile, "%s", date);
      fscanf(inFile, "%s", state);
      fscanf(inFile, "%d", &newPos);
      fscanf(inFile, "%d", &newTot);
      fscanf(inFile, "%d", &newDeath);
      fscanf(inFile, "%d", &currHos);
      fscanf(inFile, "%d", &currVent);
      totalPos += newPos;

      strcpy(currS, state);
      
      while((strcmp(state, currS) == 0) && currS != NULL){
         fscanf(inFile, "%s", date);
         fscanf(inFile, "%s", state);
         fscanf(inFile, "%d", &newPos);
         fscanf(inFile, "%d", &newTot);
         fscanf(inFile, "%d", &newDeath);
         fscanf(inFile, "%d", &currHos);
         fscanf(inFile, "%d", &currVent);

         totalPos += newPos;
      }
      totalPos += - newPos;
      printStar(currS, totalPos);

      totalPos = 0;
      totalPos = newPos;
   }

   while(!feof(inFile)) {
      fscanf(inFile, "%s", date);
      fscanf(inFile, "%s", state);
      fscanf(inFile, "%d", &newPos);
      fscanf(inFile, "%d", &newTot);            //the last one
      fscanf(inFile, "%d", &newDeath);
      fscanf(inFile, "%d", &currHos);
      fscanf(inFile, "%d", &currVent);

      totalPos += newPos;

   }

   printStar(state, totalPos);
   printf("\n\n");

   //fclose(inFile);

   //program after histogram -----------------------------------

   printf("Which state or territory data you would wasnt to anlyze (i.e. CA):\n");
   scanf("%s",inputS);
   
   
   int totalDea;
   
   printf("\n. . . .\n");
   
   while(strcmp(inputS, "q") != 0) {
      //inFile = fopen("COVID19USdata_2020_2021.txt", "r");
      rewind(inFile);
      fgets(trash,300,inFile);
      i = 0;
      totalDea = 0;
   
      while(!feof(inFile)){
   
         fscanf(inFile, "%s", date);
         fscanf(inFile, "%s", state);
         fscanf(inFile, "%d", &newPos);
         fscanf(inFile, "%d", &newTot);
         fscanf(inFile, "%d", &newDeath);
         fscanf(inFile, "%d", &currHos);
         fscanf(inFile, "%d", &currVent);
      
         if(strcmp(state, inputS) == 0) {
         
            strcpy(inCoState[i].date, date);
            strcpy(inCoState[i].state, state);
            inCoState[i].newPos = newPos;
            inCoState[i].newTot = newTot;
            inCoState[i].newDeath = newDeath;
            inCoState[i].currHos = currHos;
            inCoState[i].currVent = currVent;
         
            totalPos += inCoState[i].newPos;
            totalDea += inCoState[i].newDeath;
            i++;
         }
      }
   
      //fclose(inFile);
   
      SelectionSortPos(inCoState,i);

      printf("Date with most positive case:\n");
      for( j = 0; j < 10; j++) {
         printCaseData(inCoState[i-j-1]);  
      }
   
      printf("            Total case: %d\n",totalPos);
      printf("           Total death: %d\n\n",totalDea);


      printf("Which state or territory data you would wasnt to anlyze (i.e. CA)\n");
      printf("Enter 'q' to quit:\n");
      scanf("%s",inputS);

   }
   fclose(inFile);

return 0;
}




