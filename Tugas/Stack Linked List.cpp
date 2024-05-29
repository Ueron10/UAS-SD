#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

struct Stack {
    Node* top;

    Stack() {
        top = nullptr;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void push(int x) {
        Node* newNode = new Node();
        newNode->data = x;
        newNode->next = top;
        top = newNode;
        cout << x << " berhasil ditambahkan ke dalam stack." << endl;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack kosong, tidak dapat menghapus elemen." << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        cout << temp->data << " berhasil dihapus dari stack." << endl;
        delete temp;
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack kosong." << endl;
            return;
        }
        cout << "Data dalam stack: " << endl;
        Node* temp = top;
        while (temp != nullptr) {
            cout << temp->data << endl;
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    char choice;
    int element;
    Stack s;

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
                s.push(element);
                break;
            case '2':
                s.pop();
                break;
            case '3':
                s.display();
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
