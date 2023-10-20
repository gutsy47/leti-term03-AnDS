#ifndef ADS_SORTS_H
#define ADS_SORTS_H


#include "../practice01/structures/dl_list.h"


void quickSortUtil(List &list, int first, int last) {
    int mid = list[(first + last) / 2]->value;
    int tmpFirst = first, tmpLast = last;
    while (first < last) {
        while (list[first]->value < mid) first++;
        while (list[last]->value > mid) last--;
        if (first <= last) {
            list.swap(first, last);
            first++;
            last--;
        }
    }
    if (tmpFirst < last) quickSortUtil(list, tmpFirst, last);
    if (first < tmpLast) quickSortUtil(list, first, tmpLast);
}


void quickSort(List &list) {
    quickSortUtil(list, 0, int(list.getSize()) - 1);
}


//void quickSort(List &list) {
//    for (int i = int(list.getSize()) - 1; i > 0; --i) {
//        for (int j = 0; j < i; ++j) {
//            if (list[j]->value > list[j + 1]->value)
//                list.swap(j, j+1);
//        }
//    }
//}



void timSort(List &list) {

}


// void quickSort(int *arr, int first, int last) {
//    int mid = arr[(first + last) / 2];
//    int tmpLast = last, tmpFirst = first;
//    while (first < last) {
//        while (arr[first] < mid) first++;
//        while (arr[last] > mid) last--;
//        if (first <= last) {
//            std::swap(arr[first], arr[last]);
//            first++;
//            last--;
//        }
//    }
//    if (tmpFirst < last) quickSort(arr, tmpFirst, last);
//    if (first < tmpLast) quickSort(arr, first, tmpLast);
//}

#endif //ADS_SORTS_H
