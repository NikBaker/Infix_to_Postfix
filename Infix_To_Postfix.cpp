#include <iostream>
#include <vector>
#include <string>

#include "Solve_case.h"

using std::cout;
using std::endl;

int main()
{
    Solve_case Case;
    Case.Input();
    if (!Case.Solve()) {
        cout << "End with error!" << endl;
        return 1;
    }
    else {
        cout << "End with succes!" << endl;
        return 0;
    }

    return 0;
}

