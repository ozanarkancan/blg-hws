/***************************
Ders : BLG221 (Veri Yap�lar�)
D�nem : 2010 G�z
Proje : #1
Ad Soyad : Ozan Arkan Can
Numara : 040090573
***************************/

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctype.h>
#include <string.h>
#include "islemler.h"

using namespace std;

typedef Ders_dugum Ders_Kayit;
typedef Islem Veriyapisi;
Veriyapisi ajanda;

void menu_yazdir();
bool islem_yap(char);
void kayit_ara();
void kayit_ekle();
void kayit_sil();
void duzenle();
void tumunulistele();
void zamanagore_listele();

int main(int argc, char *argv[]){
    ajanda.olustur();
    if(argc == 3){
            //T�m listeyi ismi verilen dosyaya yazar
            if((*argv[1] == 't') || (*argv[1] == 'T')){
                             ajanda.dosyaya_yaz(1, argv[2]);
                             ajanda.kapat();
                             return EXIT_SUCCESS;
                                                      }
            //�lgili kelimeye uygun dersleri arar ve ekrana yazd�r�r
            if((*argv[1] == 'd') || (*argv[1] == 'D')){
                        ajanda.arama_ekranayazdir(ajanda.ara(argv[2]) , 2);
                        ajanda.isaretciliste_temizle();
                        ajanda.kapat();
                        return EXIT_SUCCESS;                             
                                                     }
            else{
                cout << "Yanlis parametre girisi" << endl;
                ajanda.kapat();
                return EXIT_FAILURE; 
                }
                
                 }                                    
    if(argc == 2){
            //Tum listeyi ekrana yazd�r�r
            if((*argv[1] == 'h') || (*argv[1] == 'H')){
                              isaretci_dugum *islem;
                              islem = ajanda.hepsinilistele();
                              ajanda.arama_ekranayazdir(islem , 2);
                              ajanda.isaretciliste_temizle();
                              ajanda.kapat();
                              return EXIT_SUCCESS;
                                                       }
            //Bitis tarihi gecenleri ekrana yazd�r�r                                           
            if((*argv[1] == 'b') || (*argv[1] == 'B')){
                              isaretci_dugum *islem;
                              islem = ajanda.hepsinilistele();                              
                              ajanda.zamanagorelistele(islem, 1, 0);
                              ajanda.kapat();
                                                      }
            else{
                cout << "Yanlis parametre girisi" << endl;
                ajanda.kapat();
                return EXIT_FAILURE;
                }                 
                 }
    //Arg�mans�z �al��t�rma                     
    if(argc == 1){
         bool bitir = false;
         char secim;
         while(!bitir){
                  menu_yazdir();
                  cin >> secim;
                  bitir = islem_yap(secim);
                  }
         ajanda.kapat();
         return EXIT_SUCCESS;
                }           
}

void menu_yazdir(){
	system("clear"); 
	cout << endl << endl;
	cout << "Odev Planlayici Uygulamasi" << endl;
	cout << "Bir islem seciniz" << endl;
	cout << "A: Kayit Arama" << endl;
	cout << "D: Kayit Guncelleme" << endl;
    cout << "E: Kayit Ekleme" << endl;
    cout << "H: Hepsini Listele" << endl;
    cout << "S: Kayit Silme" << endl;	
	cout << "T: Hepsini Sil" << endl;
    cout << "Z: Zamana gore listele" << endl;
    cout << "C: Cikis" << endl;	
	cout << endl;
	cout << "Bir secenek giriniz {A, D, E, H, S, T, Z, C} : ";	
}

