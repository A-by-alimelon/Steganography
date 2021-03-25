//
//  main.cpp
//  Steganography
//
//  Created by A on 2021/03/22.
//

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;

void encoding(string);

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        exit(1);
    }
    
    char option = *argv[1];
    
    if (option == 'e') {
        encoding(argv[2]);
    }
    
    return 0;
}

void encoding(string s) {
    ifstream readFile;
    FILE *fd;
    
    fd = fopen("origin.bmp", "rb");
    if (fd == NULL) {
        fputs("File error", stderr);
        exit(1);
    }
    
    fseek(fd, 0, SEEK_END);
    long lSize = ftell(fd);
    
    unsigned char *buffer = (unsigned char*)malloc(lSize + 1);
    memset(buffer, 0, lSize + 1);
    
    char bfType[2];
    unsigned char bfSize[4];
    unsigned char startOffset[4];
    
    fseek(fd, 0, SEEK_SET);
    fread(bfType, 2, 1, fd);
    fseek(fd, 2, SEEK_SET);
    fread(bfSize, 4, 1, fd);
    
    cout << bfType << endl;
    cout << "bfSize" << endl;
    
    for (int i = 0; i < 4; i++) {
        printf("%d ", i);
        printf("%x ", bfSize[i]);
    }
    
//    int size = static_cast<int>(bfSize);
    
    char bm[] = "BM";

    if ( strcmp(bm, bfType) != 0 ) {
        cout << "bmp 파일이 아닙니다." << endl;
        exit(1);
    }
    
    fseek(fd, 10, SEEK_SET);
    fread(startOffset, 4, 1, fd);
    
    int num = 0;
    num = static_cast<int>(startOffset[0]);
    printf("hi %d", num);
    
    fseek(fd, num, SEEK_SET);
    fread(buffer, 100, 1, fd);
  
    cout << "" << endl;
    
    for (int i = 0; i < 100; i++) {
        //sizeof로 하면 배열의 크기인 100자까지 나오므로 null값인 \0까지 for문 반복
        printf("%d: ", i);
        printf("%x ", buffer[i]);
        printf("%c ", buffer[i]);
    }
    
    int bIndex = 0;
    
    //char inputText[] = "hi i'm seongJu";
    string inputText = s;
    cout << endl;
    
    for (int i = 0; inputText[i] != '\0'; i++) {
        cout << i ;
        cout << inputText[i] ;
        cout << bitset<8>(inputText[i]) << endl;
        bitset<8> t = bitset<8>(inputText[i]);
        int k = 1;
        bitset<8> b;
        
        for (int j = 7; j>=0; j--) {
            if (j%2 == 1) {
                b = bitset<8>(buffer[bIndex]);
            }
                
            cout <<"바꾸기 전: ";
            cout << b << endl;
            
            printf("%d: ", j);
            cout << t[j] << endl;
            b.set(k, t[j]);
            k = (k + 1) % 2;
            
            if (k == 1) {
                cout << "바뀐 비트: " ;
                cout << b << endl;
                bIndex++;
            }
            
        }
    }
}
