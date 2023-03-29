#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
    string data; // 노드가 저장하는 데이터
    // 다음 노드를 가리키는 포인터의 주소를 저장하는 배열
    Node* childNodes[10];

    // 생성자
    Node(string data) {
        this->data = data;
    }

    // 소멸자
    ~Node() {
        //자식 노드를 지우는 코드
    }

    void linkchildnode(Node* ptr) {
        for (int i = 0; i < 10; i++) {
            childNodes[i] = ptr;
        }
    }
};

class tree {
public:
    Node* root;

    tree() {
        root = nullptr;
    }
    ~tree() {
        delete root;
    }

    void addNode(Node* Parentnodeptr, string data) {
        if(root == nullptr)
        Node* newNode = new Node(data);
        Parentnodeptr->linkchildnode(newNode);
        
    }
};

void main() {

}