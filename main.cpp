#include "set.h"
#include <iostream>
using namespace Chaos;
void pr_int(int& i){
    i++;
    printf("%d\n",i);
}
#define set_contains_debug(t, d) if(t.Contains(d)){printf("set contains:%d\n",d);}else{printf("set doesnt contain:%d\n",d);}
int main(void){
    Set<int> set = {128};
    return 0;
}