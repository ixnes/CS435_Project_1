#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int *getRandomArray(int n) {
    srand(time(NULL));
    int *ret = (int *) malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        //Generate random numbers until we find one that isn't already in the array
        int r;
        bool duplicate = false;
        do {
            r = rand();
            for (int j = 0; j < i; j++) {
                if (r == ret[j]) {
                    duplicate = true;
                    break;
                }
            }
        } while (duplicate);
        ret[i] = r;
    }
    return ret;
}

int *getSortedArray(int n) {
    int *ret = (int *) malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        ret[i] = n-i;
    }
    return ret;
}

int main() {
    int *arr = getRandomArray(10);
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << endl;
    }

    cout << endl << endl;

    arr = getSortedArray(10);
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << endl;
    }
}