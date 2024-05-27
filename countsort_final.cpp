// C++ program to demonstrate the implementation of List
#include <iostream>
#include <iterator>
#include <list>
#include <bits/stdc++.h>
#define MAXCHAR 1024
#define MAX 100

using namespace std;

void countSort(vector<int>& arr, vector<string>& date)
{
    int max = *max_element(arr.begin(), arr.end());
    int min = *min_element(arr.begin(), arr.end());
    int range = max - min + 1;
 
    vector<int> count(range), output(arr.size());
    vector<string> temp(date.size());
    for (int i = 0; i < arr.size(); i++)
        count[arr[i] - min]++;
 
    for (int i = 1; i < count.size(); i++)
        count[i] += count[i - 1];
 
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        temp[count[arr[i] - min] - 1] = date[i];
        count[arr[i] - min]--;
    }
 
    for (int i = 0; i < arr.size(); i++){
        arr[i] = output[i];
        date[i] = temp[i];
}
}
 
typedef struct{
	vector<int> value;
	vector<string> date;
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
    
    countSort(project.value, project.date);
    for (int i = 0; i < project.value.size(); i++){
        printf("The value is: %d and date is: ", project.value[i]);
        cout << project.date[i] << " ";
        cout << "\n";
}

	return 0;
}

