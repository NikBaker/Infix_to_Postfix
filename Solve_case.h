#pragma once

#include <iostream>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class Solve_case
{private:
    map<string, double> m;      // мапа для хранения значений переменных
    //string input;               // входная инфиксная запись      
    //string stack = "";          // стек для операций и скобок
    //vector<string> postfix_;    // постфиксная запись
    //string sub_str;             
private:
    void Input();
    // Приоритет операции
    int Priority(const char& ch);
    // Результат операции ch над двумя операндами a И b
    double Operation(const char& ch, const double& a, const double& b);
    // Унарный минус
    double UnMinus(const double& a) { return -a; }
    bool Is_number(const char& ch);
    bool Is_leter(const char& ch);
    bool Is_Unar_Minus(string& in, int& pos);
    bool Is_operation(const char& ch);
    // Занесение константы в постфиксную запись
    bool Add_number_to_Postfix(string& in, string& sub, int& pos, vector<string>& postfix);
    // Занесение переменной в постфиксную запись
    void Add_variable_to_Postfix(string& in, string& sub, int& pos, vector<string>& postfix);
    // Занесение операции в стек или в постфиксную запись
    void Add_operation(string& in, vector<string>& postfix, string& st, int& pos);
    // Выталкивание из стека операций
    bool Push(string& st, vector<string>& postfix);
    // Занесение остатка стека в постфиксную запись
    bool Put_the_rest_of_stack(string& st, vector<string>& postfix);
    bool Infix_To_Postfix(string& in, string& stack, vector<string>& postfix_, string& sub_str);
    bool Result_of_the_expr(vector<string>& postfix_);

public:
    Solve_case();
    bool Solve();
};

