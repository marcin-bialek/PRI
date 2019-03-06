//  Created by Marcin Białek 
//  Program to convert decimal number to binary (big endian).
//  Input range: 0 - 9,223,372,036,854,775,807

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//  Function to convert positive number to binary string (big endian).
//  @param decimalNumber Positive decimal number
//  @param buffer Buffer for binary string (size of at least 64)
void decimalToBinaryString(unsigned long long decimalNumber, char* buffer) {
    //  Convert number to binary (little endian)
    char binaryString[128];
    int index = 0;
    
    do {
        binaryString[index] = decimalNumber & 1 ? '1' : '0';
        index++;
        decimalNumber = decimalNumber >> 1;
    } while(decimalNumber);
    
    //  Rewrite binary number (in litter endian) to buffer (in big endian)
    int index2 = 0;
    
    while(index--) {
        buffer[index2++] = binaryString[index];
    }
    
    buffer[index2] = '\0';
}


//  Function displaying proper usage of an app
void displayProperUsage() {
    printf("Usage: DecToBin [positive integer]\n");
}


//  Main function
int main(int argc, const char * argv[]) {
    //  Return if user provided too less or too much arguments
    if(argc != 2) {
        displayProperUsage();
        return 1;
    }
    
    //  Try to convert input to int
    unsigned long long decimalNumber = atoll(argv[1]);
    
    //  Try to convert back int to string
    char numberString[128];
    sprintf(numberString, "%llu", decimalNumber);
    
    //  Return if both strings are different
    if(strcmp(argv[1], numberString) != 0) {
        displayProperUsage();
        return 1;
    }
    
    //  Convert number to binary then display result
    char binaryString[128];
    decimalToBinaryString(decimalNumber, binaryString);
    
    printf("%s\n", binaryString);
    
    return 0;
}

