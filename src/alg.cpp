// Copyright 2021 NNTU-CS
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <utility>
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error: " << filename << std::endl;
        return;
    }

    std::string word = "";
    while (true) {
        int ch = file.get();

        if (ch == EOF) {
            if (!word.empty()) {
                tree.insert(word);
            }
            break;
        }

        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            word += std::tolower(ch);
        }
        else {
            if (!word.empty()) {
                tree.insert(word);
                word = "";
            }
        }
    }
    file.close();
}

bool compareFreq(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    if (a.second != b.second) {
        return a.second > b.second;
    }
    return a.first < b.first;
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> elements;
    tree.getAll(elements);

    std::sort(elements.begin(), elements.end(), compareFreq);

    std::ofstream outFile("result/freq.txt");

    for (const auto& el : elements) {
        std::cout << el.first << " " << el.second << std::endl;
        if (outFile.is_open()) {
            outFile << el.first << " " << el.second << "\n";
        }
    }

    if (outFile.is_open()) {
        outFile.close();
    }
}
