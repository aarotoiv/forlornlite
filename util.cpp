#include "util.hpp"

//limit the value to 1, -1, 0
//there may be better ways to do this 
int plusMinusOne(int val){
    if(val > 0)
        return 1;
    else if(val < 0)
        return -1;
    else if(val == 0)
        return 0;
}