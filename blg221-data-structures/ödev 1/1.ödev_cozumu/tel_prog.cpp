#include <iostream>
#include <stdlib.h>
#include <iomanip>

#include <ctype.h>

#include "dosyaislemleri.h"


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
			cout << "Programi sonlandirmak istediðinize emin misiniz? (E/H):";
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
	char ad[AD_UZUNLUK];
	int secim;	
	cout << "Lutfen kaydini silmek istediginiz kisinin adini giriniz (tum liste için '*'a basiniz):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,AD_UZUNLUK);		
	int *kisisayisi=defter.ara(ad); 
	if(kisisayisi[0]==-1){
		cout << "Aradiginiz kriterlere uygun kayit bulunamadi" << endl;		
	}
	else {
		if (kisisayisi[0]!=-1 && kisisayisi[1]==-1){		
			cout << "Kayit bulundu." << endl;
			defter.sil(kisisayisi[0]);
			cout << "Kayit silindi." << endl;
		}
		else
			cout << "Silmek istediginiz kayidin numarasini giriniz (Islem yapmadan cikmak icin -1 giriniz): " ;
		cin >> secim;
		bool bulundu = false;
		for (int i=0; i<MAXKAYIT; i++)
		{
			if (kisisayisi[i]==secim)
			{
				bulundu=true;
				break;
			}
		}
		if(!bulundu)
		{
			cout << "Yanlis giris" << endl;
			return;
		}
		if(secim==-1 ) return;
		defter.sil(secim);	
		cout << "Kayit silindi" <<endl;
		
	}
	getchar();
};
void kayit_guncelle(){
	char ad[AD_UZUNLUK];
	int secim;	
	cout << "Lutfen kaydini guncellemek istediginiz kisinin adini giriniz (tum liste için '*'a basiniz):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,AD_UZUNLUK);		
	int* kisisayisi=defter.ara(ad); 
	if(kisisayisi[0]==-1){
		cout << "Aradiginiz kriterlere uygun kayit bulunamadi" << endl;		
	}
	else {
		if (kisisayisi[0]!=-1 && kisisayisi[1]==-1){		
			cout << "Kayit bulundu." << endl;
			// KAYIT GUNCELLEME SATIRLARI BURAYA copy-paste
		}
		else
			cout << "Guncellemek istediginiz kayidin numarasini giriniz (Islem yapmadan cikmak icin -1 giriniz): " ;
		cin >> secim;
		bool bulundu = false;
		for (int i=0; i<MAXKAYIT; i++)
		{
			if (kisisayisi[i]==secim)
			{
				bulundu=true;
				break;
			}
		}
		if(!bulundu)
		{
			cout << "Yanlis giris" << endl;
			return;
		}
		if(secim==-1) return;
		Tel_Kayit yenikayit;
		cout << "Lutfen guncel bilgileri giriniz" << endl;
		cout << "Ad : " ;
		cin.ignore(1000, '\n');
		cin.getline(yenikayit.ad,AD_UZUNLUK);
		cout << "Telefon numarasi :";
		cin >> setw(TELNO_UZUNLUK) >> yenikayit.telno;
		defter.guncelle(secim,&yenikayit);	
		cout << "Kaydiniz basariyla guncellendi" <<endl;		
	}
	getchar();
};
