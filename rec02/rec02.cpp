//
//  main.cpp
//  rec02
//
//  Created by Elias Attias on 2/7/20.
//  Copyright © 2020 Elias Attias. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Chemical{
    vector<string> name;
    int carbon;
    int hydrogen;
};

void readFile(ifstream& chemicals);
void fillVector(ifstream& chemicals, vector<Chemical>& vectorOfChem);
size_t position(const vector<Chemical>& vectorOfChem, int carbon, int hydrogen);
void sort(vector<Chemical>& vectorOfChem);
void display(const vector<Chemical>& vectorOfChem);

int main(){
    ifstream chemicals;
    vector<Chemical> vectorOfChem;
    readFile(chemicals);
    fillVector(chemicals, vectorOfChem);
    sort(vectorOfChem);
    display(vectorOfChem);
}

void display(const vector<Chemical>& vectorOfChem){
    for (int i = 0; i < vectorOfChem.size(); i ++){
        cout << "C" << vectorOfChem[i].carbon << "H" << vectorOfChem[i].hydrogen << " ";
        for (int j = 0; j < vectorOfChem[i].name.size(); j ++){
            cout << vectorOfChem[i].name[j] << " ";
        }
        cout << endl;
    }
}

void sort(vector<Chemical>& vectorOfChem){
    for (int i = 0; i < vectorOfChem.size(); i ++){
        for (int j = 0; j < vectorOfChem.size() - 1; j ++){
            if (vectorOfChem[j].carbon > vectorOfChem[j+1].carbon){
                swap(vectorOfChem[j], vectorOfChem[j+1]);
            }
            else if(vectorOfChem[j].carbon == vectorOfChem[j+1].carbon){
                if (vectorOfChem[j].hydrogen > vectorOfChem[j+1].hydrogen){
                    swap(vectorOfChem[j], vectorOfChem[j+1]);
                }
            }
        }
    }
}

size_t position(const vector<Chemical>& vectorOfChem, int carbon, int hydrogen){
    for(size_t i = 0; i < vectorOfChem.size(); i++){
        if (vectorOfChem[i].carbon == carbon && vectorOfChem[i].hydrogen == hydrogen){
            return i;
        }
    }
    return vectorOfChem.size();
}

void fillVector(ifstream& chemicals, vector<Chemical>& vectorOfChem){
    string firstWord;
    char carbonAtom;
    char hydrogenAtom;
    int carbon;
    int hydrogen;
    while(chemicals >> firstWord){
        chemicals >> carbonAtom >> carbon >> hydrogenAtom >> hydrogen;
        size_t index = position(vectorOfChem,carbon,hydrogen);
        if (index == vectorOfChem.size()){
            Chemical chemical{{firstWord}, carbon, hydrogen};
            vectorOfChem.push_back(chemical);
        }
        else{
            vectorOfChem[index].name.push_back(firstWord);
        }
    }
}

void readFile(ifstream& chemicals){
    string fileName;
    do{
        chemicals.clear(); //to avoid defective stream before trying to open file
        cout << "could not open the file, enter file name:" << endl;
        cin >> fileName;
        chemicals.open(fileName);
    }
    while(!chemicals);
}

