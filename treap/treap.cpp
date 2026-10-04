#include <iostream>
#include <vector>
#include <random> 

class Randomizer {
private:
    std::mt19937 gen;

public:
    Randomizer() : gen(std::random_device{}()) {}

    int randint(int min, int max) {
        std::uniform_int_distribution<> distrib(min, max);
        return distrib(gen);
    }
};

class Node {
    friend class Treap;

    private:
        int value;
        int size;
        int priority;

        Node* left = nullptr;
        Node* right = nullptr;

        Node(int value_, int size_, int priority_): value(value_), size(size_), priority(priority_) {}
};

class Treap {
    Node* root = nullptr;
    Randomizer randomizer = Randomizer();
    private:
        
        void free(Node* node) {
            if (!node) {
                return;
            }
            free(node->left);
            free(node->right);
            delete node;

        }

        void print(Node* node) {
            if (!node) {
                return;
            }
            print(node->left);
            std::cout << node->value << " ";
            print(node->right);

        }
        
        int get_size(Node* node) {
            if (!node) {
                return 0;
            }
            return node->size;
        }

        void update(Node* node) {
            if (!node) {
                return;
            }
            node->size = get_size(node->left) + get_size(node->right) + 1;
            return;
        }
        
        void split(Node* root, int pos, Node*& left, Node*& right) {
            if (!root) {
                left = nullptr;
                right = nullptr;
                return;
            }
            if (pos <= get_size(root->left)) {
                split(root->left, pos, left, root->left);
                right = root;
            } else {
                split(root->right, pos-get_size(root->left)-1, root->right, right);
                left = root;
            }
            update(root);
        }
        
        Node* merge(Node* left, Node* right) {
            if (!left && !right) {
                return nullptr;
            } if (!left) {
                return right;
            } else if (!right) {
                return left;
            }
            Node* merged;
            if (left->priority >= right->priority) {
                merged = left;
                merged->right = merge(merged->right, right);
            } else {
                merged = right;
                merged->left = merge(left, merged->left);
            }
            update(merged);
            return merged;
        }

    public:
        Treap(Node* root_ = nullptr): root(root_) {}

        ~Treap() {
            free(root);
            root = nullptr;
        }

        bool empty() {
            return root == nullptr;
        }

        void print() {
            std::cout << "[ ";
            print(root);
            std::cout << "]\n";
        }

        std::pair<Treap, Treap> split(int pos) {
            Node* left;
            Node* right;
            split(root, pos, left, right);
            root = nullptr;
            return std::make_pair(Treap(left), Treap(right));
        }

        void merge_right(Treap& right) {
            root = merge(root, right.root);
            right.root = nullptr;
        }

        void merge_left(Treap& left) {
            root = merge(left.root, root);
            left.root = nullptr;
        }

        void insert(int pos, int value) {
            if (pos < 0 || pos > get_size(root)) {
                throw std::out_of_range("insert");
            }

            Node* new_node = new Node(value, 1, randomizer.randint(0, INT_MAX));
            Node* left;
            Node* right;
            split(root, pos, left, right);
            root = merge(left, merge(new_node, right));
        }

        int remove(int pos) {
            if (pos < 0 || pos >= get_size(root)) {
                throw std::out_of_range("remove");
            }

            Node* left;
            Node* right;
            Node* temp;
            split(root, pos, left, right);
            split(right, 1, temp, right);
            int value = temp->value;
            delete temp;
            root = merge(left, right);
            return value;
        }

        int at(int pos) {
            if (pos < 0 || pos >= get_size(root)) {
                throw std::out_of_range("at");
            }

            Node* left;
            Node* right;
            Node* temp;
            split(root, pos, left, right);
            split(right, 1, temp, right);
            int value = temp->value;
            right = merge(temp, right);
            root = merge(left, right);
            return value;
        }

};

int main() {
    Treap treap;
    treap.insert(0, 5);
    treap.insert(0, 6);
    treap.insert(0, 67);
    std::cout<<"removed: "<<treap.remove(0)<<"\n";
    treap.insert(52, 11);
    treap.print();
}

