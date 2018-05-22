#ifndef ISLEMLER_H
#define ISLEMLER_H
#include <stdio.h>
#include "dugumler.h"

struct Islem{
       Ders_dugum *bas;
       isaretci_dugum *baslangic;
       char *dosyaadi;
       FILE *odevplanlayici;
       void olustur();
       void kapat();
       void listebosalt();
       void dosyadan_oku();
       void dosyaya_yaz(int, char *);
       Ders_dugum *dugum_olustur(char *, char *, int *);
       void ekle(char *, char *, int*);
       void sil(int sirano, int secim);
       int *tarih_hesapla(int *);
       isaretci_dugum *hepsinilistele();
       void isaretciliste(isaretci_dugum *);
       void isaretciliste_temizle();
       isaretci_dugum *ara(char *);
       int arama_ekranayazdir(isaretci_dugum *, int );
       void zamanagorelistele(isaretci_dugum *, int , int );     
            };
#endif            
