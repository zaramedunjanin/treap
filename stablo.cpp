#ifndef STABLO_CPP
#define STABLO_CPP
#include "stablo.h"
#include <iostream>
#include<utility>
#include <cstdlib>
using namespace std;

template<typename Tip>
void Stablo<Tip>::BrojElemenata(Cvor* cvor) {
    if(cvor == nullptr)
        return;
    broj_elemenata++;
    BrojElemenata(cvor->ld);
    BrojElemenata(cvor->dd);
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::NapraviStablo(Cvor *cvor) {
    if(cvor != nullptr){
        broj_elemenata++;
        Cvor* novi = new Cvor(cvor->element);
        novi->prioritet = cvor->prioritet;
        novi->ld = NapraviStablo(cvor->ld);
        novi->dd = NapraviStablo(cvor->dd);
        if(novi->ld != nullptr)
            novi->ld->rod = novi;
        if(novi->dd != nullptr)
            novi->dd->rod = novi;
        return novi;
    }
    return nullptr;
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::NajmanjiElement(Stablo<Tip>::Cvor *cvor) {
    if(cvor == nullptr)
        return nullptr;
    Cvor *trenutni = cvor;
    while(trenutni->ld != nullptr)
        trenutni = trenutni->ld;
    return trenutni;
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::NajveciElement(Stablo<Tip>::Cvor *cvor) {
    if(cvor == nullptr)
        return nullptr;
    Cvor *trenutni = cvor;
    while(trenutni->dd != nullptr)
        trenutni = trenutni->dd;
    return trenutni;
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::NajmanjiPrioritet(Stablo<Tip>::Cvor* cvor) {
    if(cvor == nullptr)
        return nullptr;
    Cvor* trenutni = cvor;
    while(trenutni != nullptr) {
        if(trenutni->ld != nullptr && trenutni->dd != nullptr){
            if(trenutni->ld->prioritet < trenutni->dd->prioritet)
                trenutni = trenutni->ld;
            else trenutni = trenutni->dd;
        }
        else if(trenutni->ld != nullptr) trenutni = trenutni->ld;
        else if(trenutni->dd != nullptr)trenutni = trenutni->dd;
        else return trenutni;
    }
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::NadjiSljedbenika(Stablo<Tip>::Cvor* cvor) {
    if(cvor->dd != nullptr)
        return NajmanjiElement(cvor->dd);
    Cvor* trenutni = cvor;
    while(trenutni != korijen && trenutni == trenutni->rod->dd)
        trenutni = trenutni->rod;
    if(trenutni == korijen)
        return nullptr;
    else return trenutni->rod;
}

template<typename Tip>
void Stablo<Tip>::Obrisi(Cvor* cvor) {
    if(cvor == nullptr)
        return;
    Obrisi(cvor->ld);
    Obrisi(cvor->dd);
    delete cvor;
}

template <typename Tip>
void Stablo<Tip>::LijevaRotacija(Cvor* cvor) {
    Cvor* roditelj = cvor->rod;
    cvor->rod->dd = cvor->ld;
    if(cvor->ld != nullptr)
        cvor->ld->rod = cvor->rod;
    cvor->rod = cvor->rod->rod;
    if(cvor->rod == nullptr)
        korijen = cvor;
    else if(cvor->rod->ld == roditelj)
        cvor->rod->ld = cvor;
    else
        cvor->rod->dd = cvor;
    cvor->ld = roditelj;
    roditelj->rod = cvor;
}

template <typename Tip>
void Stablo<Tip>::DesnaRotacija(Cvor* cvor) {
    Cvor* roditelj = cvor->rod;
    cvor->rod->ld = cvor->dd;
    if(cvor->dd != nullptr)
        cvor->dd->rod = cvor->rod;
    cvor->rod = cvor->rod->rod;
    if(cvor->rod == nullptr)
        korijen = cvor;
    else if(cvor->rod->ld == roditelj)
        cvor->rod->ld = cvor;
    else
        cvor->rod->dd = cvor;
    cvor->dd = roditelj;
    roditelj->rod = cvor;
}

template <typename Tip>
void Stablo<Tip>::RotacijaGore(Cvor* cvor) {
    if(cvor->rod == nullptr || (cvor->rod != nullptr && cvor->prioritet <= cvor->rod->prioritet))
        return;
    if(cvor->rod->dd == cvor)
        LijevaRotacija(cvor);
    else
        DesnaRotacija(cvor);
    RotacijaGore(cvor);
}

template <typename Tip>
void Stablo<Tip>::RotacijaDolje(Cvor* cvor) {
    if(cvor->ld == nullptr && cvor->dd == nullptr)
        return;
    if(cvor->rod != nullptr){
        if(cvor->prioritet > cvor->rod->prioritet){
            if(cvor->rod->ld == cvor)
                DesnaRotacija(cvor);
            else if(cvor->rod->dd == cvor)
                LijevaRotacija(cvor);
        }
    }
    if(cvor->ld != nullptr && cvor->dd != nullptr){
        if(cvor->ld->prioritet > cvor->dd->prioritet)
            RotacijaDolje(cvor->ld);
        else
            RotacijaDolje(cvor->dd);
    }
    else if(cvor->ld != nullptr)
        RotacijaDolje(cvor->ld);
    else RotacijaDolje(cvor->dd);
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Find(Tip element, Cvor* cvor) {
    if(cvor == nullptr || element == cvor->element)
        return cvor;
    if(element < cvor->element) return Find(element, cvor->ld);
    else return Find(element, cvor->dd);
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Find(Tip element) {
    return Find(element, korijen);
}

template <typename Tip>
pair<typename Stablo<Tip>::Cvor*, bool> Stablo<Tip>::Insert(Tip element) {
    if(korijen == nullptr) {
        korijen = new Cvor(element);
        broj_elemenata = 1;
        return {korijen, true};
    }
    Cvor *trenutni = korijen, *prethodni = nullptr;
    while(trenutni != nullptr) {
        if(element == trenutni->element)
            return {trenutni, false};
        prethodni = trenutni;
        if(element < trenutni->element)
            trenutni = trenutni->ld;
        else trenutni = trenutni->dd;
    }
    Cvor *novi = new Cvor(element,prethodni);
    if(element < prethodni->element)prethodni->ld = novi;
    else prethodni->dd = novi;

    RotacijaGore(novi);
    broj_elemenata++;
    return {novi,true};
}

template <typename Tip>
pair<typename Stablo<Tip>::Cvor*, bool> Stablo<Tip>::Insert(Cvor* cvor) {
    if(korijen == nullptr){
        korijen = new Cvor(cvor->element);
        korijen->prioritet = cvor->prioritet;
        broj_elemenata = 1;
        return {korijen, true};
    }
    Cvor *trenutni = korijen, *prethodni = nullptr;
    while(trenutni != nullptr) {
        if(cvor->element == trenutni->element)
            return {trenutni, false};
        prethodni = trenutni;
        if(cvor->element < trenutni->element)
            trenutni = trenutni->ld;
        else trenutni = trenutni->dd;
    }
    Cvor *novi = new Cvor(cvor->element, prethodni);
    novi->prioritet = cvor->prioritet;
    if(cvor->element < prethodni->element) prethodni->ld = novi;
    else prethodni->dd = novi;

    RotacijaGore(novi);
    broj_elemenata++;
    return {novi,true};
}

template <typename Tip>
void Stablo<Tip>::Erase(Cvor* za_brisanje) {
    if(za_brisanje->dd == nullptr) {
        if(za_brisanje->ld == nullptr) {
            if(za_brisanje->rod != nullptr) {
                if(za_brisanje->rod->dd == za_brisanje)
                    za_brisanje->rod->dd = nullptr;
                else za_brisanje->rod->ld = nullptr;
            }
            else korijen = nullptr;
        }
        else{
            if(za_brisanje->rod != nullptr){
                if(za_brisanje->rod->dd == za_brisanje)
                    za_brisanje->rod->dd = za_brisanje->ld;
                else za_brisanje->rod->ld = za_brisanje->ld;
                za_brisanje->ld->rod = za_brisanje->rod;
            }
            else {
                korijen = za_brisanje->ld;
                za_brisanje->ld->rod = nullptr;
            }
        }
    }
    else {
        Cvor* sljedbenik = NadjiSljedbenika(za_brisanje);
        if(sljedbenik->rod == za_brisanje) {
            sljedbenik->rod = za_brisanje->rod;
            if(za_brisanje->rod != nullptr) {
                if(za_brisanje->rod->dd == za_brisanje)
                    za_brisanje->rod->dd = sljedbenik;
                else za_brisanje->rod->ld = sljedbenik;
            }
            else korijen = sljedbenik;
            if(za_brisanje->ld != nullptr)
                za_brisanje->ld->rod = sljedbenik;
            sljedbenik->ld = za_brisanje->ld;
        }
        else {
           sljedbenik->rod->ld = sljedbenik->dd;
           if(sljedbenik->dd != nullptr)
             sljedbenik->dd->rod = sljedbenik->rod;
           sljedbenik->dd = za_brisanje->dd;
           za_brisanje->dd->rod = sljedbenik;
           sljedbenik->ld = za_brisanje->ld;
           if(za_brisanje->ld != nullptr)
             za_brisanje->ld->rod = sljedbenik;
           sljedbenik->rod = za_brisanje->rod;
           if(za_brisanje->rod != nullptr) {
              if(za_brisanje->rod->ld == za_brisanje)
                za_brisanje->rod->ld = sljedbenik;
              else za_brisanje->rod->dd = sljedbenik;
           }
           else korijen = sljedbenik;
        }

        RotacijaDolje(sljedbenik);
    }
    za_brisanje = nullptr;
    delete za_brisanje;
    broj_elemenata--;
}

template <typename Tip>
int Stablo<Tip>::Erase(const Tip &element) {
    Cvor *za_brisanje = Find(element);
    if(za_brisanje != nullptr) {
        Erase(za_brisanje);
        return 1;
    }
    return 0;
}

template <typename Tip>
pair<Stablo<Tip>, Stablo<Tip>> Split(Stablo<Tip> &S, Tip k) {
    typename Stablo<Tip>::Cvor* novi = new typename Stablo<Tip>::Cvor(k);
    novi->prioritet = S.korijen->prioritet + rand();
    S.Insert(novi);
    Stablo<Tip> Sl, Sd;
    Sl.korijen = S.korijen->ld;
    Sd.korijen = S.korijen->dd;
    Sl.BrojElemenata(S.korijen->ld);
    Sd.BrojElemenata(S.korijen->dd);
    return {Sl, Sd};
}

template <typename Tip>
Stablo<Tip> Merge(Stablo<Tip> &S1, Stablo<Tip> &S2) {
    Tip vrijednost = (S1.NajveciElement(S1.korijen)->element + S2.NajmanjiElement(S2.korijen)->element)/2;
    typename Stablo<Tip>::Cvor *novi = new typename Stablo<Tip>::Cvor(vrijednost, nullptr, S1.korijen, S2.korijen);
    novi->prioritet = rand()%min(S1.NajmanjiPrioritet(S1.korijen)->prioritet, S2.korijen->prioritet);

    S1.korijen->rod = novi;
    S2.korijen->rod = novi;
    Stablo<Tip> S(novi);
    S.RotacijaDolje(S.korijen);
    S.broj_elemenata = S1.broj_elemenata + S2.broj_elemenata;
    S.Erase(novi);
    return S;
}

template <typename Tip>
void Stablo<Tip>::InOrderRek(Cvor* cvor) {
    if(cvor==nullptr) return;
    InOrderRek(cvor->ld);
    cout<<cvor->element<<"-"<<cvor->prioritet<<" ";
    InOrderRek(cvor->dd);
}

/*
template <typename Tip>
void Stablo<Tip>::Ispisi(Cvor* cvor) {
    if(cvor == nullptr)
        return ;
    cout<<cvor->element<<"-"<<cvor->prioritet<<endl;
    if(cvor->ld != nullptr)
        cout<<cvor->ld->element<<"-"<<cvor->ld->prioritet<<" ";
    if(cvor->dd != nullptr)
        cout<<cvor->dd->element<<"-"<<cvor->dd->prioritet;
    cout<<endl;
    Ispisi(cvor->dd);
    Ispisi(cvor->ld);
}
template <typename Tip>
void Stablo<Tip>::Ispisi(){
    Ispisi(korijen);
}*/

#endif // STABLO_CPP
