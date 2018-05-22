/***************************
Ders : BLG221 (Veri Yap�lar�)
D�nem : 2010 G�z
�dev : #1
Ad Soyad : Ozan Arkan Can
Numara : 040090573
***************************/

#include <iostream>
#include <stdlib.h>
#include <iomanip>

#include <ctype.h>

#include "dosyaislemleri.h"

#define MAX 100 // Arama yap�ld���nda bulunan kay�tlar�n s�ralar�n� tutmak i�in olu�turulan dizi i�in max. eleman say�s�

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
	cout << "Lutfen aramak istediginiz kisinin adini giriniz (tum liste i�in '*'a basiniz):" << endl;
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
    FILE *yenidosya; // Kay�t s�ralar�n� tutan dosya i�in pointer
    int kayitno_d[MAX];
    /* Silme i�lemi i�in onay al�n�rken girilen kay�t s�ras�n�n arama neticesinde bulunan kay�tlar i�erisinde
    olup olmad���n� kontrol etmek i�in olu�turulan dizi*/
    
    char tercih; // Kullan�c�dan evet/hay�r giri�i almak i�in de�i�ken
    
    int breakkontrol = 0;// Kullan�c�n�n girdi�i kay�d�n e�le�memi� olmas� durumuyla ilgili bir de�i�ken
    
    char ad[AD_UZUNLUK];
	int secim;	 
    cout << "Lutfen kaydini silmek istediginiz kisinin adini giriniz (tum liste i�in '*'a basiniz):" << endl;
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
		        
			/*Aramada tek bir kay�t bulundu�u i�in kay�t s�ralar�n�n tutuldu�u dosyada tek bir kay�t vard�r.
            Bu kayd� dosyadan okuyup defter.sil fonksiyonuna parametre olarak g�nderiliyor*/		        
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
	        
            yenidosya = fopen("kayitno.txt", "r+"); // Kay�t s�ralar�n�n tutuldu�u dosya a��l�yor
            
            // Kay�t s�ralar� bir diziye at�l�yor
            for(int i = 0; i < kisisayisi; i++)
                fscanf(yenidosya, "%d", &kayitno_d[i]);   
            
            /* Kullan�c�n girdi�i kay�t s�ras� arama sonucunda bulunan kay�tlar i�erisinde varsa 
            defter.sil fonksiyonuna parametre olarak g�nderiliyor*/
            for (int i = 0; i < kisisayisi; i++){
                if(kayitno_d[i] == secim){
                   defter.sil(secim);
                   cout << "Kayit silindi" <<endl;
                   breakkontrol = 1;
                   break;
                                         }   
                                            }
           	// Kullan�c�n girdi�i kay�t no arama sonucunda bulunmam��sa uyar� mesaj� yazd�r�l�yor
            if(breakkontrol == 0)
                cout << "Girdiginiz kayit no bulunmamaktadir. Lutfen tekrar deneyiniz..." << endl; 
            }	
			
	}

    getchar();
};
void kayit_guncelle(){
    FILE *yenidosya; // Kay�t s�ralar�n� tutan dosya i�in pointer
    int kayitno_d[MAX];
    /* G�ncelleme i�lemi i�in onay al�n�rken girilen kay�t s�ras�n�n arama neticesinde bulunan kay�tlar i�erisinde
    olup olmad���n� kontrol etmek i�in olu�turulan dizi*/

    char tercih; // Kullan�c�dan evet/hay�r giri�i almak i�in de�i�ken
    
    int breakkontrol = 0;// Kullan�c�n�n girdi�i kay�d�n e�le�memi� olmas� durumuyla ilgili bir de�i�ken
    
    char ad[AD_UZUNLUK];
	int secim;	
	cout << "Lutfen kaydini guncellemek istediginiz kisinin adini giriniz (tum liste i�in '*'a basiniz):" << endl;
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
		        
			/*Aramada tek bir kay�t bulundu�u i�in kay�t s�ralar�n�n tutuldu�u dosyada tek bir kay�t vard�r.
            Bu kayd� dosyadan okuyup defter.guncelle fonksiyonuna parametre olarak g�nderiliyor*/                
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
            
            yenidosya = fopen("kayitno.txt", "r+"); // Kay�t s�ralar�n�n tutuldu�u dosya a��l�yor
            
            // Kay�t s�ralar� bir diziye at�l�yor
            for(int i = 0; i < kisisayisi; i++)
                fscanf(yenidosya, "%d", &kayitno_d[i]);   
            
            /* Kullan�c�n girdi�i kay�t s�ras� arama sonucunda bulunan kay�tlar i�erisinde varsa 
            defter.g�ncelle fonksiyonuna parametre olarak g�nderiliyor*/
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
           	// Kullan�c�n girdi�i kay�t no arama sonucunda bulunmam��sa uyar� mesaj� yazd�r�l�yor
            if(breakkontrol == 0)
                cout << "Girdiginiz kayit no bulunmamaktadir. Lutfen tekrar deneyiniz..." << endl; 
            }	
			
	}
		
	getchar();
};
