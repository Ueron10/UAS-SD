#include <iostream>

using namespace std;

const int MAX_NAME_LENGTH = 50;
int nextItemId = 1;

// Structure to represent an item
struct Item {
    int id;
    char name[MAX_NAME_LENGTH];
    double price;
    int quantity;
    Item* next;

    // Constructor to initialize an item
    Item(const char* n, double p, int q)
        : id(nextItemId++), price(p), quantity(q), next(nullptr) {
        // Copy the name of the item
        int i = 0;
        while (n[i] != '\0' && i < MAX_NAME_LENGTH - 1) {
            name[i] = n[i];
            i++;
        }
        name[i] = '\0'; // Ensure null-terminated string
    }
};

// Structure to represent a category
struct Category {
    char name[MAX_NAME_LENGTH];
    Item* items; // Head of the linked list of items
    Category* subcategories; // Head of the linked list of subcategories
    Category* next; // Pointer to the next category

    // Constructor to initialize a category
    Category(const char* n)
        : items(nullptr), subcategories(nullptr), next(nullptr) {
        // Copy the name of the category
        int i = 0;
        while (n[i] != '\0' && i < MAX_NAME_LENGTH - 1) {
            name[i] = n[i];
            i++;
        }
        name[i] = '\0'; // Ensure null-terminated string
    }
};

// Structure to represent an order
struct Order {
    char itemName[MAX_NAME_LENGTH];
    int quantity;
    Order* next;

    // Constructor to initialize an order
    Order(const char* n, int q)
        : quantity(q), next(nullptr) {
        // Copy the name of the item
        int i = 0;
        while (n[i] != '\0' && i < MAX_NAME_LENGTH - 1) {
            itemName[i] = n[i];
            i++;
        }
        itemName[i] = '\0'; // Ensure null-terminated string
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

// Global variables to store the root of the category tree and the order queue
Category* root = new Category("Root");
Order* orderQueueHead = nullptr;
Order* orderQueueTail = nullptr;

// Function to check if two strings are equal
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

// Function to check if a string is empty or contains only spaces
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

// Function to find a category by name recursively
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

// Function to find an item by name recursively
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

// Function to add an item to the inventory of a category
void addItem(Category* category, Item* newItem) {
    newItem->next = category->items;
    category->items = newItem;
}

// Function to add a subcategory to a category
void addSubcategory(Category* category, Category* newCategory) {
    newCategory->next = category->subcategories;
    category->subcategories = newCategory;
}

// Function to add an inventory item (category, subcategory, or item)
void addInventoryItem(Stack& actionLog) {
    int choice;
    double itemPrice; // Define itemPrice variable
    int itemQuantity; // Define itemQuantity variable

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
                        while (cin.get() != '\n'); // Ignore invalid input
                        return;
                    }

                    cout << "Masukkan jumlah barang: ";
                    cin >> itemQuantity;

                    if (cin.fail()) {
                        cout << "Jumlah barang harus berupa angka." << endl;
                        cin.clear();
                        while (cin.get() != '\n'); // Ignore invalid input
                        return;
                    }

                    Item* newItem = new Item(itemName, itemPrice, itemQuantity);
                    addItem(subcategory, newItem);
                    actionLog.push("Add", itemName, itemQuantity); // Log the action
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
                return; // Exit the function to return to the previous menu
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    }
}

// Function to add an order to the order queue
void addOrder() {
    char itemName[MAX_NAME_LENGTH];
    int quantity;

    cout << "Masukkan nama barang: ";
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

// Function to print the list of orders in the order queue
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

// Function to print the inventory recursively
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

// Function to process orders one by one from the beginning of the queue
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
                // Process the order
                double totalCost = item->price * currentOrder->quantity;
                item->quantity -= currentOrder->quantity;
                cout << "Pesanan untuk " << currentOrder->itemName << " berhasil diproses.\n";
                cout << "\nRincian pesanan:\n";
                cout << "Nama Barang: " << currentOrder->itemName << endl;
                cout << "Harga Barang: " << item->price << endl;
                cout << "Jumlah Barang: " << currentOrder->quantity << endl;
                cout << "Total Harga: " << totalCost << endl;
                actionLog.push("Take", currentOrder->itemName, currentOrder->quantity); // Log the action

                // Move to the next order
                previousOrder = currentOrder;
                currentOrder = currentOrder->next;

                // Remove the processed order from the queue
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
                // Insufficient stock, move the order to the end of the queue
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
            // Item not found, move the order to the end of the queue
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

    // Menggunakan informasi dalam lastAction untuk langsung mengubah kuantitas item
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


// Main function to manage the program
int main() {
    int choice;
    Stack actionLog;
    
    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah Kategori/Subkategori/Barang\n";
        cout << "2. Lihat Inventory\n";
        cout << "3. Tambah Pesanan\n";
        cout << "4. Proses Pesanan\n";
        cout << "5. Daftar Pesanan\n";
        cout << "6. Transaksi\n";
        cout << "7. Undo\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addInventoryItem(actionLog);
                break;
            case 2:
                printInventory(root);
                break;
            case 3:
                addOrder();
                break;
            case 4:
                processOrder(root, actionLog);
                break;
            case 5:
                printOrders();
                break;
            case 6:
                cout << "\nTransaksi:\n";
                actionLog.display();
                break;
            case 7:
                undoLastAction(root, actionLog);
                break;    
            case 0:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    } while (choice != 0);

    // Deallocate memory (not shown here for brevity)

    return 0;
}

   
