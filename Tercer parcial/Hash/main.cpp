#include "HashTable.h"

using namespace std;

int main() {
    int size;
    cout << "Enter the size of the hash table: ";
    cin >> size;

    HashTable hashTable(size);

    int option;
    do {
        cout << "\nMenu:\n";
        cout << "1. Insert string\n";
        cout << "2. Insert integer\n";
        cout << "3. Display table\n";
        cout << "4. Exit\n";
        cout << "Select an option: ";
        cin >> option;

        switch (option) {
            case 1: {
                string str;
                cout << "Enter a string: ";
                cin >> str;
                hashTable.insert(str);
                break;
            }
            case 2: {
                int num;
                cout << "Enter an integer: ";
                cin >> num;
                hashTable.insert(num);
                break;
            }
            case 3:
                hashTable.display();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (option != 4);

    return 0;
}
