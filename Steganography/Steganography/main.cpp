//
//  main.cpp
//  Steganography
//
//  Created by A on 2021/03/22.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream readFile;
//    char bfType[2];
//    char bfSize[2];
//
    readFile.open("origin.bmp", ios::binary);
//    assert(readFile.is_open());
//
//    readFile.read((char*)&bfType, 2);
//
//    for (int i = 0; i < sizeof(bfType) / sizeof(char); i++) {
//        printf("%c\n", bfType[i]);
//    }
//
//    readFile.read((char*)&bfSize, sizeof(bfSize));
//
//    cout << "=====" << endl;
//
//    for (int i = 0; i < sizeof(bfSize) / sizeof(char); i++) {
//        printf("%d", i);
//        printf("%c\n", bfSize[i]);
//    }
//
//    cout << bfType << endl;
//    cout << bfSize << endl;
    
    if (readFile.is_open()) {
        cout << "is open" << endl;
        while (!readFile.eof()) {
            char arr[10000];
            readFile.read((char*)&arr, sizeof(arr));
            cout << arr << endl;
        }
    } else {
        cout << "no" << endl;
    }

    readFile.close();
    return 0;
}
