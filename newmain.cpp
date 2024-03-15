//sai sahu
//3/11/24
//shunting yard
//var names, func names and modularity inspired by Jazveer K
//logistics and node inspired by Arjun v. and Nikaansh S.
//printing function found from Geeks4Geeks

#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

// Function prototypes
void pushStack(Node* &top, Node* newNode);
Node* popStack(Node* &top);
Node* peekStack(Node* top);
void enqueueQueue(Node* &front, Node* &rear, Node* newNode);
void dequeueQueue(Node* &front);
bool isOperator(char c);
int getPrecedence(char c);
void convertToPostfix(const char* input, char* postfixExpression);
Node* constructExpressionTree(const char* postfixExpression);
void printInfixExpression(Node* root);
void printPrefixExpression(Node* root);
void printPostfixExpression(Node* root);

int main() {
    char input[100];
    Node* root = nullptr;
    Node* stackTop = nullptr;
    Node* queueFront = nullptr;
    Node* queueRear = nullptr;
    bool running = true;
    char command[10];

   
    
    while (running) {
        // Prompting User
        cout << endl << "enter a prompt: " << endl;
        cout << "Calculate" << endl;
        cout << "Quit" << endl << endl;
        
        cin.get(command, 10);
        cin.clear();
        cin.ignore(100, '\n');
        
        if (strcmp(command, "Quit") == 0) {
            running = false;
        }
        
        else if (strcmp(command, "Calculate") == 0) {
            // Input
            cout << "enter equation in infix notation format: ";
            cin.getline(input, 100);
            
            char postfixExpression[100];
            convertToPostfix(input, postfixExpression);

            root = constructExpressionTree(postfixExpression);
            
            // Output
            cout << "Postfix Expression Format: " << postfixExpression << endl;
            cout << "Infix notation Format: ";
            printInfixExpression(root);
            cout << endl;
            cout << "Prefix Notation format: ";
            printPrefixExpression(root);
            cout << endl;
            cout << "Postfix Notation Format: ";
            printPostfixExpression(root);
            cout << endl;
        }
    }
    return 0;
}

//stack related functions - push and pop
void pushStack(Node* &top, Node* newNode) {
    newNode->setNext(top);
    top = newNode;
}

Node* popStack(Node* &top) {
    if (top == nullptr) {
        cerr << "Stack underflow" << endl;
        return nullptr;
    }
    Node* data = top;
    top = top->getNext();
    return data;
}

Node* peekStack(Node* top) {
    if (top == nullptr) {
        cerr << "Stack is empty" << endl;
        return nullptr;
    }
    return top;
}

// que related functions - enque deque
void enqueueQueue(Node* &front, Node* &rear, Node* newNode) {
    if (front == nullptr) {
        front = rear = newNode;
    } else {
        rear->setNext(newNode);
        rear = newNode;
    }
}

void dequeueQueue(Node* &front) {
    if (front == nullptr) {
        cerr << "Queue is empty" << endl;
        return;
    }
    Node* data = front;
    front = front->getNext();
    delete data;
}

//functions names from Jazveer K

bool isOperator(char c) { //operator tools and signifiers
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int getPrecedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    return 0;
}

//this is the function for post fix

void convertToPostfix(const char* input, char* postfixExpression) {
    Node* operatorStack = nullptr;
    int i = 0;
    int j = 0;

    while (input[i] != '\0') {
        char token = input[i];
        
        if (token == '(')
            pushStack(operatorStack, new Node(token));
        
        else if (isdigit(token)) {
            postfixExpression[j++] = token;
        }
        
        else if (token == ')') {
            while (peekStack(operatorStack)->getData() != '(') {
                postfixExpression[j++] = popStack(operatorStack)->getData();
            }
            popStack(operatorStack); // remove (
        } 
        
        else if (isOperator(token)) {
            while (operatorStack != nullptr && getPrecedence(peekStack(operatorStack)->getData()) >= getPrecedence(token)) {
                postfixExpression[j++] = popStack(operatorStack)->getData();
            }
            pushStack(operatorStack, new Node(token));
        }
        
        i++;
    }

    while (operatorStack != nullptr) {
        postfixExpression[j++] = popStack(operatorStack)->getData();
    }

    postfixExpression[j] = '\0';
}

// Expression Tree Construction
Node* constructExpressionTree(const char* postfixExpression) {
    Node* nodeStack = nullptr;
    int i = 0;

    while (postfixExpression[i] != '\0') {
        char token = postfixExpression[i];
        Node* newNode = new Node(token);
        
        if (!isOperator(token)) { //if token is avalible
            pushStack(nodeStack, newNode);
        } 
        else {
            Node* right = popStack(nodeStack);
            Node* left = popStack(nodeStack);
            newNode->setLeft(left);
            newNode->setRight(right);
            pushStack(nodeStack, newNode);
        }
        
        i++;
    }
    
    return popStack(nodeStack);
}

//printing provided expressions
void printInfixExpression(Node* root) {
    if (root != nullptr) {
        if (isOperator(root->getData())) {
            cout << "(";
        }
        printInfixExpression(root->getLeft());
        cout << root->getData();
        printInfixExpression(root->getRight());
        if (isOperator(root->getData())) {
            cout << ")";
        }
    }
}

void printPrefixExpression(Node* root) {
    if (root != nullptr) {
        cout << root->getData();
        printPrefixExpression(root->getLeft());
        printPrefixExpression(root->getRight());
    }
}

void printPostfixExpression(Node* root) {
    if (root != nullptr) {
        printPostfixExpression(root->getLeft());
        printPostfixExpression(root->getRight());
        cout << root->getData();
    }
}
