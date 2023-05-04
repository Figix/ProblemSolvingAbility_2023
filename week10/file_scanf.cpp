#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "myFileHeader.h"



int main() {
	char Format[255];
	char input[255];

	fileGenerator();
	fileReader(Format,input,255);

	printf("%s\n", Format);
	printf("%s\n", input);

	return 0;
}






