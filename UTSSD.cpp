#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_HARI = 20;
const int MAX_MATKUL = 50;
const int MAX_WAKTU = 20;

class Node {
public:
    char hari[MAX_HARI];
    char matkul[MAX_MATKUL];
    char waktu[MAX_WAKTU];
    Node* next;

    Node(const char* h, const char* m, const char* w) : next(nullptr) {
        int i = 0;
        while (h[i] != '\0' && i < MAX_HARI - 1) {
            hari[i] = h[i];
            ++i;
        }
        hari[i] = '\0';

        i = 0;
        while (m[i] != '\0' && i < MAX_MATKUL - 1) {
            matkul[i] = m[i];
            ++i;
        }
        matkul[i] = '\0';

        i = 0;
        while (w[i] != '\0' && i < MAX_WAKTU - 1) {
            waktu[i] = w[i];
            ++i;
        }
        waktu[i] = '\0';
    }
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void tambahJadwal(const char* hari, const char* matkul, const char* waktu) {
        Node* newNode = new Node(hari, matkul, waktu);
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
            Node* temp = head;
            cout << "Jadwal Keseluruhan:" << endl;
            cout << "+-------------------------+-------------------------+-------------------------+" << endl;
            cout << "|          Hari           |         Waktu           |      Mata Kuliah        |" << endl;
            cout << "+-------------------------+-------------------------+-------------------------+" << endl;
            while (temp != nullptr) {
                cout << "| " << setw(24) << left << temp->hari << "| "
                     << setw(24) << left << temp->waktu << "| "
                     << setw(24) << left << temp->matkul << "|" << endl;
                temp = temp->next;
            }
            cout << "+-------------------------+-------------------------+-------------------------+" << endl;
        }
    }

    void cariHari(const char* targetHari, Node* curr) {
        if (curr == nullptr) {
            cout << "Tidak ada jadwal pada hari tersebut." << endl;
            return;
        }

        if (hariMatch(curr->hari, targetHari)) {
            cout << "Hasil Pencarian Jadwal pada Hari " << targetHari << ":" << endl;
            cout << "| " << curr->hari << " | " << curr->waktu << " | " << curr->matkul << " |" << endl;
        }

        cariHari(targetHari, curr->next);
    }

    bool hariMatch(const char* hari1, const char* hari2) {
        int i = 0;
        while (hari1[i] != '\0' && hari2[i] != '\0') {
            if (hari1[i] != hari2[i]) {
                return false;
            }
            ++i;
        }
        return hari1[i] == '\0' && hari2[i] == '\0';
    }

    void cariMatkul(const char* targetMatkul, Node* curr) {
        if (curr == nullptr) {
            cout << "Tidak ditemukan jadwal untuk mata kuliah tersebut." << endl;
            return;
        }

        if (matkulMatch(curr->matkul, targetMatkul)) {
            cout << "Hasil Pencarian Jadwal untuk Mata Kuliah \"" << targetMatkul << "\":" << endl;
            cout << "| " << curr->hari << " | " << curr->waktu << " | " << curr->matkul << " |" << endl;
        }

        cariMatkul(targetMatkul, curr->next);
    }

    bool matkulMatch(const char* matkul1, const char* matkul2) {
        int i = 0;
        while (matkul1[i] != '\0' && matkul2[i] != '\0') {
            if (matkul1[i] != matkul2[i]) {
                return false;
            }
            ++i;
        }
        return matkul1[i] == '\0' && matkul2[i] == '\0';
    }

    void cariHariWrapper(const char* targetHari) {
        cariHari(targetHari, head);
    }

    void cariMatkulWrapper(const char* targetMatkul) {
        cariMatkul(targetMatkul, head);
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
    return  (hari[0] == 'S' && hari[1] == 'e' || hari[2] == 'n') ||
            (hari[0] == 'S' && hari[1] == 'e' || hari[2] == 'l') ||
            (hari[0] == 'S' && hari[1] == 'a' || hari[2] == 'b') ||  
            (hari[0] == 'R' && hari[1] == 'a') ||                      
            (hari[0] == 'K' && hari[1] == 'a') ||                      
            (hari[0] == 'J' && hari[1] == 'u') ||                      
            (hari[0] == 'M' && hari[1] == 'i');                       
}


int main() {
    LinkedList jadwalList;
    char hari[MAX_HARI];
    char waktu[MAX_WAKTU];
    char matkul[MAX_MATKUL];
    int pilihan;

    do {
        cout << "\nMenu\n";
        cout << "1. Tambahkan Jadwal\n";
        cout << "2. Tampilkan Jadwal";
        cout << "3. Cari\n";
        cout << "4. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                system("cls");
                cout << "Silakan Masukkan Hari (Senin - Minggu): ";
                cin >> hari;

                if (!isValidHari(hari)) {
                    cout << "Hari tidak valid! Masukkan kembali." << endl;
                    break;
                }

                cout << "Silakan Masukkan Mata Kuliah: ";
                cin.ignore(); 
                cin.getline(matkul, MAX_MATKUL);
                cout << "Silakan Masukkan Waktu: ";
                cin >> waktu;
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
                        cin >> hari;
                        jadwalList.cariHariWrapper(hari);
                        break;
                    case 'b':
                        system("cls");
                        cout << "Silakan Masukkan Matkul: ";
                        cin.ignore();
                        cin.getline(matkul, MAX_MATKUL);
                        jadwalList.cariMatkulWrapper(matkul);
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