//实现一棵AVL树，包括插入、删除、查找、遍历等操作
// Created by root on 2021/4/25.

#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

//定义一个AVL树类
template <class T>
class AVLTree{
private:
    //定义AVL树的节点
    struct Node{
        T data;
        Node *left;
        Node *right;
        int height;
        Node(const T &d, Node *l = nullptr, Node *r = nullptr, int h = 0)
                :data(d), left(l), right(r), height(h){}
    };
    Node *root;
    int size;

    int height(Node *t) const{
        return t == nullptr ? -1 : t->height;
    }
    
    void insert(const T &x, Node *&t){
        if(t == nullptr){
            t = new Node(x);
            size++;
        }
        else if(x < t->data){
            insert(x, t->left);
            if(height(t->left) - height(t->right) == 2){
                if(x < t->left->data)
                    rotateWithLeftChild(t);
                else
                    doubleWithLeftChild(t);
            }
        }
        else if(t->data < x){
            insert(x, t->right);
            if(height(t->right) - height(t->left) == 2){
                if(t->right->data < x)
                    rotateWithRightChild(t);
                else
                    doubleWithRightChild(t);
            }
        }
        else
            ;
        t->height = max(height(t->left), height(t->right)) + 1;
    }
    void remove(const T &x, Node *&t){
        if(t == nullptr)
            return;
        if(x < t->data){
            remove(x, t->left);
            if(height(t->right) - height(t->left) == 2){
                if(t->right->left != nullptr && height(t->right->left) > height(t->right->right))
                    doubleWithRightChild(t);
                else
                    rotateWithRightChild(t);
            }
        }
        else if(t->data < x){
            remove(x, t->right);
            if(height(t->left) - height(t->right) == 2){
                if(t->left->right != nullptr && height(t->left->right) > height(t->left->left))
                    doubleWithLeftChild(t);
                else
                    rotateWithLeftChild(t);
            }
        }
        else if(t->left != nullptr && t->right != nullptr){
            Node *tmp = t->right;
            while(tmp->left != nullptr)
                tmp = tmp->left;
            t->data = tmp->data;
            remove(t->data, t->right);
            if(height(t->left) - height(t->right) == 2){
                if(t->left->right != nullptr && height(t->left->right) > height(t->left->left))
                    doubleWithLeftChild(t);
                else
                    rotateWithLeftChild(t);
            }
        }
        else{
            Node *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
            size--;
        }
        if(t != nullptr)
            t->height = max(height(t->left), height(t->right)) + 1;
    }
    void rotateWithLeftChild(Node *&k2){
        Node *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }
    void rotateWithRightChild(Node *&k2){
        Node *k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(k2->height, height(k1->right)) + 1;
        k2 = k1;
    }
    void doubleWithLeftChild(Node *&k3){
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }
    void doubleWithRightChild(Node *&k3){
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);
    }
    void makeEmpty(Node *&t){
        if(t != nullptr){
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }
    void printTree(Node *t) const{
        if(t != nullptr){
            printTree(t->left);
            cout << t->data << " ";
            printTree(t->right);
        }
    }
    Node *clone(Node *t) const{
        if(t == nullptr)
            return nullptr;
        else
            return new Node(t->data, clone(t->left), clone(t->right), t->height);
    }
    Node *findMin(Node *t) const{
        if(t == nullptr)
            return nullptr;
        if(t->left == nullptr)
            return t;
        return findMin(t->left);
    }
    Node *findMax(Node *t) const{
        if(t == nullptr)
            return nullptr;
        if(t->right == nullptr)
            return t;
        return findMax(t->right);
    }
    bool contains(const T &x, Node *t) const{
        if(t == nullptr)
            return false;
        else if(x < t->data)
            return contains(x, t->left);
        else if(t->data < x)
            return contains(x, t->right);
        else
            return true;
    }
    void preOrder(Node *t) const{
        if(t != nullptr){
            cout << t->data << " ";
            preOrder(t->left);
            preOrder(t->right);
        }
    }
    void inOrder(Node *t) const{
        if(t != nullptr){
            inOrder(t->left);
            cout << t->data << " ";
            inOrder(t->right);
        }
    }
    void postOrder(Node *t) const{
        if(t != nullptr){
            postOrder(t->left);
            postOrder(t->right);
            cout << t->data << " ";
        }
    }
    void levelOrder(Node *t) const{
        if(t == nullptr)
            return;
        queue<Node *> q;
        q.push(t);
        while(!q.empty()){
            Node *tmp = q.front();
            q.pop();
            cout << tmp->data << " ";
            if(tmp->left != nullptr)
                q.push(tmp->left);
            if(tmp->right != nullptr)
                q.push(tmp->right);
        }
    }
    void preOrderNonRecursion(Node *t) const{
        if(t == nullptr)
            return;
        stack<Node *> s;
        s.push(t);
        while(!s.empty()){
            Node *tmp = s.top();
            s.pop();
            cout << tmp->data << " ";
            if(tmp->right != nullptr)
                s.push(tmp->right);
            if(tmp->left != nullptr)
                s.push(tmp->left);
        }
    }
    void inOrderNonRecursion(Node *t) const{
        if(t == nullptr)
            return;
        stack<Node *> s;
        Node *tmp = t;
        while(tmp != nullptr || !s.empty()){
            while(tmp != nullptr){
                s.push(tmp);
                tmp = tmp->left;
            }
            tmp = s.top();
            s.pop();
            cout << tmp->data << " ";
            tmp = tmp->right;
        }
    }
    void postOrderNonRecursion(Node *t) const{
        if(t == nullptr)
            return;
        stack<Node *> s;
        Node *tmp = t;
        Node *lastVisit = nullptr;
        while(tmp != nullptr || !s.empty()){
            while(tmp != nullptr){
                s.push(tmp);
                tmp = tmp->left;
            }
            tmp = s.top();
            s.pop();
            if(tmp->right == nullptr || tmp->right == lastVisit){
                cout << tmp->data << " ";
                lastVisit = tmp;
                tmp = nullptr;
            }
            else{
                s.push(tmp);
                tmp = tmp->right;
            }
        }
    }
public:
    AVLTree(){
        root = nullptr;
        size = 0;
    }
    AVLTree(const AVLTree &rhs){
        root = clone(rhs.root);
        size = rhs.size;
    }
    ~AVLTree(){
        makeEmpty(root);
    }
    const T &findMin() const{
        return findMin(root)->data;
    }
    const T &findMax() const{
        return findMax(root)->data;
    }
    bool contains(const T &x) const{
        return contains(x, root);
    }
    bool isEmpty() const{
        return root == nullptr;
    }
    void printTree() const{
        if(isEmpty())
            cout << "Empty tree" << endl;
        else
            printTree(root);
    }
    void makeEmpty(){
        makeEmpty(root);
    }
    void insert(const T &x){
        insert(x, root);
    }
    void remove(const T &x){
        remove(x, root);
    }
    void preOrder() const{
        if(isEmpty())
            cout << "Empty tree" << endl;
        else
            preOrder(root);
    }
    void inOrder() const{
        if(isEmpty())
            cout << "Empty tree" << endl;
        else
            inOrder(root);
    }
    void postOrder() const{
        if(isEmpty())
            cout << "Empty tree" << endl;
        else
            postOrder(root);
    }
    void levelOrder() const{
        if(isEmpty())
            cout << "Empty tree" << endl;
        else
            levelOrder(root);
    }
    void preOrderNonRecursion() const{
        if(isEmpty())
            cout << "Empty tree" << endl;
        else
            preOrderNonRecursion(root);
    }
    void inOrderNonRecursion() const{
        if(isEmpty())
            cout << "Empty tree" << endl;
        else
            inOrderNonRecursion(root);
    }
    void postOrderNonRecursion() const{
        if(isEmpty())
            cout << "Empty tree" << endl;
        else
            postOrderNonRecursion(root);
    }
};

//定义一个类，用于测试AVL树
class Test{
private:
    int x;
public:
    Test(int n = 0):x(n){}
    bool operator<(const Test &rhs) const{
        return x < rhs.x;
    }
    bool operator>(const Test &rhs) const{
        return x > rhs.x;
    }
    bool operator==(const Test &rhs) const{
        return x == rhs.x;
    }
    friend ostream &operator<<(ostream &os, const Test &rhs){
        os << rhs.x;
        return os;
    }
};

//定义一个函数，用于测试AVL树

