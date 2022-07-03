#include <iostream>
#include <string>

#include "Solve_case.h"

using std::to_string;
using std::cout;
using std::cin;
using std::endl;

Solve_case::Solve_case() {
    m = {};
    string stack = "";
    vector<string> postfix_ = {};
    string sub_str = "";
    input = "";
}

void Solve_case::Input() {
    // ���� ��������� ���������
    cout << "Enter the expression: " << endl;
    cin >> input;
}

int Solve_case::Priority(const char& ch) {
    if (ch == '+' || ch == '-') {
        return 1;
    }
    else if (ch == '*' || ch == '/') {
        return 2;
    }
    else if (ch == '~') { // ������� �����
        return 3;
    }
}

double Solve_case::Operation(const char& ch, const double& a, const double& b) {
    if (ch == '+') {
        return a + b;
    }
    else if (ch == '-') {
        return a - b;
    }
    else if (ch == '*') {
        return a * b;
    }
    else if (ch == '/') {
        if (b != 0) {
            return a / b;
        }
        else {
            throw "Division by zero!";
        }
    }
}

bool Solve_case::Is_number(const char& ch) {
    return (ch >= '0' && ch <= '9');
}

bool Solve_case::Is_leter(const char& ch) {
    return (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z');
}

bool Solve_case::Is_Unar_Minus(int& pos) {
    return (input[pos] == input[0] || input[pos - 1] == '(' || input[pos - 1] == '+' || input[pos - 1] == '-' || input[pos - 1] == '*' || input[pos - 1] == '/');
}

bool Solve_case::Is_operation(const char& ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '~');
}

bool Solve_case::Add_number_to_Postfix(int& pos) {
    if (Is_leter(input[pos + 1])) {    // �������� �� ������������ ���������� ��������������
        return false;
    }
    else {
        sub_str.push_back(input[pos]);
        int number_of_dots = 0;

        int j = pos + 1;
        while (input[j] == '.' || (input[j] >= '0' && input[j] <= '9')) {
            if (input[j] == '.') {
                number_of_dots++;
            }
            sub_str.push_back(input[j]);
            j++;
        }
        if (number_of_dots > 1) {
            cout << "Wrong format of const (numbers of dots > 1)" << endl;
            return false;
        }
        // ��������� ��������� � ����������� ������
        postfix_.push_back(sub_str);
        sub_str = "";
        pos = j - 1; // ������������ �� ������� ����� ���������
        return true;
    }
}

void Solve_case::Add_variable_to_Postfix(int& pos) {
    sub_str.push_back(input[pos]);
    int j = pos + 1;
    while ((input[j] >= '0' && input[j] <= '9') || (input[j] >= 'a' && input[j] <= 'z') || (input[j] >= 'A' && input[j] <= 'Z')) {
        sub_str.push_back(input[j]);
        j++;
    }
    // ��������� �������� ���������� � ����������� ������
    if (m.find(sub_str) == m.end()){    // ���� � ��������� ��� �� ���� ����� ����������
        double temp;
        cout << "Enter the value for " << sub_str << ": ";
        cin >> temp;
        m[sub_str] = temp;  //  ��������� � ���� �������� ��� ����������
    }
    postfix_.push_back(sub_str);     //
    sub_str = "";
    pos = j - 1; // ������������ �� ������� ����� ����������
}

void Solve_case::Add_operation(int& pos) {
    auto it11 = find(stack.begin(), stack.end(), '~');
    auto it1 = find(stack.begin(), stack.end(), '+');
    auto it2 = find(stack.begin(), stack.end(), '-');
    auto it3 = find(stack.begin(), stack.end(), '*');
    auto it4 = find(stack.begin(), stack.end(), '/');

    // 2.a) ���� � ����� ��� �������� ��� ������� ��������� ����� �������� ����������� ������, �������� �������� � ����;
    if ((it1 == stack.end() && it2 == stack.end() && it3 == stack.end() && it4 == stack.end() && it11 == stack.end()) || (stack[stack.size() - 1] == '(')) {
        stack.push_back(input[pos]);
    }
    // 2.b) ���� ����� �������� ����� ������� ���������, ��� ������� �������� � �����, �� ����� �������� �������� � ����;
    else if (Priority(input[pos]) > Priority(stack[stack.size() - 1])) {
        stack.push_back(input[pos]);
    }
    // 2.c) ���� ����� �������� ����� ������� ��� ������ ���������, ��� ������� �������� � �����, �� ��������, ����������� � �����,
    //      �� ��������� ����������� ������ ��� �� �������� � ����������� �������, ��� � ����� ��������, ��������������� � ����������� ������,
    //      � ����� �������� �������� � ����.
    else {
        for (int j = stack.size() - 1; j >= 0; --j) {
            if (stack[j] != '(' && (Priority(stack[j]) >= Priority(input[pos]))) {
                postfix_.push_back(string(1, stack[j]));
                stack = stack.erase(j, 1);
            }
            else {
                break;
            }
        }
        stack.push_back(input[pos]);
    }
}

