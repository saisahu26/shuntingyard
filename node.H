//sai sahu
//var names from Jazveer K
//modulairty from Arjun V (partially) and Nikaansh S (Getters were given)

#ifndef NODE_H
#define NODE_H

class Node { //names pulled from Jazveerk K's 'Node.cpp/Node.H" files from github.com/JazveerK
private:
    char data;
    Node* next;
    Node* left;
    Node* right;

public:
    // Constructors
    Node();
    Node(char newData);
    
    // Getters
    char getData();
    Node* getNext();
    Node* getLeft();
    Node* getRight();
    
    // Setters
    void setData(char newData);
    void setNext(Node* newNext);
    void setLeft(Node* newLeft);
    void setRight(Node* newRight);
};

#endif
