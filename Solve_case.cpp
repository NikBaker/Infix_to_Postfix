#include <iostream>
#include <string>

#include "Solve_case.h"

using std::to_string;
using std::cout;
using std::cin;
using std::endl;

Solve_case::Solve_case() {
    m = {};
    /*string stack = "";
    vector<string> postfix_;
    string sub_str;*/
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

bool Solve_case::Is_Unar_Minus(string& in, int& pos) {
    return (in[pos] == in[0] || in[pos - 1] == '(' || in[pos - 1] == '+' || in[pos - 1] == '-' || in[pos - 1] == '*' || in[pos - 1] == '/');
}

bool Solve_case::Is_operation(const char& ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '~');
}

bool Solve_case::Add_number_to_Postfix(string& in, string& sub, int& pos, vector<string>& postfix) {
    if (Is_leter(in[pos + 1])) {    // �������� �� ������������ ���������� ��������������
        return false;
    }
    else {
        sub.push_back(in[pos]);
        int number_of_dots = 0;

        int j = pos + 1;
        while (in[j] == '.' || (in[j] >= '0' && in[j] <= '9')) {
            if (in[j] == '.') {
                number_of_dots++;
            }
            sub.push_back(in[j]);
            j++;
        }
        if (number_of_dots > 1) {
            cout << "Wrong format of const (numbers of dots > 1)" << endl;
            return false;
        }
        // ��������� ��������� � ����������� ������
        postfix.push_back(sub);
        sub = "";
        pos = j - 1; // ������������ �� ������� ����� ���������
        return true;
    }
}

void Solve_case::Add_variable_to_Postfix(string& in, string& sub, int& pos, vector<string>& postfix) {
    sub.push_back(in[pos]);
    int j = pos + 1;
    while ((in[j] >= '0' && in[j] <= '9') || (in[j] >= 'a' && in[j] <= 'z') || (in[j] >= 'A' && in[j] <= 'Z')) {
        sub.push_back(in[j]);
        j++;
    }
    // ��������� �������� ���������� � ����������� ������
    if (m.find(sub) == m.end()){    // ���� � ��������� ��� �� ���� ����� ����������
        double temp;
        cout << "Enter the value for " << sub << ": ";
        cin >> temp;
        m[sub] = temp;  //  ��������� � ���� �������� ��� ����������
    }
    postfix.push_back(sub);     //
    sub = "";
    pos = j - 1; // ������������ �� ������� ����� ����������
}

void Solve_case::Add_operation(string& in, vector<string>& postfix, string& st, int& pos) {
    auto it11 = find(st.begin(), st.end(), '~');
    auto it1 = find(st.begin(), st.end(), '+');
    auto it2 = find(st.begin(), st.end(), '-');
    auto it3 = find(st.begin(), st.end(), '*');
    auto it4 = find(st.begin(), st.end(), '/');

    // 2.a) ���� � ����� ��� �������� ��� ������� ��������� ����� �������� ����������� ������, �������� �������� � ����;
    if ((it1 == st.end() && it2 == st.end() && it3 == st.end() && it4 == st.end() && it11 == st.end()) || (st[st.size() - 1] == '(')) {
        st.push_back(in[pos]);
    }
    // 2.b) ���� ����� �������� ����� ������� ���������, ��� ������� �������� � �����, �� ����� �������� �������� � ����;
    else if (Priority(in[pos]) > Priority(st[st.size() - 1])) {
        st.push_back(in[pos]);
    }
    // 2.c) ���� ����� �������� ����� ������� ��� ������ ���������, ��� ������� �������� � �����, �� ��������, ����������� � �����,
    //      �� ��������� ����������� ������ ��� �� �������� � ����������� �������, ��� � ����� ��������, ��������������� � ����������� ������,
    //      � ����� �������� �������� � ����.
    else {
        for (int j = st.size() - 1; j >= 0; --j) {
            if (st[j] != '(' && (Priority(st[j]) >= Priority(in[pos]))) {
                postfix.push_back(string(1, st[j]));
                st = st.erase(j, 1);
            }
            else {
                break;
            }
        }
        st.push_back(in[pos]);
    }
}

