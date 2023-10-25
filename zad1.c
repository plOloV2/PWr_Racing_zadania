#define _USE_MATH_DEFINE
#include <stdio.h>
#include <math.h>
float ust_wartosc=3;        //argumenty funkcji 
float delta_t=1;
float Kp=1;
float Ki=1;
float Kd=1;

float pop_blad=0;
float pop_cal=0;
float odczyt_war=0;
float PID(){            //kontroler PID
    float wyjscie, blad;
    blad=ust_wartosc-odczyt_war;
    wyjscie=Kp*blad+Ki*(pop_cal+blad*delta_t)+Kd*((blad-pop_blad)/delta_t);
    pop_blad=blad;
    printf("%.3f\n\n", wyjscie);
    if(wyjscie>5)       //ograniczenie wartowsci wyjsciowych
        wyjscie=5;
    else if(wyjscie<-5)
        wyjscie=-5;
    return wyjscie;
}
float obiekt(float sterowanie){     //emulacja obiektu
    float e=M_E, wynik;
    wynik=1-pow(e,(-sterowanie/10));
    return wynik;
}
int main(){             //petla wywolujaca funkcje
    for (int i=0; i<50; i++){
        printf("%.3f\n", odczyt_war);
        float syg_ster=obiekt(PID());
        odczyt_war+=syg_ster;
    }
    return 0;
}