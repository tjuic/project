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

void SelectionSortCase (Covidcase covidState[], int size) {
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
   Covidcase covidCase[10000];     //unknow max data
   Covidcase inCoState[1000];
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
   
   char garbage[20];
   int garb;
   char trash[300];
   //fscanf(inFile, "%s %s %d %d %d %d %d", garbage, garbage, garb, garb, garb, garb, garb);
   fgets(trash,300,inFile);
   
   printf(". . . .\n");
   
   
   int i = 0;
   int j = 0;
   int count = 0;
   char currS[20];
   int totalPos = 0;
   int totDea = 0;
   
   while(!feof(inFile)){
      // fscanf(inFile, "%s %s %d %d %d %d %d", covidCase[i].date, covidCase[i].state, &covidCase[i].newPos,
                             //&covidCase[i].newTot, &covidCase[i].newDeath, &covidCase[i].currHos, &covidCase[i].currVent);
      fscanf(inFile, "%s", covidCase[i].date);
      fscanf(inFile, "%s", covidCase[i].state);
      fscanf(inFile, "%d", &covidCase[i].newPos);
      fscanf(inFile, "%d", &covidCase[i].newTot);
      fscanf(inFile, "%d", &covidCase[i].newDeath);
      fscanf(inFile, "%d", &covidCase[i].currHos);
      fscanf(inFile, "%d", &covidCase[i].currVent);
      
      if(strcmp(covidCase[i].state, inputS) == 0) {
         //inCoState[j] = covidCase[i];
         
         strcpy(inCoState[j].date,covidCase[i].date);
         strcpy(inCoState[j].state,covidCase[i].state);
         inCoState[j].newPos = covidCase[i].newPos;
         inCoState[j].newTot = covidCase[i].newTot;
         inCoState[j].newDeath = covidCase[i].newDeath;
         inCoState[j].currHos = covidCase[i].currHos;
         inCoState[j].currVent = covidCase[i].currVent;
         
         printf("                   Date: %s\n", inCoState[j].date);
         printf("                  State: %s\n", inCoState[j].state);         
         printf("      New positive test: %d tests\n", inCoState[j].newPos);
         printf("             Total test: %d cases\n", inCoState[j].newTot);
         printf("              New death: %d deaths\n", inCoState[j].newDeath);
         printf(" Currently hospitalized: %d cases\n", inCoState[j].currHos);
         printf("Current on a ventilator: %d cases\n\n", inCoState[j].currVent);
         
         
         
         totalPos += inCoState[j].newPos;
         totDea += inCoState[j].newDeath;
         j++;
         break;
      }
      i++;
   }
   
   fclose(inFile);
   
   //printCaseData(inCoState);
   
   //SelectionSortCase(inCoState,j);
   //printf("\n10 most increase case:\n");
   // for( i = 0; i < 3; i++) {
   //    printPlanetData(exoplanets[i]);  
   // }
//    printf("\n10 most increase case:\n");
//    for( i = 0; i < 10; i++) {
//       printCaseData(inCoState[j-i-1]);  
//    }
   
        //  printf("                   Date: %s\n", inCoState[0].date);
        //  printf("                  State: %s\n", inCoState[0].state);       
        //  printf("      New positive test: %d tests\n", inCoState[0].newPos);
        //  printf("             Total test: %d cases\n", inCoState[0].newTot);
        //  printf("              New death: %d deaths\n", inCoState[0].newDeath);
        //  printf(" Currently hospitalized: %d cases\n", inCoState[0].currHos);
        //  printf("Current on a ventilator: %d cases\n\n", inCoState[0].currVent);
   printf("            Total case: %d\n",totalPos);
   printf("           Total death: %d\n",totDea);
   
   
   
   return 0;
}


