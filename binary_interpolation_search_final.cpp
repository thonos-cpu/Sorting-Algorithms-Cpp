// C++ program to demonstrate the implementation of List
#include <iostream>
#include <iterator>
#include <list>
#include <bits/stdc++.h>
#include <sstream>
#define MAXCHAR 1024
#define MAX 100

using namespace std;

int daysBetweenDates(string date1, string date2)
{
    stringstream ss(date1 + "/" + date2);
    int year, month, day;
    char hyphen;
 
    // Parse the first date into seconds
    ss >> day >> hyphen >> month >> hyphen >> year;
    struct tm starttm = { 0, 0, 0, day,
                        month - 1, year - 1900 };
    time_t start = mktime(&starttm);
 
    // Parse the second date into seconds
    ss >> hyphen >> day >> hyphen
        >> month >> hyphen >> year;
    struct tm endtm = { 0, 0, 0, day,
                        month - 1, year - 1900 };
    time_t end = mktime(&endtm);
 
    // Find out the difference and divide it
    // by 86400 to get the number of days
    return abs(end - start) / 86400;
}


int interpolationSearch(vector<string> &arr, int lo, int hi, string x)
{
    int pos;
 
    // Since array is sorted, an element present
    // in array must be in range defined by corner
    if (lo <= hi) {
 
        // Probing the position with keeping
        // uniform distribution in mind.
        pos = lo + (((double)(hi - lo) / daysBetweenDates(arr[hi], arr[lo])) * daysBetweenDates(x, arr[lo]));
 
        // Condition of target found
        if (arr[pos] == x)
            return pos;
 
        // If x is larger, x is in right sub array
        if (arr[pos] < x)
            return interpolationSearch(arr, pos + 1, hi, x);
 
        // If x is smaller, x is in left sub array
        if (arr[pos] > x)
            return interpolationSearch(arr, lo, pos - 1, x);
    }
    return -1;
}

typedef struct{
	vector<int> value;
	vector<string> date;
	vector<unsigned long int> cumulative;
} comb;


int main()
{

comb project;

//setting buffer and token for later use to tokenize the csv file
FILE *fp;
    char line[MAXCHAR];
    char *token;
    int count = 0;
    
    //opening file
     fp = fopen("C:\\Users\\tasis\\OneDrive\\Documents\\effects-of-covid-19-on-trade-at-15-december-2021-provisional.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open file\n");
        exit(1);
    }
	
	//tokenizing the csv file while simutaniously inserting the tokens into the vector along with their assinged date
	while (fgets(line, MAXCHAR, fp) != NULL && count < MAX){
        token = strtok(line, ",");
        int i = 0;
        while (token != NULL && i < 10) {
            if (i == 2) {
                project.date.push_back(token);
            }
            if (i == 8) {
                project.value.push_back(atoi(token));
            }
            if (i == 9) {
                project.cumulative.push_back(atol(token));
            }
		if(strchr(token, '"') != NULL){
			token = strtok(NULL, ",");
			while(strchr(token, '"') == NULL){
				token = strtok(NULL, ",");
			}
		}
			token = strtok(NULL, ",");
			i++;
        }
        count++;
    }

    fclose(fp);
    string s;
    
    int n = sizeof(project.date) / sizeof(project.date[0]);
    cout << "Enter the date you want to find: ";
    cin >> s;
    
    if(interpolationSearch(project.date, 0, n-1, s) == -1){
    	printf("The is no such date on the excel file!");
	}   else {
		printf("The date you are looking for is in position: %d and the value is: %d and cumulative is: %d", interpolationSearch(project.date, 0, n-1, s), project.value[interpolationSearch(project.date, 0, n-1, s)], project.cumulative[interpolationSearch(project.date, 0, n-1, s)]);
	}

	return 0;
}

