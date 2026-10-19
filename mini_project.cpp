#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;
vector<int> naive(const string &text, const string &pat)
{
    vector<int> result;
    int n = text.size(), m = pat.size();
    for (int i = 0; i + m <= n; i++)
    {
        int j = 0;
        while (j < m && text[i + j] == pat[j])
            j++;
        if (j == m)
            result.push_back(i);
    }
    return result;
}
vector<int> rabinKarp(const string &text, const string &pat)
{
    vector<int> result;
    int n = text.size(), m = pat.size();
    if (m > n)
        return result;
    int d = 256, q = 101;
    int h = 1;
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;
    int p = 0, t = 0;
    for (int i = 0; i < m; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + text[i]) % q;
    }
    for (int i = 0; i + m <= n; i++)
    {
        if (p == t)
        {
            int j = 0;
            while (j < m && text[i + j] == pat[j])
                j++;
            if (j == m)
                result.push_back(i);
        }
        if (i + m < n)
        {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0)
                t += q;
        }
    }
    return result;
}
void print(const vector<int> &v)
{
    if (v.empty())
        cout << "not found";
    for (int x : v)
        cout << x << " ";
    cout << endl;
}
void test(string text, string pat)
{
    cout << "Text    : " << (text.size() < 50 ? text : "(large text)") << endl;
    cout << "Pattern : " << (pat.size() < 50 ? pat : "(large pattern)") << endl;
    int runs = 100, count = 0;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < runs; i++)
        count += naive(text, pat).size();
    double naiveTime = duration<double, micro>(high_resolution_clock::now() - start).count() / runs;
    start = high_resolution_clock::now();
    for (int i = 0; i < runs; i++)
        count += rabinKarp(text, pat).size();
    double rkTime = duration<double, micro>(high_resolution_clock::now() - start).count() / runs;
    cout << "Naive  found at: ";
    print(naive(text, pat));
    cout << "Rabin-Karp found at: ";
    print(rabinKarp(text, pat));
    cout << "Naive time      : " << naiveTime << " us" << endl;
    cout << "Rabin-Karp time : " << rkTime << " us" << endl;
    cout << "----------------------------------------" << endl;
}
int main()
{
    test("ABABDABACDABABCABAB", "ABABCABAB");
    test("AABAACAADAABAABA", "AABA");
    test("HELLO WORLD", "XYZ");
    test("abcdefg", "abc");
    test("abcdefg", "efg");
    test("hello", "hello");
    test("hi", "hello");
    test("banana", "a");
    test("aaaaa", "aaa");
    test("Hello hello HELLO", "hello");
    test(string(100000, 'a'), string(100, 'a') + "b");
    test(string(200000, 'a'), string(500, 'a') + "b");
    test(string(50000, 'a') + "b", string(1000, 'a') + "b");
    string t, p;
    for (int i = 0; i < 100000; i++)
        t += "ab";
    for (int i = 0; i < 300; i++)
        p += "ab";
    test(t, p + "c");
    return 0;
}