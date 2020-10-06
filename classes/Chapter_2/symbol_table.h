#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "node.h"

const int MAX = 100;

class Symbol_Table{

private:
    Node* head[MAX];

public:
    Symbol_Table(/* args */);
    int hashf(std::string id);   // Hash function
    bool insert(std::string id, std::string scope, 
                std::string type, int lineNo);
    std::string find(std::string id);
    bool deleteRecord(std::string id);
    bool modify(std::string id, std::string scope,
                std::string type, int lineNo);
};

#endif
