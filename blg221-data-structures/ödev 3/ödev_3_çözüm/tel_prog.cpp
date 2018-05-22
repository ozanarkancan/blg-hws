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
void temizle(); 


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
             temizle();
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
	int k=0;
	cout << "Lutfen aramak istediginiz kisinin adini giriniz (tum liste için '*'a basiniz):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,AD_UZUNLUK);		
	Liste_isaretci* p = defter.ara(ad); 
	Liste_isaretci* tmp = p;
	while (tmp)
	{
		cout << tmp->sira << ". " << tmp->isaretci->ad << " " << tmp->isaretci ->telno <<endl;
		tmp=tmp->sonraki;
		k++;
	}
	if(!p){
		cout << "Aradiginiz kriterlere uygun kayit bulunamadi" << endl;		
	}
	
	// baðlý liste bellekten siliniyor.
	tmp = p;
	while(p)
	{
        tmp = p;
        p = p->sonraki;
        delete tmp;
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
    int k=0;
    int i=0;
    bool bulundu=false;	
	cout << "Lutfen kaydini silmek istediginiz kisinin adini giriniz (tum liste için '*'a basiniz):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,AD_UZUNLUK);		
	Liste_isaretci* p = defter.ara(ad); 
	Liste_isaretci* tmp = p;
	while (tmp)
	{
		cout << tmp->sira << ". " << tmp->isaretci->ad << " " << tmp->isaretci ->telno <<endl;
		tmp=tmp->sonraki;
		k++;
	}
	if(!p)
	{
		cout << "Aradiginiz kriterlere uygun kayit bulunamadi" << endl;		
	}
	else
	{
		if (p && !(p->sonraki))
		{		
			cout << "Kayit bulundu." << endl;
			defter.sil(p->sira);
			cout << "Kayit silindi." << endl;
			return;
		}
		else
			cout << "Silmek istediginiz kayidin numarasini giriniz (Islem yapmadan cikmak icin -1 giriniz): " ;
		cin >> secim;
		if(secim==-1) return;
		tmp=p;
		while(tmp)
		{
            if(tmp->sira ==secim)
                bulundu=true;
            tmp=tmp->sonraki;
        }
		if(bulundu==true){
                          
                          defter.sil(secim);
                cout << "Kayit silindi" <<endl;
            }
            
        else cout<< "yanlis girdiniz."  << endl; 
	}
	tmp = p;
	while(p)
	{
        tmp = p;
        p = p->sonraki;
        delete tmp;
    }
	getchar();
};
void kayit_guncelle(){
	char ad[AD_UZUNLUK];
	int secim;
    int k=0;
    int i=0;
    bool bulundu=false;
    Tel_Kayit yenikayit;	
	cout << "Lutfen kaydini guncellemek istediginiz kisinin adini giriniz (tum liste için '*'a basiniz):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,AD_UZUNLUK);		
	Liste_isaretci* p = defter.ara(ad); 
	Liste_isaretci* tmp = p;
	while (tmp)
	{
		cout << tmp->sira << ". " << tmp->isaretci->ad << " " << tmp->isaretci ->telno <<endl;
		tmp=tmp->sonraki;
		k++;
	}
	if(!p){
		cout << "Aradiginiz kriterlere uygun kayit bulunamadi" << endl;		
	}
	
	else {
		if (p && !(p->sonraki)){		
			cout << "Kayit bulundu." << endl;
			cout << "Lutfen guncel bilgileri giriniz" << endl;
		    cout << "Ad : " ;
		    cin.getline(yenikayit.ad,AD_UZUNLUK);
		    cout << "Telefon numarasi :";
		    cin >> setw(TELNO_UZUNLUK) >> yenikayit.telno;
		    defter.guncelle(p->sira,&yenikayit);	
		    cout << "Kaydiniz basariyla guncellendi" <<endl;
			return;
		}
		else
			cout << "Guncellemek istediginiz kayidin numarasini giriniz (Islem yapmadan cikmak icin -1 giriniz): " ;
		cin >> secim;
		if(secim==-1) return;
		tmp=p;
		while(tmp)
		{
            if(tmp->sira ==secim)
                bulundu=true;
            tmp=tmp->sonraki;
        }
        if(bulundu==true)
		{
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
		else cout << "yanlis sayi girdiniz."	<< endl;	
	}
	tmp = p;
	while(p)
	{
        tmp = p;
        p = p->sonraki;
        delete tmp;
    }
	getchar();
};
void temizle(){ 
    char secim;
    cout << "Telefon defterindeki butun kayitlari silmek istediginize emin misiniz?(E/H)"<< endl;
    cin >> secim;
    if(secim=='E' || secim=='e'){ 
        defter.listebosalt(); 
        cout << "Temizle islemi tamamlandi."<< endl;
    }
    if(secim=='H' || secim=='h')return;
}