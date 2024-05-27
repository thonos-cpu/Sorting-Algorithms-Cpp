// C++ program to demonstrate the implementation of List
#include <iostream>
#include <iterator>
#include <list>
#include <bits/stdc++.h>
#define MAXCHAR 1024
#define MAX 100

using namespace std;

int Binary_search(const vector<string>& sorted_vec, string key) {
   size_t mid, left = 0 ;
   
   size_t right = sorted_vec.size();
   
   while (left < right) {
      mid = left + (right - left)/2;
      if (key > sorted_vec[mid]){
          left = mid+1;
      }
      else if (key < sorted_vec[mid]){                                        
        right = mid;
      }
      else {                                                                  
        return mid;
     }                                                                                                               
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
    
    cout << "Enter the date you want to find: ";
    cin >> s;
    
    if(Binary_search(project.date, s) == -1){
    	printf("The is no such date on the excel file!");
	}   else {
		printf("The date you are looking for is in position: %d and the value is: %d and cumulative is: %lu", Binary_search(project.date, s), project.value[Binary_search(project.date, s)], project.cumulative[Binary_search(project.date, s)]);
	}

	return 0;
}

