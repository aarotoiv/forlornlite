#include "util.hpp"

int plusMinusOne(int val){
    if(val > 0)
        return 1;
    else if(val < 0)
        return -1;
    else if(val == 0)
        return 0;
}