#define DERS_AD_UZUNLUK 20
#define IS_UZUNLUK 30

//Derslerle ilgili i�leri tutan d���m
struct Is_dugum{
       char is[IS_UZUNLUK];
       int tarih[5];//0. elamandan 4. elemana  kadar gun,ay,yil,saat,dakika de�erlerini tutan dizi
       Is_dugum *sonraki;
                };
//Dersleri tutan d���m
struct Ders_dugum{
       char ders[DERS_AD_UZUNLUK];
       Ders_dugum *sonraki;
       Is_dugum *isptr;
                 };
//Listeyi dosyaya kaydederken kullan�lan d���m
struct Dosya_Kayit{
       char ders[DERS_AD_UZUNLUK];
       char is[IS_UZUNLUK];
       int tarih[5];
                  };
//arama yap�ld���nda bulunanlarla ilgili i�lemlerin yap�ld��� liste i�in dugum
struct  isaretci_dugum{
        int kayitsirasi;//isaretci listesi i�leri tuttu�u i�in i�lerin sayac�
        int derssira;//Derslerin sayac�
        int issayac;//Bir dersin i�inin sayac�
        char ders[DERS_AD_UZUNLUK];
        int kalansure[5];//Biti� tarihine kalansureyi tutan dizi
        Is_dugum *bulunan;
        isaretci_dugum *sonraki;
                       };                                   
