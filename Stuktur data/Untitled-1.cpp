#include <iostream>
using namespace std;

#define MAX_SIZE 5

struct Queue {
    int elements[MAX_SIZE];
    int head = -1;
    int tail = -1;
   
    bool isEmpty() {
        if (head == -1 && tail == -1) {
            cout << "Kosong" << endl;
            return true;
        }
        return false;
    }

    bool isFull() {
        return (tail == MAX_SIZE - 1);
    }

    void enqueue(int x) {
         if (isFull()) {
            cout << "Queue penuh, tidak dapat menambahkan elemen." << endl;
            return;
        } else {
            tail++;
        }
        elements[tail] = x;
        cout << x << " berhasil ditambahkan ke dalam queue." << endl;
    }

    void dequeue() {
        if (isEmpty()) {
            return;
        }
        cout << elements[head++] << " berhasil dihapus dari queue." << endl;
        if (head > tail) {
            head = tail = -1;
        }
    }

    void display() {
        if (isEmpty()) {
            return;
        }
        cout << "Tampilan: " << endl;
        for (int i = head; i <= tail; i++) {
            cout << elements[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    char choice;
    int element;
    Queue q;

    do {
        cout << "Pilih operasi stack:" << endl;
        cout << "1. Enqueue" << endl;
        cout << "2. Dequeue" << endl;
        cout << "3. Tampilkan" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilihan Anda: ";
        cin >> choice;

        switch (choice) {
            case '1':
                cout << "Masukkan elemen yang ingin ditambahkan: ";
                cin >> element;
                q.enqueue(element);
                break;
            case '2':
                q.dequeue();
                break;
            case '3':
                q.display();
                break;
            case '4':
                cout << "Terima kasih, keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (choice != '4');

    return 0;
}