bool islem_yap(char secim){
	bool sonlandir=false;
	switch (secim) { 
	    case 'A': case 'a': 
			kayit_ara();
			break; 
		case 'D': case 'd':
             duzenle();
             break;
        case 'E': case 'e': 
			kayit_ekle();
			break; 
        case 'H': case 'h':
             tumunulistele();
             break;
        case 'S': case 's': 
			kayit_sil();
			break;
		case 'T': case 't':
            ajanda.listebosalt();
            cout << "Ajanda bosaltilmistir. " << endl; 
            getchar();
            break; 
        case 'Z': case 'z':
             zamanagore_listele();
             break;
        case 'C': case 'c': 
			cout << "Programi sonlandirmak istediginize emin misiniz? (E/H):";
			cin >> secim;
			if(secim=='E' || secim=='e')
				sonlandir=true; 
				break; 
		default: 
			cout << "Hata: Yanlis giris yaptiniz" << endl; 
			cout << "Tekrar deneyiniz {A, E, H, S, T, C} :" ;
			cin >> secim;
			sonlandir = islem_yap(secim);
			break; 
	}
	return sonlandir;
}

void kayit_ara(){
    isaretci_dugum *islem;
    char ad[DERS_AD_UZUNLUK];
	cout << "Lutfen aramak istediginiz isle ilgili dersin adini giriniz:" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,DERS_AD_UZUNLUK);		
    islem = ajanda.ara(ad);    
    if(islem == NULL){
		cout << "Aradiginiz kriterlere uygun kayit bulunamadi" << endl;
        getchar();
        return;      
                     }
    else
        ajanda.arama_ekranayazdir(islem , 2);
    ajanda.isaretciliste_temizle();
    getchar();
};

void kayit_ekle(){
	char dersad[DERS_AD_UZUNLUK];	
	char isad[IS_UZUNLUK];
	int tarih[5];
    cout << "Lutfen kaydetmek istediginiz dersin ve isin bilgilerini giriniz" << endl;
	cout << "Dersin Adi : " ;	
	cin.ignore(1000, '\n');
    cin.getline(dersad,DERS_AD_UZUNLUK);
    cout << "Yapilmasi gereken isin adi :";
	cin.getline(isad,IS_UZUNLUK);
    cin >> setw(IS_UZUNLUK);
	cout << "Isin bitis tarihini giriniz (gun ay yil) :";
	cin >> setw(3) >> tarih[0] >> tarih[1] >> tarih[2];
    cout << "Isin bitis saatini giriniz (saat dakika) :";
    cin >> setw(2) >> tarih[3] >> tarih[4];
    ajanda.ekle(dersad, isad, tarih);
    cout << "Kaydiniz eklenmistir" << endl;
    getchar();
    getchar();
};

