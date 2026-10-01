//
// Created by DDWQ on 29.09.2026.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Methods.h"
#include "Node.h"

void Methods::show(const std::string &name) {
    std::ifstream fin(name);
    std::string line;
    if (fin.is_open()) {
        while (std::getline(fin, line)) {
            std::cout << line << std::endl;
        }
        fin.close();
    }
}

std::vector<Token> Methods::tokenize(const std::string &line) {
    std::vector<Token> tokens;
    int i = 0;
    while (i < line.size()) {
        char c = line[i];

        if (isspace(c)) {
            i++;
            continue;
        }

        if (isalpha(c)) {
            std::string word;
            while (i < line.size() && isalnum(line[i])) {
                word += line[i];
                i++;
            }

            if (word == "int" || word == "print") {
                tokens.push_back({"KEYWORD", word});
            } else {
                tokens.push_back({"ID", word});
            }
            continue;
        }

        if (isdigit(c)) {
            std::string num;
            while (i < line.size() && isdigit(line[i])) {
                num += line[i];
                i++;
            }
            tokens.push_back({"NUM", num});
            continue;
        }

        if (c == '=' || c == '+' || c == '-' || c == '*' || c == '/') {
            tokens.push_back({"OP", std::string(1, c)});
            i++;
            continue;
        }

        if (c == '(' || c == ')') {
            tokens.push_back({"PAREN", std::string(1, c)});
            i++;
            continue;
        }

        if (c == ';') {
            tokens.push_back({"SEMI", ";"});
            i++;
            continue;
        }

        i++;
    }
    return tokens;
}


Node Methods::parse(const std::vector<Token>& tokens) {
    Node root;

    if (tokens[0].type == "KEYWORD" && tokens[0].value == "int") {
        root.type = "VarDecl";
        root.value = "int";

        Node nameNode;
        nameNode.type = "Id";
        nameNode.value = tokens[1].value;

        Node valueNode;
        valueNode.type = "Num";
        valueNode.value = tokens[3].value;

        root.children.push_back(nameNode);
        root.children.push_back(valueNode);
    }
    else if (tokens[0].type == "KEYWORD" && tokens[0].value == "print") {
        root.type = "Print";

        Node expr;
        expr.type = "BinOp";
        expr.value = tokens[3].value;

        Node left;
        left.type = "Id";
        left.value = tokens[2].value;

        Node right;
        right.type = "Id";
        right.value = tokens[4].value;

        expr.children.push_back(left);
        expr.children.push_back(right);
        root.children.push_back(expr);
    }

    return root;
}


void Methods::eval(const Node& node, std::map<std::string, int>& vars) {
    if (node.type == "VarDecl") {
        std::string name = node.children[0].value;
        int value = std::stoi(node.children[1].value);
        vars[name] = value;
    }
    else if (node.type == "Print") {
        Node expr = node.children[0];
        if (expr.type == "BinOp") {
            std::string leftName = expr.children[0].value;
            std::string rightName = expr.children[1].value;
            int result = 0;
            if (expr.value == "+") result = vars[leftName] + vars[rightName];
            else if (expr.value == "-") result = vars[leftName] - vars[rightName];
            else if (expr.value == "*") result = vars[leftName] * vars[rightName];
            else if (expr.value == "/") result = vars[leftName] / vars[rightName];
            std::cout << result << std::endl;
        }
    }
}