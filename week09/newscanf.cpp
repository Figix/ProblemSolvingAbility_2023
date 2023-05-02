#include <stdio.h>

#include <string.h>



/*

 * %d %f %c %s \t

 * 5개의 키워드 구현하기

 * 문자열이 조금이라도 일치하지 않을 경우 return -1로 오류 출력해도 됨

 */



int vr_scanf(const char* str, void* a, void* b, void* c, void* d)
{
    char input_str[1024];  // 임시 문자열
    char* token;         // 문자열 파싱을 위한 포인터
    int index = 0;       // 지정된 변수를 저장하기 위한 인덱스
    const char* dev = " ";  // 자를 문자열 저장용
    
    
    gets_s(input_str);


    char* token = strtok(input_str, dev);    //구분자는 콤마(,)입니다.

    while (token != NULL)
    {
        printf("%s\n", token);        //자른 문자 출력

        if (token == "%d") {

        }
        else if (token == "%f") {

        }
        else if (token == "%c") {

        }
        else if (token == "%s") {

        }
        else if (token == "\t") {

        }
        token = strtok(NULL, dev);
    }



    return 0;   //return -1;
}



int main()
{
    int a;
    char b;
    float c;
    char d[1024];
    
    printf("Enter values: ");

    int result = vr_scanf("%d|%c %f,%s", &a, &b, &c, d);

    if (result == 0)
        printf("Values entered: %d %c %f %s\n", a, b, c, d);
    else
        printf("Error\n");
    
    return 0;
}