//
// Created by sigris on 11.06.2025.
//

#include "AuxiliaryFunctions.h"


int intFoo(){
    return 1;
}

int multiply(int a, int b, int c){
    return a * b * c;
}

std::string myreverse(std::string a){
    std::reverse(a.begin(), a.end());
    return a;
}

std::vector<int> mutableVector(std::vector<int> a){
    for (auto& i : a){
        i = i * i;
    }
    return a;
}

std::pair<int, int> mutablePair(int a, int b){
    return {a * a, b * b};
}

std::tuple<int, std::string, std::vector<int>> mutableTuple(const std::tuple<int, std::string, std::vector<int>>& mew){
    int first = std::get<0>(mew);
    std::string second = std::get<1>(mew);
    std::vector<int> third = std::get<2>(mew);

    first = first * first;

    std::reverse(second.begin(), second.end());

    third = mutableVector(third);

    return std::make_tuple(first, second, third);
}

void multiplyVector(std::vector<int>& mew){
    for (auto& i : mew){
        i = i * i;
    }
}

tested getTested(int a, int b){
    return {a, b};
}