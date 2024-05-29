#include <iostream>

using namespace std;

const int MAX_NAME_LENGTH = 50;
int nextItemId = 1;

struct Item {
    int id;
    char name[MAX_NAME_LENGTH];
    double price;
    int quantity;
    Item* next;

    Item(const char* n, double p, int q)
        : id(nextItemId++), price(p), quantity(q), next(nullptr) {
        int i = 0;
        while (n[i] != '\0' && i < MAX_NAME_LENGTH - 1) {
            name[i] = n[i];
            i++;
        }
        name[i] = '\0'; 
    }
};


struct Category {
    char name[MAX_NAME_LENGTH];
    Item* items; 
    Category* subcategories; 
    Category* next;

    Category(const char* n)
        : items(nullptr), subcategories(nullptr), next(nullptr) {
        int i = 0;
        while (n[i] != '\0' && i < MAX_NAME_LENGTH - 1) {
            name[i] = n[i];
            i++;
        }
        name[i] = '\0';
    }
};

struct Order {
    char itemName[MAX_NAME_LENGTH];
    int quantity;
    Order* next;

    Order(const char* n, int q)
        : quantity(q), next(nullptr) {
        int i = 0;
        while (n[i] != '\0' && i < MAX_NAME_LENGTH - 1) {
            itemName[i] = n[i];
            i++;
        }
        itemName[i] = '\0';
    }
};
struct StackNode {
    char action[MAX_NAME_LENGTH];
    char itemName[MAX_NAME_LENGTH];
    int quantity;
    StackNode* next;

    StackNode(const char* act, const char* item, int qty) : quantity(qty), next(nullptr) {
        int i = 0;
        while (act[i] != '\0' && i < MAX_NAME_LENGTH - 1) {
            action[i] = act[i];
            i++;
        }
        action[i] = '\0';
        i = 0;
        while (item[i] != '\0' && i < MAX_NAME_LENGTH - 1) {
            itemName[i] = item[i];
            i++;
        }
        itemName[i] = '\0';
    }
};

struct Stack {
    StackNode* top;

    Stack() : top(nullptr) {}

    bool isEmpty() {
        return top == nullptr;
    }

    void push(const char* action, const char* itemName, int quantity) {
        StackNode* newNode = new StackNode(action, itemName, quantity);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (!isEmpty()) {
            StackNode* temp = top;
            top = top->next;
            delete temp;
        }
    }

    StackNode* peek() {
        return top;
    }

    void display() {
        StackNode* current = top;
        while (current) {
             cout << "Action: " << current->action << ", Item: " << current->itemName << ", Quantity: " << current->quantity <<  endl;
            current = current->next;
        }
    }
};

Category* root = new Category("Root");
Order* orderQueueHead = nullptr;
Order* orderQueueTail = nullptr;

bool areStringsEqual(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false;
        }
        i++;
    }
    return str1[i] == '\0' && str2[i] == '\0';
}

bool isStringEmptyOrSpacesOnly(const char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] != ' ') {
            return false;
        }
        i++;
    }
    return i == 0 || str[0] == '\0';
}

Category* findCategory(Category* category, const char* name) {
    if (areStringsEqual(category->name, name)) {
        return category;
    }
    for (Category* subcategory = category->subcategories; subcategory; subcategory = subcategory->next) {
        Category* foundCategory = findCategory(subcategory, name);
        if (foundCategory) {
            return foundCategory;
        }
    }
    return nullptr;
}

Item* findItem(Category* category, const char* itemName) {
    for (Item* item = category->items; item; item = item->next) {
        if (areStringsEqual(item->name, itemName)) {
            return item;
        }
    }
    for (Category* subcategory = category->subcategories; subcategory; subcategory = subcategory->next) {
        Item* foundItem = findItem(subcategory, itemName);
        if (foundItem) {
            return foundItem;
        }
    }
    return nullptr;
}

void addItem(Category* category, Item* newItem) {
    newItem->next = category->items;
    category->items = newItem;
}

void addSubcategory(Category* category, Category* newCategory) {
    newCategory->next = category->subcategories;
    category->subcategories = newCategory;
}

