void processOrder(Category* root) {
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
