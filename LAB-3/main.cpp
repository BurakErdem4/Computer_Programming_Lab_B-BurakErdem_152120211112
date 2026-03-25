#include <iostream>
#include <string>

using namespace std;

struct Page {
    string url;
    string title;
    int accessTime[3];
    Page* next;
    Page* prev;
};

// menu ekrana yazdirma
void displayMenu() {
    cout << "\n=== Tarayicimiz ===" << endl;
    cout << "1. Yeni Sayfa Ziyaret Et (Visit)" << endl;
    cout << "2. Geri Git (Back)" << endl;
    cout << "3. Ileri Git (Forward)" << endl;
    cout << "4. Su Anki Sayfayi Sil (Delete)" << endl;
    cout << "5. Gecmisi Goruntule (Display History)" << endl;
    cout << "6. Cikis (EXIT)" << endl;
    cout << "Seciminiz: ";
}

// sayfa ziyaret et
void visitPage(Page*& head, Page*& tail, Page*& current, string url, string title, int h, int m, int s) {
    Page* newPage = new Page();
    newPage->url = url;
    newPage->title = title;
    newPage->accessTime[0] = h;
    newPage->accessTime[1] = m;
    newPage->accessTime[2] = s;
    newPage->next = nullptr;
    newPage->prev = nullptr;

    if (head == nullptr) {
        // tarayici yeni acildiginda (gecmis olusmadi daha)
        head = newPage;
        tail = newPage;
        current = newPage;
    } else {
        // eger sayfalarda geziyorsak
        
        // eger geri tusuyla eski bir sayfadaysak ve yeni bir linke tiklarsak,
        // eski gecmisi unutmaliyiz.
        if (current != tail) {
            Page* temp = current->next;
            while(temp != nullptr) {
                Page* toDelete = temp;
                temp = temp->next;
                delete toDelete; 
            }
        }
        
        current->next = newPage;
        newPage->prev = current;
        
        tail = newPage;
        current = newPage;
    }
    cout << "\n[Ziyaret Edildi] -> " << title << " (" << url << ") - Saat: " << h << ":" << m << ":" << s << endl;
}

// geri
void goBack(Page*& current) {
    if (current == nullptr) {
        cout << "[Hata] Tarayici gecmisi bos!" << endl;
    } else if (current->prev != nullptr) {
        current = current->prev; // su anki sayfayi bir onceki sayfa yap
        cout << "[Geri Gidildi] Su anki sayfa: " << current->title << " (" << current->url << ")" << endl;
    } else {
        cout << "[Hata] Daha fazla geri gidilemez. Ilk sayfadasiniz." << endl;
    }
}

// ileri
void goForward(Page*& current) {
    if (current == nullptr) {
        cout << "[Hata] Tarayici gecmisi bos!" << endl;
    } else if (current->next != nullptr) {
        current = current->next; // su anki sayfayi bir sonraki sayfa yap
        cout << "[Ileri Gidildi] Su anki sayfa: " << current->title << " (" << current->url << ")" << endl;
    } else {
        cout << "[Hata] Daha fazla ileri gidilemez, daha ilerisi yok" << endl;
    }
}

// gecmisi gorme
void displayHistory(Page* head, Page* current) {
    if (head == nullptr) {
        cout << "[Bilgi] Gecmis tamamen bos." << endl;
        return;
    }

    cout << "\nGecmis" << endl;
    Page* temp = head;
    int index = 1;
    
    while (temp != nullptr) {
        // yazdiracagimiz sayfa, su anki sayfaysa "=>" degilse bos birakiyoruz
        if (temp == current) {
            cout << " => ";
        } else {
            cout << "    ";
        }
        
        cout << index << ". " << temp->title << " (" << temp->url << ") - Girdi: ";
        
        // saat yazdirmasi icin for
        for (int i = 0; i < 3; i++) {
            cout << temp->accessTime[i];
            if (i < 2) cout << ":"; 
        }
        cout << endl;
        
        temp = temp->next;
        index++;
    }
    cout << "-------" << endl;
}

// silme
void deleteCurrent(Page*& head, Page*& tail, Page*& current) {
    if (current == nullptr) {
        cout << "[Hata] Silinecek sayfa yok, gecmis bos." << endl;
        return;
    }

    Page* toDelete = current;
    cout << "[Silindi] -> " << current->title << " (" << current->url << ")" << endl;

    if (current == head) {
        head = current->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        current = head; 
    } else if (current == tail) {
        tail = current->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        current = tail; 
    } else {
        current->prev->next = current->next; 
        current->next->prev = current->prev; 
        current = current->prev;             
    }

    delete toDelete; 

    if (head == nullptr) {
        tail = nullptr;
        current = nullptr;
    }
}

int main() {
    Page* head = nullptr;    // ilk sayfa
    Page* tail = nullptr;    // son sayfa
    Page* current = nullptr; // Su an acik olan sayfa
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string u, t; int h, m, s;
                cout << "URL (ornek olarak google.com): "; cin >> u;
                cout << "Baslik (ornek olarak Google): "; cin >> t;
                cout << "Saat [Boslukla Saat Dakika Saniye] ( ornek: 14 30 00): "; cin >> h >> m >> s;
                visitPage(head, tail, current, u, t, h, m, s);
                break;
            }
            case 2:
                goBack(current);
                break;
            case 3:
                goForward(current);
                break;
            case 4:
                deleteCurrent(head, tail, current);
                break;
            case 5:
                displayHistory(head, current);
                break;
            case 6: {
                cout << "\nTarayici kapaniyor. Bellek temizleniyor..." << endl;
                Page* temp = head;
                while (temp != nullptr) {
                    Page* toDelete = temp;
                    temp = temp->next;
                    delete toDelete;
                }
                return 0; // Programi kapat
            }
            default:
                cout << "Hata! lutfen 1-6 arasi secim yapin." << endl;
        }
    }
    return 0;
}

