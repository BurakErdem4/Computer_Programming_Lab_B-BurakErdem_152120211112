#include <iostream>
#include <string>

using namespace std;

struct Node {
    string songTitle; // Sarkinin adi
    Node* next;       // Zincirdeki bir sonraki sarki
};

// Menumuz
void displayMenu() {
    cout << "\n--- Calma Listesi ---" << endl;
    cout << "1. Sarki Ekle (En basa)" << endl;
    cout << "2. Sarkiyi Ara" << endl;
    cout << "3. Listeyi Goruntule" << endl;
    cout << "4. Cik" << endl;
    cout << "Seciminiz: ";
}


// sarki ekleme 
void addSong(Node*& head, string songName) {
    Node* newNode = new Node();
    newNode->songTitle = songName;
    newNode->next = head;
    head = newNode;
    
    cout << "[Basarili] '" << songName << "' listeye eklendi." << endl;
}


//  Listeyi gorme
void displayList(Node* head) {
    if (head == nullptr) {
        cout << "[Bilgi] Liste su an bos." << endl;
        return;
    }
    cout << "\n--- Guncel Calma Listesi ---" << endl;
    Node* current = head;
    int count = 1;
    while (current != nullptr) {
        cout << count << ". " << current->songTitle << endl;
        current = current->next;
        count++;
    }
    cout << "--------------------------" << endl;
}

//  Sarki arama 
void searchSong(Node* head, string searchName) {
    Node* current = head;
    int position = 1;
    while (current != nullptr) {
        if (current->songTitle == searchName) {
            cout << "[Bulundu] '" << searchName << "' sarkisi listede " << position << ". sirada" << endl;
            return; 
        }
        current = current->next; 
        position++;
    }
    cout << "[Bulunamadi] '" << searchName << "' listede boyle  bir sarki yok." << endl;
}




int main() {
    Node* head = nullptr; 
    int choice;
    string songName;

    while (true) {
        displayMenu();
        cin >> choice;

        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Eklenecek sarkinin adi : ";
                getline(cin, songName);
              
                addSong(head, songName);
               break;
            case 2:
                cout << "Aradiginiz sarkinin adi: ";
                getline(cin, songName);
		searchSong(head, songName);
                break;
            case 3:
                displayList(head);
                break;
            case 4:
                cout << "Programdan cikiliyor" << endl;
                return 0;
            default:
                cout << "Hata! Lutfen  isleminizi 1-4 arasi secin." << endl;
        }
    }
    return 0;
}
