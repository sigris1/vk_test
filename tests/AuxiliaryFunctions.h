//
// Created by sigris on 11.06.2025.
//

#pragma once
#include "string"
#include "vector"
#include "iostream"

int intFoo();

int multiply(int a, int b, int c);

std::string myreverse(std::string a);

std::vector<int> mutableVector(std::vector<int> a);

std::pair<int, int> mutablePair(int a, int b);

std::tuple<int, std::string, std::vector<int>> mutableTuple(const std::tuple<int, std::string, std::vector<int>>& mew);

void multiplyVector(std::vector<int>& mew);

class tested{
public:
    tested(int a, int b)
        :a_(a)
        ,b_(b)
        {}

    friend std::ostream& operator<<(std::ostream& os, const tested& t) {
        os << "tested(" << t.a_ << ", " << t.b_ << ")";
        return os;
    }

private:
    int a_;
    int b_;
};


tested getTested(int a, int b);