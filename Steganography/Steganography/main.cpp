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
    FILE *fd;
    
    fd = fopen("origin.bmp", "rb");
    if (fd == NULL) {
        fputs("File error", stderr);
        exit(1);
    }
    
    fseek(fd, 0, SEEK_END);
    long lSize = ftell(fd);
    cout << lSize << endl;
    
    unsigned char *buffer = (unsigned char*)malloc(lSize + 1);
    memset(buffer, 0, lSize + 1);
    
    unsigned char bfType[2];
    unsigned char bfSize[2];
    
    fseek(fd, 0, SEEK_SET);
    fread(bfType, 2, 1, fd);
    fseek(fd, 2, SEEK_SET);
    fread(bfSize, 2, 1, fd);
    
    cout << bfType << endl;
    cout << bfSize << endl;
//
//    printf("%x ", bfType[0]);
//    printf("%x ", bfSize[0]);
    
//    for (int i = 0; bfType[i]!='\0'; i++) {
//        //sizeof로 하면 배열의 크기인 100자까지 나오므로 null값인 \0까지 for문 반복
//        printf("%x ", bfType[i]);
//    }
    
    for (int i = 0; i < 2; i++) {
        //sizeof로 하면 배열의 크기인 100자까지 나오므로 null값인 \0까지 for문 반복
        printf("%d ", i);
        printf("%x ", bfSize[i]);
    }
    
    
    
    //    readFile.open("origin.bmp", ios::binary);
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
    
    //    if (readFile.is_open()) {
    //        cout << "is open" << endl;
    //        while (!readFile.eof()) {
    //            char arr[10000];
    //            readFile.read((char*)&arr, sizeof(arr));
    //            cout << arr << endl;
    //        }
    //    } else {
    //        cout << "no" << endl;
    //    }
    //
    //    readFile.close();
    return 0;
}
