#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <string>
#include <unordered_map>
#include <filesystem>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int value) : key(value), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root; // 트리의 루트 노드 포인터. 
    // x의 왼쪽 서브트리 값들은 모두 x->key보다 작음
    // x의 오른쪽 서브트리 값들은 모두 x->key보다 큼

    Node* insert(Node* node, int key) {
        // 이론: BST 규칙에 따라 탐색 경로를 타고 내려가 리프의 빈 자리에 삽입. 
        // key == noe->key인 경우 아무것도 하지 않음. 

        // 빈자리에 새 노드 삽입.
        if (!node) return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key); // 왼쪽으로 재귀
        else if (key > node->key)
            node->right = insert(node->right, key); // 오른쪽으로 재귀
        return node; // 현재 서브트리의 루트 반환
    }

    Node* search(Node* node, int key) {
        if (!node || node->key == key) return node;
        if (key < node->key) return search(node->left, key);
        else return search(node->right, key);
    }    

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (!node) return;
        cout << node->key << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->key << " ";
    }

    void levelorder(Node* root) {
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* node = q.front(); q.pop();
            cout << node->key << " ";
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }

public:
    BST() : root(nullptr) {} // 생성자에서 빈 트리 생성
    // 이론적으로는 공집합으로부터 시작해서 삽입으로 트리를 구성

    void insert(int key) { root = insert(root, key); }

    bool search(int key) { return search(root, key) != nullptr; }

    void inorder() { inorder(root); cout << endl; }
    void preorder() { preorder(root); cout << endl; }
    void postorder() { postorder(root); cout << endl; }
    void levelorder() { levelorder(root); cout << endl; }
};

int main() {
    BST tree;
    unordered_map<int, int> value_to_row; // 값 → CSV 행 번호 매핑

    ifstream file("/home/siwon/study_ws/src/baselab/data_structure/src/example_data.csv");
    if (!file.is_open()) {
        cerr << "CSV 파일을 열 수 없습니다!" << endl;
        return 1;
    }

    string line;
    getline(file, line); // 헤더 제거
    int row = 1; // 헤더 제외한 첫 번째 데이터가 1행

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, valueStr;
        getline(ss, idStr, ',');
        getline(ss, valueStr, ',');

        int value = stoi(valueStr);
        tree.insert(value);
        value_to_row[value] = row;
        row++;
    }

    cout << "CSV 데이터를 BST에 삽입 완료!" << endl;

    cout << "중위순회(Inorder): ";
    tree.inorder();

    cout << "전위순회(Preorder): ";
    tree.preorder();

    cout << "후위순회(Postorder): ";
    tree.postorder();

    cout << "레벨순회(Level-order): ";
    tree.levelorder();

    // 사용자 입력 받아서 찾기
    int query;
    cout << "\n찾고 싶은 값을 입력하세요: ";
    cin >> query;

    if (tree.search(query)) {
        cout << query << " 값은 CSV " << value_to_row[query] << "행에 있습니다." << endl;
    } else {
        cout << query << " 값은 트리와 CSV에 존재하지 않습니다." << endl;
    }

    return 0;

}
