#ifndef ADS_TIMSORT_H
#define ADS_TIMSORT_H

#include "../practice01/structures/dl_list.h"

class TimSortUtils {
private:
    static void insertionSort(List&);
    static int getMinRun(int);

    friend void timSort(List &list);
};


void TimSortUtils::insertionSort(List &list) {
    for (int i = 1; i < list.getSize(); ++i)
        for (int j = i; j > 0 && list[j - 1]->value > list[j]->value; --j)
            list.swap(j, j-1);
}


int TimSortUtils::getMinRun(int n) {
    // Return n if n < 64, 65 if there's at least
    // one bit less than 6 & equal to 1, else 64
    int mask = 0;
    while (n >= 64) {
        mask |= n & 1;
        n >>= 1;
    }
    return n + mask;
}


/// Sort list via tim sort
void timSort(List &list) {

}

#endif //ADS_TIMSORT_H