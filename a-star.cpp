#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cstddef>
#include <cmath>
#include <windows.h>
#include <cstdlib>
#include <iomanip>
using namespace std;

int celX = 9;
int celY = 19;
int wym2=20;
int wym1=20;
int stX = 8;
int stY = 1;

class Obiekt
{
public:
    int pozX;
    int pozY;
    //Obiekt *rodzic;
    int rodzicX=0;
    int rodzicY=0;
    int g=0;
    double h;
    double f;
    bool odblokowany=true;//na starcie odblokowany
    int jakaLista=0; //0==bez przypisania 1==otwarta 2==zamknieta
    string droga = "0";
};
Obiekt tablicaOb[20][20];
//void UstawRodzica(Obiekt obiektR, Obiekt *obiektS)
//{
//    obiektS->rodzic = &obiektR;
//    //obiektS.rodzicY = obiektR;
//}

void ObliczF(Obiekt *obiekt) {
    obiekt->h=sqrt((obiekt->pozX-celX)*(obiekt->pozX-celX)+(obiekt->pozY-celY)*(obiekt->pozY-celY));
    obiekt->f=obiekt->g+obiekt->h;//niejawny int na double
};

bool SprawdzOtw()
{
int najmniejsza = 9999;
int x=0;
int y=0;
int licznik=0;
for(int i=0;i<wym2;i++)
 {
  for(int j=0;j<wym1;j++)
   {
        if (tablicaOb[i][j].f<=najmniejsza && tablicaOb[i][j].jakaLista==1)
        {
            najmniejsza = tablicaOb[i][j].f;
            x = i;
            y = j;
            licznik++;
        }
   }
 }
if (tablicaOb[x][y].pozX == celX && tablicaOb[x][y].pozY == celY )
{
    return true;
}
if (licznik==0)
{
    return false;
}

tablicaOb[x][y].jakaLista=2;
tablicaOb[x][y].odblokowany = false;
if (x+1<wym2&&tablicaOb[x+1][y].odblokowany==true)
{

    tablicaOb[x+1][y].jakaLista=1;
    tablicaOb[x+1][y].g=tablicaOb[x][y].g+1;
    ObliczF(&tablicaOb[x+1][y]);
    tablicaOb[x+1][y].rodzicX=x;
    tablicaOb[x+1][y].rodzicY=y;
    tablicaOb[x+1][y].droga="?";
}
if (x-1>0&&tablicaOb[x-1][y].odblokowany==true)
{

    tablicaOb[x-1][y].jakaLista=1;
    tablicaOb[x-1][y].g=tablicaOb[x][y].g+1;
    ObliczF(&tablicaOb[x-1][y]);
    tablicaOb[x-1][y].rodzicX=x;
    tablicaOb[x-1][y].rodzicY=y;
    tablicaOb[x-1][y].droga="?";
}
if (y+1<wym1&&tablicaOb[x][y+1].odblokowany==true)
{

    tablicaOb[x][y+1].jakaLista=1;
    tablicaOb[x][y+1].g=tablicaOb[x][y].g+1;
    ObliczF(&tablicaOb[x][y+1]);
    tablicaOb[x][y+1].rodzicX=x;
    tablicaOb[x][y+1].rodzicY=y;
    tablicaOb[x][y+1].droga="?";
}
if (y-1>0&&tablicaOb[x][y-1].odblokowany==true)
{

    tablicaOb[x][y-1].jakaLista=1;
    tablicaOb[x][y-1].g=tablicaOb[x][y].g+1;
    ObliczF(&tablicaOb[x][y-1]);
    tablicaOb[x][y-1].rodzicX=x;
    tablicaOb[x][y-1].rodzicY=y;
    tablicaOb[x][y-1].droga="?";
}

SprawdzOtw();
}

bool WyswietlRozw(int x, int y)
{
//    cout<<"\n"<<tablicaOb[x][y].rodzicX;
//    cout<<"\n"<<tablicaOb[x][y].rodzicY;
    int a = tablicaOb[x][y].rodzicX;
    int b = tablicaOb[x][y].rodzicY;
    if (a==stX && b==stY)
    {
        return true;
    }
    tablicaOb[a][b].droga="X";
    WyswietlRozw(a, b);
}


