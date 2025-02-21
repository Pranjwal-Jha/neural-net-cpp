#include <vector>
#include <iostream>
using namespace std;
int main(){
    std::vector<vector<int>> mat;
    mat.resize(9,vector<int>(1,0));
    for(auto& c:mat){
        for(auto& c2:c){
            std::cout << c2 << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return 0;
}
