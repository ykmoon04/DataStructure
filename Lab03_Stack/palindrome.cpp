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

    cout << "문자열을 입력하세요 : ";
    cin >> input;
    len = input.length();

    if (len > 100) {
        cout << "ERROR : 문자열 최대 길이 초과" << endl;
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