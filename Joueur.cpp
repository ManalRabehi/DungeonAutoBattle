#include <iostream>
#include <string>


using namespace std;

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