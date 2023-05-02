#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

/** ���� �μ� �Լ��� �뷫���� ����
void varFunc( int fix, ...){
    va_list ap; //�Լ��� ���޵Ǵ� �μ����� ���ÿ� ����ǰ�, �� �� ���ÿ� �ִ� �μ��� �д� �� val_list�� ������ ������ �ϳ��� �ʿ���
    va_start(ap,fix) // ap�����Ͱ� ù�� ° ���� �μ��� ����Ű���� �ʱ�ȭ�Ѵ�.
    va_arg(ap, �μ�Ÿ��) //���� �μ��� �д� ���. va_arg�� �Լ��� �ƴ϶� ��ũ�� �Լ��̱⿡ �ι�° �μ��� ���������� sizeof �����ڿ� ĳ��Ʈ �����ڷ� ���޵�
    va_end(ap) //�� ����ϸ� ���� ��������    
}
*/

int myscanf(const char* format, ...) {
    va_list args;
    
    va_start(args, format);

    int n = 0;
    char buf[1024];

    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        va_end(args);
        return EOF;
    }

    /** format���� �Է��� ���� *p�� �迭ó�� 0���� �ϳ��� �ö󰡸� üũ�ϴ� ����̴�. ���� ������ ���ڿ��� ������ ��Ÿ���� \0�� ���� ��������.*/
    for (const char* p = format; *p != '\0'; ++p) { 
        if (*p == '%') {
            ++p;
            switch (*p) {
            case 'd':
                while (isspace(*buf)) ++buf;
                int val = strtol(buf, &buf, 10);
                *(va_arg(args, int*)) = val;
                ++n;
                break;
            case 'f':
                while (isspace(*buf)) ++buf;
                float fval = strtof(buf, &buf);
                *(va_arg(args, float*)) = fval;
                ++n;
                break;
            case 's':
                while (isspace(*buf)) ++buf;
                char* sval = va_arg(args, char*);
                int len = strlen(buf);
                strncpy(sval, buf, len);
                sval[len - 1] = '\0'; // remove newline character
                ++n;
                break;
            case 'c':
                break;

            default:
                break;
            }
        }
    }

    va_end(args);
    return n;
}