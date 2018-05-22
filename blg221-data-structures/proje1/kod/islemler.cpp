#include "islemler.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

void Islem::olustur(){
     bas = NULL;
     dosyadan_oku();
}

void Islem::kapat(){     
     dosyaadi = "odevplanlayici.txt";
     dosyaya_yaz(0, dosyaadi);
     listebosalt();
}

void Islem::listebosalt(){
     Ders_dugum *p;
     Is_dugum *q;
     while(bas){
                p = bas;
                bas = bas->sonraki;
                q = p->isptr;
                //Önce dersle ilgili iþler listenin sürekli baþýndan siliniyor
                while(q){
                         p->isptr = p->isptr->sonraki;
                         delete q;
                         q = p->isptr;
                         }
                delete p;//Sonra ders siliniyor
                }
}

void Islem::dosyadan_oku(){
     Dosya_Kayit kayit;
     dosyaadi = "odevplanlayici.txt";
     if(!(odevplanlayici = fopen(dosyaadi, "r+")))
         if(!(odevplanlayici = fopen(dosyaadi, "w+"))){
                         cerr << "Dosya acilamadi" << endl;
                         cerr << "Sadece bellekte calisilacak" << endl;
                         return;
                                                  }
     fseek(odevplanlayici, 0, SEEK_SET);
     while(!feof(odevplanlayici)){
                              fread(&kayit, sizeof(Dosya_Kayit), 1, odevplanlayici);
                              if(feof(odevplanlayici))
                                  break;
                              ekle(kayit.ders, kayit.is, kayit.tarih);
                              }
     fclose(odevplanlayici);
}     

void Islem::dosyaya_yaz(int a,char *dosyaismi){
     if(a != 0) //Eðer argümanlý çalýþtýrýldýysa girilen dosyaismi atanýyor
         dosyaadi = dosyaismi;
     Dosya_Kayit kayit;
     Ders_dugum *dersler;
     Is_dugum *i;
     if(!(odevplanlayici = fopen(dosyaadi, "w+"))){
                     cerr << "Dosya acilamadi" << endl;
                     return ;
                                              }
     dersler = bas;
     while(dersler){
                  i = dersler->isptr;
                  while(i){
                           strcpy(kayit.ders,dersler->ders);
                           strcpy(kayit.is, i->is);
                           for(int j = 0; j < 5; j++)
                               kayit.tarih[j] = i->tarih[j];
                          if(a == 0)
                              fwrite(&kayit, sizeof(Dosya_Kayit), 1, odevplanlayici);
                          else{
                          int *kalansure;
                          fprintf(odevplanlayici, "Dersin adi: %s \nYapilmasi gereken isin adi: %s \nBitis tarihi: %d.%d.%d \nBitis saati: ", kayit.ders, kayit.is, kayit.tarih[0], kayit.tarih[1], kayit.tarih[2]);
                          if(kayit.tarih[3] < 10) fprintf(odevplanlayici, "0");
                          fprintf(odevplanlayici, "%d:", kayit.tarih[3]);
                          if(kayit.tarih[4] < 10) fprintf(odevplanlayici, "0");
                          fprintf(odevplanlayici, "%d\n", kayit.tarih[4]);
                          kalansure = tarih_hesapla(i->tarih);    
                          if(kalansure[4] < 0)
                              fprintf(odevplanlayici, "Bitis zamani gecmistir...\n\n");
                          else{
                              fprintf(odevplanlayici, "Kalansure ");       
                              if(kalansure[0] != 0) fprintf(odevplanlayici, "%d ay ", kalansure[0]);
                              if(kalansure[1] != 0) fprintf(odevplanlayici, "%d gun ", kalansure[1]);
                              if(kalansure[2] != 0) fprintf(odevplanlayici, "%d saat ", kalansure[2]);
                              fprintf(odevplanlayici, "%d dakikadir \n\n", kalansure[3]);
                              }
                              }
                           i = i->sonraki;
                           }
                  dersler = dersler->sonraki;
                  }
     fclose(odevplanlayici);
}

