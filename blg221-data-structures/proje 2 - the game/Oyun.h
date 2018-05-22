#ifndef OYUN_H
#define OYUN_H

#include <stdio.h>
#include "Yapilar.h"

struct Oyun{
    void baslat();
    int zar(int);
    int zarlab();
    karakter *player;
    karakter *oyuncu_olustur();
    dusman *dusman_olustur(); 
    void dovus(karakter *, dusman *, int , int);
    int dovus_sira(karakter *, dusman *);  
    void maze(hucre *, int, int);
    void labirent();
    void lab_yazdir(hucre *, int, int);
    bool komsu_varmi(hucre *, int, int);
    Kuyruk mezarlik;
    Yigin yigin;
    void bitir();
    };

#endif    
