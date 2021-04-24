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
   Covidcase covidCase[500];     //unknow max data
   Covidcase inCoState[500];
   Covidcase tempS[500];   // emp = {0};
   
   int ns;
   char inputS[10];
   char trash[300];
   int i = 0;
   int j = 0;
   int totalPos = 0;
   int newPos, newTot, newDeath, currHos, currVent;
   char date[20], state[20], currS[20];

   printf("COVID-19 cases of the US by states and territories\n\n");
   //printf("How many states or territories would you want to analyze, max of 56\n");
   //printf("(in alphabetical order):\n");        //i.e. CA): 
   //scanf("%d",&ns);
   printf("Covid cases by state and terrotories (* represent a 1000 cases): \n");

   inFile = fopen("COVID19USdata_2020_2021.txt", "r");

   fgets(trash,300,inFile);

   for(i = 0; i < 55; i++) {
   //while(!feof(inFile)) {   
      //j = 0;
      //totalPos = 0;
      //covidCase[j] = tempS[0];
      //j++;
      fscanf(inFile, "%s", date);
      fscanf(inFile, "%s", state);
      fscanf(inFile, "%d", &newPos);
      fscanf(inFile, "%d", &newTot);
      fscanf(inFile, "%d", &newDeath);
      fscanf(inFile, "%d", &currHos);
      fscanf(inFile, "%d", &currVent);
      totalPos += newPos;
      strcpy(currS, state);
      //j++;
      while((strcmp(state, currS) == 0) && currS != NULL){
         fscanf(inFile, "%s", date);
         fscanf(inFile, "%s", state);
         fscanf(inFile, "%d", &newPos);
         fscanf(inFile, "%d", &newTot);
         fscanf(inFile, "%d", &newDeath);
         fscanf(inFile, "%d", &currHos);
         fscanf(inFile, "%d", &currVent);

         totalPos += newPos;
         //j++;
      }
      totalPos += - newPos;
      printStar(currS, totalPos);

      totalPos = 0;
      totalPos = newPos;
      //tempS[0] = covidCase[j-1];

      // j = 0;
      // while(strcmp(covidCase[j].state, currS) == 0) {
      //    covidCase[j] = emp;
      //    j++;
      // }
      // totalPos = 0;
   //}
   }

   while(!feof(inFile)) {
      fscanf(inFile, "%s", date);
      fscanf(inFile, "%s", state);
      fscanf(inFile, "%d", &newPos);
      fscanf(inFile, "%d", &newTot);
      fscanf(inFile, "%d", &newDeath);
      fscanf(inFile, "%d", &currHos);
      fscanf(inFile, "%d", &currVent);

      totalPos += newPos;

   }

   printStar(state, totalPos);
   printf("\n\n");

   fclose(inFile);
   
   //program after histogram -----------------------------------
   //inFile = NULL;
   //fseek(inFile, 81, 81);

   printf("Which state or territory data you would wasnt to anlyze (i.e. CA):\n");
   scanf("%s",inputS);
   
   
   
   inFile = fopen("COVID19USdata_2020_2021.txt", "r");
   // if(inFile == NULL) {
   //    printf("No Data Available.\n");
   //    return -1;  //file open error          //not needed, one file need
   // }
   
   //char trash[300];
   fgets(trash,300,inFile);
   
   printf(". . . .\n");
   
   
   i = 0;
   j = 0;
   newPos = 0, newTot = 0, newDeath = 0, currHos = 0, currVent = 0;
   strcpy(date, NULL);
   strcpy(state, NULL);
   totalPos = 0;
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


