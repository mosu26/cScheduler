#include "givenA3.h"
#include <ctype.h>
#include <stdlib.h>

/* function definition number 1*/
int readCourse (
   char filename [MAX_STR],
   char courseName [NUMBER_COURSES][MAX_STR],
   int courseID [NUMBER_COURSES]
){

  int length;// declaring an integer named length
  FILE*file;//declaring a pointer named file that points to the file
  file = fopen(filename, "r"); // opening the file in reading mode
  if (file == NULL){// if file is null it will return -1
    return -1;
  }

  while (!feof(file)){ // while loop with a condition that it will keep going until end of file is reached
    for (int i=0; i<NUMBER_COURSES; i++){// for loop that iterates through the courseName array and scans the corresponding values 
      fgets(courseName[i], MAX_STR, file);// scans each value from file
      length = strlen(courseName[i]);// initializing length for each course name
      courseName[i][length-1] = '\0';// getting rid of the newline by assigning null as the last character for each course name
    }

    for (int j=0; j<NUMBER_COURSES;j++){ // for loop that iterates through courseID array 
      fscanf(file, "%d", &courseID[j]);//scans each value and assigns it to the appropriate position in the array
    }
  }

  fclose(file);// closes file
  return 1;// returns 1 if everything worked properly 
}


/* function definition for function 2*/
int readProfs (
   char filename [MAX_STR],
   int courseID [NUMBER_COURSES],
   char profName [NUMBER_PROFS][MAX_STR],
   int coursesTaught [NUMBER_PROFS][NUMBER_COURSES]
 ){

  // declaring variables
  int length;
  int i;
  int j;

  FILE*file2; // declaring pointer to a file named file2
  file2 = fopen(filename, "r");// opening file in reading mode
  if (file2==NULL){ // if file is null, returns -1
    return -1;
  }

  while (!feof(file2)){//while loop with a condition that it will keep going until end of file is reached
    for (i=0; i<NUMBER_PROFS; i++){ // for loop that iterates through the profName array and scans the corresponding names
      fgets(profName[i], MAX_STR,file2);// scans the names from the file
      length = strlen(profName[i]); // initializes the length for each profname 
      profName[i][length-1] = '\0';//getting rid of the newline by assigning null as the last character for each prof name

    }
    for (i=0; i<NUMBER_PROFS; i++){// for loop to iterate through each prof and assign the numbers which tell what courses they are teaching
      for (j=0; j<NUMBER_COURSES; j++){ //for loop to scan the values and populate the coursesTaught array
        fscanf(file2,"%d",&coursesTaught[i][j]);// scans the integer value (either a 1 or 0) from the file
        if (coursesTaught[i][j] == 1){ // if the integer equals to 1(meaning the prof is teaching the course), replace it with the corresponding courseID
          coursesTaught[i][j] = courseID[j];
        }
      }
    }// closes the entire nested for loop
  }
  fclose(file2);// closes file

return 1;// returns 1 if everything works fine
}



/* function definition for number 3*/

int nCourses (
int n,
char profName [NUMBER_PROFS][MAX_STR],
int coursesTaught [NUMBER_PROFS][NUMBER_COURSES]
){
  // declaring variables
  int i;
  int j;
  int profCount = 0;
  int taughtCount;

  for (i=0; i<NUMBER_PROFS; i++){ //for loop to iterate through each prof and count the number of courses they teach
    taughtCount = 0; // reinitializes taughtCount to 0 for each prof
    for(j=0; j<NUMBER_COURSES; j++){ // for loop that iterates through the array coursesTaught 
      if (coursesTaught[i][j] != 0){ // if statement where everytime the number is not equal to 0 (meaning the prof teaches the course) it increases taughtCount by 1
        taughtCount = taughtCount + 1;
      }
    }
    if (taughtCount >= n){ // if taughtCount is greater than n, meaning that prof teachers atleast n or more courses, the prof's name gets printed   
      printf("%s, ", profName[i]);// printing prof name
      profCount = profCount + 1;// the prof count increases by 1
    }
  }// closes the entire nested for loop
  printf("\n");
  return profCount;// returns the prof count to main 
}


/* function definition for function 4*/
int getCourseName (
int courseNum,
char cNameFound [MAX_STR],
char courseName [NUMBER_COURSES][MAX_STR],
int courseID [NUMBER_COURSES]
){

  for(int i = 0; i < NUMBER_COURSES; i++){// for loop to iterate through the array courseID
    if (courseNum == courseID[i]){ // if the courseNum is equal to any of the numbers in the array which stores the course IDs, the course exists
      strcpy(cNameFound, courseName[i]);// copies the corresponding course name into cNameFound which stores it
      cNameFound[MAX_STR-1] = '\0';// adds the null to cNameFound (which is a string)
      return 1;// returns 1 if the course was found
    }
  }
  return 0;// returns 0 otherwise
}



