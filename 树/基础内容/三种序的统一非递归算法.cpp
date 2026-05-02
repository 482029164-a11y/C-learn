#include <iostream>
#include <stack>

using namespace std;

// 1. 底层物理结构：二叉树节点
struct BTNode {
    char data;
    BTNode *lchild, *rchild;
    
    // 构造函数，方便快速创建节点
    BTNode(char val) {
        data = val;
        lchild = NULL;
        rchild = NULL;
    }
};

// 2. 状态机指令集
struct Command {
    int type;      // 0表示 VISIT (展开子树), 1表示 PRINT (输出节点自身)
    BTNode* node;  // 指令绑定的物理节点
    
    Command(int t, BTNode* n) {
        type = t;
        node = n;
    }
};

// 3. 核心计算引擎：统一遍历
void UnifiedTraversal(BTNode* root, int mode) {
    if (root == NULL) return;
    
    stack<Command> st;
    st.push(Command(0, root)); // 发动机点火：压入根节点的展开指令
    
    while (!st.empty()) {
        Command cmd = st.top();
        st.pop();
        
        // 物理防线：遇到空指针直接抛弃
        if (cmd.node == NULL) continue;
        
        // 状态分发
        if (cmd.type == 1) {
            // 收到绝对安全的打印指令，直接输出
            cout << cmd.node->data << " ";
        } 
        else {
            // 收到展开指令(type==0)，进行拓扑拆解
            // 绝对法则：利用栈的 LIFO(后进先出) 特性，压栈顺序必须与目标输出顺序相反
            
            if (mode == 1) { 
                // 【先序遍历】 目标: 根 -> 左 -> 右 
                // 压栈顺序: 右 -> 左 -> 根
                st.push(Command(0, cmd.node->rchild));
                st.push(Command(0, cmd.node->lchild));
                st.push(Command(1, cmd.node)); 
            }
            else if (mode == 2) { 
                // 【中序遍历】 目标: 左 -> 根 -> 右 
                // 压栈顺序: 右 -> 根 -> 左
                st.push(Command(0, cmd.node->rchild));
                st.push(Command(1, cmd.node)); 
                st.push(Command(0, cmd.node->lchild));
            }
            else if (mode == 3) { 
                // 【后序遍历】 目标: 左 -> 右 -> 根 
                // 压栈顺序: 根 -> 右 -> 左
                st.push(Command(1, cmd.node)); 
                st.push(Command(0, cmd.node->rchild));
                st.push(Command(0, cmd.node->lchild));
            }
        }
    }
    cout << endl;
}

// 4. 系统纪律：物理内存释放 (后序遍历的实际应用)
void DestroyTree(BTNode* root) {
    if (root == NULL) return;
    DestroyTree(root->lchild);
    DestroyTree(root->rchild);
    delete root; // 彻底湮灭物理内存
}

// 5. 驱动测试
int main() {
    /* 
       构建实验沙盘的二叉树拓扑结构:
             A
           /   \
          B     C
         /     / \
        D     E   F
    */
    BTNode* root = new BTNode('A');
    root->lchild = new BTNode('B');
    root->rchild = new BTNode('C');
    root->lchild->lchild = new BTNode('D');
    root->rchild->lchild = new BTNode('E');
    root->rchild->rchild = new BTNode('F');

    cout << "========== 统一状态机遍历引擎 ==========" << endl;
    
    cout << "[Mode 1] 先序遍历 (预期: A B D C E F): \n实际输出: ";
    UnifiedTraversal(root, 1);
    
    cout << "\n[Mode 2] 中序遍历 (预期: D B A E C F): \n实际输出: ";
    UnifiedTraversal(root, 2);
    
    cout << "\n[Mode 3] 后序遍历 (预期: D B E F C A): \n实际输出: ";
    UnifiedTraversal(root, 3);
    
    cout << "========================================" << endl;

    // 清理内存，防止泄漏
    DestroyTree(root);
    
    return 0;
}
