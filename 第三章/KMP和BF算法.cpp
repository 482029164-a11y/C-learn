#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. BF 算法 (Brute Force / 暴力匹配)
// ==========================================
int BF_match(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    
    if (m == 0 || n < m) return -1;

    int i = 0; // 主串指针
    int j = 0; // 模式串指针

    while (i < n && j < m) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        } else {
            // 匹配失败，主串指针回退，模式串指针归零
            i = i - j + 1; 
            j = 0;
        }
    }

    if (j == m) {
        return i - j; // 返回匹配成功的起始下标
    }
    return -1; 
}

// ==========================================
// 2. 教科书标准版：构建 next 数组 (next[0] = -1)
// ==========================================
[Image of KMP next array textbook definition with next[0]=-1]
void getnext(string t, int *next) {
    int j = 0;
    int k = -1;
    next[0] = -1;
    
    // 强制转换为 int 避免无符号整数溢出风险
    while (j < (int)t.length() - 1) {
        // 如果退到起点(-1) 或者 字符匹配成功,C++短路特性，不用担心数组越界 
        if (k == -1 || t[j] == t[k]) {
            ++j;
            ++k;
            next[j] = k;
        } else {
            // 匹配失败，向前回溯
            k = next[k];
        }
    }
}

// ==========================================
// 3. 教科书标准版：KMP 匹配主函数
// ==========================================
int KMP_match(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    
    if (m == 0 || n < m) return -1;

    // 动态分配 next 数组
    int *next = new int[m];
    getnext(pattern, next);
    
    int i = 0; // 主串指针
    int j = 0; // 模式串指针
    
    while (i < n && j < m) {
        // 【核心适配逻辑】：
        // 如果 j == -1，说明模式串的第 0 个字符和主串当前的 i 字符都不匹配。
        // 这时必须强制让主串指针 i 往前走一步 (i++)，模式串指针 j 从 -1 变回 0 (j++)，准备下一轮。
        // 同样利用了 C++ 的短路特性，j == -1 成立时不会执行 text[i] == pattern[j] 导致越界。
        if (j == -1 || text[i] == pattern[j]) {
            i++;
            j++;
        } else {
            // 匹配失败，查阅 next 数组让 j 回溯，主串指针 i 保持不动
            j = next[j];
        }
    }
    
    // 释放动态分配的内存，防止内存泄漏
    delete[] next;
    
    if (j == m) {
        return i - j; // 返回匹配成功的起始下标
    }
    return -1;
}

// ==========================================
// 4. 测试模块
// ==========================================
int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    
    cout << "主串:   " << text << endl;
    cout << "模式串: " << pattern << endl;
    cout << "-----------------------------------" << endl;

    // 测试 BF 算法
    int bf_result = BF_match(text, pattern);
    if (bf_result != -1) {
        cout << "[BF 算法]  匹配成功！起始下标为: " << bf_result
