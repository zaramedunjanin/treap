#include<iostream>
#include "stablo.h"
#include <ctime>
using namespace std;

int main(){
    //srand(time(0));
    Stablo<int> S1;
    S1.Insert(17);
    S1.Insert(30);
    S1.Insert(25);
    S1.Insert(35);
    S1.Insert(5);
    S1.Insert(45);
    S1.Insert(32);
    S1.Insert(12);
    S1.Insert(10);

    S1.Insert(18);
    S1.Insert(100);
    S1.Insert(11);
    S1.Insert(300);
    S1.Insert(51);
    S1.Insert(52);
    S1.Insert(53);
    S1.Insert(41);
    S1.Insert(42);
    S1.Insert(43);
    S1.Insert(37);

    S1.Erase(12);
    cout<<"Stablo: "<<endl<<endl;
    S1.InOrder();
    cout<<endl<<endl<<"Razdvojeno stablo:"<<endl<<endl;
    pair<Stablo<int>, Stablo<int>> par = Split(S1, 29);
    par.first.InOrder();
    cout<<endl<<endl;
    par.second.InOrder();
    cout<<endl<<endl<<"Ponovo spojeno stablo:"<<endl<<endl;
    Stablo<int> S2 = Merge(par.first, par.second);
    S2.InOrder();

    Stablo<int> S3, S4;

    S4.Insert(11);
    S4.Insert(1);
    S4.Insert(13);
    S4.Insert(14);
    S4.Insert(15);
    S4.Insert(16);
    S4.Insert(17);
    S4.Insert(18);
    S4.Insert(19);

    S3.Insert(40);
    S3.Insert(2);
    S3.Insert(5);
    S3.Insert(6);
    S3.Insert(12);
    S3.Insert(20);
    S3.Insert(9);
    cout<<endl;
    return 0;
}
