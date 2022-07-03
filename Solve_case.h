#pragma once

#include <iostream>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class Solve_case
{private:
    map<string, double> m;      // ���� ��� �������� �������� ����������
    //string input;               // ������� ��������� ������      
    //string stack = "";          // ���� ��� �������� � ������
    //vector<string> postfix_;    // ����������� ������
    //string sub_str;             
private:
    void Input();
    // ��������� ��������
    int Priority(const char& ch);
    // ��������� �������� ch ��� ����� ���������� a � b
    double Operation(const char& ch, const double& a, const double& b);
    // ������� �����
    double UnMinus(const double& a) { return -a; }
    bool Is_number(const char& ch);
    bool Is_leter(const char& ch);
    bool Is_Unar_Minus(string& in, int& pos);
    bool Is_operation(const char& ch);
    // ��������� ��������� � ����������� ������
    bool Add_number_to_Postfix(string& in, string& sub, int& pos, vector<string>& postfix);
    // ��������� ���������� � ����������� ������
    void Add_variable_to_Postfix(string& in, string& sub, int& pos, vector<string>& postfix);
    // ��������� �������� � ���� ��� � ����������� ������
    void Add_operation(string& in, vector<string>& postfix, string& st, int& pos);
    // ������������ �� ����� ��������
    bool Push(string& st, vector<string>& postfix);
    // ��������� ������� ����� � ����������� ������
    bool Put_the_rest_of_stack(string& st, vector<string>& postfix);
    bool Infix_To_Postfix(string& in, string& stack, vector<string>& postfix_, string& sub_str);
    bool Result_of_the_expr(vector<string>& postfix_);

public:
    Solve_case();
    bool Solve();
};

