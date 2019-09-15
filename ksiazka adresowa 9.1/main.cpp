#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include<conio.h>

using namespace std;

struct Adresat
{
    int id=0;
    string imie ="", nazwisko="", numerTelefonu="", email="", adres="";
};

vector<Adresat>adresaci;

vector<Adresat> zapisanieDanychZLiniiDoWektoraGlownego(vector<string> wektorZPliku)
{
    Adresat wczytanaOsoba[1];
    string linia ="";
    string tablicaPomocnicza[6];
    for (vector<string>::iterator itr = wektorZPliku.begin(); itr != wektorZPliku.end(); ++itr)
    {
        linia = *itr;
        string jedenWyraz="";
        int licznik=0;

        for(short i=0; i < linia.length(); i++)
        {
            if(linia[i] != '|')
            {
                jedenWyraz+=linia[i];
            }
            else if (linia[i] == '|' || i==linia.length()-1)
            {
                tablicaPomocnicza[licznik] = jedenWyraz;
                jedenWyraz = "";
                licznik++;
            }
        }
        wczytanaOsoba[0].id = atoi(tablicaPomocnicza[0].c_str());
        wczytanaOsoba[0].imie = tablicaPomocnicza[1];
        wczytanaOsoba[0].nazwisko = tablicaPomocnicza[2];
        wczytanaOsoba[0].numerTelefonu = tablicaPomocnicza[3];
        wczytanaOsoba[0].email = tablicaPomocnicza[4];
        wczytanaOsoba[0].adres = tablicaPomocnicza[5];

        adresaci.push_back(wczytanaOsoba[0]);
    }
    return adresaci;
}

int policzOsobyWPliku (vector<Adresat>)
{
    int iloscOsob=0;

    if (adresaci.empty() == true)
        iloscOsob=0;
    else
        iloscOsob = adresaci.back().id;

    return iloscOsob;
}

