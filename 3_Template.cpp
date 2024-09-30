#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
    vector<int> seg;

public:
    SegmentTree(int n)
    {
        seg.resize(4 * n + 1);
    }

    void build(int ind, int low, int high, int arr[])
    {
        if (low == high)
        {
            seg[ind] = arr[low];
            return;
        }

        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);

        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    int query(int ind, int low, int high, int l, int r)
    {
        // no overlap
        if (r < low || high < l)
        {
            return INT_MAX;
        }

        // complete overlap
        if (low >= l && high <= r)
        {
            return seg[ind];
        }

        int mid = (low + high) / 2;

        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, high, l, r);

        return min(left, right);
    }

    void update(int ind, int low, int high, int i, int val)
    {
        if (low == high)
        {
            seg[ind] = val;
            return;
        }

        int mid = (low + high) / 2;

        if (i <= mid)
        {
            update(2 * ind + 1, low, mid, i, val);
        }
        else
        {
            update(2 * ind + 2, mid + 1, high, i, val);
        }

        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
};

int main()
{
    int n;
    cin >> n;
    int arr1[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr1[i];
    }

    SegmentTree s1(n);
    s1.build(0, 0, n - 1, arr1);

    int m;
    cin >> m;
    int arr2[m];
    for (int i = 0; i < m; i++)
    {
        cin >> arr2[i];
    }

    SegmentTree s2(m);
    s2.build(0, 0, m - 1, arr2);

    int q;
    cin >> q;

    while (q--)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;

            int min1 = s1.query(0, 0, n - 1, l1, r1);
            int min2 = s2.query(0, 0, m - 1, l2, r2);

            cout << min(min1, min2);
        }
        else
        {
            int arrno, i, val;
            cin >> arrno >> i >> val;

            if (arrno == 1)
            {
                s1.update(0, 0, n - 1, i, val);
                arr1[i] = val;
            }
            else
            {
                s2.update(0, 0, m - 1, i, val);
                arr2[i] = val;
            }
        }
    }

    return 0;
}