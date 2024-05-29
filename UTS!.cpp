#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_HARI = 7;
const int MAX_MATKUL = 50;
const int MAX_WAKTU = 20;

class Node {
public:
    char hari[MAX_HARI][3];
    char matkul[MAX_MATKUL][3][MAX_MATKUL];
    char waktu[MAX_HARI][3][MAX_WAKTU];
    Node* next;

    Node(const char h[][3], const char m[][3][MAX_MATKUL], const char w[][3][MAX_WAKTU]) : next(nullptr) {
        for (int i = 0; i < MAX_HARI; ++i) {
            for (int j = 0; j < 3; ++j) {
                hari[i][j] = h[i][j];
            }
        }

        for (int i = 0; i < MAX_MATKUL; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < MAX_MATKUL; ++k) {
                    matkul[i][j][k] = m[i][j][k];
                }
            }
        }

        for (int i = 0; i < MAX_HARI; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < MAX_WAKTU; ++k) {
                    waktu[i][j][k] = w[i][j][k];
                }
            }
        }
    }
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void tambahJadwal(const char h[][3], const char m[][3][MAX_MATKUL], const char w[][3][MAX_WAKTU]) {
        Node* newNode = new Node(h, m, w);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void tampilkanJadwal() {
        if (head == nullptr) {
            cout << "Tidak ada jadwal yang tersimpan." << endl;
        } else {
            // Implementasi tampilan jadwal
            Node* temp = head;
            while (temp != nullptr) {
                for (int i = 0; i < MAX_HARI; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if (temp->hari[i][j] == '\0') break;
                        cout << temp->hari[i][j];
                    }
                    cout << " ";
                }
                cout << "| ";
                for (int i = 0; i < MAX_HARI; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        for (int k = 0; k < MAX_MATKUL; ++k) {
                            if (temp->matkul[i][j][k] == '\0') break;
                            cout << temp->matkul[i][j][k];
                        }
                        if (temp->matkul[i][j][0] == '\0') break;
                        cout << " ";
                    }
                    if (temp->matkul[i][0][0] == '\0') break;
                    cout << "| ";
                }
                cout << "| ";
                for (int i = 0; i < MAX_HARI; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        for (int k = 0; k < MAX_WAKTU; ++k) {
                            if (temp->waktu[i][j][k] == '\0') break;
                            cout << temp->waktu[i][j][k];
                        }
                        if (temp->waktu[i][j][0] == '\0') break;
                        cout << " ";
                    }
                    if (temp->waktu[i][0][0] == '\0') break;
                    cout << "| ";
                }
                cout << endl;
                temp = temp->next;
            }
        }
    }

    void cariHari(const char* targetHari) {
        // Implementasi pencarian jadwal berdasarkan hari
    }

    void cariMatkul(const char* targetMatkul) {
        // Implementasi pencarian jadwal berdasarkan mata kuliah
    }

    void hapusSemua() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    ~LinkedList() {
        hapusSemua();
    }
};

bool isValidHari(const char* hari) {
    // Implementasi validasi hari
    return  (hari[0] == 'S' && hari[1] == 'e' && hari[2] == 'n') ||
            (hari[0] == 'S' && hari[1] == 'e' && hari[2] == 'l') ||
            (hari[0] == 'S' && hari[1] == 'a' && hari[2] == 'b') ||  
            (hari[0] == 'R' && hari[1] == 'a') ||                      
            (hari[0] == 'K' && hari[1] == 'a') ||                      
            (hari[0] == 'J' && hari[1] == 'u') ||                      
            (hari[0] == 'M' && hari[1] == 'i');                       
}

int main() {
    LinkedList jadwalList;
    char hari[MAX_HARI][3];
    char waktu[MAX_HARI][3][MAX_WAKTU];
    char matkul[MAX_MATKUL][3][MAX_MATKUL];
    int pilihan;

    do {
        cout << "\nMenu\n";
        cout << "1. Tambahkan Jadwal\n";
        cout << "2. Tampilkan Jadwal\n";
        cout << "3. Cari\n";
        cout << "4. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                system("cls");
                // Input jadwal baru
                cout << "Silakan Masukkan Hari (Senin - Minggu): ";
                for (int i = 0; i < MAX_HARI; ++i) {
                    cin >> hari[i];
                }
                cout << "Silakan Masukkan Mata Kuliah: ";
                for (int i = 0; i < MAX_MATKUL; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        cin >> matkul[i][j];
                    }
                }
                cout << "Silakan Masukkan Waktu: ";
                for (int i = 0; i < MAX_HARI; ++i) {
                    for (int j = 0; i < 3; ++j) {
                        cin >> waktu[i][j];
                    }
                }
                jadwalList.tambahJadwal(hari, matkul, waktu);
                system("cls");
                cout << "Berhasil\n";
                break;
            case 2:
                system("cls");
                jadwalList.tampilkanJadwal();
                break;
            case 3:
                system("cls");
                char pilihcari;
                cout << "\n Cari:\n";
                cout << "a. Hari\n";
                cout << "b. Mata Kuliah\n";
                cout << "Pilih(a/b): ";
                cin >> pilihcari;
                switch (pilihcari) {
                    case 'a':
                        system("cls");  
                        cout << "Silakan Masukkan Hari (Senin - Minggu): ";
                        // Input hari yang akan dicari
                        break;
                    case 'b':
                        system("cls");
                        cout << "Silakan Masukkan Matkul: ";
                        // Input mata kuliah yang akan dicari
                        break;
                    default:
                        system("cls");
                        cout << "Pilihan tidak valid!" << endl;
                }
                break;
            case 4:
                system("cls"); 
                cout << "Terima kasih, sampai jumpa!" << endl;
                break;
            default:
                system("cls");
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 4);

    return 0;
}

