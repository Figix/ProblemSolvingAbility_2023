#include <iostream>

using namespace std;

void translate_num2Rome(int num);
int share_Rome(int cal_num, int devide_num);
int translate_Rome2num(string str1);

string str;

int main(int argc, char* argv[]) {
    int num;

    while (true) {
        cout << "1~3999 ������ ���� �Է����ֽñ� �ٶ��ϴ�. : " << endl;
        cin >> num;

        if (cin.fail()) {
            cin.clear(); // �Է� ���۸� �ʱ�ȭ�մϴ�.
            cin.ignore(10000, '\n'); // �Է� ���ۿ��� '\n'������ ���ڸ� �����մϴ�.
            cout << "�߸��� �Է��Դϴ�." << endl;
        }
        else {
            if (num >= 1 && num <= 3999) {
                cout << "�θ��� ���� ǥ�� : ";
                translate_num2Rome(num);

                cout << "�θ���->���� ��ȯ : " << translate_Rome2num(str) << endl;

            }
            else {
                cout << "1~3999 ���� ���� ���� �Է��ϼ̽��ϴ�." << endl;

            }
        }
        str = "";
        cout << endl;
    }


    return 0;
}

void translate_num2Rome(int num) {
    int checknum, calnum = num;

    calnum = share_Rome(calnum, 1000);
    calnum = share_Rome(calnum, 500);
    calnum = share_Rome(calnum, 100);
    calnum = share_Rome(calnum, 50);
    calnum = share_Rome(calnum, 10);
    calnum = share_Rome(calnum, 5);
    calnum = share_Rome(calnum, 1);

    cout << str << endl;
}

int share_Rome(int cal_num, int devide_num) {
    int result = 0;
    int count = 0;

    string Romenum;
    //�θ��� ��ȣ ���ϴ� ����
    switch (devide_num)
    {
    case 1000:
        Romenum = "M";
        break;
    case 500:
        Romenum = "D";
        break;
    case 100:
        Romenum = "C";
        break;
    case 50:
        Romenum = "L";
        break;
    case 10:
        Romenum = "X";
        break;
    case 5:
        Romenum = "V";
        break;
    case 1:
        Romenum = "I";
        break;
    default:
        break;
    }

    if ((cal_num / devide_num) > 0) {
        count = cal_num / devide_num;
        for (int i = 0; i < count; i++) {
            str += Romenum;
        }
        result = cal_num % devide_num;
    }
    else {
        result = cal_num;
    }

    return result;
}

int translate_Rome2num(string str1) {
    int result = 0;
    for (int i = 0; i < str1.length(); i++) {
        string A = str1.substr(i, 1);
        if (A == "M") {
            result += 1000;
        }
        else if (A == "D") {
            result += 500;
        }
        else if (A == "C") {
            result += 100;
        }
        else if (A == "L") {
            result += 50;
        }
        else if (A == "X") {
            result += 10;
        }
        else if (A == "V") {
            result += 5;
        }
        else if (A == "I") {
            result += 1;
        }
    }
    return result;
}
/*

��ȣ	��
I	1
V	5
X	10
L	50
C	100
D	500
M	1000
*/