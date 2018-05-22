/***************************
Ders : BLG221 (Veri Yapýlarý)
Dönem : 2010 Güz
Ödev : #1
Ad Soyad : Ozan Arkan Can
Numara : 040090573
***************************/

#include <iostream>
#include <stdlib.h>
#include <iomanip>

#include <ctype.h>

#include "dosyaislemleri.h"

#define MAX 100 // Arama yapýldýðýnda bulunan kayýtlarýn sýralarýný tutmak için oluþturulan dizi için max. eleman sayýsý

using namespace std;



typedef Dosya Veriyapisi;

Veriyapisi defter;


void menu_yazdir();
bool islem_yap(char);
void kayit_ara();
void kayit_ekle();
void kayit_sil();
void kayit_guncelle();


int main(){	
	defter.olustur();	
	bool bitir = false; 
	char secim; 	
	while (!bitir) { 
		menu_yazdir(); 
		cin >> secim;
		bitir = islem_yap(secim); 
		} 	
	defter.kapat();
	return EXIT_SUCCESS;
}

void menu_yazdir(){
	system("clear"); 
	cout << endl << endl;
	cout << "Telefon Defteri Uygulamasi" << endl;
	cout << "Bir islem seciniz" << endl;
	cout << "A: Kayit Arama" << endl;
	cout << "E: Kayit Ekleme" << endl;
	cout << "G: Kayit Guncelleme" << endl;
	cout << "S: Kayit Silme" << endl;	
	cout << "C: Cikis" << endl;	
	cout << endl;
	cout << "Bir secenek giriniz {A, E, G, S, C} : ";	
}

bool islem_yap(char secim){
	bool sonlandir=false;
	switch (secim) { 
	case 'A': case 'a': 
			kayit_ara();
			break; 
		case 'E': case 'e': 
			kayit_ekle();
			break; 
		case 'G': case 'g': 
			kayit_guncelle();
			break;
		case 'S': case 's': 
			kayit_sil();
			break;
		case 'C': case 'c': 
			cout << "Programi sonlandirmak istediginize emin misiniz? (E/H):";
			cin >> secim;
			if(secim=='E' || secim=='e')
				sonlandir=true; 
				break; 
		default: 
			cout << "Hata: Yanlis giris yaptiniz" << endl; 
			cout << "Tekrar deneyiniz {A, E, G, S, C} :" ;
			cin >> secim;
			sonlandir = islem_yap(secim);
			break; 
	}
	return sonlandir;
}

