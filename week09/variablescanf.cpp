#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

/** ���� �μ� �Լ��� �뷫���� ����
void varFunc( int fix, ...){
va_list ap;         //�Լ��� ���޵Ǵ� �μ����� ���ÿ� ����ǰ�, �� �� ���ÿ� �ִ� �μ��� �д� �� val_list�� ������ ������ �ϳ��� �ʿ���
va_start(ap,fix)        // ap�����Ͱ� ù�� ° ���� �μ��� ����Ű���� �ʱ�ȭ�Ѵ�.
va_arg(ap, �μ�Ÿ��) //���� �μ��� �д� ���. va_arg�� �Լ��� �ƴ϶� ��ũ�� �Լ��̱⿡ �ι�° �μ��� ���������� sizeof �����ڿ� ĳ��Ʈ �����ڷ� ���޵�
va_end(ap)              //�� ����ϸ� ���� �����ϱ�, ������ �޸� �Ҵ� ������� ������
}
*/
int myscanf(const char* format, ...);
const char* bufcopy(const char* str, int start, int end);

int main() {
    int int_value;
    float float_value;
    char chararr_value[1024];
    char c_value;

    myscanf("%d %f %s %c", &int_value, &float_value, &chararr_value, &c_value);

    printf("int value : %d\n", int_value);
    printf("float value : %f\n", float_value);
    printf("char[] value : %s\n", chararr_value);
    printf("char value : %c\n", c_value);

    return 0;
}


int myscanf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    int n = 0;
    char buf[1024];
    char tmpbuf[100];
    int i = 0;
    int iA = 0;
    int iB = 0;

    int val = 0;
    float fval = 0.0;
    char* sval;
    char cval;
    char* argstr;
    int len = 0;

    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        va_end(args);
        return EOF;
    }

    printf("%s \t", format);
    printf("%s \n", buf);

    /** format�� *p�� �迭ó�� 0���� �ϳ��� �ö󰡸� üũ�ϴ� ����̴�. ���� ������ ���ڿ��� ������ ��Ÿ���� \\0�� ���� ��������.*/
    for (const char* p = format; *p != '\0'; ++p) {
        if (*p == '%') {
            ++p;
            switch (*p) {
                //int isspace(int) �ش� �Լ��� �ش簪�� �������� üũ�ϴ� �Լ��̴�. ' ', '\\n', '\\t', '\\v', '\\f', '\\r' 6���� ������
                //��ȯ�� : �����̶�� 0�� �ƴ� �� ��ȯ. ������ �ƴ� �ٸ� ���ڶ�� 0 ��ȯ.
            case 'd':
                while (isspace(buf[i])) { ++i; }
                iA = i++;
                while (!isspace(buf[i])) { ++i; }
                iB = --i;

                val = strtol(bufcopy(buf, iA, iB), NULL, 10);
                *(va_arg(args, int*)) = val;
                ++n;
                ++i;
                break;
            case 'f':
                while (isspace(buf[i])) { ++i; }
                iA = i++;
                while (!isspace(buf[i])) { ++i; }
                iB = --i;

                fval = strtof(bufcopy(buf, iA, iB), NULL);
                *(va_arg(args, float*)) = fval;
                ++n;
                ++i;
                break;
            case 's':
                while (isspace(buf[i])) { ++i; }
                iA = i++;
                while (!isspace(buf[i])) { ++i; }
                iB = --i;

                sval = (char*)bufcopy(buf, iA, iB);
                argstr = va_arg(args, char*);
                strcpy(argstr, sval);

                ++n;
                ++i;
                break;
            case 'c':
                while (isspace(buf[i])) { ++i; }
                iA = i++;
                while (!isspace(buf[i])) { ++i; }
                iB = --i;

                cval = buf[iA];
                *(va_arg(args, char*)) = cval;

                ++n;
                ++i;
                break;

            default:
                break;
            }
        }
    }

    va_end(args);
    return n;

}

const char* bufcopy(const char* str, int start, int end) {
    const int len = end - start;

    char tmp[1024]; // �޸� �Ҵ�
    int index = 0;

    for (int i = start; i <= end; i++) {
        tmp[index++] = str[i];
    }
    tmp[index] = '\0';

    const char* result = tmp;

    return result;
}