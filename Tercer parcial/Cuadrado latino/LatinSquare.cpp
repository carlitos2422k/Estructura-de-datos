#include "LatinSquare.h"
#include <iostream>
using namespace std;

LatinSquare::LatinSquare(int size): n(size) {}

void LatinSquare::generate(){
    for(int i=0; i < n ; i++){
        for(int j=0; j < n; j++){
            cout << (i+j)% n+1 << " ";
        }
        cout << endl;
    }
}