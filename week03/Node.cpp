#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
    string data; // ��尡 �����ϴ� ������
    // ���� ��带 ����Ű�� �������� �ּҸ� �����ϴ� �迭
    Node* childNodes[10];

    // ������
    Node(string data) {
        this->data = data;
    }

    // �Ҹ���
    ~Node() {
        //�ڽ� ��带 ����� �ڵ�
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