#include <iostream>
#include <queue>


// Структура элемента двоичного дерева
template<class T>
struct BinaryTreeNode{
    T value;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
    BinaryTreeNode* father;
    BinaryTreeNode(const T val) : value(val), left(nullptr), right(nullptr) {}
};

// Структура элемента декартового дерева
template<class Key, class Pri>
struct DecartTreeNode{
    std::pair<Key, Pri> node;
    DecartTreeNode* left;
    DecartTreeNode* right;
    DecartTreeNode* father;
    DecartTreeNode(const Key x, const Pri y) : node({x,y}), left(nullptr), right(nullptr) {}
};


// Функтр удаления узла
template<class Node>
class Remove {
public:
    Remove () = default;
    void operator()(Node* node){
        delete node;
    }
};

// Функтр траверсы
template<class Node, class Func>
class Traverse {
public:
    Traverse () = default;
    void operator()(Node* root, Func func){
        // Создаем очередь, и помещаем в нее корень
        std::queue<Node*> q;
        q.push(root);

        while(!q.empty()) {
            // Выводим перевый элемент из очереди и удаляем его из нее
            Node* node = q.front();
            q.pop();
            // Если у элемента были дочерние элементы, то идем с лева направо
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
            func(node);
        }

    }

};


// Функтр, рассчитывающий глубину дерева
template<class Tree>
class Depth{
public:

    Depth() = default;

    size_t operator() (Tree* root) {

        if(root == nullptr) {
            return 0;
        }
        // Заносим корень в очередь
        std::queue<Tree*> q;
        size_t depth = 0;
        q.push(root);

        // Пока в очереди есть элементы - наращиваем глубину
        while (!q.empty()) {
            depth++;

            // Проходимся по слою
            for (int i = q.size(); i > 0 ; i--) {
                Tree* tmp = q.front();
                q.pop();

                if (tmp->left != nullptr) {
                    q.push(tmp->left);
                }

                if (tmp->right != nullptr) {
                    q.push(tmp->right);
                }
            }

        }

        return depth;
    }

};


template<class Key, class Pri>
class DecartTree {
public:

    DecartTree() {
        root = nullptr;
    }

    // Павило пяти

    // Конструктор копирования
    DecartTree(const DecartTree& copy) {
        DeleteTree();
        std::copy(copy.root, copy.root, root);
    }

    // Конструктор перемещения
    DecartTree(DecartTree&& rvalue) noexcept {
        DeleteTree();
        root = rvalue.root;
        rvalue.root = nullptr;
    }

    // Оператор присваивания копированием
    DecartTree& operator= (const DecartTree& rvalue) {
        DeleteTree();
        std::copy(rvalue.root, rvalue.root, root);
        return *this;
    }

    // Оператор присваивания перемещением
    DecartTree& operator= (DecartTree&& rvalue) {
        DeleteTree();
        root = rvalue.root;
        rvalue.root = nullptr;
        return *this;
    }

    // Деструктор
    ~DecartTree() {
        if(root == nullptr) {
            return;
        }
        DeleteTree();
//        std::queue<DecartTreeNode<Key, Pri> *> q;
//        q.push(root);

//        while (!q.empty()) {
//            for (int i = q.size(); i > 0 ; i--) {
//                DecartTreeNode<Key, Pri>* tmp = q.front();
//                q.pop();

//                if (tmp->left != nullptr) {
//                    q.push(tmp->left);
//                }

//                if (tmp->right != nullptr) {
//                    q.push(tmp->right);
//                }
//                delete tmp;
//            }

//        }
    }




    // Метод, разделяющий за дерево на деревья left и right
    void Split(DecartTreeNode<Key, Pri>* node, Key x, DecartTreeNode<Key, Pri>*& left, DecartTreeNode<Key, Pri>*& right ){
        if (node == nullptr) {
            left = nullptr;
            right = nullptr;
        } else if (node->node.first <= x) {
            Split(node->right, x, node->right, right);
            left = node;
        } else {
            Split(node->left, x, left, node->left);
            right = node;
        }
    }

    // Метод, отвечающий за добавление элемента в дерево
    void Insert(Key x, Pri y) {

        // Проверяем, что корень проинициализирован
        if (root == nullptr) {
            root = new DecartTreeNode<Key, Pri>(x,y);
            return;
        }

        // Текущий элемент
        DecartTreeNode<Key, Pri>* node = root;
        // Элемент предок
        DecartTreeNode<Key, Pri>* prev = nullptr;
        // Элемент, заполненный входными зачениями
        DecartTreeNode<Key, Pri>* input = new DecartTreeNode<Key,Pri>(x,y);

        // Опускаемся, пока не дойдем до нужного приоритета
        while(true) {
            if (node == nullptr || node->node.second < y){
                break;
            }
            prev = node;
            if (x <= node->node.first) {
                node = node->left;
            } else {
                node = node->right;
            }
        }

        // Сплитим дерево по заданому ключу и заносим left и right деревья в input
        Split(node, x, input->left, input->right);

        // Собираем дерево
        if(node == root) {
            root = input;
        } else if (x > prev->node.first) {
            prev->right = input;
        } else {
            prev->left = input;
        }
    }

    size_t GetDepth() {
        Depth<DecartTreeNode <Key, Pri> > depth;
        return depth(root);
    }

private:

    void DeleteTree() {
        Traverse<DecartTreeNode<Key, Pri>, Remove<DecartTreeNode<Key, Pri>> > Del;
        Del(root, remover);
    }


    DecartTreeNode<Key, Pri>* root;
    Remove<DecartTreeNode<Key, Pri> > remover;
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
        DeleteTree();
        std::copy(copy.root, copy.root, root);
    }

    // Конструктор перемещения
    BinaryTree(BinaryTree&& rvalue) noexcept {
        DeleteTree();
        root = rvalue.root;
        rvalue.root = nullptr;
    }

    // Оператор присваивания копированием
    BinaryTree& operator= (const BinaryTree& rvalue) {
        DeleteTree();
        std::copy(rvalue.root, rvalue.root, root);
        return *this;
    }

    // Оператор присваивания перемещением
    BinaryTree& operator= (BinaryTree&& rvalue) {
        DeleteTree();
        root = rvalue.root;
        rvalue.root = nullptr;
        return *this;
    }

    // Деструктор
    ~BinaryTree() {
        if(root == nullptr) {
            return;
        }
        DeleteTree();
//        std::queue<BinaryTreeNode<T> *> q;
//        q.push(root);

//        while (!q.empty()) {
//            for (int i = q.size(); i > 0 ; i--) {
//                BinaryTreeNode<T> * tmp = q.front();
//                q.pop();

//                if (tmp->left != nullptr) {
//                    q.push(tmp->left);
//                }

//                if (tmp->right != nullptr) {
//                    q.push(tmp->right);
//                }
//                delete tmp;
//            }

//        }
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

    size_t GetDepth() {
        Depth<BinaryTreeNode<T>> depth;
        return depth(root);
    }


private:

    void DeleteTree() {
        Traverse<BinaryTreeNode<T>, Remove<BinaryTreeNode<T> > > Del;
        Del(root, remover);
    }

    BinaryTreeNode<T>* root;
    Remove<BinaryTreeNode<T> > remover;


};

using LLType = long long;

int main() {

    BinaryTree<LLType> tree;
    DecartTree<LLType, LLType> treap;
    int n;
    std::cin >> n;
    LLType x, y;
    for (int i = 0; i < n; i++) {
        std::cin >> x >> y;
        tree.Insert(x);
        treap.Insert(x, y);
    }
    std::cout << tree.GetDepth() - treap.GetDepth();
    return 0;
}
