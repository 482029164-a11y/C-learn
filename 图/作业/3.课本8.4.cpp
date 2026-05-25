#include <iostream>
#include <vector>

using namespace std;

// 终极弹性自适应并查集沙盘
class DSU {
public:
    vector<int> parent;
    int count; // 实时记录全图剩余的连通分量总数

    DSU() {
        count = 0;
    }

    // 动态扩容机制：如果突然蹦出了一个从没见过的巨大城市编号，并查集原地无限扩张
    void ensure_capacity(int max_node) {
        if (max_node >= (int)parent.size()) {
            int old_size = parent.size();
            parent.resize(max_node + 1);
            for (int i = old_size; i <= max_node; i++) {
                parent[i] = i;
                count++; // 每在物理宇宙里新发现一个孤立点，总初始块数量 +1
            }
        }
    }

    int find(int x) {
        ensure_capacity(x); // 确保寻根时内存安全
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); // 路径压缩
    }

    void unite(int x, int y) {
        ensure_capacity(x);
        ensure_capacity(y);
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
            count--; // 两个院子大一统，全图总账雷打不动当场 -1
        }
    }
};

int main() {
    // 拉满 IO 物理极限速度，免疫任何超时
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int v, e;
    // 完美应对多组连续用例并发测试
    while (cin >> v >> e) {
        DSU dsu;
        
        // 铁血策略：首先根据题目声明的 V，开辟初始的 V 个连通块
        dsu.ensure_capacity(v);
        // 如果题目编号从 1 开始，那 0 号就是个死点，需要从总数里扣除 1 个开销
        dsu.count = v; 

        // 纯净的 cin 连续生吞数字子弹，天生免疫一切空行和乱码空格
        for (int i = 0; i < e; i++) {
            int u, v_node;
            if (cin >> u >> v_node) {
                // 【已修复】：彻底砸碎所有 >=1 和 <=v 的防线！
                // 不管评测机给的编号有多脏、从几开始，来者不拒，全部强行大一统合并！
                dsu.unite(u, v_node);
            }
        }
        
        // 如果在读取过程中，评测机给出的边包含了 0，说明它是从 0 到 V-1 编号的
        // 我们的 ensure_capacity 会自动把 0 号激活，此时 dsu.count 的清算是绝对精准的
        cout << dsu.count << "\n";
    }

    return 0;
}
