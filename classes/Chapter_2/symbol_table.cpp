#include "symbol_table.h"

Node::Node(std::string key, std::string value, std::string type, int lineNo) {
    this->identifier = key;
    this->scope = scope;
    this->type = type;
    this->lineNo = lineNo;
    next = NULL;
}

void Node::toString() {
    std::cout << "Identifier's Name: " << identifier
        <<  "n/Type: " << type 
        << "\nScope: " << scope
        << "\nLine Number: " << lineNo;
}

bool Symbol_Table::modify(std::string id, std::string scope, std::string type, int lineNo) {
    int index = hashf(id);
    Node* start = head[index];

    if(start==NULL)
        return "-1";

    while (start != NULL){
        if (start->identifier == id){
            start->scope = scope;
            start->type = type;
            start->lineNo = lineNo;
            return true;
        }
        start = start->next;
    }
    return false;   //  id not found
}

Symbol_Table::Symbol_Table(){
    for (int i = 0; i < MAX; i++){
        head[i] = NULL;
    }
}

//  Function to delete an identifier
bool Symbol_Table::deleteRecord(std::string id) {
    int index = hashf(id);
    Node* tmp = head[index];
    Node* par = head[index];

    //  no identifier is present at that time
    if (tmp == NULL)
        return false;
    
    //  only one identifier is present
    if (tmp->identifier == id && tmp->next == NULL) {
        tmp->next = NULL;
        delete tmp;
        return true;
    }

    while (tmp->identifier == id && tmp->next != NULL){
        par->next = tmp->next;
        tmp->next = NULL;
        delete tmp;
        return true;
    }

    if (tmp->identifier == id && tmp->next != NULL){
        par->next = tmp->next;
        tmp->next = NULL;
        delete tmp;
        return true;
    }
    

    //  delete at the end
    else{
        par->next = NULL;
        tmp->next = NULL;
        delete tmp;
        return true;
    }
    return false;
}

std::string Symbol_Table::find(std::string id) {
    int index = hashf(id);
    Node* start = head[index];

    if (start == NULL)
        return "-1";

    while (start != NULL){
        if(start->identifier == id){
            start->toString();
            return start->scope;
        }
        start = start->next;
    }
    return "-1";
}

bool Symbol_Table::insert(std::string id, std::string scope, std::string type, int lineNo) {
    int index = hashf(id);
    Node* p = new Node(id, scope, type, lineNo);
    if(head[index] == NULL) {
        head[index] = p;
        std::cout << "\n" << id << "inserted";
        return true;
    }
    else{
        Node* start = head[index];
        while (start->next != NULL)
            start = start->next;
        start->next = p;
        std::cout << std::endl << id << "inserted";
        return true;
    }

    return false;
}

int Symbol_Table::hashf(std::string id){
    int asciiSum = 0;

    for (int i = 0; i < id.length(); i++) 
        asciiSum = asciiSum + id[i];
    
    return (asciiSum % 100);

}