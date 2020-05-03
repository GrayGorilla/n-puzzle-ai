#ifndef SEARCH_TREE_HPP
#define SEARCH_TREE_HPP

#include <memory>
#include <vector>

struct Node {
    std::vector<std::vector<int>> value;
    std::vector<std::shared_ptr<Node>> children;
    std::unique_ptr<Node> parent;
};

class SearchTree {
    private:
        std::shared_ptr<Node> root;
    public:
        SearchTree();
        ~SearchTree();
};

#endif
