#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std; 
class Hero {
protected :
    string nom; 
    int pv, pvMax, attaque, defense, vitesse; 
    // états
    bool saignement = false;
    bool brulure = false;
    int bouclier = 0;
    
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
                 << " Vitesse : " << vitesse;
            if (saignement) { cout << " [Saignement]"; }
            if (brulure) { cout << " [Brûlure]"; }
            if (bouclier > 0) { cout << " [Bouclier: " << bouclier << "]"; }
            cout << endl;
    }

    virtual int getClasse() const = 0; 
    virtual int calculerDegats(const Hero& cible) const = 0;

    virtual void perdrePV(int montant) {
        if (bouclier > 0) {
            int bloque = min(bouclier, montant);
            bouclier -= bloque;
            montant -= bloque;
        }
        pv -= max(0, montant);
        if (pv < 0) pv = 0;
    }

    virtual void effetDebutTour() {
        if (saignement) {
            pv -= 5;
            if (pv < 0) pv = 0;
        }
        if (brulure) {
            pv -= 8;
            if (pv < 0) pv = 0;
        }
    }
    virtual void effetFinTour() {} 

    bool estVivant() const {
        return pv > 0; 
    }

    int getDefense() const { return defense; }
    int getAttaque() const { return attaque; }
    int getVitesse() const { return vitesse; }
    int getPV() const { return pv; }
    int getPVMax() const { return pvMax; }

    virtual void restaurerPV() {
        pv = pvMax; 
    }

    void appliquerSaignement() { saignement = true; }
    void appliquerBrulure() { brulure = true; }
    void ajouterBouclier(int montant) { bouclier += montant; }

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
            return; // esquive
        }
        Hero::perdrePV(montant);
    }
};

/* =========================
   PALADIN
   ========================= */

class Paladin : public Hero {
public:
    Paladin(string nom, int pv, int attaque, int defense, int vitesse)
        : Hero(nom, pv, attaque, defense, vitesse) {}
    int getClasse() const override { return 4; }
    int calculerDegats(const Hero& cible) const override {
        int degats = attaque / max(1, cible.getDefense());
        return max(1, degats);
    }
    void effetFinTour() override {
        int regen = max(1, static_cast<int>(pvMax * 0.05));
        pv += regen;
        if (pv > pvMax) pv = pvMax;
    }
};

/* =========================
   ASSASSIN
   ========================= */

class Assassin : public Hero {
public:
    Assassin(string nom, int pv, int attaque, int defense, int vitesse)
        : Hero(nom, pv, attaque, defense, vitesse) {}
    int getClasse() const override { return 5; }
    int calculerDegats(const Hero& cible) const override {
        int degats = attaque * 1.5 / max(1, cible.getDefense());
        if (rand() % 100 < 40) degats *= 2;
        return max(1, degats);
    }
    void effetFinTour() override {
        int regen = max(1, static_cast<int>(pvMax * 0.05));
        pv += regen;
        if (pv > pvMax) pv = pvMax;
    }
};

/* =========================
   DRUIDE
   ========================= 
   Classe dérivée de Hero.
   Le Druide est un héros sans effet spécial.
   Il sert d'exemple d'extension du jeu avec un nouveau type de héros.
   */

class Druide : public Hero {
public:
    // Constructeur de Druide 
    Druide(string nom, int pv, int attaque, int defense, int vitesse)
        : Hero(nom, pv, attaque, defense, vitesse) {}

    // Getter de classe
    int getClasse() const override {
        return 6;
    }

    // Calcul des dégats 
    int calculerDegats(const Hero& cible) const override {
        return attaque / max(1, cible.getDefense());
    }
};

// =========================
// OBJETS
// =========================
// Classe abstraite représentant un objet utilisable par un héros.
class Objet {
public:
    virtual ~Objet() {}
    virtual void appliquer(Hero& h) = 0;
};

// La Potion restaure entièrement les points de vie du héros grâce à la méthode restaurerPV.
class Potion : public Objet {
public:
    void appliquer(Hero& h) override { h.restaurerPV(); }
};

// Exemple d'objet bonus d'attaque temporaire.
class Anneau : public Objet {
public:
    void appliquer(Hero& h) override { cout << h.getPV() << " bonus attaque temporaire !\n"; }
};

// Méthode de génération d'un héros aléatoire. Le type de héros est choisi aléatoirement grâce au random.
// Les statistiques sont comprises entre 50 et 100.
Hero* genererHeroAleatoire() {
    int type = rand() % 6;
    int pv = rand() % 51 + 50;
    int attaque = rand() % 51 + 50;
    int defense = rand() % 51 + 50; 
    int vitesse = rand() % 51 + 50; 

    // Le switch permet de regrouper les différents cas possible de héros (Guerrier, Mage...).
    switch(type) {
        case 0: defense = int(defense * 1.2); return new Guerrier("Guerrier", pv, attaque, defense, vitesse);
        case 1: attaque = int(attaque * 1.2); return new Mage("Mage", pv, attaque, defense, vitesse);
        case 2: vitesse = int(vitesse * 1.2); return new Archer("Archer", pv, attaque, defense, vitesse);
        case 3: return new Paladin("Paladin", pv, attaque, defense, vitesse);
        case 4: return new Assassin("Assassin", pv, attaque, defense, vitesse);
        case 5: return new Druide("Druide", pv, attaque, defense, vitesse);
    }   
    return nullptr;
}

