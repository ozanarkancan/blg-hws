#include "dosyaislemleri.h"
#include <iostream>
#include <stdlib.h>

#include <string.h>


using namespace std;



void Dosya::ekle(Tel_Kayit *ykptr){
	fseek(teldefteri, 0, SEEK_END);
	fwrite(ykptr, sizeof(Tel_Kayit), 1, teldefteri);
}

void Dosya::olustur(){	
	dosyaadi="teldefteri.txt";
	teldefteri = fopen( dosyaadi, "r+" );
	if(!teldefteri){		
		if(!(teldefteri = fopen( dosyaadi, "w+" ))){
			cerr << "Dosya acilamadi" << endl;
			exit(1);
		}
	}
}

void Dosya::kapat(){
	fclose(teldefteri);
}

int Dosya::ara(char aranacak[]){
	FILE *yenidosya; // Kay�t s�ralar�n� tutmak i�in a��lacak dosya i�in pointer
    Tel_Kayit k;
	int sayac=0;
	bool tumu=false;
	int bulunan=0;
	if(strcmp(aranacak,"*")==0)
		tumu=true;
	fseek(teldefteri, 0, SEEK_SET);
	yenidosya = fopen("kayitno.txt", "w+"); // Kay�t s�ralar�n� tutmak i�in dosya a��l�yor
    while(!feof(teldefteri)){		
		sayac++;
		fread( &k, sizeof (Tel_Kayit), 1, teldefteri);		
		if(feof(teldefteri)) break;

		if(!tumu && strnicmp(k.ad, aranacak, strlen(aranacak))!=0)
			continue;
		cout << sayac << "." << k.ad << " " << k.telno << endl;
        fprintf(yenidosya ,"%d ",sayac); // Kay�t bulunduk�a dosyaya yaz�l�yor
        bulunan++;
	}	
	fclose(yenidosya);// Kay�t arama i�lemi bitince dosya kapat�l�yor
    return bulunan;
}

void Dosya::guncelle(int kayitno, Tel_Kayit *ykptr){
	if(fseek(teldefteri, sizeof(Tel_Kayit)*(kayitno-1), SEEK_SET)==0)
		fwrite(ykptr, sizeof(Tel_Kayit), 1, teldefteri);
}

void Dosya::sil(int kayitno){
	Tel_Kayit boskayit={"",""};	
	if(fseek(teldefteri, sizeof(Tel_Kayit)*(kayitno-1), SEEK_SET)==0)
		fwrite(&boskayit, sizeof(Tel_Kayit), 1, teldefteri);
}
