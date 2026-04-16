#include <iostream>
using namespace std;

#define MAX 100

struct Tiket {
    string namaPenumpang;
    string asal;
    string tujuan;
};

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
    *(q->data + q->rear) = t;   // pointer aritmatika
    cout << "Penumpang masuk antrian!\n";
}

struct Hist {
    string aksi;
    Hist* next;
};

Hist *topS = NULL;

bool isEmptyS() {
    return topS == NULL;
}

void pushHistory(string aksi){
    Hist* baru = new Hist;
    baru->aksi = aksi;
    baru->next = topS;
    topS = baru;
}

void popHistory(){
    if(isEmptyS()){
        cout<<"Riwayat kosong\n";
        return;
    }
    Hist *hapus = topS;
    cout<<"Undo aksi: "<<hapus->aksi<<endl;
    topS = topS->next;
    delete hapus;
}

void peekHistory(){
    if(isEmptyS()){
        cout<<"Riwayat kosong\n";
        return;
    }
    cout<<"Aksi terakhir: "<<topS->aksi<<endl;
}

void tampilHistory(){
    if(isEmptyS()){
        cout<<"Belum ada riwayat\n";
        return;
    }
    Hist* bantu = topS;
    cout<<"\n--- Riwayat Aksi ---\n";
    while(bantu != NULL){
        cout<<bantu->aksi<<endl;
        bantu = bantu->next;
    }
}

void dequeue(Queue *q, Tiket *t) {
    if (isEmptyQ(q)) {
        cout << "Antrian kosong (Underflow)\n";
        return;
    }

    *t = *(q->data + q->front);

    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;

    cout << "Tiket diproses: " << t->namaPenumpang << endl;

    pushHistory("Proses tiket: " + t->namaPenumpang);
}

void tampilQueue(Queue *q) {
    if (isEmptyQ(q)) {
        cout << "Antrian kosong\n";
        return;
    }

    cout<<"\n--- Daftar Antrian ---\n";
    for (int i = q->front; i <= q->rear; i++) {
        cout << (q->data + i)->namaPenumpang
             << " (" << (q->data + i)->asal
             << " -> " << (q->data + i)->tujuan << ")\n";
    }
}

int main() {
    Queue q;
    Tiket t;
    initQueue(&q);

    int pilih;
    do {
        cout<<"\n===== MENU LOKET TIKET =====\n";

        cout<<"1. Tambah Antrian\n";
        cout<<"2. Proses Tiket\n";
        cout<<"3. Tampil Antrian\n";
        cout<<"4. Tampil Riwayat\n";
        cout<<"5. Melihat Riwayat\n";
        cout<<"6. Menghapus Riwayat\n";
        cout<<"0. Keluar\n";
        cout<<"Pilih: "; cin>>pilih;

        switch(pilih){
            case 1:
                cout<<"Nama: "; cin>>t.namaPenumpang;
                cout<<"Asal: "; cin>>t.asal;
                cout<<"Tujuan: "; cin>>t.tujuan;
                enqueue(&q,t);
                pushHistory("Tambah antrian: " + t.namaPenumpang);
                break;

            case 2:
                dequeue(&q,&t);
                break;

            case 3:
                tampilQueue(&q);
                break;

            case 4:
                tampilHistory();
                break;

            case 5:
                peekHistory();
                break;

            case 6:
                popHistory();
                break;
        }

    } while(pilih != 0);
}