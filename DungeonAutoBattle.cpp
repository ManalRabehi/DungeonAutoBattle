#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std; 

class Hero {
protected :
    string nom; 
    int pv, pvMax, attaque, defense, vitesse; 
    
public :

    Hero() : nom(""), pv(0), pvMax(0), attaque(0), defense(0), vitesse(0){}

    Hero(string nom, int pv, int attaque, int defense, int vitesse) {
        this->nom = nom;
        this->pv = pv;
        this->pvMax = pv;
        this->attaque = attaque;
        this->defense = defense;
        this->vitesse = vitesse; 
    }

    virtual ~Hero() {}

    void afficherStats() const {
        cout << nom << " PV : " << pv
             << " Attaque : " << attaque
             << " Defense : " << defense
             << " Vitesse : " << vitesse << endl; 
    }

    virtual int getClasse() const = 0; 
    virtual int calculerDegats(const Hero& cible) const = 0;

    virtual void perdrePV(int montant) {
        pv -= montant;
        if (pv < 0) pv = 0; 
    }

    virtual void effetDebutTour() {}
    virtual void effetFinTour() {} 

    bool estVivant() const {
        return pv > 0; 
    }

    int getDefense() const { return defense; }
    int getAttaque() const { return attaque; }
    int getVitesse() const { return vitesse; }
    int getPV() const { return pv; }
    int getPVMax() const { return pvMax; }
};

/* =========================
   GUERRIER
   ========================= */
class Guerrier : public Hero {
public: 
    Guerrier(string nom, int pv, int attaque, int defense, int vitesse)
        : Hero(nom, pv, attaque, defense, vitesse) {}

    int getClasse() const override {
        return 1;
    }

    int calculerDegats(const Hero& cible) const override {
        float bonus = 1.0f;

        if (pv < 0.3f * pvMax) {
            bonus = 1.2f;
        }

        int degats = (attaque * bonus) / max(1, cible.getDefense());
        return max(1, degats);
    }
};

/* =========================
   MAGE
   ========================= */
class Mage : public Hero {
public:
    Mage(string nom, int pv, int attaque, int defense, int vitesse)
        : Hero(nom, pv, attaque, defense, vitesse) {}

    int getClasse() const override {
        return 2;
    }

    int calculerDegats(const Hero& cible) const override {
        int defenseReduite = cible.getDefense() * 0.7;

        float facteur = 0.8f + (rand() % 41) / 100.0f;

        int degats = (attaque / max(1, defenseReduite)) * facteur;
        return max(1, degats);
    }
};

/* =========================
   ARCHER
   ========================= */
class Archer : public Hero {
public:
    Archer(string nom, int pv, int attaque, int defense, int vitesse)
        : Hero(nom, pv, attaque, defense, vitesse) {}

    int getClasse() const override {
        return 3;
    }

    int calculerDegats(const Hero& cible) const override {
        int degats = attaque / max(1, cible.getDefense());

        if (rand() % 100 < 20) {
            degats *= 2;
        }

        return max(1, degats);
    }

    void perdrePV(int montant) override {
        if (rand() % 100 < 15) {
            return;
        }
        Hero::perdrePV(montant);
    }
};

Hero* genererHeroAleatoire() {
    int type = rand() % 3;
    int pv = rand() % 51 + 50;
    int attaque = rand() % 51 + 50;
    int defense = rand() % 51 + 50; 
    int vitesse = rand() % 51 + 50; 

    switch(type) {
        case 0: 
            defense = int(defense * 1.2); 
            return new Guerrier("Guerrier", pv, attaque, defense, vitesse);
        case 1: 
            attaque = int(attaque * 1.2); 
            return new Mage("Mage", pv, attaque, defense, vitesse);
        case 2: 
            vitesse = int(vitesse * 1.2); 
            return new Archer("Archer", pv, attaque, defense, vitesse);
    }
    return nullptr;
}

int combat(Hero* h1, Hero* h2) {
    Hero* premier;
    Hero* second;
    
    if (h1->getVitesse() >= h2->getVitesse()) {
        premier = h1;
        second = h2; 
    }else{
        premier = h2;
        second = h1; 
    }

    while (h1->estVivant() && h2->estVivant()) {
        premier->effetDebutTour();
        int degats1 = premier->calculerDegats(*second);
        second->perdrePV(degats1);
        premier->effetFinTour(); 

        if (!second->estVivant()) break; 

        second->effetDebutTour();
        int degats2 = second->calculerDegats(*premier);
        premier->perdrePV(degats2);
        second->effetFinTour(); 
    }

    if (h1->estVivant()){
        return 1;

    }else{
        return 2; 
    }
}

/*_____________
  CLASSE JOUEUR
  _____________
*/


class Joueur{
private :
    string nom;
    Hero* equipe[6];

public :

    Joueur() : nom(""){
        for (int i = 0; i<6; i++) {
            equipe[i] = nullptr; 
        }
    }

    Joueur(string nom){
        this->nom = nom; 
        for (int i = 0; i<6; i++) {
            equipe[i] = nullptr; 
        }
    }

    ~Joueur() {
        for (int i=0; i<6; i++) {
            if (equipe[i]) {
                delete equipe[i]; 
                equipe[i] = nullptr; 
            }
        }
    }

    string getNom() const {return nom;}

    void ajouterHero(Hero* h) {
        for (int i = 0; i<6; i++) {
            if (equipe[i] == nullptr) {
                equipe[i] = h; 
            }
        }
        cout << "Équipe pleine, impossible d'ajouter le héros !"<<endl;
        delete h;  

    }

    void selectionnerEquipe(Hero* selection[3]) {
        int j = 0; 
        for (int i=0; i<6 && j<3; i++) {
            if (equipe[i] != nullptr && equipe[i]->estVivant()) {
                selection[j++] = equipe[i]; 
            }
        }
        if (j < 3) {
            cout<< "Attention il y a moins de 3 héros vivants disponibles !"<<endl;
        }

    }

    void genererEquipeAleatoire(int n) {
        for (int i = 0; i < n && i<6; i++) {
            ajouterHero(genererHeroAleatoire()); 
        }
    }

    void afficherEquipe() const {
        cout << "Équipe de "<<nom<<" : "<<endl;
        for (int i = 0; i<6; i++) {
            if (equipe[i] != nullptr) {
                equipe[i]->afficherStats(); 
            }
        }
        cout<<endl;
    }
}; 
