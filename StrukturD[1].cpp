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
       
        int count = 0;
        Node* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        Node* jadwalArray[count];
        temp = head;
        int index = 0;
        while (temp != nullptr) {
            jadwalArray[index++] = temp;
            temp = temp->next;
        }
 const char* urutanHari[] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};

        
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                int indexHari1 = -1, indexHari2 = -1;
                for (int k = 0; k < 7; k++) {
                    if (urutanHari[k][0] == jadwalArray[j]->hari[0] && urutanHari[k][1] == jadwalArray[j]->hari[1]) {
                        indexHari1 = k;
                    }
                    if (urutanHari[k][0] == jadwalArray[j + 1]->hari[0] && urutanHari[k][1] == jadwalArray[j + 1]->hari[1]) {
                        indexHari2 = k;
                    }
                }
          
                if (indexHari1 > indexHari2) {
                    Node* tempNode = jadwalArray[j];
                    jadwalArray[j] = jadwalArray[j + 1];
                    jadwalArray[j + 1] = tempNode;
                }
            }
        }
        
       
        cout << "Jadwal Keseluruhan:" << endl;
         cout << "+-------------------------+-------------------------+-------------------------+" << endl;
        cout << "|          Hari           |         Waktu           |      Mata Kuliah        |" << endl;
        cout << "+-------------------------+-------------------------+-------------------------+" << endl;
        for (int i = 0; i < count; i++) {
            cout << "| " << setw(24) << left << jadwalArray[i]->hari << "| "
                 << setw(24) << left << jadwalArray[i]->waktu << "| "
                 << setw(24) << left << jadwalArray[i]->matkul << "|" << endl;
            cout << "+-------------------------+-------------------------+-------------------------+" << endl;
        }
    }
}

 void cariHari(const char* targetHari) {
        LinkedList hasilCari;
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->hari[0] == targetHari[0] && temp->hari[1] == targetHari[1] && temp->hari[2] == targetHari[2]) {
                hasilCari.tambahJadwal(temp->hari, temp->matkul, temp->waktu);
            }
            temp = temp->next;
        }
        if (hasilCari.head == nullptr) {
            cout << "Tidak ada jadwal pada hari tersebut." << endl;
        } else {
            cout << "Hasil Pencarian Jadwal pada Hari " << targetHari << ":" << endl;
            hasilCari.tampilkanJadwal();
        }
    }

void cariMatkulRekursif(Node* current, const char* targetMatkul) {
    if (current == nullptr) {
        return;
    }

    const char* str1 = current->matkul;
    const char* str2 = targetMatkul;
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }

    if (*str2 == '\0') {
        cout << "Hari: " << current->hari << ", Waktu: " << current->waktu << ", Mata Kuliah: " << current->matkul << endl;
    }

    cariMatkulRekursif(current->next, targetMatkul);
}

void cariMatkul(const char* targetMatkul) {
    cout << "Hasil Pencarian Jadwal untuk Mata Kuliah \"" << targetMatkul << "\":" << endl;
    cariMatkulRekursif(head, targetMatkul);
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
        cout << "2. Tampilkan Jadwal\n";
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
                        jadwalList.cariHari(hari);
                        break;
                    case 'b':
                        system("cls");
                        cout << "Silakan Masukkan Matkul: ";
                        cin.ignore();
                        cin.getline(matkul, MAX_MATKUL);
                        jadwalList.cariMatkul(matkul);
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