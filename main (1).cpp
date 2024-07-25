

#include <iostream>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

// TreeNode class to construct nodes for binary search tree
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

// Heap class to construct min-heap
class MinHeap {
private:
    vector<int> heap;

    void heapify(int idx) {
        int smallest = idx;
        int leftChild = 2 * idx + 1;
        int rightChild = 2 * idx + 2;

        if (leftChild < heap.size() && heap[leftChild] < heap[smallest])
            smallest = leftChild;
        if (rightChild < heap.size() && heap[rightChild] < heap[smallest])
            smallest = rightChild;
        if (smallest != idx) {
            swap(heap[idx], heap[smallest]);
            heapify(smallest);
        }
    }

public:
    void insert(int value) {
        heap.push_back(value);
        int idx = heap.size() - 1;
        while (idx > 0 && heap[idx] < heap[(idx - 1) / 2]) {
            swap(heap[idx], heap[(idx - 1) / 2]);
            idx = (idx - 1) / 2;
        }
    }

    void buildHeap(vector<int>& values) {
        heap = values;
        for (int i = heap.size() / 2 - 1; i >= 0; --i) {
            heapify(i);
        }
    }

    void printHeap() {
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }
};

// Non-member function to insert a node into BST
TreeNode* add(TreeNode* root, int value) {
    if (root == nullptr) {
        return new TreeNode(value);
    }
    if (value < root->val) {
        root->left = add(root->left, value);
    } else {
        root->right = add(root->right, value);
    }
    return root;
}

// Non-member function for post-order traversal of BST
void postOrder(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return;
    postOrder(root->left, result);
    postOrder(root->right, result);
    result.push_back(root->val);
}

// Non-member function for pre-order traversal of BST
void preOrder(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return;
    result.push_back(root->val);
    preOrder(root->left, result);
    preOrder(root->right, result);
}

// Function to populate BST from given data
TreeNode* populateTree(vector<int>& data) {
    TreeNode* root = nullptr;
    for (size_t i = 0; i < data.size(); ++i) {
        root = add(root, data[i]);
        if (i == 0)
            cout << data[i] << " is inserted as the root of BST" << endl;
        else
            cout << data[i] << " is inserted in BST" << endl;
    }
    return root;
}

int main() {
    int n;
    cout << "How many nodes do you want to insert into the BST? ";
    cin >> n;
    cin.ignore(); // Ignore the newline character left in the input buffer

    cout << "Enter " << n << " values to insert into the BST: ";
    string input;
    getline(cin, input);
    stringstream ss(input);

    vector<int> data;
    int value;
    while (ss >> value) {
        data.push_back(value);
    }

    cout << "Constructing BST from given data..." << endl;
    TreeNode* root = populateTree(data);

    // Post-order traversal and min-heap construction using insert method
    vector<int> postOrderData;
    postOrder(root, postOrderData);
    cout << "Post-order traversal of BST: ";
    for (int val : postOrderData) {
        cout << val << " ";
    }
    cout << endl;

    MinHeap heap1;
    for (int val : postOrderData) {
        heap1.insert(val);
    }
    cout << "Min-heap using insert method: ";
    heap1.printHeap();

    // Pre-order traversal and min-heap construction using buildHeap method
    vector<int> preOrderData;
    preOrder(root, preOrderData);
    cout << "Pre-order traversal of BST: ";
    for (int val : preOrderData) {
        cout << val << " ";
    }
    cout << endl;

    MinHeap heap2;
    heap2.buildHeap(preOrderData);
    cout << "Min-heap using buildHeap method: ";
    heap2.printHeap();

    return 0;
}
