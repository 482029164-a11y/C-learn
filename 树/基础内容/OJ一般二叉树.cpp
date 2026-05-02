#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// 1. 底层物理结构：二叉树节点定义
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 2. 核心建树引擎：基于先序序列 + 空标记('#')
TreeNode* buildTreePreOrder() {
    string s;
    // 从标准输入流读取一个字符串，如果流断开或读到 '#'，则返回 NULL
    if (!(cin >> s) || s == "#") {
        return NULL; 
    }
    
    // 【核心转换】：利用 stringstream 进行安全的类型降维
    int num;
    stringstream ss(s);
    ss >> num;
    
    // 建立当前物理节点
    TreeNode* root = new TreeNode(num);
    
    // 递归接管左右子树的构建
    root->left = buildTreePreOrder();
    root->right = buildTreePreOrder();
    
    return root;
}

// 3. 测试探针：中序遍历打印（用于验证树的拓扑是否正确）
void inOrderPrint(TreeNode* root) {
    if (root == NULL) return;
    inOrderPrint(root->left);
    cout << root->val << " ";
    inOrderPrint(root->right);
}

// 4. 系统纪律：物理内存湮灭
void destroyTree(TreeNode* root) {
    if (root == NULL) return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root; // 释放堆内存
}

// 5. 驱动中枢
int main() {
    /*
      【OJ 模拟说明】
      在真正的 OJ 平台中，不需要打印提示语。
      你可以输入这组测试数据：1 2 # # 3 # #
      这代表一棵树：根节点是 1，左孩子是 2，右孩子是 3。
      (2 的左右孩子为空，3 的左右孩子为空)
    */
    cout << "请输入先序遍历序列 (使用空格分隔，'#'代表空节点): \n";
    cout << "示例测试数据: 1 2 # # 3 # #\n> ";
    
    // 启动建树引擎，接管输入流
    TreeNode* root = buildTreePreOrder();
    
    // 验证物理拓扑
    cout << "\n[物理验证] 建树成功！中序遍历输出结果为: ";
    inOrderPrint(root); 
    // 对于示例数据 1 2 # # 3 # #，中序遍历的预期输出应该是: 2 1 3
    cout << "\n";
    
    // 引擎停机前清理战场
    destroyTree(root);
    
    return 0;
}
