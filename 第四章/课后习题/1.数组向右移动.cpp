#include <iostream>
#include <vector>

using namespace std;

// 底层物理翻转引擎，严格兼容 C++98
void reverse_inplace(vector<int>& arr, int left, int right) {
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}

// 三次反转算法引擎
void circular_shift_right(vector<int>& arr, int m) {
    int n = arr.size();
    if (n <= 1) return;
    
    // 剥离冗余的循环圈数
    m = m % n; 
    if (m == 0) return;
    
    // 启动三次物理翻转
    reverse_inplace(arr, 0, n - 1);     
    reverse_inplace(arr, 0, m - 1);     
    reverse_inplace(arr, m, n - 1);     
}

int main() {
    // 1. C++98 标准防线：在栈上静态分配原生数组
    int raw_data[] = {1, 2, 3, 4, 5};
    
    // 2. 物理内存拷贝计算：
    // sizeof(raw_data) 计算整个数组占据的字节数
    // sizeof(int) 计算单个元素的字节数
    // 两者相除得到元素的绝对个数
    int num_elements = sizeof(raw_data) / sizeof(int);
    
    // 3. 利用原生指针区间 [起始地址, 结束地址的后一位) 批量初始化 vector
    vector<int> arr(raw_data, raw_data + num_elements);
    
    int m = 2;
    
    circular_shift_right(arr, m);
    
    // C++98 标准中遍历 vector 的标准做法
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
