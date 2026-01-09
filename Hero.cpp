#include <iostream>
#include <string>
using namespace std; 


class Hero {
protected :
    string nom; 
    int pv, attaque, defense, vitesse; 
    
public :

    Hero() : nom(""), pv(0), attaque(0), defense(0), vitesse(0){}

    Hero(string nom, int pv, int attaque, int defense, int vitesse) {
        this->nom = nom;
        this->pv = pv;
        this->attaque = attaque;
        this->defense = defense;
        this->vitesse = vitesse; 
    }

    //Destructeur virtuel de Hero
    virtual ~Hero() {}

    void afficherStats() const {
        cout << nom << " PV : "<< pv<<" Attaque : "<<attaque<<" Defense : "<< defense<< " Vitesse : "<<vitesse<<endl; 
    }

    virtual int getClasse() const = 0; 

    virtual int calculerDegats(const Hero& cible) const = 0;

    virtual void perdrePV(int montant) {
        pv -= montant;
        if (pv < 0) {
            pv = 0; 
        }
    };

    virtual void effetDebutTour() {};

    virtual void effetFinTour() {}; 

    //Fonction pour savoir si le hero est vivant ou non
    bool estVivant() const {
        return pv > 0; 
    }


}; 