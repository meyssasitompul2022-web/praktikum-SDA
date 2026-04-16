#include <iostream>
#include <cmath>
using namespace std;

#define MAX 100

struct Kereta {
    int id;
    string nama, asal, tujuan;
    int harga;
};

struct Tiket {
    string namaPenumpang;
    string asal, tujuan;
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
        prev = step;
        step += sqrt(jumlah);

        if (prev >= jumlah) {
            cout << "Tidak ditemukan\n";
            return;
        }
    }

    for (int i = prev; i < min(step, jumlah); i++) {
        if ((data+i)->id == key) {
            cout << "Ditemukan: " << (data+i)->nama << endl;
            return;
        }
    }

    cout << "Tidak ditemukan\n";
}

void merge(Kereta *data, int l, int m, int r) {
    Kereta temp[MAX];
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

struct Queue {
    Tiket data[MAX];
    int front, rear;
};

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

bool isFullQ(Queue *q) {
    return q->rear == MAX - 1;
}

bool isEmptyQ(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, Tiket t) {
    if (isFullQ(q)) {
        cout << "Antrian penuh (Overflow)\n";
        return;
    }

    if (isEmptyQ(q))
        q->front = 0;

    q->rear++;
    *(q->data + q->rear) = t;
    cout << "Penumpang masuk antrian\n";
}

void dequeue(Queue *q, Tiket *t) {
    if (isEmptyQ(q)) {
        cout << "Antrian kosong (Underflow)\n";
        return;
    }

    *t = *(q->data + q->front);

    cout << "Diproses: " << t->namaPenumpang 
         << " (" << t->asal << " -> " << t->tujuan << ")\n";

    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
}

void tampilQueue(Queue *q) {
    if (isEmptyQ(q)) {
        cout << "Antrian kosong\n";
        return;
    }

    for (int i = q->front; i <= q->rear; i++) {
        cout << (q->data + i)->namaPenumpang
             << " (" << (q->data + i)->asal
             << " -> " << (q->data + i)->tujuan << ")\n";
    }
}

struct Stack {
    Tiket data[MAX];
    int top;
};

void initStack(Stack *s) {
    s->top = -1;
}

bool isFullS(Stack *s) {
    return s->top == MAX - 1;
}

bool isEmptyS(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, Tiket t) {
    if (isFullS(s)) {
        cout << "Stack penuh (Overflow)\n";
        return;
    }

    s->top++;
    *(s->data + s->top) = t;
}

void pop(Stack *s) {
    if (isEmptyS(s)) {
        cout << "Riwayat kosong (Underflow)\n";
        return;
    }

    cout << "Dihapus: " << (s->data + s->top)->namaPenumpang << endl;
    s->top--;
}

void tampilStack(Stack *s) {
    if (isEmptyS(s)) {
        cout << "Riwayat kosong\n";
        return;
    }

    for (int i = s->top; i >= 0; i--) {
        cout << (s->data + i)->namaPenumpang
             << " (" << (s->data + i)->asal
             << " -> " << (s->data + i)->tujuan << ")\n";
    }
}

void peek(Queue *q, Stack *s) {
    if (!isEmptyQ(q))
        cout << "Antrian depan: " << (q->data + q->front)->namaPenumpang << endl;
    else
        cout << "Antrian kosong\n";

    if (!isEmptyS(s))
        cout << "Transaksi terakhir: " << (s->data + s->top)->namaPenumpang << endl;
    else
        cout << "Riwayat kosong\n";
}

int main() {
    Kereta data[MAX];
    Queue q;
    Stack s;

    initQueue(&q);
    initStack(&s);

    int pilih;

    do {
        cout << "\n=== MENU KERETA API ===\n";
        cout << "1. Tampilkan Data\n";
        cout << "2. Tambah Data\n";
        cout << "3. Cari Rute\n";
        cout << "4. Cari ID\n";
        cout << "5. Urutkan Nama\n";
        cout << "6. Urutkan Harga\n";
        cout << "7. Tambah antrian Tiket\n";
        cout << "8. Proses Tiket\n";
        cout << "9. Tampil Antrian\n";
        cout << "10. Tampil Riwayat\n";
        cout << "11. Hapus Riwayat\n";
        cout << "12. Melihat data\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tampilData(data); break;
            case 2: tambahData(data); break;
            case 3: cariRute(data); break;
            case 4: cariID(data); break;
            case 5: mergeSort(data, 0, jumlah-1); break;
            case 6: sortHarga(data); break;

            case 7: {
                Tiket t;
                cin.ignore();
                cout << "Nama: "; getline(cin, t.namaPenumpang);
                cout << "Asal: "; getline(cin, t.asal);
                cout << "Tujuan: "; getline(cin, t.tujuan);
                enqueue(&q, t);
                break;
            }

            case 8: {
                Tiket t;
                dequeue(&q, &t);
                push(&s, t);
                break;
            }

            case 9: tampilQueue(&q); break;
            case 10: tampilStack(&s); break;
            case 11: pop(&s); break;
            case 12: peek(&q, &s); break;
        }

    } while (pilih != 0);

    return 0;
}