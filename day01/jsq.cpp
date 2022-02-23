#include <iostream>
using namespace std;

int main()
{
    char c, op;
    float i, j;

    while (true)
    {
        cout << "Press Any Key (Exclude Enter, Space) To Start, Press 'q' To Exit" << endl;
        cin >> c;
        if (c == 'q')
        {
            cout << "Bye!!" << endl;
            break;
        }
        cout << "Input I Enter, Operator Enter And J, Enter" << endl;
        cin >> i >> op >> j;
        switch (op)
        {
        case '+':
            cout << i << op << j << "=" << i + j << endl;
            break;
        case '-':
            cout << i << op << j << "=" << i - j << endl;
            break;
        case '*':
            cout << i << op << j << "=" << i * j << endl;
            break;
        case '/':
            if (j == 0)
            {
                cout << "J Must Not Be 0 !!" << endl;
                break;
            }
            cout << i << op << j << "=" << i / j << endl;
            break;

        default:
            cout << "ERROR: Unknow Operator" << endl;
            break;
        }
    }
    return 0;
}