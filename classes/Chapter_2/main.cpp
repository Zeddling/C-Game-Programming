#include "symbol_table.h"

int main() {
    Symbol_Table st;
    std::string check;

    std::cout << "**** SYMBOL TABLE ****";

    // insert 'if'
    if ( st.insert("if", "local", "keyword", 4) ) 
        std::cout << "-successful";
    else
        std::cout << "\nFailed to insert.\n";
    
    // insert 'number' 
    if (st.insert("number", "global", "variable", 2)) 
        std::cout << " -successfully\n\n"; 
    else
        std::cout << "\nFailed to insert\n"; 
  
    // find 'if' 
    check = st.find("if"); 
    if (check != "-1") 
        std::cout << "Identifier Is present\n"; 
    else
        std::cout << "\nIdentifier Not Present\n";
    
// delete 'if' 
    if (st.deleteRecord("if")) 
        std::cout << "if Identifier is deleted\n"; 
    else
        std::cout << "\nFailed to delete\n"; 
  
    // modify 'number' 
    if (st.modify("number", "global", "variable", 3)) 
        std::cout << "\nNumber Identifier updated\n"; 
  
    // find and print 'number' 
    check = st.find("number"); 
    if (check != "-1") 
        std::cout << "Identifier Is present\n"; 
    else
        std::cout << "\nIdentifier Not Present"; 
  
    return 0; 
}