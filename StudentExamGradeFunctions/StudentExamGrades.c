#define _CRT_SECURE_NO_WARNINGS
#define NUMBEROFSTUDENTS 5
#include<stdio.h>
#include <stdlib.h>
#include <math.h>
void inputNames(char studentNames[][20]);
void inputGrades(double examGrades[][5], char studentNames[][20]);
void printResults(double examGrades[][5], char studentNames[][20],double[]);
double calculateAverage(double[]);
double findStandardDeviation(double finalGrades[]);
int findMax(double finalGrades[]);
int findMin(double finalGrades[]);
int main() {
	char studentNames[NUMBEROFSTUDENTS][20];
	double examGrades[NUMBEROFSTUDENTS][5];
	double finalGrades[NUMBEROFSTUDENTS];
	inputNames(studentNames);
	inputGrades(examGrades, studentNames);
	printResults(examGrades, studentNames, finalGrades);

	return 0;
}
//must be ran before input grades to avoid using uninitialized values.
void inputNames(char studentNames[][20]) {
	for (int i = 0; i < NUMBEROFSTUDENTS; i++){
		printf("Please enter the name of student %d\n", i + 1);
		scanf("%s", &studentNames[i]);
	}
}
void inputGrades(double examGrades[][5], char studentNames[][20]){
	for (int i = 0; i < NUMBEROFSTUDENTS; i++){
		//set student id number
		//this means that [x][0] is the student id; do not use for other stuff.
		examGrades[i][0] = i;
		for (int j = 1; j < 5; j++){
			printf("Please input the grade %s recieved on exam %d\n", studentNames[i], j);
			//set student grade in ofset md aray. 
			scanf("%lf", &examGrades[i][j]);
		}
	}
}
void printResults(double examGrades[][5], char studentNames[][20],double finalGrades[]) {

	//apply grade weighting.
	double finalGradeInterim = 0;
	const double examWeights[] = { 0.10,0.20,0.30,0.40 };
	char letterGrade;

	for (int i = 0; i < NUMBEROFSTUDENTS; i++) {
		finalGradeInterim = 0;
		printf("The exam grades for %s\n",studentNames[i]);
		for (int j = 1; j < 5; j++){
			printf("Exam %d \n %.2lf\n", j, examGrades[i][j]);
			finalGradeInterim += (examGrades[i][j] * examWeights[j - 1]);
			
		

		}
		if (finalGradeInterim <= 59)      letterGrade = 'F';
		else if (finalGradeInterim <= 69) letterGrade = 'D';
		else if (finalGradeInterim <= 79) letterGrade = 'C';
		else if (finalGradeInterim <= 89) letterGrade = 'B';
		else                              letterGrade = 'A';
		printf("The final grade for %s is %.2lf which is a %c\n", studentNames[i], finalGradeInterim, letterGrade);
		finalGrades[i] = finalGradeInterim;
	}
	printf("The class average is %.2lf%%\n", calculateAverage(finalGrades));
	printf("The lowest grade is %.2lf%% from %s\n", finalGrades[findMin(finalGrades)], studentNames[findMin(finalGrades)]);
	printf("The highest grade is %.2lf%% from %s\n", finalGrades[findMax(finalGrades)], studentNames[findMax(finalGrades)]);
	printf("The standard deviation is %.2lf", findStandardDeviation(finalGrades));


}
double calculateAverage(double finalGrades[]) {
	double total = 0;
	for (int i = 0; i < NUMBEROFSTUDENTS; i++)
	{
		total += finalGrades[i];
	}
	return (total / NUMBEROFSTUDENTS);
}
int findMax(double finalGrades[]) {
	double max = 0;
	int indexOfMax = 0;
	for (int i = 0; i < NUMBEROFSTUDENTS; i++)
	{
		indexOfMax = finalGrades[i] > max ? i : indexOfMax;
		max = finalGrades[i] > max ? finalGrades[i] : max;
	}
	return indexOfMax;
}
int findMin(double finalGrades[]) {
	double min = 10000000;
	int indexOfMin = 0;
	for (int i = 0; i < NUMBEROFSTUDENTS; i++)
	{
		indexOfMin = finalGrades[i] < min ? i : indexOfMin;
		min = finalGrades[i] < min ? finalGrades[i] : min;
	}
	return indexOfMin;
}
double findStandardDeviation(double finalGrades[]) {
	double grades[NUMBEROFSTUDENTS];
	double sumOfSquares = 0;
	double varience;
	memcpy(grades, finalGrades, NUMBEROFSTUDENTS* sizeof(double));
	double average = calculateAverage(grades);
	for (int i = 0; i < NUMBEROFSTUDENTS; i++)
	{
		grades[i] -= average;
		grades[i] *= grades[i];
		sumOfSquares += grades[i];
	}
	varience = (sumOfSquares / NUMBEROFSTUDENTS);
	return (sqrt(varience));

}