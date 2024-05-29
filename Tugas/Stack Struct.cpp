#include <iostream>
using namespace std;

#define MAX_SIZE 100

struct Stack {
    int elements[MAX_SIZE];
    int top = -1;

    bool isEmpty() {
        return (top == -1);
    }

    bool isFull() {
        return (top == MAX_SIZE - 1);
    }

    void push(int x) {
        if (isFull()) {
            cout << "Stack penuh, tidak dapat menambahkan elemen." << endl;
            return;
        }
        elements[++top] = x;
        cout << x << " berhasil ditambahkan ke dalam stack." << endl;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack kosong, tidak dapat menghapus elemen." << endl;
            return;
        }
        cout << elements[top--] << " berhasil dihapus dari stack." << endl;
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack kosong." << endl;
            return;
        }
        cout << "Tampilan: " << endl;
        for (int i = top; i >= 0; i--) {
            cout << elements[i] << endl;
        }
        cout << endl;
    }
};

int main() {
    char choice;
    int element;
    Stack st;

    do {
        cout << "Pilih operasi stack:" << endl;
        cout << "1. Push" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Tampilkan" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilihan Anda: ";
        cin >> choice;

        switch (choice) {
            case '1':
                cout << "Masukkan elemen yang ingin ditambahkan: ";
                cin >> element;
                st.push(element);
                break;
            case '2':
                st.pop();
                break;
            case '3':
                st.display();
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
