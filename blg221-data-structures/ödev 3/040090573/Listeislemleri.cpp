#include "liste.h"
#include <iostream>
#include <stdlib.h>

#include <string.h>

using namespace std;

void Liste::olustur(){
     bas = NULL;
     dugumsayisi = 0;
     dosyadan_oku();
     }

isaretci_eleman Liste::ara(char *aranacak){
    baslangic = NULL;
    Tel_dugum *tara;
    int sayac = 0;
    int bulunan = 0;
    tara = bas;
    bool tumu = false;
    if(strcmp(aranacak, "*") == 0)
        tumu = true; 
    while(tara != NULL){
                isaretci_eleman *arama_sonuc;
                sayac++;
                if(tumu){
                        arama_sonuc->kayitsirasi = sayac;
                        arama_sonuc->aranan = tara;
                        isaretci_liste(arama_sonuc);
                        bulunan++;
                         }
                else{
                     //Liste alfabetik tutuldugu için arama yapýldýðýnda listede aranan kelimeden büyük bir yere geçildiðinde döngü durduruluyor
                     if(strnicmp(tara->ad, aranacak, strlen(aranacak) ) > 0)
                        break;
                     
                     if(strnicmp(tara->ad, aranacak, strlen(aranacak)) == 0){
                                           bulunan++;
                                           arama_sonuc->kayitsirasi = sayac;
                                           arama_sonuc->aranan = tara;
                                           isaretci_liste(arama_sonuc);
                                                                             }
                     }                                                         
                tara = tara->sonraki;
                      }
    
    return *baslangic;
}

void Liste::sil(int sirano){
     Tel_dugum *tara, *arka;
     int sayac = 1;
     tara = bas;
     if(sirano <= 0){
               cout << "Hatali kayit sira numarasi. \n";
               return;
                    }
     if(sirano == 1){
               bas = bas->sonraki;
               delete tara;
               dugumsayisi--;
               return;
                    }
     while( (tara != NULL) && (sayac < sirano) ){
            arka = tara;
            tara = tara->sonraki;
            sayac++;
                                                }
     if(sayac < sirano){
              //Verilen sýrano çok büyük
              cout << "Silinecek kayit bulunamadi. \n";
                       }
     else{
          //Kayýt bulundu
          arka->sonraki = tara->sonraki;
          delete tara;
          dugumsayisi--;
          }
}

void Liste::listebosalt(){
     Tel_dugum *p;
     while (bas){
           p = bas;
           bas = bas->sonraki;
           delete p;
                }
     dugumsayisi = 0;
     cout << "Liste tamamen silindi." << endl;
}

void Liste::ekle(Tel_dugum *eklenecek){
     Tel_dugum *tara, *arka;
     Tel_dugum *yeni;
     tara = bas;
     yeni = new Tel_dugum;
     *yeni = *eklenecek;
     yeni->sonraki = NULL;
     if(bas == NULL){
            //Ýlk dugum ekleniyor
            bas = yeni;
            dugumsayisi++;
            return;
                     }
     if( strcmp(yeni->ad, bas->ad) <= 0 ){
         //Liste baþýna ekle
         yeni->sonraki = bas;
         bas = yeni;
         dugumsayisi++;
         return;
                                         }
     while( tara && (strcmp(yeni->ad, tara->ad) > 0) ){
            arka = tara;
            tara = tara->sonraki;
                                                      }
     
     if(tara){
              //Araya ekleme
              yeni->sonraki = tara;
              arka->sonraki = yeni;
             }
     else
         arka->sonraki = yeni;
     
     dugumsayisi++;
}

void Liste::guncelle(int kayitno, Tel_dugum *yeni){
     Tel_dugum *tara;
     int sayac = 1;
     tara = bas;
     while( tara && (sayac < kayitno) ){
            sayac++;
            tara = tara->sonraki;
                                       }
     
     if(tara){
              yeni->sonraki = tara->sonraki;
              *tara = *yeni;
             }
     else
         cout << "Guncellenecek kayit numarasi hatali. \n";
}                                                                                                                                                               

void Liste::kapat(){
     dosyaya_yaz();
     listebosalt();
}

void Liste::dosyadan_oku(){
     struct Dosya_Kayit{
            char ad[AD_UZUNLUK];
            char telno[TELNO_UZUNLUK];
                       };
      Dosya_Kayit kayit;
      Tel_dugum *yeni;
      dosyaadi = "teldefteri.txt";
      if(!(teldefteri = fopen(dosyaadi, "r+")))
          if(!(teldefteri = fopen(dosyaadi, "w+"))){
                          cerr << "Dosya acilamadi" << endl;
                          exit(1);}
      fseek(teldefteri, 0, SEEK_SET);
      while(!feof(teldefteri)){
                               yeni = new Tel_dugum;
                               fread(&kayit, sizeof(Dosya_Kayit),1, teldefteri);
                               if(feof(teldefteri))
                                   break;
                               strcpy(yeni->ad, kayit.ad);
                               strcpy(yeni->telno, kayit.telno);
                               yeni->sonraki = NULL;
                               ekle(yeni);
                               }
      fclose(teldefteri);
};

void Liste::dosyaya_yaz(){
     struct Dosya_Kayit{
            char ad[AD_UZUNLUK];
            char telno[TELNO_UZUNLUK];
                       };
     Dosya_Kayit kayit;
     Tel_dugum *p;
     if(!(teldefteri = fopen(dosyaadi, "w+"))){
                          cerr << "Dosya acilamadi" << endl;
                          exit(1);}
     p = bas;
     while(p){
              strcpy(kayit.ad, p->ad);
              strcpy(kayit.telno, p->telno);
              fwrite(&kayit,sizeof(Dosya_Kayit),1,teldefteri);
              p = p->sonraki;
              }
    fclose(teldefteri);
};
//Ýþaretçi listesini tutmak için fonksiyon
void Liste::isaretci_liste(isaretci_eleman *arama_sonuc){
     isaretci_eleman *yeni;
     isaretci_eleman *tara, *arka;
     tara = baslangic;
     yeni = new isaretci_eleman;
     *yeni = *arama_sonuc;
     yeni->sonraki = NULL;
     
     if(baslangic == NULL){
            //Ýlk dugum ekleniyor
            baslangic = yeni;
            return;
                          }
     while(tara != NULL){                     
                 arka = tara;
                 tara = tara->sonraki;
                         }     
          arka->sonraki = yeni;
   
   return;
         
}          
//Ýþaretçi listesini silmek için fonksiyon
void Liste::isaretciliste_temizle(){
     isaretci_eleman *p;
     while (baslangic != NULL){
           p = baslangic;
           baslangic = baslangic->sonraki;
           delete p;
                }
}                                                         
                                                                                                                                  
