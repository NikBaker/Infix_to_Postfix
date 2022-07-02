#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <map>
#include <set>
#include <stdlib.h>
using namespace std;

struct MyEl
{
    char for_char;
    double for_const = 0;
};

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

int main()
{
    // ОПЕРАНДАМИ МОГУТ БЫТЬ ЛИБО БУКВЫ, ЛИБО ВЕЩЕСТВЕННЫЕ КОНСТАНТЫ

    string stack = "";
    string postfix = "";

    vector<MyEl> postfix_my;

    string input= "";

    cout << "Enter the expression: " << endl;
    cin >> input;

    map<char, double> Map_for_chars;    // map<string, double> Map_for_chars???;
    set<char> Set_for_chars;
    
    // Выделим из входной строки константы и добавим их через цифры в мапу
    string sub;
    int count_of_sym = 0; // количество символов в подстроке
    int number_of_const = 0; // номер константы
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] >= '0' && input[i] <= '9') {  //  если встретили цифру
            sub.push_back(input[i]);
            int number_of_dots = 0;
            count_of_sym++;
            i--; // возвращаемся на позицию до начала константы
            int j = i + 2; // новый индекс для добавления оставшейся части константы в подстроку
            while (input[j] == '.' || (input[j] >= '0' && input[j] <= '9')) {
                if (input[j] == '.') {
                    number_of_dots++;
                }
                sub.push_back(input[j]);
                j++;
                count_of_sym++;
            }
            if (number_of_dots > 1) {
                cout << "Wrong format" << endl;
                return 3;
            }

            input = input.erase(i + 1, count_of_sym); // удаляем из строки подстроку с константой
            number_of_const++;
            input.insert(i + 1, to_string(number_of_const)); // добавляем в строку вместо константы её идентификатор (номер константы)

            string s = to_string(number_of_const);
            // s[0] - это только первый символ. Если номер константы будет равен 12, то s[0] = 1 и произойдет коллизия с 1!!!
            Map_for_chars[s[0]] = atof(sub.c_str()); // добавляем в мапу по нашему идентификатору значение константы

            sub = "";
            count_of_sym = 0;
            i+=2; // перемещаемся на позицию после установленного идентификатора

        }
    }

    // Заполняем множество уникальных операндов нашего выражения
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] >= 'a' && input[i] <= 'z' || input[i] >= 'A' && input[i] <= 'Z') {
            Set_for_chars.insert(input[i]);
        }
    }

    double tempo = 0;
    // Вводим значения для операндов нашего выражения
    for (const auto& oper : Set_for_chars) {
        cout << "Enter the value for " << oper << ": ";
        cin >> tempo;
        cout << endl;
        Map_for_chars[oper] = tempo;
    }
    
    for (auto it = begin(input); it != end(input); ++it) {
        auto c = *it;
        if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '1' && c <= '9') { // 1. Константы и переменные кладутся в формируемую запись
            postfix.push_back(c);
            continue;
        }

        if (c == '(') { // 3. Открывающая скобка кладется в стек.
            stack.push_back(c);
            continue;
        }

        if (c == '-') {
            if (it == begin(input) || *prev(it) == '(' || *prev(it) == '+' || *prev(it) == '-' || *prev(it) == '*' || *prev(it) == '/') {
                c = '~';
            }
        }
        
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '~') { // 2. При появлении операции в исходном массиве :

            auto it11 = find(stack.begin(), stack.end(), '~');
            auto it1 = find(stack.begin(), stack.end(), '+');
            auto it2 = find(stack.begin(), stack.end(), '-');
            auto it3 = find(stack.begin(), stack.end(), '*');
            auto it4 = find(stack.begin(), stack.end(), '/');

            // 2.a) Если в стеке нет операций или верхним элементом стека является открывающая скобка, операция кладется в стек;
            if ((it1 == stack.end() && it2 == stack.end() && it3 == stack.end() && it4 == stack.end() && it11 == stack.end()) || (stack[stack.size() - 1] == '(')) {
                stack.push_back(c);
            }
            // 2.b) Если новая операция имеет больший приоритет, чем верхняя операция в стеке, то новая операция кладется в стек;
            else if (Priority(c) > Priority(stack[stack.size() - 1])) { // (c == '*' || c == '/') && (stack[stack.size() - 1] == '+' || stack[stack.size() - 1] == '-')
                stack.push_back(c);
            }
            // 2.c) Если новая операция имеет меньший или равный приоритет, чем верхняя операция в стеке, то операции, находящиеся в стеке,
            //      до ближайшей открывающей скобки или до операции с приоритетом меньшим, чем у новой операции, перекладываются в формируемую запись,
            //      а новая операция кладется в стек.
            else {
                    for (int i = stack.size() - 1; i >= 0; --i) {
                        if (stack[i] != '(' && Priority(stack[i]) >= Priority(c)) { // && (i != 0)
                            postfix.push_back(stack[i]);
                            stack = stack.erase(i, 1);
                        }
                        else {
                            break;
                        }
                    }
               
                stack.push_back(c);

            }
            continue;
        }

        // 4. Закрывающая скобка выталкивает из стека в формируемую запись все операции до ближайшей открывающей скобки, открывающая
        //    скобка удаляется из стека.
        if (c == ')') {  
            auto it7 = find(stack.begin(), stack.end(), '(');

            if (it7 != stack.end()) {
                for (int i = stack.size() - 1; i >= 0; --i) {
                    if (stack[i] != '(') {
                        postfix.push_back(stack[i]);
                    }
                    else {
                        stack = stack.erase(i, stack.size() - i);
                        break;
                    }
                }
            }
            // Если стек закончился до того, как был встречен токен открывающая скобка, то в выражении пропущена скобка.
            else {
                cout << "Wrong expression" << endl;
                return 1;
            }
        }
        else { // Если встретилось что-то кроме операндов, операций, констант или скобочек
            cout << "Wrong expression" << endl; 
            return 1;
        }

    }

    // 5. После того, как мыдобрались до конца исходного выражения, операции, оставшиеся в стеке, перекладываются в формируемое выражение.
    
    for (int i = stack.size() - 1; i >= 0; --i) {
        //  Если токен оператор на вершине стека — открывающая скобка, то в выражении пропущена скобка.
        if (stack[i] == '(') {
            cout << "Wrong expression" << endl;
            return 1;
        }
        postfix.push_back(stack[i]);
    }


    //cout << "Postfix form: " << endl;
    //cout << postfix << endl;

    cout << endl;

    // Вычисление выражения по постфиксной записи и средствами программы: 
    
    // 1. Обработка входного символа
    //    * Если на вход подан операнд, он помещается на вершину стека.
    //    * Если на вход подан знак операции, то соответствующая операция выполняется над требуемым количеством значений, извлечённых из стека, 
    //      взятых в порядке добавления.Результат выполненной операции кладётся на вершину стека.
    // 2. Если входной набор символов обработан не полностью, перейти к шагу 1.
    // 3. После полной обработки входного набора символов результат вычисления выражения лежит на вершине стека.

    vector<double> res_of_expr;
    double temp;
    for (int i = 0; i < postfix.size(); ++i) {
        if (postfix[i] >= 'a' && postfix[i] <= 'z' || postfix[i] >= 'A' && postfix[i] <= 'Z' || postfix[i] >= '1' && postfix[i] <= '9') {
            res_of_expr.push_back(Map_for_chars[postfix[i]]); 
        }
        else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/') {
            if (res_of_expr.size() == 1) {
                cout << "Wrong format" << endl;
                return 3;
            }
            try {
                double temp_res = Operation(postfix[i], res_of_expr[res_of_expr.size() - 2], res_of_expr[res_of_expr.size() - 1]);
                res_of_expr.pop_back();
                res_of_expr.pop_back();
                res_of_expr.push_back(temp_res);
            }
            catch (const char* exception) {
                cout << exception << endl;
                return 2;
            }
        }
        else if (postfix[i] == '~') {
            if (res_of_expr.size() == 0) {
                cout << "Wrong format" << endl;
                return 3;
            }
            double temp_minus = UnMinus(res_of_expr[res_of_expr.size() - 1]);
            res_of_expr.pop_back();
            res_of_expr.push_back(temp_minus);
        }
    }
 
    // для определения корректности в конце проверить, что размер стека равен 1
    if (res_of_expr.size() == 1) {
        if (number_of_const == 0) {
            cout << "Postfix form: " << endl;
            cout << postfix << endl;
            cout << endl;

            cout << "Result of expression: " << endl;
            cout << res_of_expr.back() << endl;
        }
        else {
            for (int i = 0; i < postfix.size(); ++i) {
                if (postfix[i] >= '1' && postfix[i] <= '9') {
                    string substr = to_string(Map_for_chars[postfix[i]]);
                    int j = substr.size() - 1;
                    while (substr[j] == '0') {
                        substr = substr.erase(j, 1);
                        j--;
                    }

                    if (substr[substr.size() - 1] == '.') {
                        substr = substr.erase(j, 1);
                    }

                    substr += ' ';

                    postfix = postfix.erase(i, 1);
                    std::copy(substr.begin(), substr.end(), std::inserter(postfix, postfix.begin() + i));
                    //cout << "substr.size() = " << substr.size() << endl;
                    i += substr.size()-1;
                }
            }
            
            cout << "Postfix form: " << endl;
            cout << postfix << endl;
            cout << endl;

            cout << "Result of expression: " << endl;
            cout << res_of_expr.back() << endl;

        }
        
    }
    else {
        cout << "Wrong format" << endl;
        return 3;
    }
    
    return 0;
}

