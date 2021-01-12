#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <windows.h>

using namespace std;
clock_t start, stop;
double t1, t2, t3;
int N;
int *tab = new int[N];

//Funkcja sortujaca algorytmem sortowania przez wstawianie
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        //Przenoszenie elementow ciagu wiekszych od klucza jedna pozycje dalej od ich aktualnej pozycji
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

//funkcja sortujaca algorytmem sortowania kopcowego

// torzenie kopca
void heapify(int arr[], int n, int i)
{
    int largest = i; //  najwiekszy zostaje korzeniem
    int l = 2 * i + 1; // lewy = 2*i + 1
    int r = 2 * i + 2; // prawy = 2*i + 2

    // Jesli lewe "dziecko" jest wieksze od korzenia
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // Jesli prawe dziecko jest wieksze
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // Jesli najwiekszy nie jest korzeniem
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Rekurencyjne sortuj poddrzewo
        heapify(arr, n, largest);
    }
}

// glowna funkcja sortowania kopcowego
void heapSort(int arr[], int n)
{
    // Budowanie kopca (zmiana rozmieszczenia tablicy)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Wyodrebnianie kolejnych elemwntow kopca
    for (int i = n - 1; i > 0; i--)
    {
        // Przoszecznie biezacego korzenia na koniec
        swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

//zapis do pliku
void printResults(int arr[], int n)
{
    ofstream plik("wyniki.txt"); //otwarcie pliku w celu zapisania w nim rozwiazan
    plik<<"Czas sortowania: "<<t3<<" s" <<endl;
    for (int i = 0; i < n; i++)
        plik<< arr[i] << " ";
        plik<< "\n";
        plik.close();
}

//testy programu

void test_1() //czas wykonywania algorytmu w przypadku, kiedy ciag jest posortowany rosn¹co
{
    int N;
    cout << "Ile elementow ma posiadac tablica? ";
    cin >> N;
    while(cin.fail() || N<=0)
    {
        cout << "Blad! podaj poprawna liczbe!" << endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> N;
    }

    int *tab = new int[N];
    srand(time(NULL));
        for (int i=0; i<N; i++)
        {
            tab[i]=rand()%101; //losujemy liczby z zakresu od 0 do 100
        }
    heapSort (tab,N); //sortowanie wylosowanej tablicy

    ofstream plik("test_1.txt"); //otwarcie pliku w celu zapisania w nim rozwiazan
    plik<<"Sortowanie uporzadkowanego ciagu o d³ugoœci: "<<N<<endl;
    int ilosc_testow;
    cout << "Ile prob ma zostac wykonane? ";
    cin >> ilosc_testow;

     for (int i=0; i<ilosc_testow; i++)
    {
        cout<<endl<<"Proba nr. "<<i+1<<endl;
        //sortowanie przez wstawianie
        cout<<"Trwa sortowanie przez wstawianie..."<<endl;
        start = clock();
        insertionSort (tab, N);
        stop = clock();
        t1=(double)(stop-start)/CLOCKS_PER_SEC;
        cout << "Czas sortowania przez wstawianie: "<<t1<<" s" <<endl<<endl;

        //sortowanie kopcowe
        cout<<"Trwa sortowanie kopcowe..."<<endl;
        start = clock();
        heapSort (tab,N);
        stop = clock();
        t2=(double)(stop-start)/CLOCKS_PER_SEC;
        cout << "Czas sortowania kopcowego: "<<t2<<" s" <<endl<<endl;

        plik << "Proba nr. "<<i+1<<endl<<endl;
        plik << "Czas sortowania przez wstawianie: "<<t1<<" s"<< endl;
        plik << "Czas sortowania kopcowego: "<<t2<<" s"<< endl<<endl;
    }

    plik.close();
}

void test_2() //czas wykonywania algorytmu w przypadku, kiedy ciag jest posortowany malejaco
{
    //odczytywanie danych z pliku

    int B[20000]= {0};
    int n = 20000;
    fstream z;
    z.open("test2_plik(20000).txt",ios::in);

    /*int B[100000]= {0};
    int n = 100000;
    fstream z;
    z.open("test2_plik(100000).txt",ios::in);*/

    /*int B[200000]= {0};
    int n = 200000;
    fstream z;
    z.open("test2_plik(200000).txt",ios::in);*/

    /*int B[300000]= {0};
    int n = 300000;
    fstream z;
    z.open("test2_plik(300000).txt",ios::in);*/

    if(!z) //jesli nie uda sie otworzyc pliku
    {
        cout<<"Nie udalo sie otworzyc pliku";
        getchar();
    }

    while (!z.eof())
        z>>B[n++];

    ofstream plik("test_2.txt"); //otwarcie pliku w celu zapisania w nim rozwiazan

    //czas sortowania przez wstawianie
    cout<<"Trwa sortowanie przez wstawianie..."<<endl;
    start = clock();
    insertionSort(B, n);
    stop = clock();
    t1=(double)(stop-start)/CLOCKS_PER_SEC;
    cout << "Czas sortowania przez wstawianie: "<<t1<<" s" <<endl<<endl;

    //czas sortowania kopcowego
    cout<<"Trwa sortowanie kopcowe..."<<endl;
    start = clock();
    heapSort(B, n);
    stop = clock();
    t2=(double)(stop-start)/CLOCKS_PER_SEC;
    cout << "Czas sortowania kopcowego: "<<t2<<" s" <<endl<<endl;

    plik << "Czas sortowania przez wstawianie: "<<t1<<" s"<< endl;
    plik << "Czas sortowania kopcowego: "<<t2<<" s"<<endl<<endl;

    plik.close();
}

void test_3() //czas wykonywania algorytmu w przypadku losowego ciagu
{
    int N;
    cout << "Ile elementow ma posiadac tablica? ";
    cin >> N;

    while(cin.fail() || N<=0)
    {
        cout << "Blad! podaj poprawna liczbe!" << endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> N;
    }

    int *tab = new int[N];

    ofstream plik("test_3.txt"); //otwarcie pliku w celu zapisania w nim rozwiazan
     plik << "Sortowanie ci¹gu liczb o d³ugoœci: " <<N<<endl;

    int ilosc_testow;
    cout << "Ile prob ma zostac wykonane? ";
    cin >> ilosc_testow;

     for (int i=0; i<ilosc_testow; i++)
    {
        srand(time(NULL));
        for (int i=0; i<N; i++)
        {
            tab[i]=rand()%101; //losujemy liczby z zakresu od 0 do 100
        }

        cout<<endl<<"Proba nr. "<<i+1<<endl;
        //sortowanie przez wstawianie
        cout<<"Trwa sortowanie przez wstawianie..."<<endl;
        start = clock();
        insertionSort (tab, N);
        stop = clock();
        t1=(double)(stop-start)/CLOCKS_PER_SEC;
        cout << "Czas sortowania przez wstawianie: "<<t1<<" s" <<endl<<endl;

        //sortowanie kopcowe
        cout<<"Trwa sortowanie kopcowe..."<<endl;
        start = clock();
        heapSort (tab,N);
        stop = clock();
        t2=(double)(stop-start)/CLOCKS_PER_SEC;
        cout << "Czas sortowania kopcowego: "<<t2<<" s" <<endl<<endl;

        plik << "Proba nr. "<<i+1<<endl<<endl;
        plik << "Czas sortowania przez wstawianie: "<<t1<<" s"<< endl;
        plik << "Czas sortowania kopcowego: "<<t2<<" s"<< endl<<endl;
    }

    plik.close();
    delete [] tab;
}

int main()
{
    cout<<"1 - Test 1 - Tablica posortowana"<<endl<<endl;
    cout<<"2 - Test 2 - Tablica posortowana odwrotnie"<<endl<<endl;
    cout<<"3 - Test 3 - Tablica zlozona z liczb losowych"<<endl<<endl;
    cout<<"4 - Sortowanie przez wstawianie - Liczby z pliku"<<endl<<endl;
    cout<<"5 - Sortowanie kopcowe - Liczby z pliku"<<endl<<endl;

    int opcja;
    cout<<"Wybierz opcje: ";
    cin>>opcja;

    switch (opcja)
    {
    case 1:
        test_1();
        break;

    case 2:
        test_2();
        break;

    case 3:
        test_3();
        break;

    case 4:
        {
            int t[50000]= {0};
            int n = 50000;
            fstream z;
            z.open("plik.txt",ios::in); //odczytywanie danych z pliku

            if(!z) //jesli nie uda sie otworzyc pliku
            {
                cout<<"Nie udalo sie otworzyc pliku";
                getchar();
                return 1;
            }
            while (!z.eof())
                z>>t[n++];

            z.close();

            cout<<"Trwa sortowanie przez wstawianie..."<<endl;
            start = clock();
            insertionSort(t, n);
            stop = clock();
            t3=(double)(stop-start)/CLOCKS_PER_SEC;
            cout << endl << "Czas sortowania przez wstawianie: "<<t3<<" s" <<endl;

            printResults(t, n);

        }
        break;

    case 5:
        {
            int  t[50000]= {0};
            int n = 50000;
            fstream z;
            z.open("plik.txt",ios::in); //odczytywanie danych z pliku

            if(!z) //jesli nie uda sie otworzyc pliku
            {
                cout<<"Nie udalo sie otworzyc pliku";
                getchar();
                return 1;
            }
            while (!z.eof())
                z>>t[n++];

            z.close();

            cout<<"Trwa sortowanie kopcowe..."<<endl;
            start = clock();
            heapSort(t, n);
            stop = clock();
            t3=(double)(stop-start)/CLOCKS_PER_SEC;
            cout << endl << "Czas sortowania kopcowego: "<<t3<<" s" <<endl;

            printResults(t, n);

        }
    }

    getch();
    return 0;
}

