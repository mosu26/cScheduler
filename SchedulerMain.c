#include "givenA3.h"
#include <ctype.h>
#include <stdlib.h>
int main () {
 
  //declared all variables here 

  int choice;
  char filename [MAX_STR] = "courses.txt";
  char courseName [NUMBER_COURSES][MAX_STR];
  int courseID [NUMBER_COURSES];
  char filename2 [MAX_STR] = "data.txt";
  char profName [NUMBER_PROFS][MAX_STR];
  int coursesTaught [NUMBER_PROFS][NUMBER_COURSES];
  char cNameFound [MAX_STR];
  int result1;
  int result2;
  int profCount;
  int result4; 
  int n;
  int courseNum;
  int cnumFound; 
  char cName [MAX_STR];
  int result5;
  int courseNum6;
  int result6;
  float result7;
  char courseValidation[50];// character array to store users input for case 2

    
  
  result1 = readCourse(filename,courseName,courseID); // calling function 1
  if (result1==-1){
    printf("Error, the result of this function is %d\n", result1);  
    return 0;// exits program
  }

  result2 = readProfs(filename2, courseID, profName, coursesTaught);// calling function 2

  if (result2 ==-1){
    printf("Error, the result of this function is %d\n", result2);
    return 0;//exits program
  }


 
    do {
        printf ("\nHere is the menu - enter a number between 1 and 7 \n\n");
       printf ("1. Task 3 – find the total number of professors who teach n or more courses\n");
       printf ("2. Task 4 – find course name, given its course number\n");
       printf ("3. Task 5 – find course number, given its course name\n");
       printf ("4. Task 6 – find all professors teaching a given course \n");
       printf ("5. Task 7 – find the average number of courses taught by a professor \n");
       printf ("6. Task 8 – display a horizontal histogram showing the number of courses taught by each professor\n");
        
      printf ("7. Exit\n");
   
       do{// do while loop that validates users choice making sure its a number between 1 and 7 
         printf ("Enter your choice: ");// user enters choice
         scanf ("%d", &choice);// scans the number
         
         if (choice>7||choice<1){// if the number meets the condition of this loop, it will print the message and ask them to enter a number again
           printf("This is not a valid choice for a task\n");// prints message
         }
       } while (choice>7||choice<1);// condition of loop
 
        switch (choice) {
            case 1:
                printf("Enter the number of courses taught: ");// user input
                scanf("%d", &n);
                profCount = nCourses(n, profName, coursesTaught);// calling function 
                printf("The number of profs teaching n or more courses is: %d\n", profCount);
                break;
            case 2:
                printf("Enter a courseID: ");// user input
                scanf("%s", courseValidation);// scans and stores in variable called courseValidation which is an array of type char
                courseNum = atoi(courseValidation);// uses function atoi to convert string to its integer form and makes courseNum equal to that
                  if (courseNum==0){// courseNum will equal 0 if string is typed and message will be printed
                    printf("Invalid input\n");
                    break;// will break out of switch and return back to the menu
                  }
                result4 = getCourseName(courseNum, cNameFound, courseName, courseID);// calls function
  
                if (result4==1){// if result is 1, will print name of the course
                  printf("%s\n", cNameFound);
                }else if(result4==0){// if result is 0, means course was not found 
                  printf("course not found\n");// prints message
                }
                printf("The result of this function is %d\n", result4);// prints overall result of function 
                break;
            case 3:
                printf("Enter a course name: ");//user input
                getchar();// clears input buffer
                fgets(cName,MAX_STR,stdin);// uses fgets to scan string
                result5 = getCourseNum(cName, &cnumFound, courseName, courseID);// calling function
                if (result5==1){
                  printf("The courseID for the course you entered is: %d\n",cnumFound);
                  printf("The result of this function is %d\n", result5);// prints overall result of function (1 in this case)
                }else if (result5 ==0){
                  printf("Course does not exist,therefore, no courseID found\n");
                  printf("The result of this function is %d\n", result5);// prints overall result of function (0 in this case)
                }
                break;
            case 4:
                printf("Enter a course ID: ");// user input
                scanf("%d", &courseNum6);
                result6 = profsTeachingCourse(courseNum6, profName, coursesTaught);// calling function
                printf("The number of profs teaching this course is: %d\n", result6);
                break; 
            case 5:
                result7 = avgNumCourses(coursesTaught);// calling function 
                printf("The average number of courses taught by a prof is: %.2f\n", result7);
                break;
            case 6:
                hhistogram(profName, coursesTaught);// calling function 
                break;
            case 7:
                printf("You have chosen to exit, bye!\n");// prints goodbye message
                break;// ends program by breaking out of swich and also exiting do while loop
            default: printf ("That is an invalid choice\n");
                
        }
        
    } while (choice != 7);
    
    
   return 0;
}

