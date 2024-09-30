#include <bits/stdc++.h>
using namespace std;

void build(int ind, int low, int high, int arr[], int seg[], int flag)
{
    if (low == high)
    {
        seg[ind] = arr[low];
        return;
    }

    int mid = (low + high) / 2;
    build(2 * ind + 1, low, mid, arr, seg, !flag);
    build(2 * ind + 2, mid + 1, high, arr, seg, !flag);

    if (flag)
    {
        seg[ind] = seg[2 * ind + 1] | seg[2 * ind + 2];
    }
    else
    {
        seg[ind] = seg[2 * ind + 1] ^ seg[2 * ind + 2];
    }
}

// int query(int ind, int low, int high, int l, int r)
// {
//     // no overlap
//     if (r < low || high < l)
//     {
//         return INT_MAX;
//     }

//     // complete overlap
//     if (low >= l && high <= r)
//     {
//         return seg[ind];
//     }

//     int mid = (low + high) / 2;

//     int left = query(2 * ind + 1, low, mid, l, r);
//     int right = query(2 * ind + 2, mid + 1, high, l, r);

//     return min(left, right);
// }

void update(int ind, int low, int high, int i, int val, int seg[], int flag)
{
    if (low == high)
    {
        seg[ind] = val;
        return;
    }

    int mid = (low + high) / 2;

    if (i <= mid)
    {
        update(2 * ind + 1, low, mid, i, val, seg, !flag);
    }
    else
    {
        update(2 * ind + 2, mid + 1, high, i, val, seg, !flag);
    }

    if (flag)
    {
        seg[ind] = seg[2 * ind + 1] | seg[2 * ind + 2];
    }
    else
    {
        seg[ind] = seg[2 * ind + 1] ^ seg[2 * ind + 2];
    }
}

int main()
{
    int n, q;
    cin >> n >> q;

    int el = pow(2, n);

    int arr[el];
    for (int i = 0; i < el; i++)
    {
        cin >> arr[i];
    }

    int seg[4 * el];

    if (el % 2 == 0)
    {
        build(0, 0, el - 1, arr, seg, 0);
    }
    else
    {
        build(0, 0, el - 1, arr, seg, 1);
    }

    while (q--)
    {
        int i, val;
        cin >> i >> val;

        i--;

        if (n % 2 == 0)
        {
            update(0, 0, el - 1, i, val, seg, 0);
        }
        else
        {
            update(0, 0, el - 1, i, val, seg, 1);
        }

        cout << seg[0] << endl;
    }

    return 0;
}