// Méthode de combat complète entre deux héros.
// Le héros le plus rapide commence et ensuite les héros s'attaquent à tour de rôle.
// La méthode retourne 1 si le heros 1 gagne, 2 si le heros 2 gagne sinon 0 en cas de match nul.
int combat(Hero* h1, Hero* h2) {
    // Détermination de l'ordre selon la vitesse 
    Hero* premier = (h1->getVitesse() >= h2->getVitesse()) ? h1 : h2;
    Hero* second = (premier == h1) ? h2 : h1;

    int tours = 0;
    const int MAX_TOURS = 100; // sécurité anti-boucle infinie

    while (h1->estVivant() && h2->estVivant()) {
        if (++tours > MAX_TOURS) {
            cout << "Match nul après " << MAX_TOURS << " tours !\n";
            return 0; // match nul
        }

        //Tour du premier héros
        premier->effetDebutTour();
        second->perdrePV(premier->calculerDegats(*second));
        premier->effetFinTour();
        if (!second->estVivant()) break;

        // Tour du second héros
        second->effetDebutTour();
        premier->perdrePV(second->calculerDegats(*premier));
        second->effetFinTour();
    }
    // on retourne le vainqueur 
    return h1->estVivant() ? 1 : 2;
}


// =========================
// CLASSE JOUEUR
// =========================

// Représente un joueur du jeu.
// Un joueur possède un nom et une équipe de héros. Une équipe peut contenir jusqu'à 6 héros.

class Joueur{
private :
    string nom;
    Hero* equipe[6];

public :

    // Constructeur par défaut
    Joueur() : nom(""){
        for (int i = 0; i<6; i++) {
            equipe[i] = nullptr; 
        }
    }

    // Constructeur avec nom
    Joueur(string nom){
        this->nom = nom; 
        for (int i = 0; i<6; i++) {
            equipe[i] = nullptr; 
        }
    }

    //Destructeur
    ~Joueur() {
        for (int i=0; i<6; i++) {
            if (equipe[i]) {
                delete equipe[i]; 
                equipe[i] = nullptr; 
            }
        }
    }

    // Getter du nom 
    string getNom() const {return nom;}

    // Méthode pour ajouter un héros dans la première case libre de l'équipe.
    // Si l'équipe est pleine le héros est supprimé.
    void ajouterHero(Hero* h) {
        for (int i = 0; i<6; i++) {
            if (equipe[i] == nullptr) {
                equipe[i] = h; 
                return;
            }
        }
        cout << "Équipe pleine, impossible d'ajouter le héros !"<<endl;
        delete h;  

    }

    // Méthode permettant de selectionner 3 héros pour le combat d'équipes.
    void selectionnerEquipe(Hero* selection[3]) {
        for (int k = 0; k < 3; k++) selection[k] = nullptr;
        int j = 0;
        for (int i = 0; i < 6 && j < 3; i++) {
            if (equipe[i] && equipe[i]->estVivant()) selection[j++] = equipe[i];
        }
        if (j < 3) cout << "Moins de 3 héros vivants !\n";
    }

    // Méthode pour générer une équipe de héros aléatoires.
    void genererEquipeAleatoire(int n) {
        for (int i = 0; i < n && i<6; i++) {
            ajouterHero(genererHeroAleatoire()); 
        }
    }

    //Permet d'afficher les statistiques de tous les héros du joueur
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

// =========================
// COMBAT D'ÉQUIPES
// =========================

// Combat automatique entre deux équipes de deux joueurs différents.
// Chaque joueur séléctionne 3 héros et ensuite les héros s'affrontent dans l'ordre de selection.
int combatEquipes(Joueur& j1, Joueur& j2) {
    // Selection des équipes de combat
    Hero* equipe1[3];
    Hero* equipe2[3]; 

    j1.selectionnerEquipe(equipe1);
    j2.selectionnerEquipe(equipe2);

    int i = 0;
    int j = 0; 

    // Enchainement des combats entre les héros
    while (i<3 && j<3) {
        cout << "\nCombat entre : " <<j1.getNom() <<" (Héros : " << i + 1 << ") et "<< j2.getNom() << "(Héros : "<< j + 1<< ")\n"; 
        int gagnant = combat(equipe1[i], equipe2[j]);

        // Le héros gagnant récupère ses PV initiaux
        if (gagnant == 1) {
            cout << j1.getNom() << " remporte ce duel ! ";
            equipe1[i]->restaurerPV();
            j++;
        }else{
            cout << j2.getNom() << " remporte ce duel ! ";
            equipe2[j]->restaurerPV();
            i++;
        }

    }
    // On détermine le vainqueur final
    if (i == 3) {
        cout << "\nCombat terminé !"<< "\n"<< j2.getNom()<< " gagne le combat d'équipes !";
        return 2; 
    }else{
        cout << "Combat terminé !"<< "\n"<< j1.getNom()<< " gagne le combat d'équipes !";
        return 1;
    }
    

}


//Test global du programme
// Permet de générer les équipes et lancer le combat.
int main() {

    // Initialisation du hasard
    srand(time(0));

    // Création des joueurs
    Joueur joueur1("Imane");
    Joueur joueur2("Saci");

    // Génération aléatoire des équipes
    joueur1.genererEquipeAleatoire(6);
    joueur2.genererEquipeAleatoire(6);

    // Affichage des équipes
    joueur1.afficherEquipe();
    joueur2.afficherEquipe();

    // Lancement du combat d'équipes
    combatEquipes(joueur1, joueur2);

    return 0;
}
