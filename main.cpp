#include "set.h"
#include <iostream>
using namespace Chaos;
int main(void){
    Set<int> set = {128};
    for(int i =0; i<64;i++){
        set.Add(i);
    }
    set.debug_print();
    return 0;
}