/*
Program that gets student's names and grades from a file, 
seperates the data into arrays, and outputs
the homework grades, and averages of students.
At the end it shows the class average,
and the student with the highest grade.

By Remley.
*/

#include <iomanip>
#include <fstream>
#include <iostream>
using namespace std;

/**
 * Total number of grades per student
 */
const int GRADE_COUNT = 7;

// Gets the letter grade for each student depending on their average.
string getLetterGrade(double average);

// gets the average of an indivdual in the class based on homework.
double calculateAverage(const double grades[], int listSize);

// finds the biggest value in an array, by sorting through the 
// items in an array and comparing them to each other.
int maxIndex(const double list[], int listSize);

//cycles through students and calls calculateAverage() to get the averages of all
//of the students in a class.
void calculateAverages(const double table[][GRADE_COUNT], double averages[],
int listSize);

//reads in data from a file containing grades.
int getData(string filename, string stringnames[], double homework[][GRADE_COUNT],
int listSize);

//displays all of the grades and averages of the students in a class.
void displayIndividualGrades(const string stringnames[], const double homework[][GRADE_COUNT],
const double averages[], int listsize);

//displays the class average and the student with the highest average in the class.
void displayClassOverview(const string stringnames[], const double averages[], int listsize);

int main()
{
	/*
	 * Total number of students
	 */
	  const int MAX_STUDENT_COUNT = 24;

	// Declare arrays
  string names[MAX_STUDENT_COUNT];
  double homework[MAX_STUDENT_COUNT][GRADE_COUNT];
  double average[MAX_STUDENT_COUNT];
  

	// Read in the data
  int numberOfStudents =
  getData("grades.txt", names, homework, MAX_STUDENT_COUNT);
  
	// Calculate each students' averages
  calculateAverages(homework, average, numberOfStudents);
  
	// Display a grid with students' grades and averages
  displayIndividualGrades(names,homework, average, numberOfStudents);

  // add a couple lines of separation for better readability
	cout << endl;

	// Display the class average and top student
  displayClassOverview(names, average, numberOfStudents);
  
  // exit program successfully
	return 0; 
}

int maxIndex(const double list[], int listSize){ 
  
  //page 485 textbook
  int index;
  int maxIndex = 0;

  // for every item in the array, if it is bigger than 0, or bigger than 
  // whatever numbers are in the array, assign that number's index to
  // maxIndex
  for (index = 1 ; index < listSize; index++)
    if (list[maxIndex] < list[index])
      maxIndex = index; 

  return maxIndex;
}


double calculateAverage(const double grades[], int listSize){

  // based off of sumArray page 484 in textbook

  int index;
  double sum = 0;

  // for all of the homework grades, add the grades to sum
  for (index = 0; index < listSize; index++){
    sum = sum + grades[index];
  }

  // divide sum by the number of homework grades
  double average = sum/listSize;
  
  return average;
}

void calculateAverages(const double table[][GRADE_COUNT], double averages[], int listSize){

  //for all of the students, calculate averages
  for (int index = 0; index < listSize; index++)
  {
    {
      averages[index] = calculateAverage(table[index], GRADE_COUNT);
    }
  }
}

int getData(string filename, string stringnames[], double homework[][GRADE_COUNT], int listSize){

  //open the file
  ifstream grades;
  grades.open(filename);

  string unuseful;
  listSize= 0;
  while (!grades.eof()){
     getline(grades, unuseful);
     listSize++;
    
  }
  grades.close();
  grades.open(filename);
  //for the max number of students, print their name and homework data
  for(int index = 0; index < listSize; index++){
    grades >> stringnames[index];
    for( int count = 0; count < GRADE_COUNT; count++){
      grades >> homework[index][count];
    }
}
  grades.close();
  return listSize;
}

void displayIndividualGrades(const string stringnames[], const double homework[][GRADE_COUNT], const double averages[], int listsize){

  cout << "Name        HW 1  HW 2  HW 3  HW 4  HW 5  HW 6  HW 7  Average  Letter" << endl;

  for (int index = 0; index < listsize ; index++){
    cout << std::left << fixed << setfill(' ') << setw(12) << stringnames[index];
    for(int count = 0; count < GRADE_COUNT; count++)
    {
      cout << std::right << setw(4) << setprecision(0) << homework[index][count] << "  ";
    }
    cout << setw(7) << setprecision(2) << averages[index] << "      " << getLetterGrade(averages[index]) << endl;

    
    
  }
}

void displayClassOverview(const string stringnames[], const double averages[], const int listsize){

  int index = maxIndex(averages,listsize);
  
  cout << "Class average: " << setprecision(2) << calculateAverage(averages,listsize) << endl;
  cout << "Student with the highest grade: " << stringnames[index];
  cout << endl;
}

string getLetterGrade(double average){

  if (average >= 90 && average <= 100){
    return "A";}
    else if (average < 90 && average >= 87){
      return "B+";}
    else if (average < 87 && average >= 80){
      return "B";}
    else if (average < 80 && average >= 77){
      return "C+";}
    else if (average < 77 && average >= 70){
      return "C";}
    else if (average < 70 && average >= 60){
      return "D";}
    else if (average < 60 && average >= 0){
      return "F";}
    else return "A";
  
}
      