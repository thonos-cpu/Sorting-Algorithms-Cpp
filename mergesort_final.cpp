
#include <iostream>
#include <iterator>
#include <list>
#include <bits/stdc++.h>
#define MAXCHAR 1024
#define MAX 1000


using namespace std;

void mergeSort(vector<int>&left, vector<int>& right, vector<int>& bars, vector<string>&date)
{
    int nL = left.size();
    int nR = right.size();
    int i = 0, j = 0, k = 0;


    while (j < nL && k < nR) 
    {
        if (left[j] < right[k]) {
            bars[i] = left[j];
            j++;
        }
        else {
            bars[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < nL) {
        bars[i] = left[j];
        j++; i++;
    }
    while (k < nR) {
        bars[i] = right[k];
        k++; i++;
    }
}

void sort(vector<int> & bar) {
    if (bar.size() <= 1) return;

    int mid = bar.size() / 2;
    vector<int> left;
    vector<int> right;

    for (size_t j = 0; j < mid;j++)
        left.push_back(bar[j]);
    for (size_t j = 0; j < (bar.size()) - mid; j++)
        right.push_back(bar[mid + j]);

    sort(left);
    sort(right);
    mergeSort(left, right, bar);
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
    
    sort(project.value, project.date);
    for (int i = 0; i < project.value.size(); i++){
        printf("The value is: %d and date is: ", project.value[i]);
        cout << project.date[i] << " ";\
        cout << "\n";
}

	return 0;
}

