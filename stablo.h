#ifndef STABLO_H
#define STABLO_H
#include<iostream>
#include <utility>
#include<random>
using namespace std;

template <typename Tip>
class Stablo {
    public:
    struct Cvor {
        Tip element;
        int prioritet;
        Cvor *rod, *ld, *dd;
        Cvor(Tip el = Tip(), Cvor* rod = nullptr, Cvor* ld = nullptr, Cvor* dd = nullptr):
            element(el), rod(rod), ld(ld), dd(dd) {prioritet = rand();}
    };

    private:
    Cvor* korijen;
    int broj_elemenata;

    Cvor* NapraviStablo(Cvor*);
    Cvor* Find(Tip element, Cvor*);
    Cvor* NajmanjiElement(Cvor*);
    Cvor* NajveciElement(Cvor*);
    Cvor* NajmanjiPrioritet(Cvor*);
    Cvor* NadjiSljedbenika(Cvor*);
    void InOrderRek(Cvor*);
    void Obrisi(Cvor* cvor);
    void LijevaRotacija(Cvor*);
    void DesnaRotacija(Cvor*);
    void RotacijaGore(Cvor*);
    void RotacijaDolje(Cvor*);
    void Ispisi(Cvor*);
    void BrojElemenata(Cvor*);

    public:
    Stablo():broj_elemenata(0),korijen(nullptr){}
    Stablo(Cvor* k):broj_elemenata(0){korijen = NapraviStablo(k);}
    Stablo(const Stablo &S):broj_elemenata(0){korijen = NapraviStablo(S.korijen);}
    ~Stablo(){Obrisi(korijen);}
    Cvor* Find(Tip element);
    pair<Cvor*,bool> Insert(Tip element);
    pair<Cvor*,bool> Insert(Cvor* cvor);
    void Erase(Cvor* za_brisanje);
    int Erase(const Tip &element);
    template<typename T> friend pair<Stablo<T>, Stablo<T>> Split(Stablo<T> &S, T k);
    template<typename T> friend Stablo<T> Merge(Stablo<T> &S1, Stablo<T> &S2);
    void InOrder() { InOrderRek(korijen);}
    void Ispisi();
};

#include "stablo.cpp"

#endif // STABLO_H
