#include <bits/stdc++.h>
bool zawiera(std::pair<float, float> a, std::pair<float, float> b, std::pair<float, float> c){      //sprawdza czy punkt lezy po prawej czy lewej stronie prostej
    if((a.second*b.first+b.second*c.first+c.second*a.first-c.second*b.first-a.second*c.first-b.second*a.first)<0) return false;
    return true;
}
std::vector<std::pair<float, float> > obwod(std::vector<std::pair<float, float> > dane){        
	std::vector<std::pair<float, float> > wynik;
	float min_x=std::numeric_limits<float>::max();
    int m;
	for(int i=0; i<dane.size(); i++){       //znajduje punkt z najmniejszym x
		if(min_x>dane[i].first){
			min_x=dane[i].first;
			m=i;
		}
		if(min_x==dane[i].first){       //jesli jest wiecej niz jeden z najmniejszym x wybiera ten o mnijeszym y
			if(dane[m].second>dane[i].second)
                m=i;
        }
	}    
	wynik.push_back(dane[m]);       //punkt z najmniejszym x jest czescia otoczki
	std::vector<std::pair<float, int> >ws_kier;         
	for(int i=0; i<dane.size(); i++){       //tworzy wektor wyznacznikow kierunkowych
		if(i==m) i++;
        if(dane[i].first==dane[m].first){
            ws_kier.push_back(std::make_pair(0, i));
        }
		else
            ws_kier.push_back(std::make_pair(((dane[i].second-dane[m].second)/(dane[i].first-dane[m].first)), i));
	}
	sort(ws_kier.begin(), ws_kier.end());       //sortuje wektor od najmniejszego (najnizej) do najwiekszego (najwyzej)
    for(int i=1; i<ws_kier.size(); i++){        //jezeli wystepuje wiecej niz jeden identyczny wspolczynnik kierunkowy usuwa punkt z mniejsza odlegloscia od poczatku ukladu 
        if(ws_kier[i].first==ws_kier[i-1].first){
            if(sqrt(pow(dane[ws_kier[i].second].first, 2)+pow(dane[ws_kier[i].second].second, 2))>sqrt(pow(dane[ws_kier[i-1].second].first, 2)+pow(dane[ws_kier[i-1].second].second, 2)))
                ws_kier.erase(ws_kier.begin()+i-1);
            else
                ws_kier.erase(ws_kier.begin()+i);
        }
    }
    wynik.push_back(dane[ws_kier[0].second]);       //algorytm Grahama
    wynik.push_back(dane[ws_kier[1].second]);
    for(int i=2; i<ws_kier.size(); i++){
        if(zawiera(wynik[wynik.size()-2], wynik[wynik.size()-1], dane[ws_kier[i].second]))
            wynik.pop_back();
        wynik.push_back(dane[ws_kier[i].second]);
    }
	return wynik;
}
int main(){
	std::vector<std::pair<float, float> > dane, wynik;
    std::fstream in;
    int il;
    float a, b;
    in.open("dane.txt");
    in>>il;             //wczytanie danych
    while(in>>a){
        in>>b;
        dane.push_back(std::make_pair(a,b));
    }
    in.close();
    while(il<dane.size())       //sprawdza czy nie pobral wiecej punktow niz zakladano
        dane.pop_back();
	if(dane.size()!=0)          //sprawdza czy dane zostaly pobrane
        wynik=obwod(dane);
    for(int i=0; i<wynik.size(); i++){     //wypisuje wynik
    	std::cout<<wynik[i].first<<" "<<wynik[i].second<<std::endl;
    }
	return 0;
}