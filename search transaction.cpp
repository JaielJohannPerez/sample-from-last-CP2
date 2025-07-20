void SearchTransaction() {
    system("CLS");
    ProcessExpiredTransactions(); 

    if (transactionQueue.size == 0) {
        cout << "||  No transactions to search!         ||\n";
        system("pause");
        return;
    }

    int id;
    cout << "========================================\n";
    cout << "||   BINARY SEARCH (TRANSACTION)      ||\n";
    cout << "========================================\n";
    cout << "Enter Transaction ID: ";
    while (!(cin >> id)) {
    			cout << left << setw(60) << " " << "Invalid input. Please enter an integer: ";
    			cin.clear();
    			cin.ignore(10000, '\n');
    		}    cin.ignore(10000, '\n');

    int n = transactionQueue.size;
    Transaction* arr = new Transaction[n];
    TransactionNode* temp = transactionQueue.front;
    for (int i = 0; i < n && temp; ++i, temp = temp->next) {
        arr[i] = temp->data;
    }
    SortTransactionArray(arr, n, 1); 

    int left = 0, right = n - 1, idx = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid].id == id) {
            idx = mid;
            break;
        }
        else if (arr[mid].id < id) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    system("CLS");
    cout << "=============================================================\n";
    cout << "||                      SEARCHED LIST                      ||\n";
    cout << "=============================================================\n";
    cout << "|| TID    | Firearm | Customer Name       | Qty |  Status   ||\n";
    cout << "||--------|---------|---------------------|-----|-----------||\n";

    if (idx != -1) {
        Transaction& t = arr[idx];
        double elapsed = difftime(time(NULL), t.timestamp);
        string status = (t.returned || elapsed >= 30.0) ? "Expired" : "Ongoing"; 

        cout << "|| "
            << setw(6)  << t.id << " | "
            << setw(7)  << t.firearmId << " | "
            << setw(3)  << t.customerName << setw(16) << " | "
            << setw(3)  << t.quantityRented << " | "
            << setw(9)  << status << " ||\n";
    }
    else {
        cout << "||       No matching transaction found.                  ||\n";
    }
    cout << "=============================================================\n";
    delete[] arr;
    cout << "Press Enter to return to the main menu...";
    cin.ignore();
    cin.get();
}
