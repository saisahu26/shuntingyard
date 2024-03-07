//saikapish sahu
//shunting yard
#include <iostream>
#include <stack>
#include <queue>
#include <cctype>

// Forward declarations
template <typename T>
class Stack;

template <typename T>
class Queue;

class ShuntingYard;

template <typename T>
class BinaryTreeNode;

class ExpressionTree;

// Stack class using linked list
template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* top;

public:
    Stack() : top(nullptr) {}

    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            std::cerr << "Stack is empty. Cannot pop.\n";
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    T peek() const {
        if (isEmpty()) {
            std::cerr << "Stack is empty. Cannot peek.\n";
            return T();
        }
        return top->data;
    }

    bool isEmpty() const {
        return top == nullptr;
    }
};

// Queue class using linked list
template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            std::cerr << "Queue is empty. Cannot dequeue.\n";
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
    }

    bool isEmpty() const {
        return front == nullptr;
    }
};

// Shunting Yard Algorithm class
class ShuntingYard {
public:
    static std::string convertToPostfix(const std::string& infixExpression);
};

// Binary Tree Node class
template <typename T>
class BinaryTreeNode {
public:
    T data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    BinaryTreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

// Expression Tree class
class ExpressionTree {
private:
    BinaryTreeNode<char>* root;

    void destroyTree(BinaryTreeNode<char>* node);

    BinaryTreeNode<char>* buildExpressionTreeHelper(const std::string& postfixExpression);

public:
    ExpressionTree() : root(nullptr) {}

    void buildTreeFromPostfix(const std::string& postfixExpression);

    void printInfixHelper(BinaryTreeNode<char>* node) const;

    void printInfix() const;

    void printPrefixHelper(BinaryTreeNode<char>* node) const;

    void printPrefix() const;

    void printPostfixHelper(BinaryTreeNode<char>* node) const;

    void printPostfix() const;

    ~ExpressionTree();
};

std::string ShuntingYard::convertToPostfix(const std::string& infixExpression) {
    std::string postfixExpression;
    std::stack<char> operators;

    for (char token : infixExpression) {
        if (std::isalnum(token)) {
            postfixExpression += token;
        } else if (token == '(') {
            operators.push(token);
        } else if (token == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfixExpression += operators.top();
                operators.pop();
            }
            operators.pop();  // Discard the '('
        } else {
            while (!operators.empty() && operators.top() != '(' && precedence(operators.top()) >= precedence(token)) {
                postfixExpression += operators.top();
                operators.pop();
            }
            operators.push(token);
        }
    }

    while (!operators.empty()) {
        postfixExpression += operators.top();
        operators.pop();
    }

    return postfixExpression;
}

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else if (op == '^') {
        return 3;
    }
    return 0; // For other characters (operands)
}

BinaryTreeNode<char>* ExpressionTree::buildExpressionTreeHelper(const std::string& postfixExpression) {
    std::stack<BinaryTreeNode<char>*> nodes;

    for (char token : postfixExpression) {
        if (std::isalnum(token)) {
            BinaryTreeNode<char>* operand = new BinaryTreeNode<char>(token);
            nodes.push(operand);
        } else {
            BinaryTreeNode<char>* right = nodes.top();
            nodes.pop();
            BinaryTreeNode<char>* left = nodes.top();
            nodes.pop();

            BinaryTreeNode<char>* operatorNode = new BinaryTreeNode<char>(token);
            operatorNode->left = left;
            operatorNode->right = right;

            nodes.push(operatorNode);
        }
    }

    return nodes.top();
}

void ExpressionTree::buildTreeFromPostfix(const std::string& postfixExpression) {
    root = buildExpressionTreeHelper(postfixExpression);
}

void ExpressionTree::destroyTree(BinaryTreeNode<char>* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void ExpressionTree::printInfixHelper(BinaryTreeNode<char>* node) const {
    if (node) {
        if (std::isalnum(node->data)) {
            std::cout << node->data;
        } else {
            std::cout << "(";
            printInfixHelper(node->left);
            std::cout << node->data;
            printInfixHelper(node->right);
            std::cout << ")";
        }
    }
}

void ExpressionTree::printInfix() const {
    printInfixHelper(root);
}

void ExpressionTree::printPrefixHelper(BinaryTreeNode<char>* node) const {
    if (node) {
        std::cout << node->data;
        printPrefixHelper(node->left);
        printPrefixHelper(node->right);
    }
}

void ExpressionTree::printPrefix() const {
    printPrefixHelper(root);
}

void ExpressionTree::printPostfixHelper(BinaryTreeNode<char>* node) const {
    if (node) {
        printPostfixHelper(node->left);
        printPostfixHelper(node->right);
        std::cout << node->data;
    }
}

void ExpressionTree::printPostfix() const {
    printPostfixHelper(root);
}

// Destructor for ExpressionTree
ExpressionTree::~ExpressionTree() {
    destroyTree(root);
}

int main() {
    std::cout << "Enter an infix expression with spaces between each token: ";
    std::string infixExpression;
    std::getline(std::cin, infixExpression);

    // Shunting Yard Algorithm
    std::string postfixExpression = ShuntingYard::convertToPostfix(infixExpression);
    std::
}
