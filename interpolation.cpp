#include <iostream>
#include <iterator>
#include <list>
#include <bits/stdc++.h>
#include <sstream>
#define MAXCHAR 1024
#define MAX 100000

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

int interpolation_binary_search(vector<string> &arr, int n, string x) {
    int low = 0, high = n - 1;

    while (low <= high && x >= arr[low] && x <= arr[high]) {
        int pos = low + (((double)(high - low) / daysBetweenDates(arr[high], arr[low])) * daysBetweenDates(x, arr[low]));

        if (arr[pos] == x) {
            return pos;
        } else if (arr[pos] < x) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }

    // If x is not found, perform a binary search on the remaining subarray
    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == x) {
            return mid;
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    // x not found in array
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
     fp = fopen("C:\\PROJECT\\PROJECT.csv", "r");
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
    
    if(interpolation_binary_search(project.date,n-1, s) == -1){
    	printf("The is no such date on the excel file!");
	}   else {
		printf("The date you are looking for is in position: %d and the value is: %d and cumulative is: %d", interpolation_binary_search(project.date,n-1, s), project.value[interpolation_binary_search(project.date,n-1, s)], project.cumulative[interpolation_binary_search(project.date, n-1, s)]);
	}

	return 0;
}

