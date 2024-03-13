// OOP_Labdarbs3_Variants4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class OverflowException {
public:
    OverflowException() {
        cout << endl << "Exception created!" << endl;
    }
    OverflowException(const OverflowException&) {
        cout << "Exception copied!" << endl;
    }
    ~OverflowException() {
        cout << "Exception finished!" << endl;
    }
};

class Article {
protected:
    string Svitr_kods;
    string Nosaukums;
    float cena_gab;

public:
    // Konstruktors
    Article() : Svitr_kods(), Nosaukums(), cena_gab() {}
    Article(string s, string n, float c) : Svitr_kods(s), Nosaukums(n), cena_gab(c) {}

    // Destruktors
    virtual ~Article() {
        cout << "Prece objekts " << Svitr_kods << " ir izdzesta.\n";
    }

    // Output info
    virtual void Print() const {
        cout << "Numurs: " << Svitr_kods << "\n";
        cout << "Nosaukums: " << Nosaukums << "\n";
        cout << "Cena: " << cena_gab << "\n" << "\n";
    }

    // Getters
    string GetBarcode() const { return Svitr_kods; }
    string GetNosaukums() const { return Nosaukums; }
    float GetPricePerUnit() const { return cena_gab; }

    // Setters
    void SetNumber(string s) { Svitr_kods = s; }
    void SetName(string n) { Nosaukums = n; }
    void SetPrice(float c) { cena_gab = c; }
};

class gramata : public Article {
private:
    string autors;

public:
    // Konstruktors
    gramata() : Article(), autors() {}
    gramata(string s, string n, float c, string a) : Article(s, n, c), autors(a) {}

    // Destruktors
    virtual ~gramata() {
        cout << "Gramata ar svitru kodu " << Svitr_kods << " ir izdzesta.\n";
    }

    // Output info
    virtual void Print() const override {
        Article::Print();
        cout << "Autors: " << autors << "\n" << "\n";
    }

    // Getters
    string GetAutors() const { return autors; }

    // Setters
    void SetAutor(string a) { autors = a; }
};

class BookShop {
private:
    typedef gramata* DPPointer;
    DPPointer* Nodes;
    static const unsigned int DEFAULT_MAX_LENGTH = 5;
    unsigned int MaxLength;
    unsigned int Length;
public:
    BookShop() : MaxLength(DEFAULT_MAX_LENGTH), Length(0) {
        Nodes = new DPPointer[MaxLength];
    }
    BookShop(unsigned int MaxLength) : MaxLength(MaxLength), Length(0) {
        Nodes = new DPPointer[MaxLength];
    }
    ~BookShop();
    static unsigned int GetDefaultMaxLength() {
        return DEFAULT_MAX_LENGTH;
    }
    int GetMaxLength() const {
        return MaxLength;
    }
    int GetLength() const {
        return Length;
    }
    void AddNode(const gramata&);
    void Print() const;
};

BookShop::~BookShop() {
    for (unsigned int i = 0; i < Length; i++)
        delete Nodes[i];
    delete[] Nodes;
}
void BookShop::Print() const {
    for (unsigned int i = 0; i < Length; i++) {
        cout << (i + 1) << ". ";
        Nodes[i]->Print();
        cout << "." << endl;
    }
}
void BookShop::AddNode(const gramata& Node) {
    if (Length == MaxLength)
        throw OverflowException();
    else
        Nodes[Length++] = new gramata(
            Node.GetBarcode(), Node.GetNosaukums(), Node.GetPricePerUnit(), Node.GetAutors()
        );
}



int main(void) {
    BookShop* Line = new BookShop(20);
    gramata* D1 = new gramata("29566960", "Mazais princis", 9.99, "S. E. Gallian");
    gramata  D2("14566549", "Gilberts un vina draugi", 18.49, "Gundega Burka");

    try {
        Line->AddNode(*D1);
    }
    catch (const OverflowException&) {
        cout << "Parak gara rinda, ludzu nomaini datus" << endl;
    }
    catch (...) {
        cout << "error" << endl;
    }
    delete D1;

    cout << "\nKlases max garums: " <<
        BookShop::GetDefaultMaxLength() << "." << endl;
    cout << "Objekta max garums: " <<
        Line->GetDefaultMaxLength() << "." << endl;
    cout << "Max grindas garums: " << Line->GetMaxLength() << "." << endl;
    cout << "si briza rindas garums: " << Line->GetLength() << "." << endl;

    try {
        Line->AddNode(D2);
        cout << "\nIeraksts pievienots veiksmgi!" << endl;
    }
    catch (const OverflowException&) {
        cout << "Parak gars teksts, ludzu nomaini" << endl;
    }
    catch (...) {
    }

    try {
        Line->AddNode(D2);
        cout << "\nJauns ieraksts pievienots" << endl;
    }
    catch (const OverflowException&) {
        cout << "Parak gars ieraksts, ludzu nomaini" << endl;
    }
    catch (...) {
    }

    Line->Print();
    delete Line;

    cin.get();
    return 0;
}
