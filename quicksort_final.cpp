// C++ program to demonstrate the implementation of List
#include <iostream>
#include <iterator>
#include <list>
#include <bits/stdc++.h>
#define MAXCHAR 1024
#define MAX 1000


using namespace std;

void swap(vector<unsigned long int>& v, int x, int y) {
    int temp = v[x];
    v[x] = v[y];
    v[y] = temp;

}
void quicksort(vector<unsigned long int> &vec, int L, int R) {
    int i, j, mid, piv;
    i = L;
    j = R;
    mid = L + (R - L) / 2;
    piv = vec[mid];

    while (i<R || j>L) {
        while (vec[i] < piv)
            i++;
        while (vec[j] > piv)
            j--;

        if (i <= j) {
            swap(vec, i, j); //error=swap function doesnt take 3 arguments
            i++;
            j--;
        }
        else {
            if (i < R)
                quicksort(vec, i, R);
            if (j > L)
                quicksort(vec, L, j);
            return;
        }
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
    
    quicksort(project.value, 0, MAX - 1);
    for (int i = 0; i < project.value.size(); i++){
        printf("The value is: %lu and date is: ", project.value[i]);
        cout << project.date[i] << " ";\
        cout << "\n";
}

	return 0;
}


