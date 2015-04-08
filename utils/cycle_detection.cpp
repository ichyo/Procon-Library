#include "../common/common.h"
// Brent's algorithms
// Time: O(index + length) Space: O(1)
template<typename T, typename Func>
pair<int, int> cycle_detection(Func next, T init) {
    // find the length of the cycle
    int power = 1;
    int len = 1;
    T tor = init;
    T hare = next(init);
    while(tor != hare) {
        if(power == len) {
            tor = hare;
            power *= 2;
            len = 0;
        }
        hare = next(hare);
        len ++;
    }

    // find the index of the first repetition
    int index = 0;
    tor = hare = init;
    REP(i, len) hare = next(hare);
    while(tor != hare) {
        tor = next(tor);
        hare = next(hare);
        index++;
    }
    return make_pair(index, len);
}

