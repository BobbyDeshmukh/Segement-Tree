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

        seg[ind] = (seg[2 * ind + 1] + seg[2 * ind + 2]);
    }

    int query(int ind, int low, int high, int l, int r)
    {
        // no overlap
        if (r < low || high < l)
        {
            return 0;
        }

        // complete overlap
        if (low >= l && high <= r)
        {
            return seg[ind];
        }

        int mid = (low + high) / 2;

        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, high, l, r);

        return (left + right);
    }

    void update(int ind, int low, int high, int i, int val)
    {
        if (low == high)
        {
            seg[ind] += val;
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

        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }
};

int main()
{
    int n;
    cin >> n;
    int arr[n];
    int mx = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        mx = max(mx, arr[i]);
    }

    mx += 1;
    int freq[mx];

    for (int i = 0; i < mx; i++)
    {
        freq[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        freq[arr[i]]++;
    }

    SegmentTree st(mx);
    st.build(0, 0, mx - 1, freq);

    int cnt = 0;

    for (int i = 0; i < n; i++)
    {
        freq[arr[i]]--;
        st.update(0, 0, mx - 1, arr[i], -1);

        cnt += st.query(0, 0, mx - 1, 1, arr[i] - 1);
    }

    cout << cnt << endl;

    return 0;
}