Ders_dugum *Islem::dugum_olustur(char *dersad, char *isad, int *tarih){
          Ders_dugum *yeniders;
          Is_dugum *yeniis;
          yeniders = new Ders_dugum;
          strcpy(yeniders->ders, dersad);
          yeniis = new Is_dugum;
          yeniders->isptr = yeniis;
          strcpy(yeniis->is , isad);
          for(int j = 0; j < 5; j++)
              yeniis->tarih[j] = tarih[j];
          yeniis->sonraki = NULL;
          yeniders->sonraki = NULL;
          return yeniders;
}
void Islem::ekle(char *dersad, char *isad, int *tarih){
     Ders_dugum *tara, *arka, *yeniders;
     Is_dugum *yeniis;
     tara = bas;
     //Basa ekleme
     if(bas == NULL){
            bas = dugum_olustur(dersad, isad, tarih);
            return;
                    }
    //Ýlk sýraya ekleme
     if(strnicmp(dersad, bas->ders, strlen(dersad)) < 0){
                       yeniders = dugum_olustur(dersad, isad, tarih);
                       yeniders->sonraki = bas;
                       bas = yeniders;
                       return;
                                      }
     while(tara && (strnicmp(dersad,tara->ders, strlen(dersad)) > 0)){
                arka = tara;
                tara = tara->sonraki;
                                                   }
     //Ayný isimde ders varsa sadece iþ ekleniyor
     if(tara && strnicmp(dersad, tara->ders, strlen(dersad)) == 0){
             yeniis = new Is_dugum;
             yeniis->sonraki = tara->isptr;
             tara->isptr = yeniis;
             strcpy(yeniis->is, isad);
             for(int j = 0; j < 5; j++)
                 yeniis->tarih[j] = tarih[j];
                                                }
     else{
          yeniders = dugum_olustur(dersad, isad, tarih);
          if(tara){//araya ekleme
                   yeniders->sonraki = tara;
                   arka->sonraki = yeniders;
                   }
          else//sona ekleme
               arka->sonraki = yeniders;
          }
      return;
}