int dodajOsobe(int ile)
{
    int iloscOsob=0;
    Adresat osoba[1];
    iloscOsob=ile;

    string imie, nazwisko, numerTelefonu, email, adres;

    system("cls");
    cout << "Dodawanie osoby" << endl;
    cout << "Podaj imie uzytkownika: ";
    cin >> imie;
    cout << "Podaj nazwisko uzytkownika: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu uzytkownika: ";
    cin.sync();
    getline(cin, numerTelefonu);
    cout << "Podaj email uzytkownika: ";
    cin >> email;
    cout << "Podaj adres uzytkownika: ";
    cin.sync();
    getline(cin, adres);

    int osobaId = iloscOsob + 1;

    osoba[0].id = osobaId;
    osoba[0].imie = imie;
    osoba[0].nazwisko = nazwisko;
    osoba[0].numerTelefonu = numerTelefonu;
    osoba[0].email = email;
    osoba[0].adres = adres;

    adresaci.push_back(osoba[0]);

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    if (plik.good())
    {
        plik << osobaId << "|";
        plik << imie << "|";
        plik << nazwisko << "|";
        plik << numerTelefonu << "|";
        plik << email << "|";
        plik << adres << "|" << endl;

        plik.close();

        cout << "Osoba zostala dodana." << endl;
        Sleep(1000);
    }
    if (plik.good()==false)
    {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
    iloscOsob++;
    return iloscOsob;
}

void szukanieImion (vector<Adresat>, string szukaneImie)
{
    for( std::vector<Adresat>::iterator itr = adresaci.begin(); itr < adresaci.end(); ++itr)
    {
        if(itr->imie == szukaneImie)
        {
            cout << itr->id << endl;
            cout << itr->imie << endl;
            cout << itr->nazwisko << endl;
            cout << itr->numerTelefonu << endl;
            cout << itr->email << endl;
            cout << itr->adres << endl;
            cout << endl << "******" << endl;
        }
    }
}

void szukanieNazwisk (vector<Adresat>, string szukaneNazwisko)
{
    for( std::vector<Adresat>::iterator itr = adresaci.begin(); itr < adresaci.end(); ++itr)
    {
        if(itr->nazwisko == szukaneNazwisko)
        {
            cout << itr->id << endl;
            cout << itr->imie << endl;
            cout << itr->nazwisko << endl;
            cout << itr->numerTelefonu << endl;
            cout << itr->email << endl;
            cout << itr->adres << endl;
            cout << endl << "******" << endl;
        }
    }
}

int usuwanieAdresata (vector<Adresat>, int usuwaneID, int ile)
{
    int iloscOsob = ile;
    int numerLiniiDoUsunieciaZPliku;

    for( std::vector<Adresat>::iterator itr = adresaci.begin(); itr < adresaci.end(); ++itr)
    {
        if(itr->id == usuwaneID)
        {
            if (adresaci.back().id == usuwaneID)
            {
                adresaci.erase(itr);
                iloscOsob = policzOsobyWPliku(adresaci);
            }
            else
            {
               adresaci.erase(itr);
            }
            int index = std::distance(adresaci.begin(), itr);

            system("pause");

            fstream plik;
            plik.open("KsiazkaAdresowa.txt", ios::out);
            for( std::vector<Adresat>::iterator itr = adresaci.begin(); itr < adresaci.begin() + (index); ++itr)
            {
                plik << itr->id << "|";
                plik << itr->imie << "|";
                plik << itr->nazwisko << "|";
                plik << itr->numerTelefonu << "|";
                plik << itr->email << "|";
                plik << itr->adres << "|" << endl;
            }
            for( std::vector<Adresat>::iterator itr = adresaci.begin() + (index); itr < adresaci.end(); ++itr)
            {
                plik << itr->id << "|";
                plik << itr->imie << "|";
                plik << itr->nazwisko << "|";
                plik << itr->numerTelefonu << "|";
                plik << itr->email << "|";
                plik << itr->adres << "|" << endl;
            }
            plik.close();

            cout << endl << "WYBRANY ADRESAT ZOSTAL USUNIETY" << endl;
            Sleep(500);
        }
    }
    return iloscOsob;
}

void edycjaKontaktu (vector<Adresat>, int edytowaneID)
{
    char wybor;
    string noweImie ="", noweNazwisko ="", nowyNumerTelefonu ="", nowyEmail ="", nowyAdres= "";
    int index=0;

    cout << endl << "CO CHCESZ EDYTOWAC?" << endl << endl;
    cout << "1. Imie" << endl;
    cout << "2. Nazwisko" << endl;
    cout << "3. Numer telefonu" << endl;
    cout << "4. Email" << endl;
    cout << "5. Adres" << endl;
    cout << "6. Powrot do menu glownego" << endl;
    cout << endl << "Twoj wybor: ";
    cin >> wybor;
    cout << endl;

    for( std::vector<Adresat>::iterator itr = adresaci.begin(); itr < adresaci.end(); ++itr)
    {
        if(itr->id == edytowaneID)
            index = std::distance(adresaci.begin(), itr);
    }
    if (wybor == '1')
    {
        cout << "Podaj nowe imie: ";
        cin >> noweImie;
        adresaci[index].imie = noweImie;
    }
    else if (wybor == '2')
    {
        cout << "Podaj nowe nazwisko: ";
        cin >> noweNazwisko;
        adresaci[index].nazwisko = noweNazwisko;
    }
    else if (wybor == '3')
    {
        cout << "Podaj nowy numer telefonu: ";
        cin.sync();
        getline(cin, nowyNumerTelefonu);
        adresaci[index].numerTelefonu = nowyNumerTelefonu;
    }
    else if (wybor == '4')
    {
        cout << "Podaj nowy adres email: ";
        cin >> nowyEmail;
        adresaci[index].email = nowyEmail;
    }
    else if (wybor == '5')
    {
        cout << "Podaj nowy adres: ";
        cin.sync();
        getline(cin, nowyAdres);
        adresaci[index].adres = nowyAdres;
    }
    else if (wybor == '6')
    {
        ;
    }

    for( std::vector<Adresat>::iterator itr = adresaci.begin(); itr < adresaci.end(); ++itr)
    {
        fstream plik;
        plik.open("KsiazkaAdresowa.txt", ios::out);

        for( std::vector<Adresat>::iterator itr = adresaci.begin(); itr < adresaci.end(); ++itr)
        {
            plik << itr->id << "|";
            plik << itr->imie << "|";
            plik << itr->nazwisko << "|";
            plik << itr->numerTelefonu << "|";
            plik << itr->email << "|";
            plik << itr->adres << "|" << endl;
        }
        plik.close();
    }
}

int main()
{
    int iloscOsob = 0;
    char wybor;
    string szukane_imie, szukane_nazwisko;
    vector<string> nierozdzielonaLinia;
    string linia="";
    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::in);

    if (plik.good()==false)
    {
        cout << "NIE MOZNA OTWORZYC PLIKU: KsizkaAdresowa.txt" << endl;
        Sleep(400);
    }
    if (plik.good()==true)
    {
        while (getline(plik, linia))
        {
            nierozdzielonaLinia.push_back(linia);
        }
        zapisanieDanychZLiniiDoWektoraGlownego(nierozdzielonaLinia);
        iloscOsob = policzOsobyWPliku(adresaci);
    }

    while (true)
    {
        system("cls");
        cout << "KSIAZKA ADRESOWA" << endl << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;

        cout << endl << "Twoj wybor: ";
        cin >> wybor;

        if (wybor == '1')
        {
            iloscOsob = dodajOsobe(iloscOsob);
        }

        else if (wybor == '2')
        {
            system("cls");
            cout << "Podaj imie do wyszukania: ";
            cin >> szukane_imie;

            szukanieImion(adresaci, szukane_imie);
            system("pause");

        }
        else if (wybor == '3')
        {
            system("cls");
            cout << "Podaj nazwisko do wyszukania: ";
            cin >> szukane_nazwisko;

            szukanieNazwisk(adresaci, szukane_nazwisko);
            system("pause");
        }
        else if (wybor == '4')
        {
            system("cls");
            for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); ++itr)
            {
                cout << itr->id << endl;
                cout << itr->imie << endl;
                cout << itr->nazwisko << endl;
                cout << itr->numerTelefonu << endl;
                cout << itr->email << endl;
                cout << itr->adres << endl;
                cout << endl << "******" << endl;
            }
            system("pause");
        }
        else if (wybor == '5')
        {
            system("cls");
            int usuwaneID=0;
            cout << "Podaj numer ID adresata, ktorego chcesz usunac z Ksiazki Adresowej: ";
            cin >> usuwaneID;
            cout << "DANE ADRESATA ZOSTANA CALKOWICIE WYMAZANE! POTWIERDZ SWOJA DECYZJE! (t/n)";
            char znak;
            znak = getch();
            if ( (znak != 't') && (znak !='n') )
                cout << "Wcisnij klawisz 't' lub klawisz 'n'!" << endl;
            if ( (znak == 't') || (znak =='n') )

                switch (znak)
                {
                case 't':
                    iloscOsob = usuwanieAdresata(adresaci, usuwaneID, iloscOsob);
                case 'n':
                    break;
                }
            system("pause");
        }
        else if (wybor == '6')
        {
            system("cls");
            int edytowaneID=0;
            cout << "Podaj numer ID adresata, ktorego dane chcesz edytowac: ";
            cin >> edytowaneID;

            edycjaKontaktu(adresaci, edytowaneID);
        }
        else if (wybor == '9')
        {
            exit(0);
        }
    }
    return 0;
}



