/***************************
Ders : BLG221 (Veri Yap�lar�)
D�nem : 2010 G�z
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
    
