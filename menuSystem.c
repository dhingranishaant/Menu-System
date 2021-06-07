
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 30
#define fieldLength 200


#define diskFile "diskFile.dat"
#define courseFile "course.txt"

struct db_type
{
   char name[fieldLength];
   int age;
   char course1[fieldLength];
   char course2[fieldLength];
   char status[fieldLength];
 };

struct courseInfo
{ 
  char code [20]; // e.g., EECS2030
  char title [fieldLength];
  char date [20];
  char time_start [20];
  char time_end [20];
  char location [20]; 
};
 
struct courseInfo courseArr[SIZE]; // global variable  array of struc
     
char prompt_menu(void);
void init_list(struct db_type * pArr[]); 
void clearDB(struct db_type * pArr[]);
void init_courseArr(void);

void writeDisk(struct db_type * pArr[]); 
void emptyDisk(void); 
void loadDisk(struct db_type * pArr[]); 

//functions declared to conclude PE2
void displayCourses(void);
void enterNew(struct db_type * pArr[SIZE]);
void displayDB(struct db_type * pArr[]);
void removeRecord (struct db_type * pArr[]);
void swap(struct db_type * pArr[]); 
void sort(struct db_type * pArr[]);
int getSize(struct db_type * pArr[]);

//global variables
//2D array names[][] stores 4 letter XXXX course codes and 2D array namesFull[][] stores EECSXXXX codes. 
char names[SIZE][SIZE];
char namesFull[SIZE][SIZE];
int indexCourseOne[SIZE];
int indexCourseTwo[SIZE];


int main(int argc, char *argv[])
{
    
    struct db_type * db_pArr[SIZE];  // main db storage

    init_list(db_pArr);  // set to NULL
    
    init_courseArr();  // load course from diskfile
    
    char choice;
    for(; ;){
      choice = prompt_menu();
      switch (choice)
      {
         case 'n': enterNew(db_pArr); break;
         case 'd': displayDB(db_pArr); break;
         case 'w': writeDisk(db_pArr);  break;    
         case 'l': loadDisk(db_pArr); break;
         case 's': sort(db_pArr); break;
	   
         case 'c': clearDB(db_pArr); break;  
         case 'e': emptyDisk();break;

         case 'v': displayCourses();break;
         case 'p': swap(db_pArr); break;
         case 'r': removeRecord(db_pArr);break;
         
         case 'q': exit(1); // terminate the whole program
       }
     }
     return 0;
}

void init_list(struct db_type * pArr[]){
  int t;
  for (t=0; t<SIZE; t++)
  { 
     pArr[t]= NULL;
  }
}

void clearDB(struct db_type * pArr[]){
   char c3[3];
   printf("are you sure to clear db? (y) or (n)? ");
 
   fgets(c3,3,stdin);
   
   if(! strcmp(c3, "y\n")){ 
    init_list(pArr);
  }
}


char prompt_menu(void){
  char s[80];
  while(1){
    printf("\n-----------------------------------------------------------------\n");
    printf("|    %-20s","(N)ew record");
    printf("%-20s","(R)emove record");
    printf("Swa(p) records\t|\n");
    printf("|    %-20s","(S)ort database");
    printf("%-20s","(C)lear database");
    printf("(D)isplay db\t|\n");
  
    printf("|    %-20s","(L)oad disk");
    printf("%-20s","(W)rite disk");
    printf("(E)mpty disk\t|\n");
  
    printf("|    %-20s", "(V)iew courses");//|\tSwa(p) record\t(Q)uit\t\t\t\t|\n");
    printf("%-20s","(Q)uit");
    printf("*Case Insensitive*\t|\n");
    printf("-----------------------------------------------------------------\n");
    printf("choose one: ");
  
    fgets(s,50, stdin); // \n added
   
    if (strlen(s) == 2 && strchr("edlsuqrcwnvpr", tolower(*s))) 
       return tolower(*s); // s[0], return the first character of s  
    
    else 
      printf("not a valid input!\n");
 }
}