void kayit_sil(){
	int ajandasilsecim;
    int sonuc;
    isaretci_dugum *islem;//i�aret�i listesinin baslang�c�n� tutmak i�in i�aret�i
    int isaretci_sayac = 0;//Bulunan kay�tlar i�in sayac
    bool BREAK_KONTROL = false;// Kullan�c�n�n girdi�i kay�d�n e�le�memi� olmas� durumuyla ilgili bir de�i�ken
    char ad[DERS_AD_UZUNLUK];
	int secim;	
	char tercih;// Kullan�c�dan evet/hay�r giri�i almak i�in de�i�ken
    cout << "Tek bir isi silmek istiyorsaniz 1'e bir dersle ilgili tum isleri silmek istiyorsaniz 2'ye basiniz: ";
    cin >> ajandasilsecim;
    
    cout << "Lutfen kaydini silmek istediginiz isle ilgili dersin adini giriniz:" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,DERS_AD_UZUNLUK);		
    islem = ajanda.ara(ad); //Kay�tlar kontrol ediliyor
    sonuc = ajanda.arama_ekranayazdir(islem , ajandasilsecim);                        	
	                       
	
        if (sonuc == 1 && ajandasilsecim == 1){		     
		    cout << "Is bulundu." << endl;
			cout << "Bu isi silmek istediginize emin misiniz? (E/H):";
			cin >> tercih;
            if(tercih == 'E' || tercih == 'e'){
		        ajanda.sil(islem->kayitsirasi, 1);
		        ajanda.isaretciliste_temizle();
                cout << "Is silindi." << endl;                              
                getchar();
                                              }
                                               }
        if(sonuc == 1 && ajandasilsecim == 2){
		    cout << "Ders bulundu." << endl;
			cout << "Bu dersle ilgili tum isleri silmek istediginize emin misiniz? (E/H):";
			cin >> tercih;
            if(tercih == 'E' || tercih == 'e'){
                ajanda.sil(islem->derssira, 0);
		        ajanda.isaretciliste_temizle();
                cout << "Ders silindi." << endl;                              
                getchar();                              
                                              }
                                             }                 
        //Girilen siran�n e�le�ip e�le�medi�ini kontrol etmek i�in
        isaretci_dugum *tarama;
        tarama = islem;
        
        if (sonuc == 0 && ajandasilsecim == 1){
                  cout << "Silmek istediginiz isin numarasini giriniz (Islem yapmadan cikmak icin -1 giriniz): ";
                  cin >> secim;
                  if(secim == -1)
                      return;
                  while(tarama != NULL){
                     if(tarama->kayitsirasi == secim){                      
                         ajanda.sil(secim , 1);
                         BREAK_KONTROL = true;
                         cout << "Is silindi" <<endl;
                         ajanda.isaretciliste_temizle();//i�aret�i listesi siliniyor
                         break;                          
                                                     }
                     tarama = tarama->sonraki;
                                       }  		
             // Kullan�c�n girdi�i kay�t no arama sonucunda bulunmam��sa uyar� mesaj� yazd�r�l�yor
             if(BREAK_KONTROL == false)
                 cout << "Girdiginiz no bulunmamaktadir. Lutfen tekrar deneyiniz..." << endl; 
                                              }                      
        if (sonuc == 0 && ajandasilsecim == 2){
                  cout << "Silmek istediginiz dersin numarasini giriniz (Islem yapmadan cikmak icin -1 giriniz): ";
                  cin >> secim;
                  if(secim == -1)
                      return;
                  while(tarama != NULL){
                     if(tarama->derssira == secim){                      
                         ajanda.sil(secim , 0);
                         BREAK_KONTROL = true;
                         cout << "Ders silindi" <<endl;
                         ajanda.isaretciliste_temizle();//i�aret�i listesi siliniyor
                         break;                          
                                                  }
                     tarama = tarama->sonraki;
                                       }  		
             // Kullan�c�n girdi�i kay�t no arama sonucunda bulunmam��sa uyar� mesaj� yazd�r�l�yor
             if(BREAK_KONTROL == false)
                 cout << "Girdiginiz no bulunmamaktadir. Lutfen tekrar deneyiniz..." << endl; 
                                              }         
    getchar();
};

void tumunulistele(){
     isaretci_dugum *islem;
     islem = ajanda.hepsinilistele();
     ajanda.arama_ekranayazdir(islem , 2);
     ajanda.isaretciliste_temizle();
     getchar();
     getchar();
};

void zamanagore_listele(){
     int secim;
     int limit = 0;//Bitis tarihi gecenleri listelemek icin ilk deger 0 d�r
     isaretci_dugum *islem;
     islem = ajanda.hepsinilistele();
     cout << "Aramak istediginiz zaman dilimini seciniz: " << endl;
     cout << "1) Bitis tarihi gecenleri listele" << endl;
     cout << "2) Belli bir aydan az olanlari listele " << endl;
     cout << "3) Belli bir gunden az olanlari listele" << endl;
     cout << "Seciminizi giriniz: " ;
     cin >> secim;
     cout << endl;
     if(secim != 1){
              cout << "Listelemek istediginiz surenin ust limitini giriniz: ";
              cin >> limit;
                  }
     ajanda.zamanagorelistele(islem, secim, limit);
     ajanda.isaretciliste_temizle();             
     getchar();
     getchar();       
};

