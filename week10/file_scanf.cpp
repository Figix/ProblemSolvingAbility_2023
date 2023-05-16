#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "myFileHeader.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	char Format[255];
	char input[255];

	fileGenerator();
	fileReader(Format, input, 255);

	printf("파일에서 읽은 텍스트를 확인합니다.\n");
	printf("Format : %s\n", Format);
	printf("Input  : %s\n", input);

	char checkList[3][3] = { "%d","%s","%c" };
	int formatCount[3] = { 0 };
	char* ptr = Format;
	int count = 0;
	for (int i = 0; i < 3; i++) {
		while (ptr = strstr(ptr, checkList[i])) { // 찾는 문자열이 발견될 때마다
			count++; // 카운트를 증가시키고
			ptr++; // 포인터를 이동시켜서 중복 검색을 방지합니다.
		}
		formatCount[i] = count;
		count = 0;
		ptr = Format;
	}
	printf("--------------------------------------\n");
	printf("%%d count : %d\n", formatCount[0]);
	printf("%%s count : %d\n", formatCount[1]);
	printf("%%c count : %d\n", formatCount[2]);

	int size = formatCount[0] + formatCount[1] + formatCount[2];
	size = 1 + size * 2;
	char** str_arr = (char**)malloc(sizeof(char*) * size);	//포인터 배열 동적 할당(문자열 갯수만큼)
	for (int i = 0; i < size; i++) {
		str_arr[i] = (char*)malloc(sizeof(char) * 100); // 문자열을 저장할 메모리 공간 할당
	}

	int index = 0;
	while (ptr = strstr(ptr, "%")) { // 찾는 문자열이 발견될 때마다
		strncpy(str_arr[count++], &Format[index], ptr - Format - index);	// 찾은 곳 위치 바로 전 위치까지 얻기
		str_arr[count - 1][ptr - Format - index] = '\0';
		//주석된 곳 처리하면 문자열 널문자 처리안되어서 오류생김

		index = ptr - Format;

		strncpy(str_arr[count++], &Format[index], 2);
		str_arr[count - 1][2] = '\0';

		index = index + 2;
		ptr = ptr + 2; // 포인터를 이동시켜서 중복 검색을 방지합니다.
	}
	int len = strlen(Format) - index;

	strncpy(str_arr[count], &Format[index], len);
	str_arr[count][len] = '\0';
	
	int tmplen;
	ptr = input;
	for (int i = 0 ; i < size; i++) {
		printf("문자열의 길이 : %d\t문자열 배열 인덱스 %d: %s\n",strlen(str_arr[i]), i, str_arr[i]);
		tmplen = strlen(str_arr[i]);
		/** 1.%체크  */
		if (strstr(str_arr[i], "%")) {
		/** 2.%종류 체크 */
		/** i의 값은 해당 문자열의 순서 */
		/** j의 값 0:int, 1:string, 2:char */
			for (int j = 0; j < 3; j++) {
				if (strstr(str_arr[i], checkList[j])) {
					//char* input_ptr = 
					int length; 

					break;
				}
			}
		}
	}



	return 0;
}