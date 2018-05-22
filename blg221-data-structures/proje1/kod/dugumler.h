#define DERS_AD_UZUNLUK 20
#define IS_UZUNLUK 30

//Derslerle ilgili iþleri tutan düðüm
struct Is_dugum{
       char is[IS_UZUNLUK];
       int tarih[5];//0. elamandan 4. elemana  kadar gun,ay,yil,saat,dakika deðerlerini tutan dizi
       Is_dugum *sonraki;
                };
//Dersleri tutan düðüm
struct Ders_dugum{
       char ders[DERS_AD_UZUNLUK];
       Ders_dugum *sonraki;
       Is_dugum *isptr;
                 };
//Listeyi dosyaya kaydederken kullanýlan düðüm
struct Dosya_Kayit{
       char ders[DERS_AD_UZUNLUK];
       char is[IS_UZUNLUK];
       int tarih[5];
                  };
//arama yapýldýðýnda bulunanlarla ilgili iþlemlerin yapýldýðý liste için dugum
struct  isaretci_dugum{
        int kayitsirasi;//isaretci listesi iþleri tuttuðu için iþlerin sayacý
        int derssira;//Derslerin sayacý
        int issayac;//Bir dersin iþinin sayacý
        char ders[DERS_AD_UZUNLUK];
        int kalansure[5];//Bitiþ tarihine kalansureyi tutan dizi
        Is_dugum *bulunan;
        isaretci_dugum *sonraki;
                       };                                   
