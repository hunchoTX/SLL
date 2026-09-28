#include <iostream>
using namespace std;

struct ElmList {
    int info;
    ElmList* next;
};

struct List {
    ElmList* first;
};

// prototype
void createList(List &L);
ElmList* createNewElement(int value);
void insertFirst(List &L, ElmList* P);
void insertLast(List &L, ElmList* P);
void insertAfter(ElmList* Prec, ElmList* P);
void printList(List L);
ElmList* searchElement(List L, int key);
void deleteFirst(List &L);

// bikin list kosong
void createList(List &L) {
    L.first = nullptr;
}

// bikin node baru pakai new
ElmList* createNewElement(int value) {
    ElmList* P = new ElmList;
    P->info = value;
    P->next = nullptr;
    return P;
}

// tambah di depan
void insertFirst(List &L, ElmList* P) {
    P->next = L.first;  // sambung P ke first yang lama
    L.first = P;        // P jadi first yang baru
}

// tambah di belakang
void insertLast(List &L, ElmList* P) {
    if (L.first == nullptr) {
        // kalau list kosong, P langsung jadi first
        L.first = P;
    } else {
        ElmList* Q = L.first;
        // geser Q sampai node terakhir
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

// tambah setelah Prec
void insertAfter(ElmList* Prec, ElmList* P) {
    P->next = Prec->next;
    Prec->next = P;
}

// cetak semua isi list
void printList(List L) {
    ElmList* P = L.first;
    while (P != nullptr) {
        cout << P->info << " ";
        P = P->next;
    }
    cout << endl;
}

// cari data, kalau ketemu return alamat nodenya, kalau tidak return nullptr
ElmList* searchElement(List L, int key) {
    ElmList* P = L.first;
    while (P != nullptr) {
        if (P->info == key) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

// hapus node pertama
void deleteFirst(List &L) {
    if (L.first == nullptr) {
        cout << "List is empty" << endl;
        return;
    }
    ElmList* P = L.first;
    L.first = P->next;  // first pindah ke node kedua
    P->next = nullptr;  // putuskan P dari list
    delete P;           // hapus dari memori
}

int main() {
    List L;
    createList(L);

    insertLast(L, createNewElement(10));
    insertLast(L, createNewElement(20));
    insertLast(L, createNewElement(30));
    cout << "print -> ";
    printList(L);   // 10 20 30

    insertFirst(L, createNewElement(5));
    cout << "print -> ";
    printList(L);   // 5 10 20 30

    if (searchElement(L, 20) != nullptr) {
        cout << "search 20 -> FOUND" << endl;
    } else {
        cout << "search 20 -> NOT FOUND" << endl;
    }

    deleteFirst(L);
    cout << "print -> ";
    printList(L);   // 10 20 30

    // hapus sisa node supaya tidak memory leak
    while (L.first != nullptr) {
        deleteFirst(L);
    }

    return 0;
}