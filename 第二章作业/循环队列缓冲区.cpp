#include <iostream>
#include <string>
using namespace std;
//这题需要注意的是，和普通的循环队列不一样，它不用空出一个位置来，但是相应的需要添加一个个数属性，来判断是否空还是满 
//还需注意：// rear 指向的是下一个空位，所以最新的元素在 rear 的前一个位置
        // 为了防止 rear - 1 变成负数，需要加上 maxsize 再取余 
class my_queue {
public:
    int *data;
    int front;
    int rear;
    int maxsize;
    int count; // 核心变量：记录队列中当前的元素个数

    my_queue(int k) {
        maxsize = k;
        if (maxsize > 0) {
            data = new int[maxsize];
        } else {
            data = NULL; // 处理容量为 0 的极端情况
        }
        front = 0;
        rear = 0;
        count = 0;
    }

    ~my_queue() {
        if (data != NULL) {
            delete[] data;
        }
    }

    bool empty() {
        return count == 0;
    }

    bool is_full() {
        return count == maxsize;
    }

    void enqueue(int value) {
        if (maxsize == 0) return; // 容量为0，无法插入，直接丢弃

        data[rear] = value; // 存入数据
        rear = (rear + 1) % maxsize; // rear 指针后移

        if (is_full()) {
            // 如果满了，刚才的插入覆盖了最早的数据，所以 front 也要被迫后移一位
            front = (front + 1) % maxsize;
        } else {
            // 如果没满，元素个数增加
            count++;
        }
    }

    int dequeue() {
        if (empty()) {
            return -1;
        }
        int val = data[front]; // 取出最早的数据
        front = (front + 1) % maxsize; // front 指针后移
        count--; // 元素个数减少
        return val;
    }

    int get_oldest() {
        if (empty()) {
            return -1;
        }
        return data[front]; // front 指向的就是最早进来的
    }

    int get_latest() {
        if (empty()) {
            return -1;
        }
        // rear 指向的是下一个空位，所以最新的元素在 rear 的前一个位置
        // 为了防止 rear - 1 变成负数，需要加上 maxsize 再取余
        int latest_index = (rear - 1 + maxsize) % maxsize;
        return data[latest_index];
    }
};

int main() {
    int k, m;
    // 读取队列容量和操作数量
    if (!(cin >> k >> m)) return 0;

    my_queue q(k);
    string cmd;

    for (int i = 0; i < m; ++i) {
        cin >> cmd;
        if (cmd == "enqueue") {
            int val;
            cin >> val;
            q.enqueue(val);
        } else if (cmd == "dequeue") {
            cout << q.dequeue() << endl;
        } else if (cmd == "get_oldest") {
            cout << q.get_oldest() << endl;
        } else if (cmd == "get_latest") {
            cout << q.get_latest() << endl;
        }
    }

    return 0;
}
