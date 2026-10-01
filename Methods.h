//
// Created by DDWQ on 29.09.2026.
//

#pragma once
#include <string>
#include <vector>
#include <map>
#include "Token.h"
#include "Node.h"

class Methods {
public:
    void show(const std::string& name);
    std::vector<Token> tokenize(const std::string& line);
    Node parse(const std::vector<Token>& tokens);
    void eval(const Node& node, std::map<std::string, int>& vars);
};