/* display all or specified course */
/**
* This function is invoked when the user enters 'v' or 'V'. 
* It prints all the courses saved in the database with course details when the user enters 'a' when this
* function is executed, or, it displays a specific course when user enters the course code (e.g. 2031 or EECS2031).
*/
void displayCourses(void){   
 // the provide sample.out uses "%s\t%-40s%-5s %s-%s   %s\n" as formatting string for printing each course info
  char inputArr[10];
  char courseCodesArr[10]; //contains 4 length course codes (e.g. 2031)
  char fullCourseCodesArr[10]; //contains 8 length course codes (e.g. EECS2031)

  printf("course code (or 'a')? ");
  scanf("%s", inputArr);
  int len = strlen(inputArr);
  int counter = 0;
  int result;
  int courseIndex = 0;

  if(inputArr[0] == 'a'){
    printf("=================================================================================\n");
    int indexFound, i;
    for(i=0; i<SIZE; i++){
      if(strcmp(courseArr[i].code, "EECS0000") == 0)
        indexFound = i;
    }
    for(i=0; i<indexFound; i++){
      printf("%s\t%-40s%-5s %s-%s   %s\n",  courseArr[i].code, courseArr[i].title, courseArr[i].date, 
      courseArr[i].time_start, courseArr[i].time_end, courseArr[i].location);
      }
      printf("=================================================================================\n");
    }

  else{
    while(counter < SIZE){
      char * str = courseArr[courseIndex].code;
      if(len == 4){
        strncpy(courseCodesArr, &str[4], 5); //strncpy is used to copy 4 digit code to inputArray from courseArr.
        if(strcmp(inputArr, courseCodesArr) == 1)
          result = 1;
        if(strcmp(inputArr, courseCodesArr) == 0){
          result = 0;
          printf("%s\t%-40s%-5s %s-%s   %s\n",  courseArr[courseIndex].code, courseArr[courseIndex].title, courseArr[courseIndex].date, 
          courseArr[courseIndex].time_start, courseArr[courseIndex].time_end, courseArr[courseIndex].location);
          break;
        }
      }

      else if(len == 8){
        strcpy(fullCourseCodesArr, str);
        if(strcmp(inputArr, fullCourseCodesArr) == 1)
          result = 1;
        if(strcmp(inputArr, fullCourseCodesArr) == 0){
          result = 0;
          printf("%s\t%-40s%-5s %s-%s   %s\n",  courseArr[courseIndex].code, courseArr[courseIndex].title, courseArr[courseIndex].date, 
          courseArr[courseIndex].time_start, courseArr[courseIndex].time_end, courseArr[courseIndex].location);
          break;
        }
      }
      courseIndex++;
      counter++;
    }

    if(result == 1 )
      printf("error! course does not exist\n");
  }
}

