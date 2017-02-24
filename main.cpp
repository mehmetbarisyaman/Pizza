//
//  main.cpp
//  Pizza
//
//  Created by Baris on 1/27/17.
//  Copyright © 2017 MBY. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class cell{
public:
    char ingredient;
    bool selected;
};

class slice{
public:
    int x1;
    int y1;
    int x2;
    int y2;
    int size;
};


int main(int argc, const char * argv[]) {
    long totalPoints=0;
    int row;
    int column;
    int minIngredients;
    int maxCells;
    ifstream inputFile("big.in");
    ofstream outputFile("bigOutput.out");
    if(!inputFile){
        cout << "Input file can not be found" << endl;
        return -1;
    }
    inputFile >> row;
    inputFile >> column;
    inputFile >> minIngredients;
    inputFile >> maxCells;
    cell pizza[row][column];
    string anyLine;
    char anyIngredient;
    int arrayRow =0;
    while(!inputFile.eof()){
        inputFile >> anyLine;
        for(int i=0; i<column; i++){
            anyIngredient = anyLine[i];
            pizza[arrayRow][i].ingredient = anyIngredient;
            pizza[arrayRow][i].selected = false;
        }
        arrayRow++;
        if(arrayRow >= row)
            break;
    }
    vector<slice>pizzaSlices;
    int tNumber=0;
    int mNumber=0;
    
    
    
    // select  slices corresponding to row number
    for(int rowCounter=0; rowCounter < row; rowCounter++){
        for(int columnCounter=0; columnCounter< column; columnCounter++){
            for(int i=0; i<12; i++){
                if(pizza[rowCounter][columnCounter+i].selected){
                    tNumber=0;
                    mNumber=0;
                    break;
                }
                if(pizza[rowCounter][columnCounter+i].ingredient== 'T')
                    tNumber++;
                else if(pizza[rowCounter][columnCounter+i].ingredient== 'M')
                    mNumber++;
            }
            if(tNumber==minIngredients && mNumber==minIngredients && columnCounter<=988){
                bool lastControl = false;
                for(int i=0; i<12; i++){
                    if(pizza[rowCounter][columnCounter+i].selected){
                        lastControl = true;
                        break;
                    }
                    pizza[rowCounter][columnCounter+i].selected = true;
                }
                if(!lastControl){
                    slice createdSlice;
                    createdSlice.x1 = columnCounter;
                    createdSlice.x2 = columnCounter+11;
                    createdSlice.y1 = rowCounter;
                    createdSlice.y2 = rowCounter;
                    createdSlice.size = 12;
                    pizzaSlices.push_back(createdSlice);
                }
            }
            tNumber = 0;
            mNumber = 0;
        }
    }
    tNumber=0;
    mNumber=0;
    // select  slices corresponding to column number
    for(int columnCounter=0; columnCounter < column; columnCounter++){
        for(int rowCounter=0; rowCounter< row-12; rowCounter++){
            for(int i=0; i<12; i++){
                if(pizza[rowCounter+i][columnCounter].selected){
                    tNumber=0;
                    mNumber=0;
                    break;
                }
                if(pizza[rowCounter+i][columnCounter].ingredient== 'T')
                    tNumber++;
                else if(pizza[rowCounter+i][columnCounter].ingredient== 'M')
                    mNumber++;
            }
            if(tNumber==minIngredients && mNumber==minIngredients && rowCounter<=988){
                bool lastControl = false;
                for(int i=0; i<12; i++){
                    if(pizza[rowCounter+i][columnCounter].selected){
                        lastControl = true;
                        break;
                    }
                    pizza[rowCounter+i][columnCounter].selected = true;
                }
                if(!lastControl){
                    slice createdSlice;
                    createdSlice.x1 = columnCounter;
                    createdSlice.x2 = columnCounter;
                    createdSlice.y1 = rowCounter;
                    createdSlice.y2 = rowCounter+11;
                    createdSlice.size = 12;
                    pizzaSlices.push_back(createdSlice);
                }
            }
            tNumber = 0;
            mNumber = 0;
        }
    }
    
    // increase the sizes of slices
    
    for (vector<slice>::iterator it = pizzaSlices.begin() ; it != pizzaSlices.end(); ++it){
        if(it->y1==it->y2){
            if(!pizza[it->y1][it->x1-1].selected&& it->size < maxCells){
                while(it->size<maxCells){
                    if(pizza[it->y1][it->x1-1].selected|| it->x1<=0)
                        break;
                    else if(!pizza[it->y1][it->x1-1].selected && it->size<maxCells && it->x1>0){
                        it->x1--;
                        it->size++;
                        pizza[it->y1][it->x1].selected = true;
                    }
                }
            }
            if(!pizza[it->y1][it->x2+1].selected && it->size< maxCells){
                while(it->size<maxCells){
                    if(pizza[it->y1][it->x2+1].selected || it->x2>=999)
                        break;
                    else if(!pizza[it->y1][it->x2+1].selected && it->size<maxCells && it->x2<999){
                        it->x2++;
                        it->size++;
                        pizza[it->y1][it->x2].selected = true;
                    }
                }
            }
        }
        
        else if(it->x1 == it->x2){
            if(!pizza[it->y1-1][it->x1].selected&& it->size < maxCells){
                while(it->size<maxCells){
                    if(pizza[it->y1-1][it->x1].selected|| it->y1<=0)
                        break;
                    else if(!pizza[it->y1-1][it->x1].selected && it->size<maxCells && it->y1>0){
                        it->y1--;
                        it->size++;
                        pizza[it->y1][it->x1].selected = true;
                    }
                }
            }
            if(!pizza[it->y2+1][it->x2].selected && it->size< maxCells){
                while(it->size<maxCells){
                    if(pizza[it->y2+1][it->x2].selected || it->y2>=999)
                        break;
                    else if(!pizza[it->y2+1][it->x2].selected && it->size<maxCells && it->y2<999){
                        it->y2++;
                        it->size++;
                        pizza[it->y2][it->x2].selected = true;
                    }
                }
            }
        }
        totalPoints += it->size;
    }
    
    
    
    
    cout << totalPoints << endl;
    
    outputFile << pizzaSlices.size() << endl;
    
    for(int i=0; i<pizzaSlices.size(); i++){
        outputFile << pizzaSlices[i].y1 << " " << pizzaSlices[i].x1 << " ";
        outputFile << pizzaSlices[i].y2 << " " << pizzaSlices[i].x2 << endl;
    }
    
    
    return 0;
}
