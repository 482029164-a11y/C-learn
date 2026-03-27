#include<bits/stdc++.h>
using namespace std;

template<class T>
class linknode{
public:
    T data;
    linknode<T>* next;
    linknode(){
        next = NULL;
    }
    linknode(T x){
        data = x;
        next = NULL;
    }
};

template<class T> 
class linkqueue{
public:
    linknode<T>* front;
    linknode<T>* rear;
    int count;

    linkqueue(){
        front = NULL;
        rear = NULL;
        count = 0; // 修复A：必须初始化
    }
    
    ~linkqueue(){
        linknode<T>* p = front;
        while(p != NULL){
            linknode<T>* temp = p->next;
            delete p;
            p = temp; 
        } 
    }
    
    void push(T x){
        linknode<T>* s = new linknode<T>(x);
        if(front == NULL){ // 修复B：正确的判空逻辑
            front = s;
            rear = s;
        }
        else{
            rear->next = s;
            rear = s;
        }
        count++;
    }
    
    bool empty(){
        return front == NULL; // 修复C配套：统一用 front 判空更安全
    }
    
    bool pop(T& x){
        if(empty()){
            return false;
        }
        else{
            x = front->data;
            linknode<T>* temp = front->next;
            delete front;
            front = temp;
            if(front == NULL) {
                rear = NULL; // 修复C：队列为空时同步置空 rear
            }
            count--;
            return true;
        } 
    }
    
    int getlength() {
        return count; 
    }
    
    bool gethead(T& e) {
        if (empty())
            return false;
        e = front->data; 
        return true;
    }
    
    void print(){
        linknode<T>* p = front;
        while(p != NULL){
            cout << p->data << " ";
            p = p->next; // 修复D：防止死循环
        }
        cout << endl;
    }
};

// 约瑟夫问题求解
bool joson(linkqueue<int>& a, linkqueue<int>& b, int m) {
    int n = a.getlength();
    if (n < 1 || m < 1) {
        return false;
    }
    
    int x; 
    for (int i = 1; i <= n; i++) {
        int j = 1;
        while (j != m) {
            a.pop(x);
            a.push(x);
            j++;
        }
        a.pop(x);
        b.push(x);
    }
    return true;
}

// 迷宫结构
struct box{
    int i;
    int j;
    box* pre;
    box(int a, int b){
        i = a;
        j = b;
        pre = NULL;
    }
};

// 打印路径
void dis(box* b){
    while(b->pre != NULL){
        cout << "[" << b->i << "," << b->j << "]" << " ";
        b = b->pre;
    } 
    // 修复E：删除了多余的 cout<<
    cout << "[" << b->i << "," << b->j << "]" << endl; 
}

// 迷宫寻路
bool mgpath(int xi, int yi, int xe, int ye){
    int mg[4][4]={
        {0,1,0,0},
        {0,0,1,1},
        {0,1,0,0},
        {0,0,0,0}
    };
    int m = 4, n = 4;
    int dx[] = {0,1,0,-1};
    int dy[] = {-1,0,1,0};
    box* b, *b1;
    linkqueue<box*> qu;
    
    b = new box(xi, yi);
    qu.push(b);
    mg[xi][yi] = -1;
    
    while(!qu.empty()){
        b = qu.front->data;
        if(b->i == xe && b->j == ye){
            dis(b);
            // 找到路径直接返回，不需要 break 后再 return
            return true; 
        }
        else{
            qu.pop(b);
            for(int di = 0; di <= 3; di++){
                int t1 = b->i + dx[di];
                int t2 = b->j + dy[di];
                if(t1 >= 0 && t1 < m && t2 >= 0 && t2 < n && mg[t1][t2] == 0){
                    b1 = new box(t1, t2);
                    mg[t1][t2] = -1;
                    b1->pre = b;
                    qu.push(b1);
                }
            }
        }
    }
    return false;
}

int main(){
    // 测试迷宫
    cout << "Maze Path (End to Start):" << endl;
    mgpath(0, 0, 3, 3);
    
    // 测试约瑟夫问题
    cout << "\nJosephus Problem (n=6, m=5):" << endl;
    linkqueue<int> a, b;
    for(int i = 1; i <= 6; i++) {
        a.push(i);
    }
    joson(a, b, 5);
    b.print(); // 期望输出: 5 4 6 2 3 1
    
    return 0;
}
