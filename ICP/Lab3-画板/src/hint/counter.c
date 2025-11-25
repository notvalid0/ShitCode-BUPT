#include "counter.h"

bool timeCounter(){
    static int showTime = 0;
    showTime++;
    if (showTime >= 120) {
        showTime = 0;
        return false;
    }
    return true;
}