#include "liste.h"
#include <iostream>
#include <stdlib.h>

#include <string.h>


using namespace std;


// BU KODLAR SLAYTLARDAN...
void Liste::ekle(Tel_dugum *eklenecek){
	Tel_dugum *tara, *arka;
	Tel_dugum *yeni;
	
	tara = bas;
	yeni = new Tel_dugum;
	*yeni = *eklenecek;
	yeni->sonraki = NULL;
	
	if(bas == NULL){
        bas = yeni;
        dugumsayisi++;
        return;
    }
    if(strcmp(yeni->ad, bas->ad) <= 0){ //BURADA <= GUNCELLEMESI VAR AKSI TAKDIRDE SIKINTI OLUYOR
        yeni->sonraki = bas;
        bas = yeni;
        dugumsayisi++;
        return;
    }
    while(tara && (strcmp(yeni->ad, tara->ad) > 0)){
        arka = tara;
        tara = tara->sonraki;
    }
    if(tara){
        yeni->sonraki = tara;
        arka->sonraki = yeni;
    }
    else
        arka->sonraki = yeni;
    dugumsayisi++;            
}

void Liste::olustur(){	
	bas = NULL;
	dugumsayisi = 0;
}

void Liste::kapat(){
     listebosalt();
	
}

Liste_isaretci* Liste::ara(char *aranacak){
	Tel_dugum *tara;
	int sayac = 0;
	bool tumu = false;
	tara = bas;
	Liste_isaretci *baslangic=NULL;
	
	if(strcmp(aranacak,"*") == 0)
		tumu = true;
		
	while(tara)
    {
		sayac++;
        
        if(tumu)
		{
			Liste_isaretci *yeni=new Liste_isaretci;
			yeni->isaretci=tara;
            yeni->sonraki=NULL;
			yeni->sira = sayac;

			// DONDURULECEK DUGUMDE KAYITLAR YA EN BASTA BASA EKLENIR (BAS = NULL iken)
			// YA DA SONA EKLENIR!!!
            if(baslangic==NULL)
                baslangic=yeni;
			else
			{
				Liste_isaretci *tmp = baslangic;
				while(tmp->sonraki)
					tmp = tmp->sonraki;
				tmp->sonraki  = yeni;
			}
        }
		
        else if(strnicmp(tara->ad, aranacak, strlen(aranacak)) > 0) break; // 1.ÞIKKIN ÇÖZÜMÜ
        
        else if(strnicmp(tara->ad, aranacak, strlen(aranacak)) == 0)
        {
            Liste_isaretci *yeni=new Liste_isaretci;
			yeni->isaretci=tara;
            yeni->sonraki=NULL;
			yeni->sira = sayac;
			
            if(baslangic==NULL)
                baslangic=yeni;
			else
			{
				Liste_isaretci *tmp = baslangic;
				while(tmp->sonraki)
					tmp = tmp->sonraki;
				tmp->sonraki  = yeni;
			}
       }
	   tara = tara->sonraki;
    }          	
	return baslangic;
}

void Liste::guncelle(int kayitno, Tel_dugum *yeni){
	Tel_dugum *tara;
	int sayac = 1;
	tara = bas;
	while(tara && (sayac < kayitno)){
        sayac++;
        tara = tara->sonraki;
    }
    if(tara){
        yeni->sonraki = tara->sonraki;
        *tara = *yeni;
    }
    else
        cout << "Guncellenecek kayit numarasi hatali."<< endl;
        
}


void Liste::sil(int sirano)
{
	Tel_dugum *tara, *arka;	
	int sayac = 1;
	tara = bas;
	if(sirano <= 0)
	{
        cout << "Hatali kayit sira numarasi" << endl;
        return;
    }
    if(sirano == 1)
	{
        bas = bas->sonraki;
        delete tara;
        dugumsayisi--;
        return;
    }
    while(tara!=NULL && (sayac < sirano))
	{
        arka = tara;
        tara = tara->sonraki;
        sayac++;
    }
    if(sayac < sirano)
	{
        cout<<"Silinecek kayit bulunamadi."<< endl;
    }
    else
	{
         arka->sonraki = tara->sonraki;
         delete tara;
         dugumsayisi--;
    }             
}

void Liste::listebosalt(){
     Tel_dugum *p;
     while(bas){
         p = bas;
         bas = bas->sonraki;
         delete p;
     }
     dugumsayisi=0;
}    