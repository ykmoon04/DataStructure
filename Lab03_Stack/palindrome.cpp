#include <iostream>
#include "stackarr.cpp"

using namespace std;

bool isPalindrome(Stack<char>& test, string str) {
    for (int i = 0; i < str.length(); i++) {
        if (test.pop() != str.at(i)) return false;
    }
    return true;
}

void main() {
    string input;
    int len;

    cout << "���ڿ��� �Է��ϼ��� : ";
    cin >> input;
    len = input.length();

    if (len > 100) {
        cout << "ERROR : ���ڿ� �ִ� ���� �ʰ�" << endl;
        return;
    }

    Stack<char> test(len);

    for (int i = 0; i < len; i++) {
        test.push(input.at(i));
    }

    cout << boolalpha << isPalindrome(test, input) << endl;

    system("pause");
    return;
}