#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int fileGenerator() {
	FILE* fp;

	// 파일 열기
	fp = fopen("data.txt", "w");

	// 파일에 데이터 쓰기
	fprintf(fp, "내 이름은 %%s이고 이번학기 점수는 %%d9999점이고 성적은 %%c를 받았습니다.\n");
	fprintf(fp, "내 이름은 멋진 이은석님이고 이번학기 점수는 989999점이고 성적은 A를 받았습니다.\n");

	// 파일 닫기
	fclose(fp);
	return 0;
}
int fileReader(char *Format, char* input, int MAX) {
	FILE* fp;

	// 파일 열기
	fp = fopen("data.txt", "r");

	// 파일로부터 한 라인씩 읽기
	fgets(Format, MAX, fp);
	fgets(input, MAX, fp);

	for (int i = 0; Format[i] != '\0'; i++) {
		if (Format[i] == '\n') { Format[i] = '\0'; }
	}
	for (int i = 0; input[i] != '\0'; i++) {
		if (input[i] == '\n') { input[i] = '\0'; }
	}

	// 파일 닫기
	fclose(fp);
	return 0;
}