/* input items into the list */
void enterNew(struct db_type * pArr[SIZE]){ 
  //records entered stored in studentIndex
  int studentIndex = getSize(pArr);
  int o = studentIndex;
  int u = studentIndex;

  //variables declared for for loops
  int i, j, k;

  int courseIndex = 0;
  int indexFound;
  char courseOne[10];
  char courseTwo[10];

  //char variables initialized for letter comparision when checking for days (e.g. M W F) in time conflict.
  char c1, c2, c3, d1, d2, d3;

  //char arrays used 
  char courseOneDays[5];
  char courseTwoDays[5];
  char dateCourse1[5];
  char dateCourse2[5];

  //variables used for strlen()
  int length1, length2;
  int inputCourseOneLength;
  int inputCourseTwoLength;
  int courseOneDaysLength;
  int courseTwoDaysLength;

  //some flags to use in code
  int flag1 = 0, flag2 = 0;
  int flag3 = 0, flag4 = 0;

  int course1done = 0;
  int course2done = 0;
  int courseOneIndexFound = 0; //indexFound for course 1
  int courseTwoIndexFound = 0; //indexFound for course 2

  pArr[studentIndex] = malloc(sizeof(struct db_type)); //memory allocation

  printf("name: ");
  fgets((*pArr[studentIndex]).name, fieldLength, stdin);

  printf("age: ");
  scanf("%d", &(*(pArr[studentIndex])).age);

  printf("course-1: ");
  scanf("%s", (*pArr[studentIndex]).course1);
  strcpy(courseOne, (*pArr[studentIndex]).course1);

  //cases for course 1
  for(i=0; i<SIZE; i++){
    if(strcmp(courseArr[courseIndex].code, "EECS0000") == 0)
      indexFound = i;
    char * str = courseArr[courseIndex].code;
    strncpy(names[courseIndex], &str[4], 5);
    strcpy(namesFull[courseIndex], str);  
    courseIndex++;
  }

  inputCourseOneLength = strlen(courseOne);
  while(flag1 != 1){
    for(k=0; k<SIZE; k++){
      if(inputCourseOneLength == 4){
        if(strcmp(courseOne, names[k]) == 0){
          flag1 = 1;
          indexCourseOne[u] = k;
          break;
        }
      }
      
      else if(inputCourseOneLength == 8){
        if(strcmp(courseOne, namesFull[k]) == 0){
          flag1 = 1;
          indexCourseOne[u] = k;
          break;
        }
      }
    }
      if(flag1 != 1){
        flag1 = 0;
        printf("course does not exist, enter again: ");
        scanf("%s", courseOne);
        inputCourseOneLength = strlen(courseOne);
    }
  }

  //cases for course 2
  if(flag1 == 1){
    course1done = 1; //marks that an existing course1 has been successfully entered by the user.
    printf("course-2: ");
    scanf("%s", (*pArr[studentIndex]).course2);
    strcpy(courseTwo, (*pArr[studentIndex]).course2);
  }

  inputCourseTwoLength = strlen(courseTwo);
  while(flag2 != 1){
    for(k=0; k<SIZE; k++){
      if(inputCourseTwoLength == 4){
        if(strcmp(courseTwo, names[k]) == 0){
          flag2 = 1;
          indexCourseTwo[o] = k;
          break;
        }
      }

      else if(inputCourseTwoLength == 8){
        if(strcmp(courseTwo, namesFull[k]) == 0){
          flag2 = 1;
          indexCourseTwo[o] = k;
          break;
        }
      }
    }

    if(flag2 != 1){
      flag2 = 2;
      printf("course does not exist, enter again: ");
      scanf("%s", courseTwo);
      inputCourseTwoLength = strlen(courseTwo);
    }
  }

  if(flag2 == 1)
    course2done = 1; //marks that an existing course2 has been successfully entered by the user.

  //for printing records finding indexFound of course details
  if(course1done == 1 && course2done == 1){
    //int i; //scope = if() statement. 
    for(i=0; i<indexFound; i++){
      if(inputCourseOneLength == 4){
        if(strcmp(names[i], courseOne) == 0){
          courseOneIndexFound = i;
          break;
        }
      }

      else if(inputCourseOneLength == 8){
        if(strcmp(namesFull[i], courseOne) == 0){
          courseOneIndexFound = i;
          break;
        }
      }
    }

    for(i=0; i<indexFound; i++){
      if(inputCourseTwoLength == 4){
        if(strcmp(names[i], courseTwo) == 0){
          courseTwoIndexFound = i;
          break;
        }
      }

      else if(inputCourseTwoLength == 8){
        if(strcmp(namesFull[i], courseTwo) == 0){
          courseTwoIndexFound = i;
          break;
        }
      }
    }

    printf("Course 1 -- %s %s\n",courseArr[courseOneIndexFound].time_start, courseArr[courseOneIndexFound].time_end);
    printf("Course 2 -- %s %s\n",courseArr[courseTwoIndexFound].time_start, courseArr[courseTwoIndexFound].time_end);

    //checking for time conflict by comparing time overlaps and days. 
    if(strcmp(courseArr[courseOneIndexFound].time_end, courseArr[courseTwoIndexFound].time_start) == 0 || 
      strcmp(courseArr[courseOneIndexFound].time_start, courseArr[courseTwoIndexFound].time_end) == 0)  {
      flag3 = 0;
    }

    else if (strcmp(courseArr[courseTwoIndexFound].time_start, courseArr[courseOneIndexFound].time_start) >= 0 && 
      strcmp(courseArr[courseTwoIndexFound].time_start, courseArr[courseOneIndexFound].time_end) <= 0)  {
      flag3++;
    }

    else if (strcmp(courseArr[courseTwoIndexFound].time_end, courseArr[courseOneIndexFound].time_start) >= 0 && 
      strcmp(courseArr[courseTwoIndexFound].time_end, courseArr[courseOneIndexFound].time_end) <= 0)  {
      flag3++;
    }

    else if (strcmp(courseArr[courseTwoIndexFound].time_start, courseArr[courseOneIndexFound].time_start) <= 0 && 
      strcmp(courseArr[courseTwoIndexFound].time_end, courseArr[courseOneIndexFound].time_end) >= 0) {
      flag3++;
    }

    else if (strcmp(courseArr[courseTwoIndexFound].time_start, courseArr[courseOneIndexFound].time_start) >= 0 && 
      strcmp(courseArr[courseTwoIndexFound].time_end, courseArr[courseOneIndexFound].time_end) <= 0) {
      flag3++;
    }

    else  {
      flag3 = 0;
    }

    strcpy(courseOneDays, courseArr[courseOneIndexFound].date);
    courseOneDaysLength = strlen(courseOneDays);
    
    strcpy(courseTwoDays, courseArr[courseTwoIndexFound].date);
    courseTwoDaysLength = strlen(courseTwoDays);

    for (i = 0; i < courseOneDaysLength; i++) {
      for (j = 0; j < courseTwoDaysLength; j++) {
        if (courseOneDays[i] == courseTwoDays[j]) {
          flag4++;
          break;
        }
      }
    }

    if (flag3 != 0 && flag4 != 0) {
      strcpy((*pArr[studentIndex]).status, "ATTENTION! time conflict");
      printf("%s\n", (*pArr[studentIndex]).status);
    } 

    else {
      strcpy((*pArr[studentIndex]).status, "SUCCESSFULL! no time conflict");
      printf("%s\n", (*pArr[studentIndex]).status);
    }
    strcpy((*pArr[studentIndex]).course1, courseOne);
    strcpy((*pArr[studentIndex]).course2, courseTwo);
  }
}

