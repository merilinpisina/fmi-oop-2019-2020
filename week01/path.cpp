
#include <iostream>
using namespace std;

int a[20][20];
int n;
bool visited[20];
int path[20], br;
void init();
bool way(int first, int second);
int main()
{
    init();
    int first, second;
    cout << "First town: ";
    cin >> first;
    cout << "Second town: ";
    cin >> second;
    br = 1;
    path[0] = first;
    if (way(first, second))
    {
        cout << "yes \n";
        for (int i = 0; i <= br - 1; i++)
            cout << path[i] << " ";
        cout << endl;
    }
    else
        cout << "no \n";
    return 0;
}
void init()
{
    cout << "n = ";
    cin >> n;
    int i, j;
    for (i = 0; i <= n - 1; i++)
    {
        a[i][i] = 1;
        for (j = i + 1; j <= n - 1; j++)
        {
            cout << "a[" << i << "][" << j << "] = "
                 << "a[" << j << "][" << i << "] = ";
            cin >> a[i][j];
            a[j][i] = a[i][j];
        }
    }
}
bool way(int first, int second)
{
    int i;
    if (first == second)
        return true;
    visited[first] = true;
    for (i = 0; i < n; i++)
        if (a[first][i] && !visited[i])
        {
            path[br] = i;
            br++;
            if (way(i, second))
                return true;
            br--;
        }
    return false;
}

bool way2(int first, int second)
{
    if (first == second)
        return true;
    if (a[first][second] == 1)
        return true;
    bool b = false;
    for (int k = 0; b == false && k <= n - 2; k++)
        if (a[first][k] == 1)
        {
            a[first][k] = 0;
            a[k][first] = 0;
            b = way(k, second);
            a[first][k] = 1;
            a[k][first] = 1;
        }
    return b;
}