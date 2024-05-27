
#include <iostream>
#include <iterator>
#include <list>
#include <bits/stdc++.h>
#define MAXCHAR 1024
#define MAX 100


using namespace std;

void heapify(std::vector<unsigned long int> &arr,vector<string> &date, int size, int i) {
    int max = i; // initialize max as root
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // if left child is larger than root
    if (left < size && arr[left] > arr[max])
        max = left;

    // if right child is larger than max
    if (right < size && arr[right] > arr[max])
        max = right;

    // if max is not root
    if (max != i) {
        // swap
        int temp = arr[i];
        string tempd = date[i];
        arr[i] = arr[max];
        date[i] = date[max];
        arr[max] = temp;
        date[max] = tempd;


        heapify(arr, date, size, max);
    }
}

void heapSort(std::vector<unsigned long int> &arr, vector<string> &date) {
    int size = arr.size();

    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, date, size, i);
    }

    for (int i = size - 1; i >= 0; i--) {
        int temp = arr[0];
        string tempd = date[0];
        arr[0] = arr[i];
        date[0] = date[i];
        arr[i] = temp;
        date[i] = tempd;

        heapify(arr, date, i, 0);
    }
}

typedef struct{
	vector<unsigned long int> value;
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
            if (i == 9) {
                project.value.push_back(atol(token));
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
    
    heapSort(project.value, project.date);
    for (int i = 0; i < project.value.size(); i++){
        printf("The value is: %lu and date is: ", project.value[i]);
        cout << project.date[i] << " ";\
        cout << "\n";
}

	return 0;
}


