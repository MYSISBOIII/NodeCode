#include "lexer.h"

class Node
{
    public:
        Node();

        std::vector<Node> children;
        std::vector<Node> parents;
};

class OpNode : public Node
{
    public:

};

class Parser 
{
    public:
        Parser();
        
        /*
        template <typename T> 
        bool is_literal(T var);
        */
        
        template <typename T>
        std::vector<T> produce_AST(string source);
};