void duzenle(){
     char dersad[DERS_AD_UZUNLUK];	
     char isad[IS_UZUNLUK];
     int tarih[5];
     isaretci_dugum *islem;
     bool BREAK_KONTROL = false;// Kullan�c�n�n girdi�i kay�d�n e�le�memi� olmas� durumuyla ilgili bir de�i�ken
     char ad[DERS_AD_UZUNLUK];
     int secim;
     int sonuc;
     char tercih;// Kullan�c�dan evet/hay�r giri�i almak i�in de�i�ken     
    
     cout << "Lutfen kaydini guncellemek istediginiz isle ilgili dersin adini giriniz:" << endl;
	 cin.ignore(1000, '\n');
	 cin.getline(ad,DERS_AD_UZUNLUK);		
     islem = ajanda.ara(ad); //Kay�tlar kontrol ediliyor
     sonuc = ajanda.arama_ekranayazdir(islem , 1);
     
     if (sonuc == 1 ){		     
         cout << "Is bulundu." << endl;
         cout << "Bu isi guncellemek istediginize emin misiniz? (E/H):";
		 cin >> tercih;
         if(tercih == 'E' || tercih == 'e'){
		        ajanda.sil(islem->kayitsirasi, 1);
	            cout << "Dersin Adi : " ;	
	            cin.ignore(1000, '\n');
                cin.getline(dersad,DERS_AD_UZUNLUK);
                cout << "Yapilmasi gereken isin adi :";
	            cin.getline(isad,IS_UZUNLUK);
                cin >> setw(IS_UZUNLUK);
	            cout << "Isin bitis tarihini giriniz (gun ay yil) :";
	            cin >> setw(3) >> tarih[0] >> tarih[1] >> tarih[2];
                cout << "Isin bitis saatini giriniz (saat dakika) :";
                cin >> setw(2) >> tarih[3] >> tarih[4];
                ajanda.ekle(dersad, isad, tarih);		        
                ajanda.isaretciliste_temizle();                            
                cout << "Kaydiniz duzenlenmistir. " << endl;
                                              }
                    }
     if(sonuc == 0){
             isaretci_dugum *tarama;
             tarama = islem;
                  cout << "Duzenlemek istediginiz isin numarasini giriniz (Islem yapmadan cikmak icin -1 giriniz): ";
                  cin >> secim;
                  if(secim == -1)
                      return;
                  while(tarama != NULL){
                     if(tarama->kayitsirasi == secim){                      
                         ajanda.sil(secim , 1);
                         BREAK_KONTROL = true;
        	             cout << "Dersin Adi : " ;	
	                     cin.ignore(1000, '\n');
                         cin.getline(dersad,DERS_AD_UZUNLUK);
                         cout << "Yapilmasi gereken isin adi :";
	                     cin.getline(isad,IS_UZUNLUK);
                         cin >> setw(IS_UZUNLUK);
	                     cout << "Isin bitis tarihini giriniz (gun ay yil) :";
	                     cin >> setw(3) >> tarih[0] >> tarih[1] >> tarih[2];
                         cout << "Isin bitis saatini giriniz (saat dakika) :";
                         cin >> setw(2) >> tarih[3] >> tarih[4];
                         ajanda.ekle(dersad, isad, tarih);
                         ajanda.isaretciliste_temizle();//i�aret�i listesi siliniyor
                         cout << "Kaydiniz duzenlenmistir. " << endl;
                         break;                          
                                                     }
                     tarama = tarama->sonraki;
                                       }  		
             // Kullan�c�n girdi�i kay�t no arama sonucunda bulunmam��sa uyar� mesaj� yazd�r�l�yor
             if(BREAK_KONTROL == false)
                 cout << "Girdiginiz no bulunmamaktadir. Lutfen tekrar deneyiniz..." << endl;
                 }
    getchar();
    getchar();
};                           
                                                       
                                              


                             