/* display records */
/**
* This function is invoked when user enters 'd' or 'D'. It displays all the records that the user has entered
* so far. Student's name, age and status is collected from pArr whereas student's course details are collected
* from courseArr. 
*/
void displayDB(struct db_type * pArr[]){
  int records = getSize(pArr);
  printf("===============================\n\n");

  if(records != 0) {
    //not static i -> lets me print all records from 0
    int i = 0;
    while(i<records){
      printf("name: %s", (*pArr[i]).name);
      printf("age: %d\n", (*(pArr[i])).age);
      printf("course1: %s\t%-40s%-5s %s-%s   %s\n",  courseArr[indexCourseOne[i]].code, 
        courseArr[indexCourseOne[i]].title, courseArr[indexCourseOne[i]].date, 
        courseArr[indexCourseOne[i]].time_start, courseArr[indexCourseOne[i]].time_end, 
        courseArr[indexCourseOne[i]].location);
      
      printf("course2: %s\t%-40s%-5s %s-%s   %s\n",  courseArr[indexCourseTwo[i]].code, 
        courseArr[indexCourseTwo[i]].title, courseArr[indexCourseTwo[i]].date, 
        courseArr[indexCourseTwo[i]].time_start, courseArr[indexCourseTwo[i]].time_end, 
        courseArr[indexCourseTwo[i]].location);

      printf("remarks: %s\n", (*pArr[i]).status);
      i++;
      printf("\n");
    }
  }
  printf("========== %d records ==========", records);
}

// Function to return number of records in pArr at present time.
int getSize(struct db_type * pArr[]) {
  int count = 0;
  int i;
  for (i = 0; i < SIZE; i++) {
    if (pArr[i] == NULL) {
      break;
    }
    count++;
  }
  return count;
}

/* remove an existing item */
void removeRecord (struct db_type * pArr[])	
{
  char removeName[fieldLength];
  printf("enter full name to remove: ");
  fgets(removeName, fieldLength, stdin);
  int numRecords = getSize(pArr);
  int i;
  int flag5 = 0;
  int foundIndex;

  for(i = 0; i < numRecords; i++){
    if(strcmp(removeName, pArr[i] -> name) == 0){
      flag5 = 1;
      foundIndex = i;
      removeName[strcspn(removeName, "\n")] = 0; // '\n' replace with '\0'
      break;
    }
  }

  if(flag5 == 1){
    for (i = foundIndex; i < numRecords - 1; i++) {
      pArr[i] = pArr[i+1];
      indexCourseOne[i] = indexCourseOne[i+1];
      indexCourseTwo[i] = indexCourseTwo[i+1];
    }
    pArr[i] = NULL;
    printf("record [%s] removed successfully.\n", removeName);
  }
  
  else if(flag5 != 1)
    printf("record not found\n");
}

