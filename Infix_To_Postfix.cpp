#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <map>
#include <set>
#include <stdlib.h>

using namespace std;

// Приоритеты операций
int Priority(const char& ch) {
    if (ch == '+' || ch == '-') {
        return 1;
    } else if (ch == '*' || ch == '/'){
        return 2;
    }
    else if (ch == '~') { // унарный минус
        return 3;
    }
}

// Операции
double Operation(const char& ch, const double& a, const double& b) {
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

double UnMinus(const double& a) {
    return -a;
}

bool Is_number(const char& ch) {
    return (ch >= '0' && ch <= '9');
}

bool Is_leter(const char& ch) {
    return (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z');
}

bool Is_Unar_Minus(string& in, int& pos) {
    return (in[pos] == in[0] || in[pos - 1] == '(' || in[pos - 1] == '+' || in[pos - 1] == '-' || in[pos - 1] == '*' || in[pos - 1] == '/');
}

bool Is_operation(const char& ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '~');
}

bool Add_number_to_Postfix(string& in, string& sub, int& pos, vector<string>& postfix) {
    if (Is_leter(in[pos + 1])) {    // проверка на правильность введенного идентификатора
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
            //cout << "Wrong format" << endl;
            return false;           // Выход
        }
        // Добавляем константу в формируемую запись
        postfix.push_back(sub);
        sub = "";
        pos = j - 1; // перемещаемся на позицию после константы
        return true;
    }   
}

void Add_variable_to_Postfix(string& in, string& sub, int& pos, vector<string>& postfix) {
    sub.push_back(in[pos]);
    int j = pos + 1;
    while ((in[j] >= '0' && in[j] <= '9') || (in[j] >= 'a' && in[j] <= 'z') || (in[j] >= 'A' && in[j] <= 'Z')) {
        sub.push_back(in[j]);
        j++;
    }
    // Добавляем значения переменных в формируемую запись
    double temp;
    cout << "Enter the value for " << sub << ": ";
    cin >> temp;
    postfix.push_back(to_string(temp));
    sub = "";
    pos = j - 1; // перемещаемся на позицию после переменной
}

void Add_operation(string& in, vector<string>& postfix, string& st, int& pos) {
    auto it11 = find(st.begin(), st.end(), '~');
    auto it1 = find(st.begin(), st.end(), '+');
    auto it2 = find(st.begin(), st.end(), '-');
    auto it3 = find(st.begin(), st.end(), '*');
    auto it4 = find(st.begin(), st.end(), '/');

    // 2.a) Если в стеке нет операций или верхним элементом стека является открывающая скобка, операция кладется в стек;
    if ((it1 == st.end() && it2 == st.end() && it3 == st.end() && it4 == st.end() && it11 == st.end()) || (st[st.size() - 1] == '(')) {
        st.push_back(in[pos]);
    }
    // 2.b) Если новая операция имеет больший приоритет, чем верхняя операция в стеке, то новая операция кладется в стек;
    else if (Priority(in[pos]) > Priority(st[st.size() - 1])) {
        st.push_back(in[pos]);
    }
    // 2.c) Если новая операция имеет меньший или равный приоритет, чем верхняя операция в стеке, то операции, находящиеся в стеке,
    //      до ближайшей открывающей скобки или до операции с приоритетом меньшим, чем у новой операции, перекладываются в формируемую запись,
    //      а новая операция кладется в стек.
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

bool Push(string& st, vector<string>& postfix) {
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
    // Если стек закончился до того, как был встречен токен открывающая скобка, то в выражении пропущена скобка.
    else {
        //cout << "Wrong expression" << endl;
        return false;
    }
}

bool Put_the_rest_of_stack(string& st, vector<string>& postfix) {
    for (int i = st.size() - 1; i >= 0; --i) {
        //  Если на вершине стека открывающая скобка, то в выражении пропущена скобка.
        if (st[i] == '(') {
            cout << "Wrong expression" << endl;
            return false;
        }
        postfix.push_back(string(1, st[i]));
    }
    cout << endl;
    return true;
}

bool Infix_To_Postfix(string& in, string& stack, vector<string>& postfix_, string& sub_str) {
    for (int i = 0; i < in.size(); ++i) {
        //1. Константы и переменные кладутся в формируемую запись
        if (Is_number(in[i])) {     
            if (!Add_number_to_Postfix(in, sub_str, i, postfix_)) {
                cout << "Wrong format of number" << endl;
                return false;
            }
        }
        else if (Is_leter(in[i])) {
            Add_variable_to_Postfix(in, sub_str, i, postfix_);
        }
        // 3. Открывающая скобка кладется в стек.
        else if (in[i] == '(') {
            stack.push_back(in[i]);
        }
        else if (Is_operation(in[i])) {
            if (in[i] == '-') {
                // Унарный минус
                if (Is_Unar_Minus(in, i)) {
                    in[i] = '~';
                }
                Add_operation(in, postfix_, stack, i);  
            }
            else {
                Add_operation(in, postfix_, stack, i);  
            }
        }
        // 4. Закрывающая скобка выталкивает из стека в формируемую запись все операции до ближайшей открывающей скобки, открывающая
        //    скобка удаляется из стека.
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
    // 5. После того, как мыдобрались до конца исходного выражения, операции, оставшиеся в стеке, перекладываются в формируемое выражение.
    if (!Put_the_rest_of_stack(stack, postfix_)) {
        cout << "Wrong format (the number of left brackets is not equal the number of right brackets)" << endl;
        return false;
    }
    return true;
}

bool Result_of_the_expr(vector<string>& postfix_) {
    // Вычисление выражения по постфиксной записи: 

    // 1. Обработка входного символа
    //    * Если на вход подан операнд, он помещается на вершину стека.
    //    * Если на вход подан знак операции, то соответствующая операция выполняется над требуемым количеством значений, извлечённых из стека, 
    //      взятых в порядке добавления.Результат выполненной операции кладётся на вершину стека.
    // 2. Если входной набор символов обработан не полностью, перейти к шагу 1.
    // 3. После полной обработки входного набора символов результат вычисления выражения лежит на вершине стека.

    vector<double> res_of_expr;
    double temp;
    for (int i = 0; i < postfix_.size(); ++i) {
        if (postfix_[i] == "+" || postfix_[i] == "-" || postfix_[i] == "*" || postfix_[i] == "/") {
            if (res_of_expr.size() == 1) {
                cout << "Wrong format" << endl; //
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
                cout << "Wrong format" << endl;     //
                return false;
            }
            double temp_minus = UnMinus(res_of_expr[res_of_expr.size() - 1]);
            res_of_expr.pop_back();
            res_of_expr.push_back(temp_minus);
        }
        else {
            res_of_expr.push_back(atof(postfix_[i].c_str()));
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
                cout << atof(c.c_str()) << " ";
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

bool Solve() {
    // Ввод исходново выражения
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

int main()
{
    // ОПЕРАНДАМИ МОГУТ БЫТЬ ЛИБО ИДЕНТИФИКАТОРЫ(из букв и цифр, первая обязательно буква), ЛИБО ВЕЩЕСТВЕННЫЕ КОНСТАНТЫ

    if (!Solve()) {
        cout << "End with error!" << endl;
        return 3;
    }
    else {
        cout << "End with succes!" << endl;
        return 0;
    }
}

// Разбить main на несколько функций (может быть поместить их в отдельный класс)

