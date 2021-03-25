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
void decoding();

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        exit(1);
    }

    char option = *argv[1];
    
    if (option == 'e') {
        encoding(argv[2]);
    } else if (option == 'd') {
        decoding();
    }
    
    return 0;
}

void encoding(string s) {
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
    
    char bm[] = "BM";

    if ( strcmp(bm, bfType) != 0 ) {
        cout << "bmp 파일이 아닙니다." << endl;
        exit(1);
    }
    
    fseek(fd, 10, SEEK_SET);
    fread(startOffset, 4, 1, fd);
    
    int num = 0;
    num = static_cast<int>(startOffset[0]);
    
    fseek(fd, num, SEEK_SET);
    fread(buffer, lSize, 1, fd);
    
    FILE *output;
    output = fopen("output.bmp", "wb");
    
    // output.bmp 에 origin.bmp 복사
    fseek(fd, 0, SEEK_SET);
    unsigned char *header = (unsigned char*)malloc(lSize + 1);
    fread(header, lSize, 1, fd);
    fwrite(header, 1, lSize, output);
    
    int bIndex = 0;

    string inputText = s;
    cout << endl;
    
    fseek(output, num, SEEK_SET);
    
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
                unsigned char c = static_cast<unsigned char>(b.to_ulong());
                printf("%x\n", c);
                fwrite(&c, sizeof(c), 1, output);
                //fseek(output, sizeof(c), SEEK_CUR);
                bIndex++;
            }
            
        }
    }

    
    fclose(fd);
    fclose(output);
    
}

void decoding() {
    FILE *fd;
    
    fd = fopen("output.bmp", "rb");
    if (fd == NULL) {
        fputs("File error", stderr);
        exit(1);
    }
    
    fseek(fd, 0, SEEK_END);
    long lSize = ftell(fd);
    
    unsigned char *buffer = (unsigned char*)malloc(lSize + 1);
    memset(buffer, 0, lSize + 1);
    
    char bfType[2];
    unsigned char startOffset[4];
    
    fseek(fd, 0, SEEK_SET);
    fread(bfType, 2, 1, fd);
    
    fseek(fd, 10, SEEK_SET);
    fread(startOffset, 4, 1, fd);
    
    char bm[] = "BM";

    if ( strcmp(bm, bfType) != 0 ) {
        cout << "bmp 파일이 아닙니다." << endl;
        exit(1);
    }
    
    int num = 0;
    num = static_cast<int>(startOffset[0]);
    
    fseek(fd, num, SEEK_SET);
    fread(buffer, lSize, 1, fd);
    
    bitset<8> c;
    c.set();
    int index = 0;
    
    for (int i = 0; i < lSize; i++) {
        index = i % 8;
//        cout << "--" ;
//        cout << index << endl;
        
        bitset<8> b = bitset<8>(buffer[i/2]);
        
//        cout << 7-index << endl;
        c.set(7-index, b[(i+1)%2]);
        
        if (index == 7) {
            unsigned char a = static_cast<unsigned char>(c.to_ulong());
            if (a < 32 || a > 127) {
                cout << endl;
                exit(1);
            }
            cout << a;
        }
    }
}