void addInventoryItem(Stack& actionLog) {
    int choice;
    double itemPrice; 
    int itemQuantity; 

    while(true){
    cout << "Pilih apa yang ingin ditambahkan:\n";
    cout << "1. Kategori\n";
    cout << "2. Subkategori\n";
    cout << "3. Barang\n";
    cout << "0. Kembali\n";
    cout << "Pilihan: ";
    cin >> choice;
    cin.ignore();
    
    switch (choice) {
        case 1: {
            char categoryName[MAX_NAME_LENGTH];
            cout << "Masukkan nama kategori baru: ";
            cin.getline(categoryName, MAX_NAME_LENGTH);

            if (isStringEmptyOrSpacesOnly(categoryName)) {
                cout << "Nama kategori tidak boleh kosong atau hanya berisi spasi." << endl;
                return;
            }

            if (findCategory(root, categoryName)) {
                cout << "Kategori sudah ada." << endl;
                return;
            }

            Category* newCategory = new Category(categoryName);
            addSubcategory(root, newCategory);
            cout << "Kategori berhasil ditambahkan." << endl;
            break;
        }
        case 2: {
            char parentCategoryName[MAX_NAME_LENGTH], subcategoryName[MAX_NAME_LENGTH];
            cout << "Masukkan nama kategori induk: ";
            cin.getline(parentCategoryName, MAX_NAME_LENGTH);

            if (isStringEmptyOrSpacesOnly(parentCategoryName)) {
                cout << "Nama kategori induk tidak boleh kosong atau hanya berisi spasi." << endl;
                return;
            }

            Category* parentCategory = findCategory(root, parentCategoryName);

            if (parentCategory) {
                cout << "Masukkan nama subkategori baru: ";
                cin.getline(subcategoryName, MAX_NAME_LENGTH);

                if (isStringEmptyOrSpacesOnly(subcategoryName)) {
                    cout << "Nama subkategori tidak boleh kosong atau hanya berisi spasi." << endl;
                    return;
                }

                if (findCategory(parentCategory, subcategoryName)) {
                    cout << "Subkategori sudah ada." << endl;
                    return;
                }

                Category* newSubcategory = new Category(subcategoryName);
                addSubcategory(parentCategory, newSubcategory);
                cout << "Subkategori berhasil ditambahkan." << endl;
            } else {
                cout << "Kategori induk tidak ditemukan." << endl;
            }
            break;
        }
        case 3: {
            char categoryName[MAX_NAME_LENGTH], subcategoryName[MAX_NAME_LENGTH], itemName[MAX_NAME_LENGTH];
            double itemPrice;
            int itemQuantity;

            cout << "Masukkan nama kategori: ";
            cin.getline(categoryName, MAX_NAME_LENGTH);

            if (isStringEmptyOrSpacesOnly(categoryName)) {
                cout << "Nama kategori tidak boleh kosong atau hanya berisi spasi." << endl;
                return;
            }

            Category* category = findCategory(root, categoryName);

            if (category) {
                cout << "Masukkan nama subkategori: ";
                cin.getline(subcategoryName, MAX_NAME_LENGTH);

                if (isStringEmptyOrSpacesOnly(subcategoryName)) {
                    cout << "Nama subkategori tidak boleh kosong atau hanya berisi spasi." << endl;
                    return;
                }

                Category* subcategory = findCategory(category, subcategoryName);

                if (subcategory) {
                    cout << "Masukkan nama barang: ";
                    cin.getline(itemName, MAX_NAME_LENGTH);

                    if (isStringEmptyOrSpacesOnly(itemName)) {
                        cout << "Nama barang tidak boleh kosong atau hanya berisi spasi." << endl;
                        return;
                    }

                    cout << "Masukkan harga barang: ";
                    cin >> itemPrice;

                    if (cin.fail()) {
                        cout << "Harga barang harus berupa angka." << endl;
                        cin.clear();
                        while (cin.get() != '\n'); 
                        return;
                    }

                    cout << "Masukkan jumlah barang: ";
                    cin >> itemQuantity;

                    if (cin.fail()) {
                        cout << "Jumlah barang harus berupa angka." << endl;
                        cin.clear();
                        while (cin.get() != '\n'); 
                        return;
                    }

                    Item* newItem = new Item(itemName, itemPrice, itemQuantity);
                    addItem(subcategory, newItem);
                    actionLog.push("Add", itemName, itemQuantity); 
                    cout << "Barang berhasil ditambahkan." << endl;
                } else {
                    cout << "Subkategori tidak ditemukan." << endl;
                }
                } else {
                    cout << "Kategori tidak ditemukan." << endl;
                }
                break;
                }
                case 0:
                return; 
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    }
}

void addOrder() {
    char itemName[MAX_NAME_LENGTH];
    int quantity;

    cout << "Masukkan nama barang: ";
    cin.ignore();
    cin.getline(itemName, MAX_NAME_LENGTH);

    if (isStringEmptyOrSpacesOnly(itemName)) {
        cout << "Nama barang tidak boleh kosong atau hanya berisi spasi." << endl;
        return;
    }

    cout << "Masukkan jumlah barang: ";
    cin >> quantity;

    if (cin.fail()) {
        cout << "Jumlah barang harus berupa angka." << endl;
        cin.clear();
        while (cin.get() != '\n'); // Ignore invalid input
        return;
    }

    Order* newOrder = new Order(itemName, quantity);
    if (!orderQueueTail) {
        orderQueueHead = orderQueueTail = newOrder;
    } else {
        orderQueueTail->next = newOrder;
        orderQueueTail = newOrder;
    }
    cout << "Pesanan berhasil ditambahkan." << endl;
}

void printOrders() {
    if (!orderQueueHead) {
        cout << "Tidak ada pesanan." << endl;
        return;
    }

    Order* current = orderQueueHead;
    cout << "Daftar pesanan:" << endl;
    while (current) {
        cout << " - " << current->itemName << ": " << current->quantity << endl;
        current = current->next;
    }
}

void printInventory(Category* category, int level = 0) {
    for (int i = 0; i < level; ++i) {
        cout << "  ";
    }
    cout << category->name << endl;

    for (Item* item = category->items; item; item = item->next) {
        for (int i = 0; i < level + 1; ++i) {
            cout << "  ";
        }
        cout << " - " << item->name << " (ID: " << item->id << ", Price: " << item->price << ", Quantity: " << item->quantity << ")" << endl;
    }

    for (Category* subcategory = category->subcategories; subcategory; subcategory =  subcategory->next) {
        printInventory(subcategory, level + 1);
    }
}

void processOrder(Category* root, Stack& actionLog) {
    if (!orderQueueHead) {
        cout << "Tidak ada pesanan untuk diproses." << endl;
        return;
    }

    Order* currentOrder = orderQueueHead;
    Order* previousOrder = nullptr;

    if (currentOrder) {
        Item* item = findItem(root, currentOrder->itemName);
        if (item) {
            if (item->quantity >= currentOrder->quantity) {
                double totalCost = item->price * currentOrder->quantity;
                item->quantity -= currentOrder->quantity;
                cout << "Pesanan untuk " << currentOrder->itemName << " berhasil diproses.\n";
                cout << "\nRincian pesanan:\n";
                cout << "Nama Barang: " << currentOrder->itemName << endl;
                cout << "Harga Barang: " << item->price << endl;
                cout << "Jumlah Barang: " << currentOrder->quantity << endl;
                cout << "Total Harga: " << totalCost << endl;
                actionLog.push("Take", currentOrder->itemName, currentOrder->quantity);

                previousOrder = currentOrder;
                currentOrder = currentOrder->next;

                if (previousOrder == orderQueueHead) {
                    orderQueueHead = currentOrder;
                } else {
                    previousOrder->next = currentOrder;
                }

                if (!currentOrder) {
                    orderQueueTail = previousOrder;
                }

                delete previousOrder;
            } else {
                cout << "Stok untuk " << currentOrder->itemName << " tidak mencukupi. Pesanan digeser ke akhir antrean." << endl;

                if (previousOrder) {
                    previousOrder->next = currentOrder->next;
                } else {
                    orderQueueHead = currentOrder->next;
                }

                if (!currentOrder->next) {
                    orderQueueTail = previousOrder;
                }

                if (orderQueueTail) {
                    orderQueueTail->next = currentOrder;
                } else {
                    orderQueueHead = currentOrder;
                }

                currentOrder->next = nullptr;
                orderQueueTail = currentOrder;
                currentOrder = currentOrder->next;
            }
        } else {
            cout << "Barang " << currentOrder->itemName << " tidak ditemukan di inventory. Pesanan digeser ke akhir antrean." << endl;

            if (previousOrder) {
                previousOrder->next = currentOrder->next;
            } else {
                orderQueueHead = currentOrder->next;
            }

            if (!currentOrder->next) {
                orderQueueTail = previousOrder;
            }

            if (orderQueueTail) {
                orderQueueTail->next = currentOrder;
            } else {
                orderQueueHead = currentOrder;
            }

            currentOrder->next = nullptr;
            orderQueueTail = currentOrder;
            currentOrder = currentOrder->next;
        }
    }
}

void undoLastAction(Category* root, Stack& actionLog) {
    if (actionLog.isEmpty()) {
         cout << "Tidak ada aksi untuk di-undo." <<  endl;
        return;
    }

    StackNode* lastAction = actionLog.peek();
    if (!lastAction) {
         cout << "Tidak ada aksi untuk di-undo." <<  endl;
        return;
    }

    Item* item = findItem(root, lastAction->itemName);
    if (item) {
        if (areStringsEqual(lastAction->action, "Add")) {
            item->quantity -= lastAction->quantity;
             cout << "Undo berhasil" << endl;
        } else if (areStringsEqual(lastAction->action, "Take")) {
            item->quantity += lastAction->quantity;
             cout << "Undo berhasil" << endl;
        } else {
             cout << "Aksi tidak dikenal." <<  endl;
            return;
        }
        actionLog.pop();
    } else {
         cout << "Item tidak ditemukan untuk di-undo." <<  endl;
    }
}

int main() {
    int choice;
    Stack actionLog;
    
     while (true) {
         cout << "\nMenu:\n";
         cout << "1. Inventori\n";
         cout << "2. Penjualan\n";
         cout << "0. Keluar\n";
         cout << "Pilih menu: ";
         cin >> choice;

        switch (choice) {
            case 1:
                system("cls");
                while (true) {
                     cout << "\nMenu Inventori:\n";
                     cout << "1. Tambahkan Barang Kategori\n";
                     cout << "2. Tampilkan Inventori\n";
                     cout << "3. Transaksi\n";
                     cout << "4. Undo\n";
                     cout << "0. Kembali\n";
                     cout << "Pilih opsi: ";
                     cin >> choice;

                    if (choice == 0) break;

                    switch (choice) {
                        case 1:
                            system("cls");
                            addInventoryItem(actionLog);
                            break;
                        case 2:
                            system("cls");
                            printInventory(root);
                            break;
                        case 3:
                            system("cls");
                            cout << "\nTransaksi:\n";
                            actionLog.display();
                            break;
                        case 4:
                            system("cls");
                            undoLastAction(root, actionLog);
                            break;
                        default:
                             cout << "Opsi tidak valid, coba lagi." <<  endl;
                    }
                }
                system("cls");
                break;
            case 2:
                while (true) {
                     cout << "\nMenu Penjualan:\n";
                     cout << "1. Pesan Barang\n";
                     cout << "2. Proses Barang\n";
                     cout << "3. Daftar Pesanan\n";
                     cout << "4. Transaksi\n";
                     cout << "5. Undo\n";
                     cout << "0. Kembali\n";
                     cout << "Pilih opsi: ";
                     cin >> choice;

                    if (choice == 0) break;

                    switch (choice) {
                        case 1:
                            system("cls");
                            addOrder();
                            break;
                        case 2:
                            system("cls");
                            processOrder(root, actionLog);
                            break;
                        case 3:
                            printOrders();
                            break;
                        case 4:
                            system("cls");
                            cout << "\nTransaksi:\n";
                            actionLog.display();
                            break;
                        case 5:
                            system("cls");
                            undoLastAction(root, actionLog);
                            break;
                        default:
                             cout << "Opsi tidak valid, coba lagi." <<  endl;
                    }
                }
                system("cls");
                break;
            case 0:
                system("cls");
                cout << "Keluar dari program." <<  endl;
                return 0;
            default:
                 cout << "Menu tidak valid, coba lagi." <<  endl;
        }
    }

    return 0;
}