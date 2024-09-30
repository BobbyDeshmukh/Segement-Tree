// Code forces Sreja and Brackets

#include <bits/stdc++.h>
using namespace std;

class Info
{
public:
    int open, close, full;

    Info() : open(0), close(0), full(0) {}
    Info(int _open, int _close, int _full) : open(_open), close(_close), full(_full) {}
};

Info merge(Info left, Info right)
{
    Info ans(0, 0, 0);

    ans.full = left.full + right.full + min(left.open, right.close);
    ans.open = left.open + right.open - min(left.open, right.close);
    ans.close = left.close + right.close - min(left.open, right.close);

    return ans;
}

void build(int ind, int low, int high, string &s, vector<Info> &seg)
{
    if (low == high)
    {
        Info temp(s[low] == '(', s[low] == ')', 0);
        seg[ind] = temp;
        return;
    }

    int mid = (low + high) / 2;

    build(2 * ind + 1, low, mid, s, seg);
    build(2 * ind + 2, mid + 1, high, s, seg);

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
}

Info query(int ind, int low, int high, int l, int r, vector<Info> &seg)
{
    if (r < low || high < l)
    {
        return Info();
    }

    // complete overlap
    if (low >= l && high <= r)
    {
        return seg[ind];
    }

    int mid = (low + high) / 2;

    Info left = query(2 * ind + 1, low, mid, l, r, seg);
    Info right = query(2 * ind + 2, mid + 1, high, l, r, seg);

    return merge(left, right);
}

int main()
{
    string s;
    cin >> s;

    int n = s.length();

    vector<Info> seg(4 * n + 1);
    build(0, 0, n - 1, s, seg);

    int q;
    cin >> q;

    while (q--)
    {
        int l, r;
        cin >> l >> r;
        l--;
        r--;

        Info result = query(0, 0, n - 1, l, r, seg);
        cout << result.full * 2 << endl;
    }

    return 0;
}