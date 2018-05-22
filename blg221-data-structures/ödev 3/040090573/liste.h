#ifndef LISTE_H
#define LISTE_H

#include "dugum.h"
#include <stdio.h>

struct Liste{
       isaretci_eleman *baslangic;//��aret�i listesi i�in ba�lang�c� tutan i�aret�i
       void isaretci_liste(isaretci_eleman *);//i�aret�i listesi i�in fonksiyon
       void isaretciliste_temizle();//i�aret�i listesini temizlemek i�in fonksiyon
       Tel_dugum *bas;
       int dugumsayisi;
       void olustur();
       void kapat();
       void listeyaz();
       void listebosalt();
       void ekle(Tel_dugum *);
       void sil(int sirano);
       isaretci_eleman ara(char *);
       void guncelle(int kayitno, Tel_dugum *);
       char *dosyaadi;
       FILE *teldefteri;
       void dosyaya_yaz();
       void dosyadan_oku();
       };
#endif       
       
