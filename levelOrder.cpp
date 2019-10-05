#include <iostream>
#include <queue>

// Структура, представляющая из себя узел бинарного дерева
template<class T>
struct BinaryTreeNode{
    T value;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
    BinaryTreeNode* father;
    BinaryTreeNode(const T val) : value(val), left(nullptr), right(nullptr) {}
};

// Класс бинарного дерева
template<class T>
class BinaryTree {
public:
    BinaryTree() {
        root = nullptr;
    }
    
    // Павило пяти

    // Конструктор копирования
    BinaryTree(const BinaryTree& copy) {
        ~BinaryTree();
        std::copy(copy.root, copy.root, root);
    }

    // Конструктор перемещения
    BinaryTree(BinaryTree&& rvalue) noexcept {
        ~BinaryTree();
        root = rvalue.root;
        rvalue.root = nullptr;
    }

    // Оператор присваивания копированием
    BinaryTree& operator= (const BinaryTree& rvalue) {
        ~BinaryTree();
        std::copy(rvalue.root, rvalue.root, root);
        return *this;
    }

    // Оператор присваивания перемещением
    BinaryTree& operator= (BinaryTree&& rvalue) {
        ~BinaryTree();
        root = rvalue.root;
        rvalue.root = nullptr;
        return *this;
    }

    // Деструктор
    ~BinaryTree() {
        if(root == nullptr) {
            return;
        }

        std::queue<BinaryTreeNode<T> *> q;
        q.push(root);

        while (!q.empty()) {
            for (int i = q.size(); i > 0 ; i--) {
                BinaryTreeNode<T> * tmp = q.front();
                q.pop();

                if (tmp->left != nullptr) {
                    q.push(tmp->left);
                }

                if (tmp->right != nullptr) {
                    q.push(tmp->right);
                }
                delete tmp;
            }

        }
    }
    
    // Метод, отвечающий за добавление элемента в дерево
    void Insert(const T value) {
        
        // Проверяем, что корень проинициализирован
        if (root == nullptr) {
            root = new BinaryTreeNode<T>(value);
            return;
        }
        
        // Нерекурсивная реализация алгоритма добавления узла
        BinaryTreeNode<T>* node = root;
        while(true) {
            // Добавление/переход влево
            if(node->value > value) {
                if (node->left == nullptr) {
                    node->left = new BinaryTreeNode<T>(value);
                    return;
                } else {
                    node = node->left;
                }
            }
            // Добавление/переход направо
            else {
                if (node->right == nullptr) {
                    node->right = new BinaryTreeNode<T>(value);
                    return;
                } else {
                    node = node->right;
                }
            }
        }
    }
    
    // Метод, отвечающий за проход по слоям сверху вниз
    void Traverse() {
        // Создаем очередь, и помещаем в нее корень
        std::queue<BinaryTreeNode<T>*> q;
        q.push(root);
        
        while(!q.empty()) {
            // Выводим перевый элемент из очереди и удаляем его из нее
            BinaryTreeNode<T>* node = q.front();
            q.pop();
            std::cout << node->value << " ";
            // Если у элемента были дочерние элементы, то идем с лева направо
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
    }
    
private:
    BinaryTreeNode<T>* root;
    
};




int main() {
    int n = 0;
    std::cin >> n;
    if (n == 0) {
        return 1;
    }
    // Создаем и заполняем дерево
    BinaryTree<int> tree;
    int input = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> input;
        tree.Insert(input);
    }
    // Послойно проходимся
    tree.Traverse();
    return 0;
}