int main (void) {

//Obiekt startowy;
//startowy.pozX = 0;
//startowy.pozY = 0;
HANDLE hOut;
hOut = GetStdHandle( STD_OUTPUT_HANDLE );
cout<<"Wczytywanie danych z pliku\n";
string nazwap="grid.txt";

//teraz deklarujemy dynamicznie tablice do, której wczytamyu nasz plik,
int rows = wym2+1;
double **G;
G = new double*[rows];
while(rows--) G[rows] = new double[wym1+1];
cout<<"\n\nNacisnij ENTER aby wczytac tablice o nazwie "<< nazwap;
getchar();
std::ifstream plik(nazwap.c_str());
for ( unsigned int i=0;i<wym2;i++)
  {
    for ( unsigned int j=0;j<wym1;j++)
    {
         plik >> G[i][j];
         tablicaOb[i][j].pozX=i;
         tablicaOb[i][j].pozY=j;
         if (G[i][j] == 5)
             {
                 tablicaOb[i][j].odblokowany=false;
                 tablicaOb[i][j].droga="#";
             }
         //cout<<tablicaOb[i][j].pozX<<tablicaOb[i][j].pozY<<"\n";
    }
  }
plik.close();

cout<<"\nWypisujemy na ekran\n\n";
for(int i=0;i<wym2;i++)
 {
  for(int j=0;j<wym1;j++)
   {
    cout<<" "<<G[i][j];
   }cout<<"\n";
 }
//na koniec czyœcimy pamiêæ po naszej tablicy
for(int i=0;i<wym2+1;i++)
{delete[] G[i];}//czyscimy wiersze
delete[] G;//zwalniamy tablice wskaznikow do wierszy

//cout << tablicaOb[0][0].odblokowany;
//cout << tablicaOb[1][3].odblokowany;

cout<<"\n\nNacisnij ENTER aby zakonczyc\n";

//tworze poczatkowy element startowy
tablicaOb[stX][stY].jakaLista=1;
ObliczF(&tablicaOb[stX][stY]);

//cout<<"\n"<<tablicaOb[0][0].f;

if (SprawdzOtw())
{
    cout<<"Znaleziono rozwiazanie\n";
    tablicaOb[stX][stY].droga="S";
    tablicaOb[celX][celY].droga="C";
    WyswietlRozw(celX,celY);

    for(int i=0;i<wym2;i++)
     {
      for(int j=0;j<wym1;j++)
       {
            cout<< " ";
            if(tablicaOb[i][j].droga=="#")
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_RED );
            }
            if(tablicaOb[i][j].droga=="X")
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN );
            }
            if(tablicaOb[i][j].droga=="0")
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN );
            }
            if(tablicaOb[i][j].droga=="?")
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_BLUE );
            }
            if(tablicaOb[i][j].droga=="C" || tablicaOb[i][j].droga=="S")
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE );
            }
            cout << tablicaOb[i][j].droga<< flush;
       }
       cout<<"\n";
     }
}
else
{
    cout<<"Nie znaleziono rozwiazania\n";
    for(int i=0;i<wym2;i++)
    {
      for(int j=0;j<wym1;j++)
       {
            cout<< " ";
            if(tablicaOb[i][j].droga=="#")
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_RED );
            }
            if(tablicaOb[i][j].droga=="X")
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN );
            }
            if(tablicaOb[i][j].droga=="0")
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN );
            }
            if(tablicaOb[i][j].droga=="?")
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_BLUE );
            }
            if(tablicaOb[i][j].droga=="C" || tablicaOb[i][j].droga=="S")
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE );
            }
            cout << tablicaOb[i][j].droga;
       }
       cout<<"\n";
    }
}
SetConsoleTextAttribute( hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN );
cout<<"\nWartosci f\n";
for(int i=0;i<wym2;i++)
    {
      for(int j=0;j<wym1;j++)
       {
            cout<< " ";
            if(tablicaOb[i][j].f==0)
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN );
                cout << "0.000";
            }
            if((tablicaOb[i][j].f<10) && (tablicaOb[i][j].f>0))
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN );
                cout << fixed << setprecision(3) << tablicaOb[i][j].f;
            }
            if (tablicaOb[i][j].f>=10)
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN );
                 cout << fixed << setprecision(2) << tablicaOb[i][j].f;
            }
       }
       cout<<"\n";
    }
getchar();
return 0;
}
