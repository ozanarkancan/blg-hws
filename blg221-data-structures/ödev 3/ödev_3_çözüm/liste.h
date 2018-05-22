#ifndef LISTE_H
#define LISTE_H
#include <stdio.h>
#include "dugum.h"

struct Liste{
	Tel_dugum *bas;
	int dugumsayisi;
	void olustur();
	void kapat();
	void listebosalt();
	void ekle(Tel_dugum *);
	Liste_isaretci* ara(char *);
	void sil(int kayitno);
	void guncelle(int kayitno, Tel_dugum *);
};
#endif
