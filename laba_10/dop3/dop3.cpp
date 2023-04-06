#include <iostream>
#define n 5

using namespace std;

int NextSet(int* a)
{
    int j;
    static int numb{ 1 };

    do
    {
        j = n - 1;

        while (j != -1 && a[j] >= a[j + 1])
            j--;
        if (j == -1)
            return 0;

        int k = n - 1;

        while (a[j] >= a[k])
            k--;
        swap(a[j], a[k]);

        int l = j + 1, r = n - 1;

        while (l < r)
            swap(a[l++], a[r--]);
    } while (j > n - 1);
    cout.width(3);
    cout << ++numb << ":  ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;

    NextSet(a);
}

void main()
{
    int a[n]{};

    for (int i = 0; i < n; i++)
        a[i] = i + 1;

    cout.width(3);
    cout << n / n << ":  ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;

    NextSet(a);
}