void kayit_ara(){
	char ad[AD_UZUNLUK];
	cout << "Lutfen aramak istediginiz kisinin adini giriniz (tum liste için '*'a basiniz):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,AD_UZUNLUK);		
	if(defter.ara(ad)==0){
		cout << "Aradiginiz kriterlere uygun kayit bulunamadi" << endl;
	}
	getchar();
};
void kayit_ekle(){
	Tel_Kayit yenikayit;	
	cout << "Lutfen kaydetmek istediginiz kisinin bilgilerini giriniz" << endl;
	cout << "Ad : " ;	
	cin.ignore(1000, '\n');
	cin.getline(yenikayit.ad,AD_UZUNLUK);
	cout << "Telefon numarasi :";
	cin >> setw(TELNO_UZUNLUK) >> yenikayit.telno;
	defter.ekle(&yenikayit);
	cout << "Kaydiniz eklenmistir" << endl;
	getchar();
};
void kayit_sil(){
    FILE *yenidosya; // Kayýt sýralarýný tutan dosya için pointer
    int kayitno_d[MAX];
    /* Silme iþlemi için onay alýnýrken girilen kayýt sýrasýnýn arama neticesinde bulunan kayýtlar içerisinde
    olup olmadýðýný kontrol etmek için oluþturulan dizi*/
    
    char tercih; // Kullanýcýdan evet/hayýr giriþi almak için deðiþken
    
    int breakkontrol = 0;// Kullanýcýnýn girdiði kayýdýn eþleþmemiþ olmasý durumuyla ilgili bir deðiþken
    
    char ad[AD_UZUNLUK];
	int secim;	 
    cout << "Lutfen kaydini silmek istediginiz kisinin adini giriniz (tum liste için '*'a basiniz):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,AD_UZUNLUK);		
	int kisisayisi=defter.ara(ad); 
	if(kisisayisi==0){
		cout << "Aradiginiz kriterlere uygun kayit bulunamadi" << endl;		
	}
	else {
		if (kisisayisi==1){		
			cout << "Kayit bulundu." << endl;
			cout << "Bu kaydi silmek istediginize emin misiniz? (E/H):";
			cin >> tercih;
            if(tercih == 'E' || tercih == 'e'){
		        
			/*Aramada tek bir kayýt bulunduðu için kayýt sýralarýnýn tutulduðu dosyada tek bir kayýt vardýr.
            Bu kaydý dosyadan okuyup defter.sil fonksiyonuna parametre olarak gönderiliyor*/		        
                yenidosya = fopen("kayitno.txt", "r+");
		        fscanf(yenidosya, "%d", &secim);
		        fclose(yenidosya);
                defter.sil(secim);
                cout << "Kayit silindi" <<endl;
                getchar();                          
                                              }
		    else
                return;    
                          }
		else{
			cout << "Silmek istediginiz kayidin numarasini giriniz (Islem yapmadan cikmak icin -1 giriniz): " ;
		    cin >> secim;
		    if(secim==-1) return;
	        
            yenidosya = fopen("kayitno.txt", "r+"); // Kayýt sýralarýnýn tutulduðu dosya açýlýyor
            
            // Kayýt sýralarý bir diziye atýlýyor
            for(int i = 0; i < kisisayisi; i++)
                fscanf(yenidosya, "%d", &kayitno_d[i]);   
            
            /* Kullanýcýn girdiði kayýt sýrasý arama sonucunda bulunan kayýtlar içerisinde varsa 
            defter.sil fonksiyonuna parametre olarak gönderiliyor*/
            for (int i = 0; i < kisisayisi; i++){
                if(kayitno_d[i] == secim){
                   defter.sil(secim);
                   cout << "Kayit silindi" <<endl;
                   breakkontrol = 1;
                   break;
                                         }   
                                            }
           	// Kullanýcýn girdiði kayýt no arama sonucunda bulunmamýþsa uyarý mesajý yazdýrýlýyor
            if(breakkontrol == 0)
                cout << "Girdiginiz kayit no bulunmamaktadir. Lutfen tekrar deneyiniz..." << endl; 
            }	
			
	}

    getchar();
};
void kayit_guncelle(){
    FILE *yenidosya; // Kayýt sýralarýný tutan dosya için pointer
    int kayitno_d[MAX];
    /* Güncelleme iþlemi için onay alýnýrken girilen kayýt sýrasýnýn arama neticesinde bulunan kayýtlar içerisinde
    olup olmadýðýný kontrol etmek için oluþturulan dizi*/

    char tercih; // Kullanýcýdan evet/hayýr giriþi almak için deðiþken
    
    int breakkontrol = 0;// Kullanýcýnýn girdiði kayýdýn eþleþmemiþ olmasý durumuyla ilgili bir deðiþken
    
    char ad[AD_UZUNLUK];
	int secim;	
	cout << "Lutfen kaydini guncellemek istediginiz kisinin adini giriniz (tum liste için '*'a basiniz):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,AD_UZUNLUK);		
	int kisisayisi=defter.ara(ad); 
	if(kisisayisi==0){
		cout << "Aradiginiz kriterlere uygun kayit bulunamadi" << endl;		
	}
	else {
		
		if (kisisayisi==1){		
			cout << "Kayit bulundu." << endl;
            cout << "Bu kaydi guncellemek istediginize emin misiniz? (E/H):";
			cin >> tercih;
            if(tercih == 'E' || tercih == 'e'){
		        
			/*Aramada tek bir kayýt bulunduðu için kayýt sýralarýnýn tutulduðu dosyada tek bir kayýt vardýr.
            Bu kaydý dosyadan okuyup defter.guncelle fonksiyonuna parametre olarak gönderiliyor*/                
                yenidosya = fopen("kayitno.txt", "r+");
		        fscanf(yenidosya, "%d", &secim);
		        fclose(yenidosya);
                Tel_Kayit yenikayit;
 		        cout << "Lutfen guncel bilgileri giriniz" << endl;
		        cout << "Ad : " ;
	            cin.ignore(1000, '\n');
		        cin.getline(yenikayit.ad,AD_UZUNLUK);
		        cout << "Telefon numarasi :";
		        cin >> setw(TELNO_UZUNLUK) >> yenikayit.telno;
                defter.guncelle(secim, &yenikayit);
                cout << "Kaydiniz basariyla guncellendi" <<endl;
                getchar();                     }     
             else
                 return;                                  
                          }
		else{
			cout << "Guncellemek istediginiz kayidin numarasini giriniz (Islem yapmadan cikmak icin -1 giriniz): " ;
		    cin >> secim;
		    if(secim==-1) return;
            
            yenidosya = fopen("kayitno.txt", "r+"); // Kayýt sýralarýnýn tutulduðu dosya açýlýyor
            
            // Kayýt sýralarý bir diziye atýlýyor
            for(int i = 0; i < kisisayisi; i++)
                fscanf(yenidosya, "%d", &kayitno_d[i]);   
            
            /* Kullanýcýn girdiði kayýt sýrasý arama sonucunda bulunan kayýtlar içerisinde varsa 
            defter.güncelle fonksiyonuna parametre olarak gönderiliyor*/
            for (int i = 0; i < kisisayisi; i++){
                if(kayitno_d[i] == secim){
                    Tel_Kayit yenikayit;
		            cout << "Lutfen guncel bilgileri giriniz" << endl;
		            cout << "Ad : " ;
		            cin.ignore(1000, '\n');
		            cin.getline(yenikayit.ad,AD_UZUNLUK);
		            cout << "Telefon numarasi :";
		            cin >> setw(TELNO_UZUNLUK) >> yenikayit.telno;
		            defter.guncelle(secim,&yenikayit);	
		            cout << "Kaydiniz basariyla guncellendi" <<endl;
                    breakkontrol = 1;
                    break;
                                         }   
                                            }
           	// Kullanýcýn girdiði kayýt no arama sonucunda bulunmamýþsa uyarý mesajý yazdýrýlýyor
            if(breakkontrol == 0)
                cout << "Girdiginiz kayit no bulunmamaktadir. Lutfen tekrar deneyiniz..." << endl; 
            }	
			
	}
		
	getchar();
};
