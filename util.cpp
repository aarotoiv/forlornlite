#include "util.hpp"

//limit the value to 1, -1, 0
//there may be better ways to do this 
int plusMinusOne(int val) {
	return val > 0 ? 1 : val < 0 ? -1 : 0;
}