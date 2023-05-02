#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

/** 가변 인수 함수의 대략적인 구조
void varFunc( int fix, ...){
    va_list ap; //함수로 전달되는 인수들은 스택에 저장되고, 이 때 스택에 있는 인수를 읽는 때 val_list형 포인터 변수가 하나가 필요함
    va_start(ap,fix) // ap포인터가 첫번 째 가변 인수를 가르키도록 초기화한다.
    va_arg(ap, 인수타입) //가변 인수를 읽는 명령. va_arg는 함수가 아니라 매크로 함수이기에 두번째 인수는 내부적으로 sizeof 연산자와 캐스트 연산자로 전달됨
    va_end(ap) //다 사용하면 끄는 습관하자    
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

    /** format으로 입력한 것을 *p로 배열처럼 0부터 하나씩 올라가며 체크하는 방식이다. 종료 조건은 문자열이 끝남을 나타내는 \0이 나올 때까지다.*/
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