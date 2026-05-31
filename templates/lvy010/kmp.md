

- 在字符串  s （主串）里找  p （模式串）
- 返回第一次匹配成功的起始下标
- 找不到就返回  -1 
 
 
 
1. 完整模板再放一遍
 
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> ne;
void get_next(const string &p) {
    int m = p.size(); ne.resize(m);
    for (int i = 1, j = 0; i < m; i++) {
        while (j && p[i] != p[j]) j = ne[j-1];
        if (p[i] == p[j]) j++;
        ne[i] = j;
    }
}

int kmp(const string &s, const string &p) {
    get_next(p);
    int n = s.size(), m = p.size();
    for (int i = 0, j = 0; i < n; i++) {
        while (j && s[i] != p[j]) j = ne[j-1];
        if (s[i] == p[j]) j++;
        if (j == m) return i - m + 1;
    }
    return -1;
}
 
 
 
 
2. 每个部分干什么
 
①  ne  数组
 
全局数组，存的是：
模式串前 i 个字符里，最长相等 前缀 & 后缀 的长度
作用：匹配失败时，不用从头比，直接跳到合适位置
 
②  get_next(p) 
 
预处理模式串  p ，算出  ne  数组
只用跑一次，非常快
 
③  kmp(s, p) 
 
-  i ：遍历主串  s ，从不回退
-  j ：遍历模式串  p ，匹配失败会跳
- 字符相等： i++、j++ 
- 不等： j = ne[j-1]  跳转
- 当  j == m ：说明完全匹配成功
返回位置： i - m + 1 
 
 
 
3. 怎么使用（套题示例）
 
int main() {
    string s, p;
    cin >> s >> p;
    int pos = kmp(s, p);
    cout << pos << endl;
    return 0;
}
 
 
输入：
 
abcabcabd
abcab
 
 
返回： 0 
因为从下标 0 开始匹配成功。
 
 
 
4. 竞赛里常见改法（你一定会用到）
 
① 要找所有匹配位置
 
把  return  改成存答案：
 
vector<int> kmp(const string &s, const string &p) {
    get_next(p);
    int n = s.size(), m = p.size();
    vector<int> res;
    for (int i = 0, j = 0; i < n; i++) {
        while (j && s[i] != p[j]) j = ne[j-1];
        if (s[i] == p[j]) j++;
        if (j == m) {
            res.push_back(i - m + 1);
            j = ne[j - 1]; // 关键：继续匹配下一个
        }
    }
    return res;
}
 
 
② 求最小循环节
 
int m = p.size();
int len = m - ne[m-1];
if (m % len == 0) cout << len << endl; // 最小周期
 
 
 
 
5. 一句话记忆
 
-  ne ：跳回哪里
-  i  只往前走
-  j  匹配失败跳  ne[j-1] 
- 匹配完  j == m  就是找到
