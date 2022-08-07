#include <iostream>
#include <algorithm>
#include <array>
#include <cmath>


template <typename T, size_t S>
void _insertsort(std::array<T, S> &arr, const size_t &l, const size_t &r) {
    for (size_t i = l + 1; i < r; i++) {
        T memory = arr[i];
        size_t j = i - 1;
        for (;(j >= l && j != SIZE_MAX) && arr[j] > memory; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = memory;
    }
}

template <typename T, size_t S>
void _heapsort(std::array<T, S> &arr, const size_t &l, const size_t &r) {
    size_t n = r - l;
    std::make_heap(arr.begin() + l, arr.begin() + r);
    std::sort_heap(arr.begin() + l, arr.begin() + r);
}

const size_t SIMPLIFICATION_CONSTANT = 64;

template <typename T, size_t S>
size_t medianex(const size_t &l, const size_t &r, const std::array<T, S> &arr) {
    size_t ai = l;
    T a = arr[ai];

    size_t ci = r - 1;
    T c = arr[ci];

    size_t bi = (l + r) / 2;
    T b = arr[bi];

    size_t mi = ai;

    if ((a <= b && b <= c) || (c <= b && b <= a)) {
        mi = bi;
    } else if (a <= c && c <= b || b <= c && c <= a) {
        mi = ci;
    }

    return mi;
}

template <typename T, size_t S>
void _introqsort(std::array<T, S> &arr, const size_t &levels_to_degradation, const size_t &l, const size_t &r) {

    if (r - l <= SIMPLIFICATION_CONSTANT) {
        _insertsort(arr, l, r);
        return;
    } 

    if (levels_to_degradation == 0) {
        _heapsort(arr, l, r);
        return;
    }

    size_t mi = medianex(l, r, arr);
    T m = arr[mi];

    size_t pbegin = l;
    size_t pend = 0;


    for (size_t pi = l; pi < r; pi++) {
        if (arr[pi] < m) {
            pbegin++;
        } else if (arr[pi] > m) {
            pend++;
        }
    }

    pend = r - pend;

    size_t li = l;
    size_t ei = pbegin;
    size_t gi = pend;

    while (li < pbegin || ei < pend || gi < r) {
        while (arr[li] < m && li < pbegin) {
            li++;
        }

        while (arr[ei] == m && ei < pend) {
            ei++;
        }

        while (arr[gi] > m && gi < r) {
            gi++;
        }

        if (li != pbegin && ei != pend && arr[li] == m) {
            std::swap(arr[li], arr[ei]);
            ei++;
        }

        if (ei != pend && gi != r && arr[gi] == m) {
            std::swap(arr[ei], arr[gi]);
            ei++;
        }

        if (li != pbegin && gi != r && arr[gi] < arr[li]) {
            std::swap(arr[li], arr[gi]);
        }

    }

    _introqsort(arr, levels_to_degradation - 1, l, pbegin);
    _introqsort(arr, levels_to_degradation - 1, pend, r);

}

template <typename T, size_t S>
void introsort(std::array<T, S> &arr, size_t n = S) {
    size_t levels_to_degradation = log(n);
    _introqsort(arr, levels_to_degradation, 0, n);
}

void microtest() {
    std::array<int, 10> a{10, 5, 1, 2, 3, 4, 5, 1, 2, 3};
    introsort(a);


    for (const int &i : a) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}


bool _trandom() {
    static const size_t NNN = 3;
    std::array<int, NNN> arr;
    for (auto &i : arr) {
        i = rand();
    }

    introsort(arr);
    for (int i = 1; i < NNN; i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

void trandom() {
    if (_trandom()) {
        std::cout << "cool\n";
    } else {
        std::cout << "not cool\n";
    }
}

int main()
{
    srand(time(0));
    for (int i = 0; i < 70; i++) trandom();
}