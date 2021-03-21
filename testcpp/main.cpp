#include <iostream>
#include <vector>
#include <map>
#include <string>

int main() {
    std::vector<std::string> msg{"hello", "World", "I", "am", "a", "VECTOR"};

    for (auto &&m : msg)
    {
        std::cout << m << std::endl;
    }
    return 0;
}
