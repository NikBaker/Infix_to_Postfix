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
    string input;               // ������� ��������� ������      
    string stack = "";          // ���� ��� �������� � ������
    vector<string> postfix_;    // ����������� ������
    string sub_str;             
private:
    // ��������� ��������
    int Priority(const char& ch);
    // ��������� �������� ch ��� ����� ���������� a � b
    double Operation(const char& ch, const double& a, const double& b);
    // ������� �����
    double UnMinus(const double& a) { return -a; }
    bool Is_number(const char& ch);
    bool Is_leter(const char& ch);
    bool Is_Unar_Minus(int& pos);
    bool Is_operation(const char& ch);
    // ��������� ��������� � ����������� ������
    bool Add_number_to_Postfix(int& pos);
    // ��������� ���������� � ����������� ������
    void Add_variable_to_Postfix(int& pos);
    // ��������� �������� � ���� ��� � ����������� ������
    void Add_operation(int& pos);
    // ������������ �� ����� ��������
    bool Push();
    // ��������� ������� ����� � ����������� ������
    bool Put_the_rest_of_stack();
    bool Infix_To_Postfix();
    bool Result_of_the_expr();

public:
    Solve_case();
    void Input();
    bool Solve();
};

