#ifndef Util_h
#define Util_h

int plusMinusOne(int val) {
    if(val > 0)
        return 1;
    else if(val < 0)
        return -1;
    else if(val == 0)
        return 0;
}

#endif