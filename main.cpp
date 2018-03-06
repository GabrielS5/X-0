
#include <SFML/Graphics.hpp>
#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct XsiO
{
    int tabla[3][3];
    int prob[3][3];
    bool Player;
    bool Bot;
};
int difi=100,laturapatrat=100;

void init(XsiO &Joc)
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            Joc.tabla[i][j]=-1;
    Joc.Player=1;
    Joc.Bot=0;
}
int ProbLinie(XsiO Joc,int i,int inam, int prie)
{
    int inamic=0,prieten=0;
    for(int j=0; j<3; j++)
    {
        if(Joc.tabla[i][j]==prie)
            prieten++;
        if(Joc.tabla[i][j]==inam)
            inamic++;
    }

    if(prieten==2)
        return difi;
    if(inamic==2)
        return difi/2;
    if(prieten==1 && inamic==0)
        return difi/10;
    return 1;

}


int ProbColoana(XsiO Joc,int j,int inam, int prie)
{
    int inamic=0,prieten=0;
    for(int i=0; i<3; i++)
    {
        if(Joc.tabla[i][j]==prie)
            prieten++;
        if(Joc.tabla[i][j]==inam)
            inamic++;
    }

    if(prieten==2)
        return difi;
    if(inamic==2)
        return difi/2;
    if(prieten==1 && inamic==0)
        return difi/10;
    return 1;

}

int ProbDiagonala(XsiO Joc,int j,int i,int inam, int prie)
{
    int inamic=0,prieten=0;

    if(i!=j && i+j!=2)
        return 0;
    if(i==j)
    {
        int k=0;
        for(int l=0; l<3; l++)
        {
            if(Joc.tabla[l][k]==prie)
                prieten++;
            if(Joc.tabla[l][k]==inam)
                inamic++;
            k++;
        }
    }
    else
    {
        int k=0;
        for(int l=2; l>=0; l--)
        {
            if(Joc.tabla[l][k]==prie)
                prieten++;
            if(Joc.tabla[l][k]==inam)
                inamic++;
            k++;
        }
    }


    if(prieten==2)
        return difi;
    if(inamic==2)
        return difi/2;
    if(prieten==1 && inamic==0)
        return difi/10;
    return 1;
}
void Afisare(int v[3][3])
{
    cout<<endl;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
            cout<<v[i][j]<<" ";
        cout<<endl;
    }

}

int Posibilitate(XsiO Joc,int i,int j,int inam,int prie)
{
    return ProbLinie(Joc,i,inam,prie)+ProbColoana(Joc,j,inam,prie)+ProbDiagonala(Joc,j,i,inam,prie);

}


void AlegereBot(XsiO &Joc,int &linieAleasa,int &coloanaAleasa,int alegere)
{

    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
            alegere=alegere-Joc.prob[i][j];
            if(alegere<=0)
            {
                linieAleasa=i;
                coloanaAleasa=j;
                i=j=3;
            }
        }
}

void MutareBot(XsiO &Joc,int inam,int prie)
{
    int suma=0,alegere,linieAleasa,coloanaAleasa;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
            if(Joc.tabla[i][j]==-1)
            {
                Joc.prob[i][j]=Posibilitate(Joc,i,j,inam,prie);
                suma=suma+Joc.prob[i][j];
            }
            else Joc.prob[i][j]=0;
        }
    alegere=rand()%suma+1;

    AlegereBot(Joc,linieAleasa,coloanaAleasa,alegere);
    Joc.tabla[linieAleasa][coloanaAleasa]=prie;
}

int updateGrafica(XsiO Joc,sf::RectangleShape rectangle[3][3])
{
    int i,j,poInaltime=0,poLatime=0;
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            rectangle[i][j].setSize(sf::Vector2f(laturapatrat, laturapatrat));
            rectangle[i][j].setOutlineColor(sf::Color::Black);
            rectangle[i][j].setOutlineThickness(-2);
            if(Joc.tabla[i][j]==-1)
            {
                rectangle[i][j].setFillColor (sf::Color(200,200,200));
            }
            if(Joc.tabla[i][j]==1)
            {
                rectangle[i][j].setFillColor (sf::Color(70,200,80));
            }
            if(Joc.tabla[i][j]==0)
            {
                rectangle[i][j].setFillColor (sf::Color(210,60,60));
            }
            rectangle[i][j].setPosition(poLatime,poInaltime);
            poLatime=poLatime+laturapatrat;
        }
        poLatime=0;
        poInaltime=poInaltime+laturapatrat;
    }
}

