/***************************
Ders : BLG221 (Veri Yap�lar�)
D�nem : 2010 G�z
�dev : #3
Ad Soyad : Ozan Arkan Can
Numara : 040090573
***************************/

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctype.h>

#include "liste.h"

using namespace std;

typedef Tel_dugum Tel_Kayit;
typedef Liste Veriyapisi;
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
    while(!bitir){
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
	cout << "T: Hepsini Sil" << endl;
    cout << "C: Cikis" << endl;	
	cout << endl;
	cout << "Bir secenek giriniz {A, E, G, S, T, C} : ";	
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
		case 'T': case 't':
            defter.listebosalt();
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
    isaretci_eleman *islem;
    char ad[AD_UZUNLUK];
	cout << "Lutfen aramak istediginiz kisinin adini giriniz (tum liste i�in '*'a basiniz):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,AD_UZUNLUK);		
    islem = &defter.ara(ad);    
    if(islem == NULL){
		cout << "Aradiginiz kriterlere uygun kayit bulunamadi" << endl;
        return;      
                     }
    else{
         //Bulunan kay�tlar�n ekrana bast�r�lmas�
         isaretci_eleman *tarama;
         tarama = islem;
         while(tarama != NULL){
             cout << tarama->kayitsirasi << "." << tarama->aranan->ad << " " << tarama->aranan->telno << endl;                      
             tarama = tarama->sonraki;
                             }
         defter.isaretciliste_temizle();//i�aret�i listesi siliniyor
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
	isaretci_eleman *islem;//i�aret�i listesinin baslang�c�n� tutmak i�in i�aret�i
    int isaretci_sayac = 0;//Bulunan kay�tlar i�in sayac
    bool BREAK_KONTROL = false;// Kullan�c�n�n girdi�i kay�d�n e�le�memi� olmas� durumuyla ilgili bir de�i�ken
    char ad[AD_UZUNLUK];
	int secim;	
	char tercih;// Kullan�c�dan evet/hay�r giri�i almak i�in de�i�ken
    cout << "Lutfen kaydini silmek istediginiz kisinin adini giriniz:" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,AD_UZUNLUK);		
    islem = &defter.ara(ad); //Kay�tlar kontrol ediliyor
	
    isaretci_eleman *tarama;
         //Ka� tane kay�t bulundu ona bak�l�yor
         tarama = islem;
         while(tarama != NULL){
             isaretci_sayac++;                      
             tarama = tarama->sonraki;
                             }
    if(isaretci_sayac == 0)
		cout << "Aradiginiz kriterlere uygun kayit bulunamadi" << endl;		
	                       
	else {
	/*Aramada tek bir kay�t bulundu�u i�in kay�tlar�n referanslar�n�n tutuldu�u listede tek bir d���m vard�r
    O d���mden kay�t s�ras� okunup defter.sil() fonksiyonuna parametre olarak d�nd�r�l�yor */
        if (isaretci_sayac == 1){		
			cout << islem->kayitsirasi << "." << islem->aranan->ad << " " << islem->aranan->telno << endl;
            cout << "Kayit bulundu." << endl;
			cout << "Bu kaydi silmek istediginize emin misiniz? (E/H):";
			cin >> tercih;
            if(tercih == 'E' || tercih == 'e'){
		    defter.sil(islem->kayitsirasi);
		    defter.isaretciliste_temizle();//i�aret�i listesi siliniyor
                                              }
                                 }              
		else{
             tarama = islem;//Baslang�ca d�n�l�yor
             //Bulunan kay�tlar�n ekrana bast�r�lmas�
             while(tarama != NULL){
                 cout << tarama->kayitsirasi << "." << tarama->aranan->ad << " " << tarama->aranan->telno << endl;                      
                 tarama = tarama->sonraki;
                                  }
             cout << "Silmek istediginiz kayidin numarasini giriniz (Islem yapmadan cikmak icin -1 giriniz): " ;
		     cin >> secim;
		     if(secim==-1) return;
             tarama = islem;//Baslangica d�n�l�yor
             
             //Kullan�c�n girdi�i kay�t no varsa defter.sil() fonksiyonuna parametre olarak d�nd�r�l�yor
             while(tarama != NULL){
                 if(tarama->kayitsirasi == secim){                      
                     defter.sil(secim);
                     BREAK_KONTROL = true;
                     cout << "Kayit silindi" <<endl;
                     defter.isaretciliste_temizle();//i�aret�i listesi siliniyor
                     break;                          
                                                 }
                 tarama = tarama->sonraki;
                                  }		
             // Kullan�c�n girdi�i kay�t no arama sonucunda bulunmam��sa uyar� mesaj� yazd�r�l�yor
             if(BREAK_KONTROL == false)
                 cout << "Girdiginiz kayit no bulunmamaktadir. Lutfen tekrar deneyiniz..." << endl;    
		
	        }
        }
	getchar();
};

