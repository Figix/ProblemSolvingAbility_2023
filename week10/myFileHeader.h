#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int fileGenerator() {
	FILE* fp;

	// ���� ����
	fp = fopen("data.txt", "w");

	// ���Ͽ� ������ ����
	fprintf(fp, "�� �̸��� %%s�̰� �̹��б� ������ %%d9999���̰� ������ %%c�� �޾ҽ��ϴ�.\n");
	fprintf(fp, "�� �̸��� ���� ���������̰� �̹��б� ������ 989999���̰� ������ A�� �޾ҽ��ϴ�.\n");

	// ���� �ݱ�
	fclose(fp);
	return 0;
}
int fileReader(char *Format, char* input, int MAX) {
	FILE* fp;

	// ���� ����
	fp = fopen("data.txt", "r");

	// ���Ϸκ��� �� ���ξ� �б�
	fgets(Format, MAX, fp);
	fgets(input, MAX, fp);

	for (int i = 0; Format[i] != '\0'; i++) {
		if (Format[i] == '\n') { Format[i] = '\0'; }
	}
	for (int i = 0; input[i] != '\0'; i++) {
		if (input[i] == '\n') { input[i] = '\0'; }
	}

	// ���� �ݱ�
	fclose(fp);
	return 0;
}
