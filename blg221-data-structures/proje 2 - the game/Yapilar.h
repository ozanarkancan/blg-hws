struct karakter{
       char *irk;
       char *saldiri_tipi;
       int strength;
       int intelligence;
       int hit_point;
       int saldiri_gucu;
       int luck;
       bool ekipman[4]; 
       int elmas_cantasi;
       };

struct dusman{
       char *irk;
       char *saldiri_tipi;
       int strength;
       int intelligence;
       int hit_point;
       int saldiri_gucu;
       dusman *sonraki;
       int tur;       
       };

struct hucre{
       int yukari;
       int asagi;
       int sol;
       int sag;
       hucre *sonraki;
       bool durum; // Labirent oluştururken ziyaret edilip edilmediğini kontrol etmek için değişken
       char karakter_burda;
       int satir;
       int sutun;
       int gelinenyon;
       char ozellik; // Elmas veya portal
       };              

struct Kuyruk{
           void olustur();
           void kapat();
           dusman *Kuyruk_bas;
           dusman *Kuyruk_son;
           void ekle(dusman *);
           void yazdir();
           };

struct Yigin{
           void olustur();
           void kapat();
           hucre *Yigin_bas;       
           void push(hucre *);
           hucre *pop();
           };           
