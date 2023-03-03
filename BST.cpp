#include <iostream>
#include <iomanip>

template <typename T>
class BinarySearchTree {
public:
    struct TreeNode {
        T val;
        TreeNode* _left;
        TreeNode* _right;
        TreeNode(T x) : val(x), _left(nullptr), _right(nullptr) {}
    };
    BinarySearchTree() : _root(nullptr) {}
    bool Empty() { return !_size; }
    int Size() { return _size; }
    void Insert(T val) {
        TreeNode* new_node = new TreeNode(val);
        if (_root == nullptr) {
            _root = new_node;
            ++_size;
            return;
        }

        TreeNode* current = _root;
        while (current != nullptr) {
            if (val < current->val) {
                if (current->_left == nullptr) {
                    current->_left = new_node;
                    ++_size;
                    return;
                }
                current = current->_left;
            }
            else {
                if (current->_right == nullptr) {
                    current->_right = new_node;
                    ++_size;
                    return;
                }
                current = current->_right;
            }
        }
    }

    bool Search(T val) const {
        TreeNode* current = _root;
        while (current != nullptr) {
            if (val == current->val) {
                return true;
            }
            current = (val < current->val) ? current->_left : current->_right;
        }
        return false;
    }

    void Remove(T val) {
        _root = Remove(_root, val);
        --_size;
    }

    TreeNode* Remove(TreeNode* node, T val) {
        if (node == nullptr) {
            return nullptr;
        }

        if (val < node->val) {
            node->_left = Remove(node->_left, val);
        }
        else if (val > node->val) {
            node->_right = Remove(node->_right, val);
        }
        else {
            // Node with no children or one child
            if (node->_left == nullptr || node->_right == nullptr) {
                TreeNode* temp = node->_left ? node->_left : node->_right;
                delete node;
                return temp;
            }
            else {
                // Node with two children
                TreeNode* temp = FindMin(node->_right);
                node->val = temp->val;
                node->_right = Remove(node->_right, temp->val);
            }
        }
        return node;
    }

    TreeNode* FindMin(TreeNode* node) {
        while (node->_left != nullptr) {
            node = node->_left;
        }
        return node;
    }

    void Output() const {
        PrintTree(_root, 0);
    }

    T* RoundLeftRootRight();
    T* RoundRightRootLeft();
    void Output(const char option)
    {
        T* tmp = new T[_size];
        switch (option)
        {
        case 'L':
            tmp = this->RoundLeftRootRight();
            for (int i = 0; i < _size; i++)
            {
                printf("%d\t", tmp[i]);
            }
            break;
        case 'R':
            tmp = this->RoundRightRootLeft();
            for (int i = 0; i < _size; i++)
            {
                printf("%d\t", tmp[i]);
            }
            break;
        default:
            printf("Wrong input\n");
            break;
        }
        printf("\n");
        delete[] tmp;
    }

    bool Contains(TreeNode* node, int val) const {
        if (node == nullptr) {
            return false;
        }
        if (val == node->val) {
            return true;
        }
        if (val < node->val) {
            return Contains(node->left, val);
        }
        return Contains(node->right, val);
    }


private:
    TreeNode* _root;
    int _size = 0;

    bool Contains(int val) const {
        return Contains(_root, val);
    }

    void RoundL(TreeNode* node, int& i, T* a)
    {
        if (node)
        {
            RoundL(node->_left, i, a);
            a[i] = node->val;
            ++i;
            RoundL(node->_right, i, a);
        }
    }

    void RoundR(TreeNode* node, int& i, T* a)
    {
        if (node)
        {
            RoundR(node->_right, i, a);
            a[i] = node->val;
            ++i;
            RoundR(node->_left, i, a);
        }
    }
    void PrintTree(TreeNode* node, int indent) const {
        if (node != nullptr) {
            PrintTree(node->_right, indent + 4);
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            std::cout << node->val << "\n";
            PrintTree(node->_left, indent + 4);
        }
    }
};

template<typename T>
T* BinarySearchTree<T>::RoundLeftRootRight()
{
    T* arr = new T[this->_size];
    int i = 0;
    RoundL(_root, i, arr);
    return arr;
}



template<typename T>
T* BinarySearchTree<T>::RoundRightRootLeft()
{
    T* arr = new T[this->_size];
    int i = 0;
    RoundR(_root, i, arr);
    return arr;
}



int main() {
    BinarySearchTree<int> bst;

    bst.Insert(5);
    bst.Insert(3);
    bst.Insert(7);
    bst.Insert(2);
    bst.Insert(4);
    bst.Insert(6);
    bst.Insert(8);
    bst.Output('L');

    for (size_t i = 0; i < 100; i++)
    {
        bst.Remove(i);
    }

    bst.Output();
    return 0;
}
