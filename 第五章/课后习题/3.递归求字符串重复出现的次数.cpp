#include <iostream>
#include <string>
using namespace std;
//需要注意到可以直接传入字符串对链串进行初始化 
struct linknode {
    char data;
    linknode* next;
    linknode() { next = NULL; }
    linknode(char m) { data = m; next = NULL; }
};
class linkstr {
public:
    linknode* head;
    int length;
    
    linkstr() {
        head = new linknode(); 
        length = 0;
    }
    
    // 修正：直接按原始字符（包含空格）构建物理链表，摒弃 stringstream 的截断
    void createl(const string& line) {
        linknode* rear = head;
        for (size_t i = 0; i < line.length(); i++) {
            linknode* s = new linknode(line[i]);
            rear->next = s;
            rear = s;
            this->length++;
        }
    }
    
    // 工业级防御：添加析构函数，在链表生命周期结束时绝对回收堆内存
    ~linkstr() {
        linknode* p = head;
        while (p != NULL) {
            linknode* temp = p;
            p = p->next;
            delete temp;
        }
    }
};

// 物理降维：传入当前指针 curr 和剩余长度 s_len，实现绝对的只读递归搜索
int chongfu(linknode* curr, int s_len, const string& t) {
    int t_len = t.length();
    
    // 绝对防线：如果剩余物理长度小于模式串长度，或节点为空，直接停机
    if (curr == NULL || s_len < t_len) {
        return 0;
    }
    
    // 在当前锚点尝试向下进行匹配
    linknode* p = curr;
    int count = 0;
    while (p != NULL && count < t_len) {
        if (p->data != t[count]) {
            break;
        }
        p = p->next;
        count++;
    }
    
    // 重叠匹配核心法则：无论是否匹配成功，物理锚点严格向后推进一步 (curr->next)
    if (count == t_len) {
        return chongfu(curr->next, s_len - 1, t) + 1;
    } else {
        return chongfu(curr->next, s_len - 1, t);
    }
}

int main() {
    string line;
    // 使用 getline 捕获完整的物理输入（包括空格）
    if (getline(cin, line)) {
        linkstr s;
        s.createl(line);
        
        string t;
        if (getline(cin, t)) {
            // 启动非破坏性递归引擎，传入首个有效节点
            int num = chongfu(s.head->next, s.length, t);
            cout << num << "\n";
        }
    }
    return 0;
}
