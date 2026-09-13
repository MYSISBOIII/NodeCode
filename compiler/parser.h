#include "lexer.h"

class Node
{
    public:
        Node();

        std::vector<Node> children;
        std::vector<Node> parents;
};

class Parser 
{
    public:
        Parser();
        template <typename T> 
        bool is_literal(T var);
        void produce_AST(string source);
};