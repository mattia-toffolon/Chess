#include <iostream>
#include <vector>
#include <algorithm>

struct e {
    int a;
};


int main(){
    // test
    std::vector<e*> vec;
    vec.push_back(new e());
    vec.push_back(new e());
    e* to_find = new e();
    vec.push_back(to_find);

    for(e* elem: vec)
        std::cout << elem << std::endl;

    std::cout << std::endl;
    if(std::replace(vec.begin(), vec.end(),to_find, (e*)nullptr) == vec.end())
        std::cout << "yes";

    for(e* elem: vec)
        std::cout << elem << std::endl;


}