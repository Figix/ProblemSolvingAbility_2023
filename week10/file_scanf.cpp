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

	printf("���Ͽ��� ���� �ؽ�Ʈ�� Ȯ���մϴ�.\n");
	printf("Format : %s\n", Format);
	printf("Input  : %s\n", input);

	char checkList[3][3] = { "%d","%s","%c" };
	int formatCount[3] = { 0 };
	char* ptr = Format;
	int count = 0;
	for (int i = 0; i < 3; i++) {
		while (ptr = strstr(ptr, checkList[i])) { // ã�� ���ڿ��� �߰ߵ� ������
			count++; // ī��Ʈ�� ������Ű��
			ptr++; // �����͸� �̵����Ѽ� �ߺ� �˻��� �����մϴ�.
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
	char** str_arr = (char**)malloc(sizeof(char*) * size);	//������ �迭 ���� �Ҵ�(���ڿ� ������ŭ)
	for (int i = 0; i < size; i++) {
		str_arr[i] = (char*)malloc(sizeof(char) * 100); // ���ڿ��� ������ �޸� ���� �Ҵ�
	}

	int index = 0;
	while (ptr = strstr(ptr, "%")) { // ã�� ���ڿ��� �߰ߵ� ������
		strncpy(str_arr[count++], &Format[index], ptr - Format - index);	// ã�� �� ��ġ �ٷ� �� ��ġ���� ���
		str_arr[count - 1][ptr - Format - index] = '\0';
		//�ּ��� �� ó���ϸ� ���ڿ� �ι��� ó���ȵǾ ��������

		index = ptr - Format;

		strncpy(str_arr[count++], &Format[index], 2);
		str_arr[count - 1][2] = '\0';

		index = index + 2;
		ptr = ptr + 2; // �����͸� �̵����Ѽ� �ߺ� �˻��� �����մϴ�.
	}
	int len = strlen(Format) - index;

	strncpy(str_arr[count], &Format[index], len);
	str_arr[count][len] = '\0';
	
	int tmplen;
	ptr = input;
	for (int i = 0 ; i < size; i++) {
		printf("���ڿ��� ���� : %d\t���ڿ� �迭 �ε��� %d: %s\n",strlen(str_arr[i]), i, str_arr[i]);
		tmplen = strlen(str_arr[i]);
		/** 1.%üũ  */
		if (strstr(str_arr[i], "%")) {
		/** 2.%���� üũ */
		/** i�� ���� �ش� ���ڿ��� ���� */
		/** j�� �� 0:int, 1:string, 2:char */
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