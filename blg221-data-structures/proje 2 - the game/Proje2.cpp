/***************************
Ders : BLG221 (Veri Yapýlarý)
Dönem : 2010 Güz
Proje : #2
Ad Soyad : Ozan Arkan Can
Numara : 040090573
***************************/

#include "Oyun.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Oyun Game;

int main(){
    srand(time(NULL));
    Game.baslat();
    Game.labirent();
    Game.bitir();
    system("pause");
    return EXIT_SUCCESS;
}               
    
