#include <iostream>
#include <cmath>
using namespace std;

struct Kereta {
    int id;
    string nama, asal, tujuan;
    int harga;
};

int jumlah = 0;

void tukar(Kereta *a, Kereta *b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void tampilData(Kereta *data) {
    if (jumlah == 0) {
        cout << "Belum ada data!\n";
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        cout << "\nData ke-" << i+1 << endl;
        cout << "ID     : " << (data+i)->id << endl;
        cout << "Nama   : " << (data+i)->nama << endl;
        cout << "Asal   : " << (data+i)->asal << endl;
        cout << "Tujuan : " << (data+i)->tujuan << endl;
        cout << "Harga  : " << (data+i)->harga << endl;
    }
}

void tambahData(Kereta *data) {
    cin.ignore();

    cout << "\n=== Input Data Kereta ===\n";
    cout << "ID     : "; cin >> (data+jumlah)->id;
    cin.ignore();

    cout << "Nama   : "; getline(cin, (data+jumlah)->nama);
    cout << "Asal   : "; getline(cin, (data+jumlah)->asal);
    cout << "Tujuan : "; getline(cin, (data+jumlah)->tujuan);

    cout << "Harga  : "; cin >> (data+jumlah)->harga;

    jumlah++;
}

void cariRute(Kereta *data) {
    string asal, tujuan;
    cin.ignore();

    cout << "Masukkan asal   : "; getline(cin, asal);
    cout << "Masukkan tujuan : "; getline(cin, tujuan);

    bool found = false;

    for (int i = 0; i < jumlah; i++) {
        if ((data+i)->asal == asal && (data+i)->tujuan == tujuan) {
            cout << "\nDitemukan: " << (data+i)->nama << endl;
            found = true;
        }
    }

    if (!found)
        cout << "Tidak ditemukan!\n";
}

void cariID(Kereta *data) {
    int key;
    cout << "Masukkan ID yang dicari: ";
    cin >> key;

    int step = sqrt(jumlah);
    int prev = 0;

    while ((data + min(step, jumlah) - 1)->id < key) {
        cout << "Cek index ke-" << min(step, jumlah)-1 << endl;
        prev = step;
        step += sqrt(jumlah);

        if (prev >= jumlah) {
            cout << "Tidak ditemukan\n";
            return;
        }
    }

    for (int i = prev; i < min(step, jumlah); i++) {
        cout << "Linear cek index ke-" << i << endl;

        if ((data+i)->id == key) {
            cout << "Ditemukan: " << (data+i)->nama << endl;
            return;
        }
    }

    cout << "Tidak ditemukan\n";
}

void merge(Kereta *data, int l, int m, int r) {
    Kereta temp[100];
    int i = l, j = m+1, k = 0;

    while (i <= m && j <= r) {
        if ((data+i)->nama < (data+j)->nama)
            temp[k++] = *(data+i++);
        else
            temp[k++] = *(data+j++);
    }

    while (i <= m) temp[k++] = *(data+i++);
    while (j <= r) temp[k++] = *(data+j++);

    for (int x = 0; x < k; x++)
        *(data + l + x) = temp[x];
}

void mergeSort(Kereta *data, int l, int r) {
    if (l < r) {
        int mid = (l + r) / 2;
        mergeSort(data, l, mid);
        mergeSort(data, mid+1, r);
        merge(data, l, mid, r);
    }
}

void sortHarga(Kereta *data) {
    for (int i = 0; i < jumlah-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < jumlah; j++) {
            if ((data+j)->harga < (data+minIdx)->harga)
                minIdx = j;
        }
        tukar(data+i, data+minIdx);
    }
}

int main() {
    Kereta data[100];
    int pilih;

    do {
        cout << "\n=== MENU KERETA API ===\n";
        cout << "1. Tampilkan Data\n";
        cout << "2. Tambah Data\n";
        cout << "3. Cari Rute\n";
        cout << "4. Cari ID\n";
        cout << "5. Urutkan Nama\n";
        cout << "6. Urutkan Harga\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tampilData(data); break;
            case 2: tambahData(data); break;
            case 3: cariRute(data); break;
            case 4: cariID(data); break;
            case 5:
                mergeSort(data, 0, jumlah-1);
                cout << "Berhasil diurutkan berdasarkan nama\n";
                break;
            case 6:
                sortHarga(data);
                cout << "Berhasil diurutkan berdasarkan harga\n";
                break;
        }
    } while (pilih != 0);

    return 0;
}
