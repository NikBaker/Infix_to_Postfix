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
    // Ввод исходново выражения
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
    else if (ch == '~') { // унарный минус
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
    if (Is_leter(input[pos + 1])) {
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
        // Добавляем константу в формируемую запись
        postfix_.push_back(sub_str);
        sub_str = "";
        pos = j - 1; // перемещаемся на позицию после константы
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
    // Добавляем значения переменных в формируемую запись
    if (m.find(sub_str) == m.end()){    // если в выражении ещё не было такой переменной
        double temp;
        cout << "Enter the value for " << sub_str << ": ";
        cin >> temp;
        m[sub_str] = temp;  //  добавляем в мапу значение для переменной
    }
    postfix_.push_back(sub_str);
    sub_str = "";
    pos = j - 1; // перемещаемся на позицию после переменной
}

void Solve_case::Add_operation(int& pos) {
    auto it11 = find(stack.begin(), stack.end(), '~');
    auto it1 = find(stack.begin(), stack.end(), '+');
    auto it2 = find(stack.begin(), stack.end(), '-');
    auto it3 = find(stack.begin(), stack.end(), '*');
    auto it4 = find(stack.begin(), stack.end(), '/');

    // 2.a) Если в стеке нет операций или верхним элементом стека является открывающая скобка, операция кладется в стек;
    if ((it1 == stack.end() && it2 == stack.end() && it3 == stack.end() && it4 == stack.end() && it11 == stack.end()) || (stack[stack.size() - 1] == '(')) {
        stack.push_back(input[pos]);
    }
    // 2.b) Если новая операция имеет больший приоритет, чем верхняя операция в стеке, то новая операция кладется в стек;
    else if (Priority(input[pos]) > Priority(stack[stack.size() - 1])) {
        stack.push_back(input[pos]);
    }
    // 2.c) Если новая операция имеет меньший или равный приоритет, чем верхняя операция в стеке, то операции, находящиеся в стеке,
    //      до ближайшей открывающей скобки или до операции с приоритетом меньшим, чем у новой операции, перекладываются в формируемую запись,
    //      а новая операция кладется в стек.
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
    // Если стек закончился до того, как был встречен токен открывающая скобка, то в выражении пропущена скобка.
    else {
        cout << "Wrong expression" << endl;
        return false;
    }
}

bool Solve_case::Put_the_rest_of_stack() {
    for (int i = stack.size() - 1; i >= 0; --i) {
        //  Если на вершине стека открывающая скобка, то в выражении пропущена скобка.
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
        //1. Константы и переменные кладутся в формируемую запись
        if (Is_number(input[i])) {
            if (!Add_number_to_Postfix(i)) {
                cout << "Wrong format of number" << endl;
                return false;
            }
        }
        else if (Is_leter(input[i])) {
            Add_variable_to_Postfix(i);
        }
        // 3. Открывающая скобка кладется в стек.
        else if (input[i] == '(') {
            stack.push_back(input[i]);
        }
        // 2. Встретили операцию
        else if (Is_operation(input[i])) {
            if (input[i] == '-') {
                // Унарный минус
                if (Is_Unar_Minus(i)) {
                    input[i] = '~';
                }
                Add_operation(i);
            }
            else {
                Add_operation(i);
            }
        }
        // 4. Закрывающая скобка выталкивает из стека в формируемую запись все операции до ближайшей открывающей скобки, открывающая
        //    скобка удаляется из стека.
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
    // 5. После того, как мыдобрались до конца исходного выражения, операции, оставшиеся в стеке, перекладываются в формируемое выражение.
    if (!Put_the_rest_of_stack()) {
        cout << "Wrong format (the number of left brackets is not equal the number of right brackets)" << endl;
        return false;
    }
    return true;
}

bool Solve_case::Result_of_the_expr() {
    // Вычисление выражения по постфиксной записи: 

    // 1. Обработка входного символа
    //    * Если на вход подан операнд, он помещается на вершину стека.
    //    * Если на вход подан знак операции, то соответствующая операция выполняется над требуемым количеством значений, извлечённых из стека, 
    //      взятых в порядке добавления.Результат выполненной операции кладётся на вершину стека.
    // 2. Если входной набор символов обработан не полностью, перейти к шагу 1.
    // 3. После полной обработки входного набора символов результат вычисления выражения лежит на вершине стека.

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

    // в конце проверить, что размер стека равен 1 (итоговое значение)
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