/* swap records */
void swap(struct db_type * pArr[]){
  struct db_type * tempPArr;
  int ind1, ind2;
  int i;
  int records = getSize(pArr);

  for(i=1; i<records; i+=2){
    tempPArr = pArr[i];
    pArr[i] = pArr[i-1];
    pArr[i-1] = tempPArr;

    ind1 = indexCourseOne[i];
    indexCourseOne[i] = indexCourseOne[i-1];
    indexCourseOne[i-1] = ind1;

    ind2 = indexCourseTwo[i];
    indexCourseTwo[i] = indexCourseTwo[i-1];
    indexCourseTwo[i-1] = ind2;
  }
} 

/* load from course.txt, store into (global) array of courses  */
void init_courseArr(void){ 
 
   FILE *fr; //file pointer
   fr = fopen (courseFile, "r");
   char arr[50];  
   int count = 0;
   while ((fgets(arr,100,fr)) != NULL)
   {  
     strncpy(courseArr[count].code,  arr, strlen(arr)-1); // remove \n  
     courseArr[count].code[strlen(arr)-1] = '\0';  //to be safe
	 
     fgets(arr,100,fr);  
     strncpy(courseArr[count].title ,  arr, strlen(arr)-1);
     courseArr[count].title[strlen(arr)-1] = '\0';  //to be safe
     
          
     fgets(arr,100,fr); 
     strncpy(courseArr[count].date,  arr, strlen(arr)-1);
     courseArr[count].date[strlen(arr)-1] = '\0';  //to be safe
	   
     // other ways, remove \n before
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].time_start,  arr);
      
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].time_end,  arr);
      
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].location,  arr); 
	  
     count++;
     fgets(arr,100,fr); // read the empty line
   }

   strcpy(courseArr[count].code, "EECS0000"); // a terminator token structure

   fclose(fr);
	 
 }
    
//*********************** DISK IO ****************************************************************

void writeDisk(struct db_type * pArr[]){
  FILE *fp;
  int i;

  if ( (fp=fopen(diskFile,"ab")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  
  for (i=0; i< SIZE ; i++)
  {
     if ( pArr[i] != NULL)
     {  
       if (fwrite( pArr[i], sizeof(struct db_type), 1, fp) != 1)
       { 
          printf("file write error\n");
       }
     } 
   }
   fclose(fp);

}

void emptyDisk(void){

  FILE *fp;
  
  char c3[3];
  printf("are you sure to empty disk? (y) or (n)? ");
  fgets(c3,3,stdin);
  if(strcmp(c3, "y\n"))  
     return;
 
  //else
  if ( (fp = fopen(diskFile,"w")) == NULL)
  {
     printf("no file to open\n");
     return;
  }
  fclose(fp); // open close, will empty the file
}


void loadDisk(struct db_type * pArr[]){
  FILE *fp;
  int i;
  char c3[3];
  printf("will overwrite current records. are you sure to load disk? (y) or (n)? ");
  fgets(c3,3,stdin);
  if(strcmp(c3, "y\n"))  
     return;

  struct db_type * tmp;  
  
  if ( (fp = fopen(diskFile,"r")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  init_list(pArr);
  for (i=0; i < SIZE ; i++)
  {    
     
     tmp =  (struct db_type *) malloc (sizeof(struct db_type));   
	   
     if (fread( tmp, sizeof(struct db_type), 1, fp) != 1)
     {
       if (feof(fp))
       { fclose(fp); 
         return;
       }
       printf("file read error\n");
     }
     else pArr[i] = tmp;
  }
}

/****bonus*************************************************************************************/

/* sort the records by ages */
void sort(struct db_type * pArr[])
{
  int i, j;
  int n = getSize(pArr);

  for(i = 0; i <= n - 2; i++){
    for(j = i + 1; j <= n - 1; j++){
      if ((*pArr[i]).age > (*pArr[j]).age){
        int ind1, ind2;
        struct db_type * tempPArr;
        tempPArr = pArr[i];
        pArr[i] = pArr[j];
        pArr[j] = tempPArr;

        ind1 = indexCourseOne[i];
        indexCourseOne[i] = indexCourseOne[j];
        indexCourseOne[j] = ind1;

        ind2 = indexCourseTwo[i];
        indexCourseTwo[i] = indexCourseTwo[j];
        indexCourseTwo[j] = ind2;
      }
    } 
  }
}  