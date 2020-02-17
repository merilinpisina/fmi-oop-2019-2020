#include <iostream>
#include <time.h>
using namespace std;
int a[20][20];

int n, x1, y1, x2, y2;
void init();
bool way(int x1, int y1);
int main()
{
    init();
    cout << "Enter koord begins and end" << endl;
    cout << "x1 = ";
    cin >> x1;
    cout << "y1 = ";
    cin >> y1;
    cout << "x2 = ";
    cin >> x2;
    cout << "y2 = ";
    cin >> y2;
    if (way(x1, y1))
        cout << "Yes " << endl;
    else
        cout << "No " << endl;
    return 0;
}
void init()
{
    srand(time(NULL));
    cout << "n = ";
    cin >> n;
    int i, j;
    for (i = 0; i <= n - 1; i++)
        for (j = 0; j <= n - 1; j++)
            a[i][j] = rand() % 2;
    for (i = 0; i <= n - 1; i++)
    {
        for (j = 0; j <= n - 1; j++)
            cout << a[i][j] << " ";
        cout << '\n';
    }
}
bool way(int x1, int y1)
{
    if (x1 < 0 || x1 > n - 1 || y1 < 0 || y1 > n - 1 || x2 < 0 || x2 > n - 1 || y2 < 0 || y2 > n - 1)
        return false;
    if (x1 == x2 && y1 == y2)
        return true;
    if (a[x1][y1] == 0)
        return false;
    a[x1][y1] = 0;
    bool b = way(x1 + 1, y1) || way(x1 - 1, y1) || way(x1, y1 + 1) || way(x1, y1 - 1) ||
             way(x1 - 1, y1 - 1) || way(x1 - 1, y1 + 1) || way(x1 + 1, y1 - 1) || way(x1 + 1, y1 + 1);
    a[x1][y1] = 1;
    return b;
}