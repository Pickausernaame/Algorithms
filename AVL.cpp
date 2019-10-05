#include <iostream>
#include <queue>
#include <deque>


struct AVLNode {
    int key;
    int size;
    int height;

    AVLNode* left = nullptr;
    AVLNode* right = nullptr;

    AVLNode(int key) : key(key), height(1), size(1) {}
};


class AVLTree {
public:
    AVLTree() {
        root = nullptr;
    }

    void InsertElement(int key, int &pos) {
        if (root == nullptr) {
            root = new AVLNode(key);
            return;
        }

        // Нерекурсивная реализация алгоритма добавления узла
        AVLNode* node = root;
        while(true) {
            ++(node->size);
            // Добавление/переход влево
            if(node->key > key) {
                if (node->right == nullptr) {
                    pos += 1; 
                } else {
                    pos += node->right->size + 1;
                }
                if (node->left == nullptr) {
                    node->left = new AVLNode(key);
                    BalanceNode(node);
                    return;
                } else {
                    node = node->left;
                }
            }
            // Добавление/переход направо
            else {
                if (node->right == nullptr) {
                    node->right = new AVLNode(key);
                    BalanceNode(node);
                    return;
                } else {
                    node = node->right;
                }
            }
        }

    }


    void RemoveElement(int pos) {
            AVLNode* node = root;
            if (node == nullptr) {
                return;
            } else if (pos >= node->size){
                return;
            }

            int sum = 0;
            std::deque<AVLNode*> q;

            while (true) {
                int rsize = 0;
                if (node->right != nullptr) {
                    rsize = node->right->size;
                }

                if (pos - sum > rsize) {
                    q.push_back(node);
                    node = node->left;
                    sum += rsize + 1;

                } else if (pos - sum < rsize) {

                    if (node->right != nullptr) {
                        q.push_back(node);
                        node = node->right;
                    } else {
                        break;
                    }

                } else {
                    AVLNode* left = node->left;
                    AVLNode* right = node->right;
                    int key = node->key;
                    delete node;
                    if (right == nullptr) {
                        if (left == nullptr) {
                            if (!q.empty()) {
                                node = q.back();
                                q.pop_back();

                                if (node->key > key) {
                                    node->left = nullptr;
                                } else {
                                    node->right = nullptr;
                                }

                                --(node->size);
                            }
                            else {
                                return;
                            }
                        }
                        else {
                            node = left;
                        }
                    } else {
                        AVLNode* min = GetMin(right);
                        min->right = DeleteMin(right);
                        min->left = left;
                        SetNodeSize(min);
                        node = BalanceNode(min);
                    }
                    break;
                }
            }
            AVLNode *node1;

            while (!q.empty()) {
                node1 = q.back();
                (node1->size)--;

                if (node1->key > node->key)
                    node1->left = node;
                else
                    node1->right = node;

                node = BalanceNode(node1);
                q.pop_back();
            }

            return;
        }

private:

    AVLNode* GetMin(AVLNode* node) {
        if (node->left == nullptr) {
            return node;
        }
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }



    AVLNode* DeleteMin(AVLNode* node) {
        while(true){
            if (node->left == nullptr) {
                return node->right;
            }
            node->left = node->left->left;
            BalanceNode(node);
        }
    }




    int GetNodeHeight(AVLNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int WhatRot(AVLNode* node) {
        return GetNodeHeight(node->right) - GetNodeHeight(node->left);
    }

    void SetNodeHeight(AVLNode* node) {
        int hleft = GetNodeHeight(node->left);
        int hright = GetNodeHeight(node->right);
        if (hleft > hright) {
            node->height = hleft++;
        } else {
            node->height = hright++;
        }
    }



    void SetNodeSize(AVLNode* node) {
        if (node->right != nullptr) {
            node->size += node->right->size;
        }
        if (node->left != nullptr) {
            node->size += node->left->size;
        }
        ++node->size;
    }

    AVLNode* RightRotate(AVLNode* node) {
        AVLNode* right = node->left;
        node->left = right->right;
        right->right = node;

        SetNodeSize(node);
        SetNodeHeight(node);
        SetNodeSize(right);
        SetNodeHeight(right);

        return right;
    }

    AVLNode* LeftRotate(AVLNode* node) {
        AVLNode* left = node->right;
        node->right = left->left;
        left->left = node;

        SetNodeSize(node);
        SetNodeHeight(node);
        SetNodeSize(left);
        SetNodeHeight(left);

        return left;
    }

    AVLNode* BalanceNode(AVLNode* node) {
        SetNodeSize(node);
        SetNodeHeight(node);

        if (WhatRot(node) == 2) {
            if (WhatRot(node->right) < 0) {
                node->right = RightRotate(node->right);
            }
            return LeftRotate(node);
        }

        if (WhatRot(node) == -2) {
            if (WhatRot(node->left) > 0) {
                node->left = LeftRotate(node->left);
            }
            return RightRotate(node);
        }
        return node;
    }


    AVLNode* root;
};

int main() {

    AVLTree tree;
    int n = 0;
    int key = 0;
    int pos = 0;
    int cmd = 0;

    std::cin >> n;
    if (n <= 0) {
        return 1;
    }

    std::queue<int> res;

    for (int i = 0; i < n; ++i) {
        std::cin >> cmd;
        if (cmd == 1) {
            std::cin >> key;

            pos = 0;
            tree.InsertElement(key, pos);
            res.push(pos);

        } else if (cmd == 2) {

            std::cin >> pos;
            tree.RemoveElement(pos);
        }
    }

    while(!res.empty()) {
        std::cout << res.front() << " ";
        res.pop();
    }
    return 0;
}