void Islem::isaretciliste(isaretci_dugum *arama_sonuc){
     isaretci_dugum *yeni;
     isaretci_dugum *tara, *arka;
     tara = baslangic;
     yeni = new isaretci_dugum;
     yeni = arama_sonuc;
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
void Islem::isaretciliste_temizle(){
     isaretci_dugum *p;
     while (baslangic != NULL){
           p = baslangic;
           baslangic = baslangic->sonraki;
           delete p;
                }
}               

isaretci_dugum *Islem::ara(char *ara_ad){
    baslangic = NULL;
    Ders_dugum *tara;
    Is_dugum *pn;
    int sayac = 0;
    int derssayac = 0;
    tara = bas;
    int *surehesap;
    while(tara){
                derssayac++;
                isaretci_dugum *aramasonuc;
                aramasonuc = new isaretci_dugum;
                //Liste alfabetik olduðu için fazla iterasyon engelleniyor
                if(strnicmp(tara->ders, ara_ad, strlen(ara_ad) ) > 0)
                        break;                
                if(strnicmp(ara_ad, tara->ders, strlen(ara_ad)) == 0){
                                   int issayac = 0;
                                   pn = tara->isptr;
                                   while(pn){
                                             issayac++;
                                             sayac++;
                                             //Bulunan iþler iþaretçi listesine atanýyor
                                             isaretci_dugum *aramasonuc;
                                             aramasonuc = new isaretci_dugum;
                                             strcpy(aramasonuc->ders , tara->ders);
                                             aramasonuc->derssira = derssayac;
                                             aramasonuc->kayitsirasi = sayac;
                                             aramasonuc->issayac = issayac;
                                             aramasonuc->bulunan = pn;
                                             surehesap = tarih_hesapla(pn->tarih);
                                             for(int j = 0; j < 5; j++)
                                                  aramasonuc->kalansure[j] = surehesap[j];
                                             isaretciliste(aramasonuc);
                                             pn = pn->sonraki;
                                             }
                                                                   }
                 else{//iþlerin listesi tutulduðu için sayacý arttýrmak üzere döngü: eþleþmeyen adlarýn bulunduðu dersler ve iþleri
                      pn = tara->isptr;
                      while(pn){
                                sayac++;
                                pn = pn->sonraki;
                                }
                      }          
                 
                 tara = tara->sonraki;
                 }
      return baslangic;
}

int *Islem::tarih_hesapla(int *tarih){
     int *kalansure;
     kalansure = new int[5];
     time_t t1, t2, lt, fark;
     lt=time(NULL);
     struct tm *local = localtime(&lt); //tm structý time.h klasöründe bulunmaktadýr 
     
     //Sistem tarihi ve saati ile isin tarih ve saati dakikaya çevriliyor
     t1 = local->tm_min + (local->tm_hour * 60) +  (local->tm_mday * 1440) + ((local->tm_mon+1) * 43200) + (local->tm_year + 1900) * 518400;
     t2 = tarih[4] + (tarih[3] * 60) +  (tarih[0] * 1440) + (tarih[1] * 43200) + (tarih[2] * 518400);
     
     //Ýkisi arasýndaki fark bulunuyor ve kalan surenin ne kadar olduðu hesaplanýyor
     fark = t2 - t1;
     kalansure[0] = fark / 43200; //ay
     kalansure[1] = (fark % 43200) / 1440; //gun
     kalansure[2] = (fark % 1440) / 60; //saat
     kalansure[3] = fark % 60; //dakika
     kalansure[4] = fark;//ileride kullanýlmak üzere farkta bu diziye ekleniyor
     
     return kalansure;
}
isaretci_dugum *Islem::hepsinilistele(){
     baslangic == NULL;
     Ders_dugum *tara;
     Is_dugum *pn;
     tara = bas;
     int *surehesap;
     int issayac;
     int derssayac = 0;
     int sayac = 0;
     //Tüm liste taranýyor ve iþaretçi listesine atýlýyor
     while(tara){
                 derssayac++;
                 pn = tara->isptr;
                 issayac = 0;
                 while(pn != NULL){                          
                           issayac++;
                           sayac++;
                           isaretci_dugum *aramasonuc;
                           aramasonuc = new isaretci_dugum;
                           strcpy(aramasonuc->ders , tara->ders);
                           aramasonuc->derssira = derssayac;
                           aramasonuc->kayitsirasi = sayac;
                           aramasonuc->issayac = issayac;
                           aramasonuc->bulunan = pn;
                           surehesap = tarih_hesapla(pn->tarih);
                           for(int j = 0; j < 5; j++)
                                aramasonuc->kalansure[j] = surehesap[j];
                           isaretciliste(aramasonuc);
                           pn = pn->sonraki;
                           }
                 tara = tara->sonraki;
                 }
     return baslangic;
}

void Islem::sil(int sirano, int secim){
     Ders_dugum *tara, *arka, *bulunacak;
     Is_dugum *pn, *isarka, *simdiki;
     int sayac = 0;
     tara = bas;     
     //Dersle ilgili tüm iþleri islmek için
     if(secim == 0){
         if(sirano <= 0){
                   cout << "Hatali kayit girdiniz." << endl;
                   return;}
         //Ýlk ders siliniyor
         if(sirano == 1){
                   bas = bas->sonraki;
                   pn = tara->isptr;
                   while(pn){
                             tara->isptr = pn->sonraki;
                             delete pn;
                             pn = tara->isptr;
                             }
                   delete tara;
                   return;
                        }
         while( (tara != NULL) && (sayac < sirano) ){
               if(sayac == 2) 
                   arka = bas;
               if(sayac > 2) 
                   arka = arka->sonraki;
                bulunacak = tara;
                tara = tara->sonraki;
                sayac++;
                                                     }
         if(sayac < sirano)
             cout << "Silinecek kayit bulunamadi. " << endl;
     
         else{
              arka->sonraki = tara;
              pn = bulunacak->isptr;
              while(pn){
                        bulunacak->isptr = pn->sonraki;
                        delete pn;
                        pn = bulunacak->isptr;
                       }
              delete bulunacak;
             }
                   }//if sonu
    
    //Tek bir iþi silmek için
    else{
         int issayac = 0;

         if(sirano <= 0){
                   cout << "Hatali kayit girdiniz." << endl;
                   return;}                       
         while( tara && (sayac < sirano) ){
                issayac = 0;
                pn = tara->isptr;
                
                    while(pn && (sayac < sirano)){
                             sayac++;
                             issayac++;
                             if(issayac == 2) 
                                 isarka = tara->isptr;
                             if(issayac > 2) 
                                 isarka = isarka->sonraki;
                             simdiki = pn;    
                             pn = pn->sonraki;                     
                                                 }
                                              
                if(sayac == sirano)
                    break;          
                arka = tara;
                tara = tara->sonraki;
                                          }
          if(sayac < sirano){
                   cout << "Hatali kayit girdiniz. " << endl;
                   return;
                            }
          else{
               //Dersle ilgili ilk iþ siliniyor
               if(issayac == 1){
                          tara->isptr = simdiki->sonraki;
                          delete simdiki;
                          //Dersle ilgili iþ kalmamasý durumunda o derste silinir
                          if(tara->isptr == NULL){
                                      arka->sonraki = tara->sonraki;
                                      delete tara;
                                                 }
                          return;
                               }
               else{
                    isarka->sonraki = simdiki->sonraki;
                    delete simdiki;
                    return;
                    }
              }
          }//else sonu
}

int Islem::arama_ekranayazdir(isaretci_dugum *islem, int secim){
     int isaretci_sayac = 0;
     isaretci_dugum *tarama;
     tarama = islem;
     while(tarama != NULL){
         isaretci_sayac++;                      
         tarama = tarama->sonraki;
                          }
     if(isaretci_sayac == 0){
		cout << "Aradiginiz kriterlere uygun kayit bulunamadi" << endl;
        return 2;
                            }     
     //Ekrana uygun sayaclarla yazdýrmak için 4 farklý yazdýrma türü var
     //Tek bir iþ
     if(secim == 1){
        if (isaretci_sayac == 1){ 		
			cout << islem->kayitsirasi << ".) " << islem->ders << " : " << islem->bulunan->is << endl;
            cout << "Isin bitis tarihi ve saati : " <<  islem->bulunan->tarih[0] << "." << islem->bulunan->tarih[1] << "." << islem->bulunan->tarih[2] << " " ;
            if(islem->bulunan->tarih[3] < 10) cout << "0";
            cout << islem->bulunan->tarih[3] << ":";
            if(islem->bulunan->tarih[4] < 10) cout << "0";
            cout << islem->bulunan->tarih[4] << endl;
            if(islem->kalansure[4] > 0){
                                   cout << "Isin bitimine kalan sure : " << endl;
                                   if(islem->kalansure[0] != 0) cout << islem->kalansure[0] << " ay "; 
                                   if(islem->kalansure[1] != 0) cout << islem->kalansure[1] << " gun ";
                                   if(islem->kalansure[2] != 0) cout << islem->kalansure[2] << " saat ";
                                   cout << islem->kalansure[3] << " dakika\n" << endl;
                                       }
            else{    
                 cout << "Isin bitis tarihi gecmistir...\n" << endl;
                }
            return 1;
                                }                 	                     
        else{
             tarama = islem;//Baslangýca dönülüyor
             while(tarama != NULL){            		
    			     cout << tarama->kayitsirasi << ".) " << tarama->ders << " : " << tarama->bulunan->is << endl;
                     cout << "Isin bitis tarihi ve saati : " <<  tarama->bulunan->tarih[0] << "." << tarama->bulunan->tarih[1] << "." << tarama->bulunan->tarih[2] << " " ;
                     if(tarama->bulunan->tarih[3] < 10) cout << "0";
                          cout << tarama->bulunan->tarih[3] << ":";
                     if(tarama->bulunan->tarih[4] < 10) cout << "0";
                          cout << tarama->bulunan->tarih[4] << endl;
                     if(tarama->kalansure[4] > 0){
                                   cout << "Isin bitimine kalan sure : " << endl;
                                   if(tarama->kalansure[0] != 0) cout << tarama->kalansure[0] << " ay "; 
                                   if(tarama->kalansure[1] != 0) cout << tarama->kalansure[1] << " gun ";
                                   if(tarama->kalansure[2] != 0) cout << tarama->kalansure[2] << " saat ";
                                   cout << tarama->kalansure[3] << " dakika\n" << endl;
                                       }
                     else{                       
                          cout << "Isin bitis tarihi gecmistir...\n" << endl;
                         }
                     tarama = tarama->sonraki;
                                  }
            return 0;
            }
               }//if sonu
     //Dersle ilgili tüm iþler
     else{
        if (isaretci_sayac == 1){		
			cout << islem->derssira << ".) " << islem->ders << " : " << islem->issayac << ".) " << islem->bulunan->is << endl;
            cout << "Isin bitis tarihi ve saati : " <<  islem->bulunan->tarih[0] << "." << islem->bulunan->tarih[1] << "." << islem->bulunan->tarih[2] << " " ;
            if(islem->bulunan->tarih[3] < 10) cout << "0";
                   cout << islem->bulunan->tarih[3] << ":";
            if(islem->bulunan->tarih[4] < 10) cout << "0";
                   cout << islem->bulunan->tarih[4] << endl;
            if(islem->kalansure[4] > 0){
                                   cout << "Isin bitimine kalan sure : " << endl;
                                   if(islem->kalansure[0] != 0) cout << islem->kalansure[0] << " ay "; 
                                   if(islem->kalansure[1] != 0) cout << islem->kalansure[1] << " gun ";
                                   if(islem->kalansure[2] != 0) cout << islem->kalansure[2] << " saat ";
                                   cout << islem->kalansure[3] << " dakika\n" << endl;
                                       }
            else{                                     
                 cout << "Isin bitis tarihi gecmistir...\n" << endl;
                }
            return 1;
                                }                   
        else{
             tarama = islem;//Baslangýca dönülüyor
             while(tarama != NULL){            		
    			     cout << tarama->derssira << ".) " << tarama->ders << " : " << tarama->issayac << ".) " << tarama->bulunan->is << endl;
                     cout << "Isin bitis tarihi ve saati : " <<  tarama->bulunan->tarih[0] << "." << tarama->bulunan->tarih[1] << "." << tarama->bulunan->tarih[2] << " " ;
                     if(tarama->bulunan->tarih[3] < 10) cout << "0";
                          cout << tarama->bulunan->tarih[3] << ":";
                     if(tarama->bulunan->tarih[4] < 10) cout << "0";
                          cout << tarama->bulunan->tarih[4] << endl;
                     if(tarama->kalansure[4] > 0){
                                   cout << "Isin bitimine kalan sure : " << endl;
                                   if(tarama->kalansure[0] != 0) cout << tarama->kalansure[0] << " ay "; 
                                   if(tarama->kalansure[1] != 0) cout << tarama->kalansure[1] << " gun ";
                                   if(tarama->kalansure[2] != 0) cout << tarama->kalansure[2] << " saat ";
                                   cout << tarama->kalansure[3] << " dakika\n" << endl;
                                                 }
                     else{
                          cout << "Isin bitis tarihi gecmistir...\n" << endl;            
                         }
                     tarama = tarama->sonraki;
                                  }
            return 0;
            }                                                                                                   
        }// else sonu           
}     
                   
void Islem::zamanagorelistele(isaretci_dugum *islem, int secim, int deger){
     isaretci_dugum *tarama;
     tarama = islem;
     int sayac_d[3] = {0};//istenilen aramaya göre kayýt bulunmamasý durumunda mesaj yazdýrmak için kayýt sayýsý kontrolü
     while(tarama){
                   switch(secim){
                                 case 1:
                                      if(tarama->kalansure[4] < 0){//Bitis tarihi geçenleri listele
    			                             cout << tarama->derssira << ".) " << tarama->ders << " : " << tarama->issayac << ".) " << tarama->bulunan->is << endl;
                                             cout << "Isin bitis tarihi ve saati : " <<  tarama->bulunan->tarih[0] << "." << tarama->bulunan->tarih[1] << "." << tarama->bulunan->tarih[2] << " " ;
                                             if(tarama->bulunan->tarih[3] < 10) cout << "0";
                                             cout << tarama->bulunan->tarih[3] << ":";
                                             if(tarama->bulunan->tarih[4] < 10) cout << "0";
                                             cout << tarama->bulunan->tarih[4] << endl << endl;
                                             sayac_d[0]++;                  
                                                               }
                                       break;
                                 case 2:
                                      //Belli bir aydan az kalanlarý listele
                                      if((tarama->kalansure[0] < deger) && (tarama->kalansure[4] > 0)){
    			                             cout << tarama->derssira << ".) " << tarama->ders << " : " << tarama->issayac << ".) " << tarama->bulunan->is << endl;
                                             cout << "Isin bitis tarihi ve saati : " <<  tarama->bulunan->tarih[0] << "." << tarama->bulunan->tarih[1] << "." << tarama->bulunan->tarih[2] << " " ;
                                             if(tarama->bulunan->tarih[3] < 10) cout << "0";
                                             cout << tarama->bulunan->tarih[3] << ":";
                                             if(tarama->bulunan->tarih[4] < 10) cout << "0";
                                             cout << tarama->bulunan->tarih[4] << endl;
                                             cout << "Isin bitimine kalan sure : " << endl;
                                             if(tarama->kalansure[0] != 0) cout << tarama->kalansure[0] << " ay "; 
                                             if(tarama->kalansure[1] != 0) cout << tarama->kalansure[1] << " gun ";
                                             if(tarama->kalansure[2] != 0) cout << tarama->kalansure[2] << " saat ";
                                             cout << tarama->kalansure[3] << " dakika\n" << endl;                                             
                                             sayac_d[1]++;
                                                                      }
                                       break;                         
                                 case 3:                                                                                                                                                                                             
                                      //Belli bir günden az kalanlarý listele
                                      if((tarama->kalansure[0] == 0) && (tarama->kalansure[1] < deger) && (tarama->kalansure[4] > 0)){
    			                             cout << tarama->derssira << ".) " << tarama->ders << " : " << tarama->issayac << ".) " << tarama->bulunan->is << endl;
                                             cout << "Isin bitis tarihi ve saati : " <<  tarama->bulunan->tarih[0] << "." << tarama->bulunan->tarih[1] << "." << tarama->bulunan->tarih[2] << " " ;
                                             if(tarama->bulunan->tarih[3] < 10) cout << "0";
                                             cout << tarama->bulunan->tarih[3] << ":";
                                             if(tarama->bulunan->tarih[4] < 10) cout << "0";
                                             cout << tarama->bulunan->tarih[4] << endl;
                                             cout << "Isin bitimine kalan sure : " << endl;
                                             if(tarama->kalansure[0] != 0) cout << tarama->kalansure[0] << " ay "; 
                                             if(tarama->kalansure[1] != 0) cout << tarama->kalansure[1] << " gun ";
                                             if(tarama->kalansure[2] != 0) cout << tarama->kalansure[2] << " saat ";
                                             cout << tarama->kalansure[3] << " dakika\n" << endl;                                
                                             sayac_d[2]++;
                                                                                                       }
                                      break;
                                 default:
                                         cout << "Yanlis secim girdiniz. Lutfen tekrar deneyiniz. " << endl << endl;
                                         break;
                                         }
                   tarama = tarama->sonraki;
                  }
        //Aranýlan zaman diliminde kayýt bulunamamasýyla ilgili uyarý yazdýrmak için döngü
        for(int i = 1; i < 4; i++){
                if((secim == i) && (sayac_d[i - 1] == 0))
                   cout << "Aradiginiz zaman diliminde kayit bulunamamistir." << endl << endl;
                                  }
       return;
}                                                                                                                                                                  
     
     
                                                           
                                                                                             
                       
                       
                                      
                    
     

