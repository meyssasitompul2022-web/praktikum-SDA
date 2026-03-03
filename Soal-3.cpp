#include <iostream>
using namespace std;

void reverseArray(int* arr, int n) {
    int* awal = arr;          
    int* akhir = arr + n - 1;  
    while (awal < akhir) {
        int temp = *awal;
        *awal = *akhir;
        *akhir = temp;

        awal++;
        akhir--;
    }
}

int main() {

    int arr[7] = {2, 3, 5, 7, 11, 13, 17};

    cout << "=== Sebelum Dibalik ===" << endl;
    
    int* ptr = arr;
    for(int i = 0; i < 7; i++) {
        cout << "Nilai: " << *(ptr + i)
             << " | Alamat: " << (ptr + i) << endl;
    }

    reverseArray(arr, 7);

    cout << "\n=== Sesudah Dibalik ===" << endl;

    for(int i = 0; i < 7; i++) {
        cout << "Nilai: " << *(ptr + i)
             << " | Alamat: " << (ptr + i) << endl;
    }

    return 0;
}