bool Solve_case::Push(string& st, vector<string>& postfix) {
    auto it = find(st.begin(), st.end(), '(');

    if (it != st.end()) {
        for (int i = st.size() - 1; i >= 0; --i) {
            if (st[i] != '(') {
                postfix.push_back(string(1, st[i]));
            }
            else {
                st = st.erase(i, st.size() - i);
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

bool Solve_case::Put_the_rest_of_stack(string& st, vector<string>& postfix) {
    for (int i = st.size() - 1; i >= 0; --i) {
        //  ���� �� ������� ����� ����������� ������, �� � ��������� ��������� ������.
        if (st[i] == '(') {
            cout << "Wrong expression" << endl;
            return false;
        }
        postfix.push_back(string(1, st[i]));
    }
    cout << endl;
    return true;
}

bool Solve_case::Infix_To_Postfix(string& in, string& stack, vector<string>& postfix_, string& sub_str) {
    for (int i = 0; i < in.size(); ++i) {
        //1. ��������� � ���������� �������� � ����������� ������
        if (Is_number(in[i])) {
            if (!Add_number_to_Postfix(in, sub_str, i, postfix_)) {
                cout << "Wrong format of number" << endl;
                return false;
            }
        }
        else if (Is_leter(in[i])) {
            Add_variable_to_Postfix(in, sub_str, i, postfix_);
        }
        // 3. ����������� ������ �������� � ����.
        else if (in[i] == '(') {
            stack.push_back(in[i]);
        }
        else if (Is_operation(in[i])) {
            if (in[i] == '-') {
                // ������� �����
                if (Is_Unar_Minus(in, i)) {
                    in[i] = '~';
                }
                Add_operation(in, postfix_, stack, i);
            }
            else {
                Add_operation(in, postfix_, stack, i);
            }
        }
        // 4. ����������� ������ ����������� �� ����� � ����������� ������ ��� �������� �� ��������� ����������� ������, �����������
        //    ������ ��������� �� �����.
        else if (in[i] == ')') {
            if (!Push(stack, postfix_)) {
                cout << "Wrong format (the number of left brackets is not equal the number of right brackets)" << endl;
                return false;
            }
        }
        else {
            cout << "Wrong expression" << endl;
            cout << "Unknown character: " << in[i] << endl;
            return false;
        }
    }
    // 5. ����� ����, ��� ����������� �� ����� ��������� ���������, ��������, ���������� � �����, ��������������� � ����������� ���������.
    if (!Put_the_rest_of_stack(stack, postfix_)) {
        cout << "Wrong format (the number of left brackets is not equal the number of right brackets)" << endl;
        return false;
    }
    return true;
}

bool Solve_case::Result_of_the_expr(vector<string>& postfix_) {
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
                /*auto it = find(m.begin(), m.end(), c);
                if (it != m.end()) {
                    
                }*/
                
            }
        }
        cout << endl;
        cout << "Result of expression: " << endl;
        cout << res_of_expr.back() << endl;
        return true;
    }
    else {
        cout << "Wrong format" << endl;     //
        return false;
    }
}

//void Solve_case::Input() {
//    // ���� ��������� ���������
//    input = "";
//    cout << "Enter the expression: " << endl;
//    cin >> input;
//}

bool Solve_case::Solve() {
    // ���� ��������� ���������
    string input = "";
    cout << "Enter the expression: " << endl;
    cin >> input;

    string stack = "";
    vector<string> postfix_;
    string sub_str;
    if (!Infix_To_Postfix(input, stack, postfix_, sub_str)) {
        return false;
    }
    else {
        if (!Result_of_the_expr(postfix_)) {
            return false;
        }
    }
    return true;
}