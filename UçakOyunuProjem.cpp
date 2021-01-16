/****************************************************************************
** Hüseyin Hıra 2018
** BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
** İlk Projem Uçak Savaş Oyunu
****************************************************************************/



#include<iostream>
#include<Windows.h>
#include<time.h>
#include<cstdlib>


using namespace std;
enum YON //kendi oluşturduğumuz yönleri içeren fonksiyon 
{
	YON_SOL = 1, //oyun içerisinde kullanılmıyor ama yön olarak bulunduğu için kodun içerisinde var
	YON_SAG = 2,
	YON_YUKARI = 3,
	YON_ASAGI = 4
};
struct MermiHucre // merminin  kursördeki yerini ayrladığımız struct
{
	int x;
	int y;

	YON yon;
	char karakter;

};

const int genislik = 80; //kursör sınırlarını belirleyen değer
const int yukseklik = 20;//kursör sınırlarını belirleyen değer

int ucakyeri = 10;
int mermiuzunlugu = 0;
char ekran[genislik][yukseklik];
char tuslar[256];
MermiHucre mermicikis[1];
int dusmanyeri = 80; //düşmanın gelmeye başladığı x kordinatını belirleyen değişken




void gotoxy(int x, int y) //kursörde hareket etmemizi sağlayan fonksiyon
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void kursoruGizle() // ekranda oluşan parlamaları engeleyen fonksiyon
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO      cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);

}




void sahneyiciz() //sahneyi ekrana çizdirmemizi sağlayan fonksiyon
{
	for (int y = 0; y < yukseklik; y++)
	{
		for (int x = 0; x < genislik; x++)
		{
			cout << ekran[x][y];
		}
		cout << endl;
	}
}

void sahneyitemizle() //sahneyi her seferinde yeniden yazdırıp kodun altalta yazmasını engelleyen kısım
{
	for (int y = 0; y < yukseklik; y++)
	{
		for (int x = 0; x < genislik; x++)
		{
			ekran[x][y] = ' ';
		}
	}
}

void sinirlariOlustur()//komut istemindeki sınırları belirleyen kod parçası
{
	for (int x = 0; x < genislik; x++)
	{
		ekran[x][0] = 219;
		ekran[x][yukseklik - 1] = 219;
	}

	for (int y = 0; y < yukseklik; y++)
	{
		ekran[0][y] = 219;
		ekran[genislik - 1][y] = 219;
	}
}

void KlavyeOku(char tuslar[]) //klavyede bastıklarımızı okuyup değerlendiren fonksiyon
{
	for (int x = 0; x < 256; x++)
		tuslar[x] = (char)(GetAsyncKeyState(x) >> 8);
}
void mermiyisahneyeyerlestir() //merminin sahnede görünmesini sağlayan fonksiyon
{
	for (int i = 0; i < mermiuzunlugu; i++)
	{
		int x = mermicikis[i].x;
		int y = mermicikis[i].y;
		ekran[x][y] = '>';

	}
}
void mermiOlustur() // mermiyi oluşturan fonksiyon
{
	mermiuzunlugu = 1;

	mermicikis[0].x = 3;
	mermicikis[0].y = ucakyeri;
	mermicikis[0].yon = YON_SAG;
	mermicikis[0].karakter = '>';

}
void KlavyeKontrol() //klavyeden kendi belirlediğimiz tuşları okuyup çalıştıran fonksiyon
{

	KlavyeOku(tuslar);

	if (tuslar['W'] != 0)
	{
		ucakyeri--;
	}
	if (tuslar['S'] != 0)
	{
		ucakyeri++;
	}
	if (tuslar['F'] != 0)
	{
		mermiOlustur();
	}
}




void mermiyihareketettir() //merminin kursörde kaymasını sağlayan fonksiyon
{
	for (int i = 0; i < mermiuzunlugu; i++)
	{
		switch (mermicikis[i].yon)
		{
		case YON_SAG:
			mermicikis[i].x++;
			break;
		}
	}
}


int main()
{

	kursoruGizle();

	mermiOlustur();



	srand(time(0));
	int rasSayi = rand();
	int i = 0;
	while (true)
	{
		for (int i = 0; i < 79; i++) //düşman sınırlardan çıkınca hata veriyordu onu düzeltmek için uçağın yanına yok olan düşman
		{
			sahneyitemizle();

			ekran[1][ucakyeri - 2] = 219;
			ekran[2][ucakyeri - 1] = 219;
			ekran[3][ucakyeri] = 219;
			ekran[2][ucakyeri + 1] = 219;
			ekran[1][ucakyeri + 2] = 219;

			ekran[dusmanyeri - i][rasSayi & 18 + 2] = 177;
			ekran[dusmanyeri - i][rasSayi & 18 + 3] = 177;


			sinirlariOlustur();
			KlavyeKontrol();

			mermiyihareketettir();

			mermiyisahneyeyerlestir();

			gotoxy(0, 0);
			sahneyiciz();
			Sleep(20); // herşeyin bilgisayar tarafından çok hızlı gerçekleşmesini engellyen kod

		}
		cout << endl << "Ates etmek icin F tusunu kullaniniz";

	}

}