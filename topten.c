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

   char trash[300];

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

   fscanf(inFile, "%s", date);
      fscanf(inFile, "%s", state);
      fscanf(inFile, "%d", &newPos);
      fscanf(inFile, "%d", &newTot);
      fscanf(inFile, "%d", &newDeath);
      fscanf(inFile, "%d", &currHos);
      fscanf(inFile, "%d", &currVent);

      if(strcmp(state, inputS) == 0) {
          strcpy(inCoState[i].date,date);
         strcpy(inCoState[i].state,state);
         inCoState[i].newPos = newPos;
         inCoState[i].newTot = newTot;
         inCoState[i].newDeath = newDeath;
         inCoState[i].currHos = currHos;
         inCoState[i].currVent = currVent;
         
         totalPos += inCoState[i].newPos;
         totDea += inCoState[i].newDeath;
         i++;
      }
   }

   fclose(inFile);

   SelectionSortPos(inCoState,i);

   printf("\nDate with most positive case:\n");
   for( j = 0; j < 10; j++) {
      printCaseData(inCoState[i-j-1]);  
   }

   printf("            Total case: %d\n",totalPos);
   printf("           Total death: %d\n",totDea);


   return 0;

}