void kayit_guncelle(){
	isaretci_eleman *islem;//i�aret�i listesinin baslang�c�n� tutmak i�in i�aret�i
    int isaretci_sayac = 0;//Bulunan kay�tlar i�in sayac
    bool BREAK_KONTROL = false;// Kullan�c�n�n girdi�i kay�d�n e�le�memi� olmas� durumuyla ilgili bir de�i�ken
    char tercih;// Kullan�c�dan evet/hay�r giri�i almak i�in de�i�ken
    char ad[AD_UZUNLUK];
	int secim;	
	cout << "Lutfen kaydini guncellemek istediginiz kisinin adini giriniz:" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,AD_UZUNLUK);		
	islem = &defter.ara(ad); 
    isaretci_eleman *tarama;
         //Ka� tane kay�t bulundu ona bak�l�yor
         tarama = islem;
         while(tarama != NULL){
             isaretci_sayac++;                      
             tarama = tarama->sonraki;
                             }	
    
    if(isaretci_sayac == 0){
		cout << "Aradiginiz kriterlere uygun kayit bulunamadi" << endl;		
	}
	else {
		if (isaretci_sayac==1){		
			cout << islem->kayitsirasi << "." << islem->aranan->ad << " " << islem->aranan->telno << endl;
            cout << "Kayit bulundu." << endl;
			cout << "Bu kaydi guncellemek istediginize emin misiniz? (E/H):";
			cin >> tercih;
            //alfabetik s�ra bozulmas�n diye �nce siliniyor sonra ekleniyor bulunan kay�t
            if(tercih == 'E' || tercih == 'e'){
		        defter.sil(islem->kayitsirasi);
		        kayit_ekle();
		        defter.isaretciliste_temizle();//i�aret�i listesi siliniyor
                                              }
                             }
        else{
			tarama = islem;//Baslang�ca d�n�l�yor
		     //Bulunan kay�tlar�n ekrana bast�r�lmas�
             while(tarama != NULL){
                 cout << tarama->kayitsirasi << "." << tarama->aranan->ad << " " << tarama->aranan->telno << endl;                      
                 tarama = tarama->sonraki;
                                  }
            cout << "Guncellemek istediginiz kayidin numarasini giriniz (Islem yapmadan cikmak icin -1 giriniz): " ;
		    cin >> secim;
		    if(secim==-1) return;
             tarama = islem;//Baslangica d�n�l�yor
             
             //Kullan�c�n girdi�i kay�t no varsa defter.sil() ve kayit_ekle fonksiyonuna parametre olarak d�nd�r�l�yor
             while(tarama != NULL){
                 if(tarama->kayitsirasi == secim){                      
                     defter.sil(secim);
                     kayit_ekle();
                     BREAK_KONTROL = true;
                     defter.isaretciliste_temizle();//i�aret�i listesi siliniyor
                     break;                          
                                                 }
                 tarama = tarama->sonraki;
                                  }		
             // Kullan�c�n girdi�i kay�t no arama sonucunda bulunmam��sa uyar� mesaj� yazd�r�l�yor
             if(BREAK_KONTROL == false)
                 cout << "Girdiginiz kayit no bulunmamaktadir. Lutfen tekrar deneyiniz..." << endl;
            }
		cout << "Kaydiniz basariyla guncellendi" <<endl;		
	}
	getchar();
};