/*function definition for function 5*/
int getCourseNum (
char cName [MAX_STR],
int * cNumFound,
char courseName [NUMBER_COURSES][MAX_STR],
int courseID [NUMBER_COURSES]
){

  char tempcName[MAX_STR];// temporary array to store the name of the course the user typed which will be changed to all lowercase
  int length;// variable to store the length of the course name the user typed
  char tempCoursename[NUMBER_COURSES][MAX_STR];// temporary array to store the course names from the file which will all be changed to lowercase

  length = strlen(cName);//initializes length with length of the course name
  if (cName[length-1]=='\n'){ // if the course the user typed had spaces, the if statement gets rid of the newline from fgets
    cName[length-1] = '\0';// gets rid of new line by assigning null character
  }

  strcpy(tempcName,cName);//copies course name user typed into its temporary array

  for(int i=0;i<strlen(tempcName);i++){//a for loop that iterates through the tempcName array and turns every character into a lowercase
     tempcName[i] = tolower(tempcName[i]);// uses function tolower to turn each character lowercase
  }

  for (int i=0; i<NUMBER_COURSES; i++){// a for loop that copies each coursename from the file into the temCourseName array
    strcpy(tempCoursename[i], courseName[i]);// copies each coursename from the file into the tempCourseName array
    for (int j=0; j<strlen(tempCoursename[i]); j++){// a for loop that will iterate through the tempCoursename array and turn every character into a lowercase
      tempCoursename[i][j] = tolower(tempCoursename[i][j]);// uses funciton tolower to turn every character into a lowercase
    }
  }
  
    for(int i = 0; i < NUMBER_COURSES; i++){// for loop that checks to see if the course name the user typed can be found in the tempCoursename array (which has values from the file)
      if(strcmp(tempcName, tempCoursename[i]) == 0){// uses strcmp funciton to check if the 2 strings are the same, if they are it would equal 0
        *cNumFound = courseID[i];//if strings are equal, the corresponding courseID is stored in cNumFound 
        return 1;// returns 1 if course is found
      }
    }
    return 0;// returns 0 otherwise
 }


//(Task 6)
int profsTeachingCourse (
int courseNum,
char profName [NUMBER_PROFS][MAX_STR],
int coursesTaught [NUMBER_PROFS][NUMBER_COURSES]
){
  int profteachCount = 0;// declares and initializes variable that will count how many profs teach the declared course 
  for (int i=0; i<NUMBER_PROFS; i++){// nested for loop that iterates through the profs and the courses they teach
    for (int j=0; j<NUMBER_COURSES; j++){
      if(courseNum == coursesTaught[i][j]){// if the courseNum is equal to any of the numbers in coursesTaught for each prof, it means the prof teaches that course
        profteachCount = profteachCount + 1;// increases profteachCount by 1 because it means a certain prof teaches that course
        printf("%s teaches this course\n", profName[i]);// prints prof's name if they teach that course
      }
    }
  }
  if (profteachCount > 0){// if profteachCount is greater then 0, meaning atleast 1 prof teaches the course, it will return the profteachCount
    return profteachCount;
  }
  return 0;// otherwise returns 0
}


// (task 7)
float avgNumCourses (int coursesTaught [NUMBER_PROFS][NUMBER_COURSES]
){
  //declaring variables
  int i;
  int j;
  float courseCount = 0;
  float average = 0;
  for (i=0; i<NUMBER_PROFS; i++){// nested for loop that will iterate through each prof and all the numbers in the coursesTaught array
    for (j=0; j<NUMBER_COURSES; j++){
      if (coursesTaught[i][j] != 0){// if the courseTaught value is not equal to 0, meaning the prof teaches the course, it increases courseCount by 1
        courseCount = courseCount + 1;
      }
    }
  }
  average = courseCount / 6;// takes the total courseCount and divides it by 6, which is the number of profs
  return average;// returns the average back to main
}


//task 8
void hhistogram (char profName [NUMBER_PROFS][MAX_STR],
int coursesTaught [NUMBER_PROFS][NUMBER_COURSES]
){
  // declaring variables
  int i;
  int j;
  int courseCount;
  int nameLength;
  
  for (i=0; i<NUMBER_PROFS; i++){// for loop that iterates through the prof names
    nameLength = strlen(profName[i]);// counts the length of each prof's name (gets reinitialized each time we move to a new prof through the for loop)
    if (nameLength < 7){// if their name is less then 7 characters theres 2 tabs
      printf("%s:\t\t", profName[i]);// prints name
    } else {// otherwise only 1 tab
      printf("%s:\t", profName[i]);// prints name
    }
    courseCount = 0; // reinitialize courseCount to 0 for each prof
    for (j=0; j<NUMBER_COURSES; j++){// for loop to iterate through coursesTaught array
      if (coursesTaught[i][j] != 0){// if the number is not equal to 0, it means the prof is teaching the course
        courseCount = courseCount+1; // increases courseCount by 1
        printf("*");// prints a star each time courseCount increases
      } 
    }
    printf(" (%d)\n", courseCount);// prints the number of courses taught by a prof in brackets
  }
}

