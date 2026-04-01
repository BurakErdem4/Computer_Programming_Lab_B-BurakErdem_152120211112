#include <iostream>
#include <string>

using namespace std;

struct MoneyBundle {
    string serialNumber;
    string currencyType;
    int billCounts[3];   
    MoneyBundle* next; 
};

struct Customer {
    string customerName;
    string transactionType;
};

const int MAX_QUEUE = 5;
Customer customerQueue[MAX_QUEUE];
int frontIndex = -1;
int rearIndex = -1;

MoneyBundle* topBundle = nullptr;

void displayMenu() {
    cout << "=== Banka yonetim sis ===" << endl;
    cout << "1 Kasaya para ekleme " << endl;
    cout << "2 musteri ekle " << endl;
    cout << " 3islem yap  " << endl;
    cout << " 4 su aki durum " << endl;
    cout << "5 cikis" << endl;
    cout << "Seciminiz: ";
}

void receiveMoney(string serial, string currency, int count100, int count50, int count20) {
    MoneyBundle* newBundle = new MoneyBundle();
    newBundle->serialNumber = serial;
    newBundle->currencyType = currency;
    newBundle->billCounts[0] = count100;
    newBundle->billCounts[1] = count50;
    newBundle->billCounts[2] = count20;
    
    newBundle->next = topBundle;
    topBundle = newBundle;
    
    cout << "[Banka] Kasaya yeni para destesi eklendi (" << currency << " - Seri: " << serial << ")\n";
}

void newCustomer(string name, string transaction) {
    if ((rearIndex + 1) % MAX_QUEUE == frontIndex) {
        cout << "[Hata] Banka sirasi dolu . Yeni musteri alinamaz .\n";
        return;
    }
    
    // eger sira bombossa ilk musteri geliyordur
    if (frontIndex == -1) {
        frontIndex = 0;
        rearIndex = 0;
    } else {
        // dairesel olarak siranin sonunu bir ilerletiyorum
        rearIndex = (rearIndex + 1) % MAX_QUEUE;
    }
    
    customerQueue[rearIndex].customerName = name;
    customerQueue[rearIndex].transactionType = transaction;
    
    cout << " Siraya yeni musteri eklendi: " << name << " (" << transaction << ")\n";
}

void processTransaction() {
    if (frontIndex == -1) {
        cout << "[Hata] Sirada bekleyen musteri yok.\n";
        return;
    }
    // Eger kasada para kalmadiysa islem yapamaz
    if (topBundle == nullptr) {
        cout << "[Hata] Kasada para kalmadi. Islem yapilamiyor.\n";
        return;
    }

    string customer = customerQueue[frontIndex].customerName;
    string transType = customerQueue[frontIndex].transactionType;
    
    MoneyBundle* bundleToUse = topBundle;
    string currency = bundleToUse->currencyType;
    
    cout << "\n[Islem Basarili] " << customer << " adli musterinin '" << transType 
         << "' islemi " << currency << " destesi ile halledildi.\n";
         
    if (frontIndex == rearIndex) {
        frontIndex = -1;
        rearIndex = -1;
    } else {
        frontIndex = (frontIndex + 1) % MAX_QUEUE;
    }
    
    topBundle = topBundle->next;
    delete bundleToUse; 
}

void displayStatus() {
    cout << "\n\n\n --- KASA DURUMU (Yigin/Stack) ---\n";
    if (topBundle == nullptr) {
        cout << "Kasa su an bos.\n";
    } else {
        MoneyBundle* temp = topBundle;
        int count = 1;
        while (temp != nullptr) {
            cout << count << ". Deste: " << temp->currencyType 
                 << " (Seri: " << temp->serialNumber << ") - 100'luk:" << temp->billCounts[0] 
                 << " 50'lik:" << temp->billCounts[1] << " 20'lik:" << temp->billCounts[2] << "\n";
            temp = temp->next;
            count++;
        }
    }
    
    cout << "\n\n--- BEKLEYEN MUSTERi (Dairesel Kuyruk/Circular Queue) ---\n";
    if (frontIndex == -1) {
        cout << "Sirada bekleyen kimse yok.\n";
    } else {
        int i = frontIndex;
        int pos = 1;
        while (true) {
            cout << pos << ". " << customerQueue[i].customerName 
                 << " (" << customerQueue[i].transactionType << ")\n";
            // Dairesel yapida son elemana ulastiysak donguyu bozalim ki çikabilelim
            if (i == rearIndex) break;
            i = (i + 1) % MAX_QUEUE;
            pos++;
        }
    }
    cout << "--------------------------------\n\n";
}

int main() {
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string serial, curr;
                int c100, c50, c20;
                cout << "Seri No: "; cin >> serial;
                cout << "Para Birimi : "; cin >> curr;
                cout << "100'luk banknotlar toplam : "; cin >> c100;
                cout << "50'lik banknotlar toplam: "; cin >> c50;
                cout << "20'lik banknotlar toplam: "; cin >> c20;
                receiveMoney(serial, curr, c100, c50, c20);
                break;
            }
            case 2: {
                string name, trans;
                cout << "Musteri Adi: "; cin >> name;
                cout << "Islem Turu (Cekim/Yatirma vs): "; cin >> trans;
                newCustomer(name, trans);
                break;
            }
            case 3:
                processTransaction();
                break;
            case 4:
                displayStatus();
                break;
            case 5: {
                cout << "Banka kapaniyor. Kasadaki paralari temizliyoruz\n";
                while (topBundle != nullptr) {
                    MoneyBundle* temp = topBundle;
                    topBundle = topBundle->next;
                    delete temp;
                }
                return 0;
            }
            default:
                cout << "Hatali secim yaptiniz . Lutfen 1-5 arasi deger girin.\n";
        }
    }
    return 0;
}
