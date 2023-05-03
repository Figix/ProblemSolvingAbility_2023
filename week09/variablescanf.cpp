#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

/** 가변 인수 함수의 대략적인 구조
void varFunc( int fix, ...){
va_list ap;         //함수로 전달되는 인수들은 스택에 저장되고, 이 때 스택에 있는 인수를 읽는 때 val_list형 포인터 변수가 하나가 필요함
va_start(ap,fix)        // ap포인터가 첫번 째 가변 인수를 가르키도록 초기화한다.
va_arg(ap, 인수타입) //가변 인수를 읽는 명령. va_arg는 함수가 아니라 매크로 함수이기에 두번째 인수는 내부적으로 sizeof 연산자와 캐스트 연산자로 전달됨
va_end(ap)              //다 사용하면 끄는 습관하기, 일종의 메모리 할당 해제라고 이해함
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

    /** format을 *p로 배열처럼 0부터 하나씩 올라가며 체크하는 방식이다. 종료 조건은 문자열이 끝남을 나타내는 \\0이 나올 때까지다.*/
    for (const char* p = format; *p != '\0'; ++p) {
        if (*p == '%') {
            ++p;
            switch (*p) {
                //int isspace(int) 해당 함수는 해당값이 공백인지 체크하는 함수이다. ' ', '\\n', '\\t', '\\v', '\\f', '\\r' 6개를 검출함
                //반환값 : 공백이라면 0이 아닌 수 반환. 공백이 아닌 다른 문자라면 0 반환.
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

    char tmp[1024]; // 메모리 할당
    int index = 0;

    for (int i = start; i <= end; i++) {
        tmp[index++] = str[i];
    }
    tmp[index] = '\0';

    const char* result = tmp;

    return result;
}