bool Solve_case::Push() {
    auto it = find(stack.begin(), stack.end(), '(');

    if (it != stack.end()) {
        for (int i = stack.size() - 1; i >= 0; --i) {
            if (stack[i] != '(') {
                postfix_.push_back(string(1, stack[i]));
            }
            else {
                stack = stack.erase(i, stack.size() - i);
                break;
            }
        }
        return true;
    }
    // ���� ���� ���������� �� ����, ��� ��� �������� ����� ����������� ������, �� � ��������� ��������� ������.
    else {
        cout << "Wrong expression" << endl;
        return false;
    }
}

bool Solve_case::Put_the_rest_of_stack() {
    for (int i = stack.size() - 1; i >= 0; --i) {
        //  ���� �� ������� ����� ����������� ������, �� � ��������� ��������� ������.
        if (stack[i] == '(') {
            cout << "Wrong expression" << endl;
            return false;
        }
        postfix_.push_back(string(1, stack[i]));
    }
    cout << endl;
    return true;
}

bool Solve_case::Infix_To_Postfix() {
    for (int i = 0; i < input.size(); ++i) {
        //1. ��������� � ���������� �������� � ����������� ������
        if (Is_number(input[i])) {
            if (!Add_number_to_Postfix(i)) {
                cout << "Wrong format of number" << endl;
                return false;
            }
        }
        else if (Is_leter(input[i])) {
            Add_variable_to_Postfix(i);
        }
        // 3. ����������� ������ �������� � ����.
        else if (input[i] == '(') {
            stack.push_back(input[i]);
        }
        else if (Is_operation(input[i])) {
            if (input[i] == '-') {
                // ������� �����
                if (Is_Unar_Minus(i)) {
                    input[i] = '~';
                }
                Add_operation(i);
            }
            else {
                Add_operation(i);
            }
        }
        // 4. ����������� ������ ����������� �� ����� � ����������� ������ ��� �������� �� ��������� ����������� ������, �����������
        //    ������ ��������� �� �����.
        else if (input[i] == ')') {
            if (!Push()) {
                cout << "Wrong format (the number of left brackets is not equal the number of right brackets)" << endl;
                return false;
            }
        }
        else {
            cout << "Wrong expression" << endl;
            cout << "Unknown character: " << input[i] << endl;
            return false;
        }
    }
    // 5. ����� ����, ��� ����������� �� ����� ��������� ���������, ��������, ���������� � �����, ��������������� � ����������� ���������.
    if (!Put_the_rest_of_stack()) {
        cout << "Wrong format (the number of left brackets is not equal the number of right brackets)" << endl;
        return false;
    }
    return true;
}

bool Solve_case::Result_of_the_expr() {
    // ���������� ��������� �� ����������� ������: 

    // 1. ��������� �������� �������
    //    * ���� �� ���� ����� �������, �� ���������� �� ������� �����.
    //    * ���� �� ���� ����� ���� ��������, �� ��������������� �������� ����������� ��� ��������� ����������� ��������, ����������� �� �����, 
    //      ������ � ������� ����������.��������� ����������� �������� ������� �� ������� �����.
    // 2. ���� ������� ����� �������� ��������� �� ���������, ������� � ���� 1.
    // 3. ����� ������ ��������� �������� ������ �������� ��������� ���������� ��������� ����� �� ������� �����.

    vector<double> res_of_expr;
    for (int i = 0; i < postfix_.size(); ++i) {
        if (postfix_[i] == "+" || postfix_[i] == "-" || postfix_[i] == "*" || postfix_[i] == "/") {
            if (res_of_expr.size() == 1) {
                cout << "Wrong format" << endl; 
                return false;
            }
            try {
                double temp_res = Operation(postfix_[i][0], res_of_expr[res_of_expr.size() - 2], res_of_expr[res_of_expr.size() - 1]);
                res_of_expr.pop_back();
                res_of_expr.pop_back();
                res_of_expr.push_back(temp_res);
            }
            catch (const char* exception) {
                cout << exception << endl;
                return false;
            }
        }
        else if (postfix_[i] == "~") {
            if (res_of_expr.size() == 0) {
                cout << "Wrong format" << endl;
                return false;
            }
            double temp_minus = UnMinus(res_of_expr[res_of_expr.size() - 1]);
            res_of_expr.pop_back();
            res_of_expr.push_back(temp_minus);
        }
        else {
            if (m.find(postfix_[i]) != m.end()) {
                res_of_expr.push_back(m[postfix_[i]]);
            }
            else {
                res_of_expr.push_back(atof(postfix_[i].c_str()));
            }            
        }
    }

    // � ����� ���������, ��� ������ ����� ����� 1 (�������� ��������)
    if (res_of_expr.size() == 1) {
        cout << "Postfix form: " << endl;
        for (const auto& c : postfix_) {
            if (Is_operation(c[0])) {
                cout << c << " ";
            }
            else {
                if (m.find(c) != m.end()) {
                    cout << c << " ";
                }
                else {
                    cout << atof(c.c_str()) << " ";
                }
            }
        }
        cout << endl;
        cout << "Result of expression: " << endl;
        cout << res_of_expr.back() << endl;
        return true;
    }
    else {
        cout << "Wrong format" << endl;  
        return false;
    }
}

bool Solve_case::Solve() {
    if (!Infix_To_Postfix()) {
        return false;
    }
    else {
        if (!Result_of_the_expr()) {
            return false;
        }
    }
    return true;
}