void Switch(XsiO &Joc)
{
    Joc.Player=(Joc.Player+1)%2;
    Joc.Bot=(Joc.Bot+1)%2;
}

int victorie(XsiO Joc)
{
    int termen,contor=0;
    for(int i=0; i<3; i++)
    {
        termen=Joc.tabla[i][0];
        for(int j=0; j<3; j++)
        {
            if(termen==Joc.tabla[i][j] && termen!=-1)
                contor++;
        }
        if(contor==3)
            return termen;
        contor=0;
    }
    for(int i=0; i<3; i++)
    {
        termen=Joc.tabla[0][i];
        for(int j=0; j<3; j++)
        {
            if(termen==Joc.tabla[j][i] && termen!=-1)
                contor++;
        }
        if(contor==3)
            return termen;
        contor=0;
    }

    if(Joc.tabla[0][0]==Joc.tabla[1][1] && Joc.tabla[1][1]==Joc.tabla[2][2])
        return Joc.tabla[0][0];
    if(Joc.tabla[0][2]==Joc.tabla[1][1] && Joc.tabla[1][1]==Joc.tabla[2][0])
        return Joc.tabla[2][0];


    return -1;
}

void Joaca(XsiO Joc,sf::RectangleShape rectangle[3][3],int single)
{
    int Continua=1,c,l,terminat=0,coloana,linia,tastaApasata=0,mutari=0;
    sf::RenderWindow win(sf::VideoMode(laturapatrat*3,laturapatrat*3), "X si O");
    while (win.isOpen())
    {
        win.clear();
        updateGrafica(Joc,rectangle);
        for(int i=0; i<3; i++)
            for(int j=0; j<3; j++)
                win.draw(rectangle[i][j]);
        win.display();
        if(victorie(Joc)!=-1)
        {
            cin>>c;
            cout<<"A castigat ";
            if(victorie(Joc)==1)
                cout<<"Player 1";
            else
                cout<<"Player 2";
            win.close();
            terminat=1;
            break;
        }
        else if(mutari==9)
        {
            cin>>c;
            cout<<"Egalitate";
            win.close();
            terminat=1;
            break;
        }
        sf::Event eveniment;
        while (win.pollEvent(eveniment) && !terminat)
        {
            if (eveniment.type == sf::Event::Closed)
                win.close();
            else if (eveniment.type == sf::Event::MouseButtonPressed)
            {
                if (eveniment.mouseButton.button == sf::Mouse::Left)
                {
                    coloana=eveniment.mouseButton.x/laturapatrat;
                    linia=eveniment.mouseButton.y/laturapatrat ;
                    tastaApasata=1;
                }
            }
        }
        if(Joc.Player && (tastaApasata || single==2))
        {
            if(single==2)
            {
                MutareBot(Joc,0,1);
                Switch(Joc);
                tastaApasata=0;
                mutari++;
            }
            else
            {
                Joc.tabla[linia][coloana]=1;
                Switch(Joc);
                tastaApasata=0;
                mutari++;
            }
        }
        else

            if(Joc.Bot && single && !Joc.Player)
            {
                MutareBot(Joc,1,0);
                Switch(Joc);
                tastaApasata=0;
                mutari++;
            }
            else if(!Joc.Player && tastaApasata && !single)
            {
                Joc.tabla[linia][coloana]=0;
                Switch(Joc);
                tastaApasata=0;
                mutari++;

            }
    }
}


int main()
{
    int i=1,maiJoci=1,single;
    sf::RectangleShape rectangle[3][3];
    srand(time(NULL));
    XsiO Joc;
    init(Joc);
    cout<<endl<<" PvP-0    PvBOT-1   BOTvBOT-2   ";
    cin>>single;
    while(maiJoci)
    {
        init(Joc);
        Switch(Joc);
        Joaca(Joc,rectangle,single);
        cout<<endl<<"Mai Joci? ";
        cin>>maiJoci;
    }
    return 0;
}
