//sai sahu
//modulairty from Jazveer K.
//var names from Arjun V and Nikaansh S
//names pulled from Jazveerk K's 'Node.cpp/Node.H" files from github.com/JazveerK
#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;



// classifier and implimenting
Node::Node() {
    data = '\0';
    //creating pointers for all directions (name from Jazveer K)
    next = nullptr;
    left = nullptr;
    right = nullptr;
}

Node::Node(char newData) {
    data = newData;
    next = nullptr;
    left = nullptr;
    right = nullptr;
}
//creating getters and setters for all sides and the data values
char Node::getData() {
    return data;
}

Node* Node::getNext() {
    return next;
}

Node* Node::getLeft() {
    return left;
}

Node* Node::getRight() {
    return right;
}

void Node::setData(char newData) {
    data = newData;
}

void Node::setNext(Node* newNext) {
    next = newNext;
}

void Node::setLeft(Node* newLeft) {
    left = newLeft;
}

void Node::setRight(Node* newRight) {
    right = newRight;
}
