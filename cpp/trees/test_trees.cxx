#include <iostream>
#include <vector>

using namespace std;


template<typename T>
struct Node {
    Node(const T v) : value(v), children() {};
    T value;
    vector<Node*> children;
};

void print(Node<int> *root) {
    if(root->children.empty()) {
        return;
    }

    for(auto c:root->children) {
        cout << c->value << " ";
    }
    cout << endl;
    for(auto c:root->children) {
        print(c);
    }
}

void buildTree(Node<int> *root, const int k) {
    auto n = root->value;
    if(n==1) {
        return;
    }
    auto numChildren = n/k;
    auto remainder = n%k;
    for(int i=0; i<numChildren; i++) {
        root->children.push_back(new Node<int>(k));
    }
    if(remainder>0) {
        root->children.push_back(new Node<int>(remainder));
    }

    for(auto c : root->children) {
        buildTree(c, k-1);
    }
}

void climbingStairs(const int n, const int k) {
    Node<int> *root = new Node<int>(n);
    buildTree(root, k);
    print(root);
}

int main()
{
    cout << "Testing trees...\n";
    climbingStairs(5, 2);
}