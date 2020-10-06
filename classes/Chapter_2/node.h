#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>

class Node {
public:
    std::string identifier, scope, type;
    int lineNo;
    Node* next;
    Node(std::string key, std::string value, std::string type, int lineNo);
    void toString();
};

#endif