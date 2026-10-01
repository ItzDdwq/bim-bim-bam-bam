#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include <windows.h>
#include "Methods.h"

void printNode(const Node& node, int depth = 0) {
    for (int i = 0; i < depth; i++) std::cout << "  ";
    std::cout << node.type << "(" << node.value << ")" << std::endl;
    for (const auto& child : node.children) {
        printNode(child, depth + 1);
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::string line;

    do {
        std::cout << "> ";
        std::getline(std::cin, line);

        std::stringstream ss(line);
        std::string command, filename;
        ss >> command >> filename;


        if (command == "help") std::cout << "Команды: "
                                            "\nhelp"
                                            "\nexit"
                                            "\nview <файл>"
                                            "\ntokens <файл>"
                                            "\nparse <файл>"
                                            "\nexec <файл>" << std::endl;
        else if (command == "view") {
            Methods m;
            m.show(filename);
        }
        else if (command == "tokens") {
            Methods m;
            std::fstream fin(filename);
            std::string fileLine;

            while (std::getline(fin, fileLine)) {
                std::vector<Token> tokens = m.tokenize(fileLine);
                for (auto& t : tokens) {
                    std::cout << t.type << "(" << t.value << ")" << std::endl;
                }
                std::cout << std::endl;
            }
        }
        else if (command == "parse") {
            Methods m;
            std::fstream fin(filename);
            std::string fileLine;
            while (std::getline(fin, fileLine)) {
                std::vector<Token> tokens = m.tokenize(fileLine);
                if (tokens.empty()) continue;
                Node root = m.parse(tokens);
                printNode(root);
            }
        }
        else if (command == "exec") {
            Methods m;
            std::fstream fin(filename);
            std::string fileLine;
            std::map<std::string, int> vars;
            while (std::getline(fin, fileLine)) {
                std::vector<Token> tokens = m.tokenize(fileLine);
                if (tokens.empty()) continue;
                Node root = m.parse(tokens);
                m.eval(root, vars);
            }
        }

    } while (line != "exit");

    return 0;
}