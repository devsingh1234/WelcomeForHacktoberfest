#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
    int t;
    cin >> t;
    int count = 1;
    while (t--)
    {
        int n;
        string s;
        cin >> n >> s;
        cout << "Case #" << count++ << ": " << endl;
        n--;
        int flag = 0;
        for (int i = 0; i < 1024; i++)
        {
            if (flag)
                break;
            string ans = "";
            for (int j = 0; j < 10; j++)
                ans += ((i >> j) & 1 ? '.' : '-');
            bool temp1 = 1, temp2 = 1;

            for (int i = 0; i < s.size(); ++i)
            {
                if (ans[i] != s[i])
                {
                    temp1 = 0;
                    break;
                }
            }
            for (int i = 0; i < ans.size(); ++i)
            {
                if (s[i] != ans[i])
                {
                    temp2 = 0;
                    break;
                }
            }
            if (!temp1 and !temp2)
            {
                n--;
                cout << ans << endl;
                if (n == 0)
                    flag = 1;
            }
        }
    }
}
