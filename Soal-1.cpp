#include <iostream>
using namespace std;

/*
Penjelasan Kompleksitas FindMin:

Algoritma ini mencari nilai terkecil dengan cara membandingkan
setiap elemen array satu per satu mulai dari indeks ke-1
sampai ke-(n-1).

Karena perulangan selalu berjalan sebanyak (n-1) kali,
baik saat kondisi terbaik (tidak pernah masuk if)
maupun kondisi terburuk (selalu masuk if),
maka jumlah langkahnya tetap sebanding dengan n.

Tmin(n)  = c1 + (c2 + c3)(n-1)
Tmax(n)  = c1 + (c2 + c3 + c4)(n-1)

Kesimpulan:
Best Case  = O(n)
Worst Case = O(n)

Artinya waktu eksekusi bertambah secara linear
sesuai jumlah data.
*/

int FindMin(int A[], int n, int &indexMin) {
    int min = A[0];
    indexMin = 0;

    for(int i = 1; i < n; i++) {
        if(A[i] < min) {
            min = A[i];
            indexMin = i;
        }
    }

    return min;
}

int main() {
    int A[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int indexMin;

    int minimum = FindMin(A, 8, indexMin);

    cout << "Nilai minimum : " << minimum << endl;
    cout << "Index minimum : " << indexMin << endl;

    return 0;
}