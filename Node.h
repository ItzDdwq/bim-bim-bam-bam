#pragma once
#include <string>
#include <vector>

struct Node {
    std::string type;
    std::string value;
    std::vector<Node> children;
};
