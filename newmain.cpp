//Saikapish Sahu
//3/15/24
//Shunting Yard
//Function names and var names/modularity derived from Jazveer K at github.com/JazveerK
//Print and Queing found from Arjun V and Nikaansh S

#include <iostream>
#include <cstring>
#include "node.H"

using namespace std;

// list of functions
void pushNode(Node* &topNode, Node* newNode);
Node* popNode(Node* &topNode);
Node* peekNode(Node* topNode);
void enqueueNode(Node* &frontNode, Node* &rearNode, Node* newNode);
Node* dequeueNode(Node* &frontNode);
bool isOperator(char c);
int precedence(char c);
void convertToPostfix(const char* input, char* postfixExpression);
Node* constructExpressionTree(const char* postfixExpression);
void displayInfix(Node* root);
void displayPrefix(Node* root);
void displayPostfix(Node* root);



// Stack functions
void pushNode(Node* &topNode, Node* newNode) {
    newNode->setNext(topNode);
    topNode = newNode;
}

Node* popNode(Node* &topNode) {
    if (topNode == nullptr) {
        cerr << "Stack underflow\n";
        return nullptr;
    }
    Node* data = topNode;
    topNode = topNode->getNext();
    return data;
}

Node* peekNode(Node* topNode) {
    if (topNode == nullptr) {
        cerr << "Stack is empty\n";
        return nullptr;
    }
    return topNode;
}

// display function being called from node
void displayInfix(Node* root) {//infix display
    if (root) {
        if (isOperator(root->getData()) && root->getData() != '(')
            cout << "(";
        displayInfix(root->getLeft());
        cout << root->getData();
        displayInfix(root->getRight());
        if (isOperator(root->getData()) && root->getData() != ')')
            cout << ")";
    }
}

void displayPrefix(Node* root) {//prefix display
    if (root) {
        cout << root->getData();
        displayPrefix(root->getLeft());
        displayPrefix(root->getRight());
    }
}

void displayPostfix(Node* root) { //post fix display
    if (root) {
        displayPostfix(root->getLeft());
        displayPostfix(root->getRight());
        cout << root->getData();
    }
}

bool isOperator(char c) { //set of operaters that will be read
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}


int precedence(char c) { //order and precedence of what operators will be taken
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
    else if (c == '(' || c == ')')
        return 0;
    return 0;
}


void convertToPostfix(const char* input, char* postfixExpression) {//main yard algorithm 
    Node* operatorStack = nullptr;
    Node* outputQueueFrontNode = nullptr; //setting queues to null
    Node* outputQueueRearNode = nullptr;
    int i = 0;

    while (input[i] != '\0') {
        char token = input[i];
        if (token == '(')
            pushNode(operatorStack, new Node(token));
        else if (isdigit(token))
            enqueueNode(outputQueueFrontNode, outputQueueRearNode, new Node(token));
        
        else if (token == ')') {
            while (operatorStack != nullptr && peekNode(operatorStack)->getData() != '(')
                enqueueNode(outputQueueFrontNode, outputQueueRearNode, popNode(operatorStack));
            popNode(operatorStack);
        } 
        
        else if (isOperator(token)) {
            while (operatorStack != nullptr && precedence(peekNode(operatorStack)->getData()) >= precedence(token) && peekNode(operatorStack)->getData() != '(')
                enqueueNode(outputQueueFrontNode, outputQueueRearNode, popNode(operatorStack));
            pushNode(operatorStack, new Node(token));
        }
        i++;
    }

    while (operatorStack != nullptr)
        enqueueNode(outputQueueFrontNode, outputQueueRearNode, popNode(operatorStack));

    // Queue into postfixExpression
    Node* current = outputQueueFrontNode;
    int j = 0;
    while (current != nullptr) {
        postfixExpression[j++] = current->getData();
        current = current->getNext();
    }
    postfixExpression[j] = '\0';
}

//actual construction of the expression binary tree
Node* constructExpressionTree(const char* postfixExpression) {
    Node* nodeStack = nullptr;
    int i = 0;

    while (postfixExpression[i] != '\0') {
        char token = postfixExpression[i];
        Node* newNode = new Node(token);
        if (!isOperator(token)) {
            newNode->setLeft(nullptr);
            newNode->setRight(nullptr);
        } 
        
        else {
            Node* right = popNode(nodeStack);
            Node* left = popNode(nodeStack);
            newNode->setLeft(left);
            newNode->setRight(right);
        }
        pushNode(nodeStack, newNode);
        i++;
    }
    return popNode(nodeStack);
}




//queueing and dequeueing the nodes
void enqueueNode(Node* &frontNode, Node* &rearNode, Node* newNode) {
    if (frontNode == nullptr) {
        frontNode = rearNode = newNode;
    } else {
        rearNode->setNext(newNode);
        rearNode = newNode;
    }
}

Node* dequeueNode(Node* &frontNode) {
    if (frontNode == nullptr) {
        cerr << "Queue is empty\n";
        return nullptr;
    }
    Node* data = frontNode;
    frontNode = frontNode->getNext();
    return data;
}

//main function that cals all the functions and prompts the user
int main() {
    char input[100];
    Node* root = nullptr;
    Node* stackTopNode = nullptr;
    Node* queueFrontNode = nullptr;
    Node* queueRearNode = nullptr;
    bool running = true;
    char command[10];
    
    while (running) {
        // user prompt
        cout << endl << "input an expression: " << endl;
        cout << "Calculate" << endl; //names from Jazveer's 'main.cpp' from github.com/JazveerK
        cout << "Quit" << endl << endl;
        
        
        cin.get(command, 10);
        cin.clear();
        cin.ignore(100, '\n');
        
        if (strcmp(command, "Quit") == 0) {
            running = false;
        }
        
        else if (strcmp(command, "Calculate") == 0) {
            
            // Input
            cout << "Enter equation in infix notation: ";
            cin.getline(input, 100);
            
            char postfixExpression[100];
            convertToPostfix(input, postfixExpression);

            root = constructExpressionTree(postfixExpression);
            
            // printing all of the fixes based on the input
            cout << "Postfix Expression: " << postfixExpression << endl;
            cout << "Infix Notation: ";
            displayInfix(root);
            cout << endl;
            cout << "Prefix Notation: ";
            displayPrefix(root);
            cout << endl;
            cout << "Postfix Notation: ";
            displayPostfix(root);
            cout << endl;
        }
    }
    return 0;
}
