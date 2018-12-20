/* 
 * File:   main.cpp
 * Author: tp
 *
 * Created on 15 December 2018, 12:52
 */

#include <cstdlib>

/* Standard Input / Output Streams Library */
#include <iostream>

/* RANDOM "srand(time(0));" */
#include <random> 
#include <ctime>
//#include <algorithm> //sort


/* array:n lisäominaisuudet */
//#include <array>
//#include <bits/stdc++.h>
using namespace std;

/*
 * Lottoarvonta:
 * 39 numeroa
 * 7 oikein voittaa päävoiton
 * 
 * arvotaan:
 * 7 + 3 numeroa
 * 
 * Palkintosummat:
 * 5    24 000€
 * 5+1  30 240€
 * 6    62 000€
 * 6+1  69 000€
 * 7    920 000€
 */

const int MAX_NUM = 39; //maksimi määrä arvottavia numeroita 1-x (normaali on 39)
const int NUMEROT = 7; //arvottavat numerot, sama määrä myös arvassa
const int LISA_NUMEROT = 3; //arvottavat lisänumerot
const int YHT = NUMEROT + LISA_NUMEROT; //Yhteismäärä numerot + lisänumerot

/* Pelaajat */
const int PELAAJAT = 1; //Kasvattamalla tätä lisätään pelaajien määrää
const int ARVAT_PER_PELAAJA = 4; //Arvat (per pelaaja)

/* Luo random numeron väliltä 1- (MAX_NUM, 39) */
int random() {
    return rand() % MAX_NUM + 1;
}

/* Tarkistaa löytyykö arvottu luku jo listasta */
bool onkoListassa(int* arr, int r) {
    for (int i = 0; i < YHT; i++) {
        if (arr[i] == r) {
            //Löytyi listasta, palauttaa true
            return true;
        }
    }
    //Ei löytynyt listasta, palauttaa false
    return false;
}

/* Uusi arpa pelaajalle/kierrokselle */
int* arpa(int koko) {

    int* arr = new int[koko];
    for (int i = 0; i < koko; i++) {
        int r = random();
        if (onkoListassa(arr, r)) { //Tarkistetaan löytyykö listasta, jos ei niin lisätään listaan
            //Palataan yksi askel taakseppäin, jotta uuden numeron luonti onnistuu
            i--;
        } else {
            arr[i] = r;
        }
    }
    return arr;
}

/* Lajittelee parametrina annetun array:n pienimmästä suurimpaan */
int* sort(int* arr, int koko) {
    int temp = 0;
    for (int i = 0; i < koko; i++) {
        for (int j = i + 1; j <= koko; j++) {
            //Kaikki negatiiviset arvot (ja nolla) ei oteta huomioon (näin ei pitäsi käydä)
            if (arr[i] <= 0 || arr[j] <= 0) {
                continue;
            }
            if (arr[j] < arr[i]) {
                //Vahdetaan järjestystä
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    /* Palautetaan takaisin parametrina annettu array
     * sortattuna pienimmästä suurimpaan */
    return arr;
}

/* Tulostaa listan sisällön */
int tulosta(int* arr, int koko) {
    for (int i = 0; i < koko; ++i) {
        cout << arr[i] << ' ';
    }
    //cout << endl;
    return 0;
}

/* Tulostaa kuinka monta meni oikein ja kertoo jos tuli voitto */
int tulikoVoittoa(int * pelaajanArpalista, int * lottoNumerot, int * lisaNumerot) {
    //parametrinä tulee (pelaajan arpalista, lottonumerot, lisänumerot)
    int oikein = 0;
    int lisanumeroOikein = 0;


    /* Käydään läpi kaikki listat (lisaNumerot, arr2, arr3) ja tarkistetaan menikö oikein */
    for (int i = 0; i < NUMEROT; i++) {
        for (int j = 0; j < YHT; j++) {
            if (pelaajanArpalista[i] == lottoNumerot[j]) {
                oikein++;
            }
        }
        for (int kierros = 0; kierros < LISA_NUMEROT; kierros++) {
            if (pelaajanArpalista[i] == lisaNumerot[kierros]) {
                lisanumeroOikein++;
            }
        }
    }

    /* Tulostaa kuinka monta meni oikein ja voittosumman */
    if (oikein >= 5) {
        cout << "Oikein oli: " << oikein <<endl;
        if (oikein == 5) {
            if (lisanumeroOikein >= 1) {
                cout << "+lisänumero oikein!" << endl;
                cout << "Voitit: 30 240€!";
            } else {
                cout << "Voitit: 24 000€!";
            }
            
        }
        if (oikein == 6) {
            if (lisanumeroOikein >= 1) {
                cout << "+lisänumero oikein!" << endl;
                cout << "Voitit: 69 000€!";
            } else {
                cout << "Voitit: 62 000€!";
            }
        }
        if (oikein == 7) {
            cout << "Päävoitto! Oikein kaikki seitsemän!" << endl;
            cout << "voitit 920 000€!";
        }
        
    } else {
        cout << "Oikein oli: " << oikein << endl;
        cout << "Ei voittoa.";
    }
    cout << endl<< endl;
    return 0;
}

int main(int argc, char** argv) {
    srand(time(0)); //Luvuille "seed" ajan perusteella

    int* kierros = arpa(YHT); //Uusi kierros;
    //static int lottoNumerot[NUMEROT]; //lottonumerot 1-7
    int* lottoNumerot = new int[NUMEROT];
    //static int lisaNumerot[LISA_NUMEROT]; //lottonumerot 8-10 (lisänumerot)
    int* lisaNumerot = new int[LISA_NUMEROT];
    
    /* Tallennetaan numerot omiin arrayhin */
    for (int i = 0; i < NUMEROT; i++) {
        int numero = kierros[i];
        lottoNumerot[i] = numero;
    }
    /* Tallennetaan numerot omiin arrayhin */
    for (int i = 0; i < LISA_NUMEROT; i++) {
        int numero = kierros[NUMEROT + i];
        lisaNumerot[i] = numero;
    }
    cout << "Lottonumerot:" << endl;
    int* s_lottoNumerot = sort(lottoNumerot, NUMEROT); //SORT
    tulosta(s_lottoNumerot, NUMEROT); //Tulostaa parametrinä annetun listan vatii (listan,listankoon)
    cout << endl;
    cout << "Lisänumerot:" << endl ;
    int* s_lisaNumerot = sort(lisaNumerot, LISA_NUMEROT); //SORT
    tulosta(s_lisaNumerot, LISA_NUMEROT); //Tulostaa parametrinä annetun listan vatii (listan,listankoon)
    cout << endl;
    /* Luodaan pelaajille arvat */
    for (int i = 0; i < PELAAJAT; i++) {
        cout << endl;
        cout << "Pelaaja " << i + 1 << ": " << endl;
        for (int j = 0; j < ARVAT_PER_PELAAJA; j++) {
            cout << "Arpa " << j + 1 << ": ";
            int* Arpa = arpa(NUMEROT); //Arvotaan pelaajalle arpa
            int* s_pelaajanArpalista = sort(Arpa, NUMEROT);
            tulosta(s_pelaajanArpalista, NUMEROT);
            /*
            for (int k = 0; k < NUMEROT; k++) {
                cout << s_pelaajanArpalista[k] << " ";
            }*/
            cout << endl;
            
            //(pelaajan arpalista, lottonumerot, lisänumerot)
            tulikoVoittoa(s_pelaajanArpalista, s_lottoNumerot, s_lisaNumerot); 
        }
    }
    //system("pause");
    return EXIT_SUCCESS;
}




