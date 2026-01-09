#ifndef HERO_H
#define HERO_H

#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib> // pour rand()

// =========================
// CLASSE ABSTRAITE HERO
// =========================
class Hero {
protected:
    std::string nom;
    int pv, pvMax, attaque, defense, vitesse;

public:
    // Constructeurs
    Hero() : nom(""), pv(0), pvMax(0), attaque(0), defense(0), vitesse(0) {}
    Hero(std::string nom, int pv, int attaque, int defense, int vitesse)
        : nom(nom), pv(pv), pvMax(pv), attaque(attaque), defense(defense), vitesse(vitesse) {}

    virtual ~Hero() {}

    // Affichage des stats
    void afficherStats() const {
        std::cout << nom << " PV : " << pv
                  << " Attaque : " << attaque
                  << " Defense : " << defense
                  << " Vitesse : " << vitesse << std::endl;
    }

    // Méthodes abstraites
    virtual int getClasse() const = 0;
    virtual int calculerDegats(const Hero& cible) const = 0;

    // Méthodes virtuelles
    virtual void perdrePV(int montant) {
        pv -= montant;
        if (pv < 0) pv = 0;
    }
    virtual void effetDebutTour() {}
    virtual void effetFinTour() {}

    // Getters
    bool estVivant() const { return pv > 0; }
    int getDefense() const { return defense; }
    int getAttaque() const { return attaque; }
    int getVitesse() const { return vitesse; }
    int getPV() const { return pv; }
    int getPVMax() const { return pvMax; }
};

// =========================
// CLASSES DERIVEES
// =========================
class Guerrier : public Hero {
public:
    Guerrier(std::string nom, int pv, int attaque, int defense, int vitesse)
        : Hero(nom, pv, attaque, defense, vitesse) {}

    int getClasse() const override { return 1; }

    int calculerDegats(const Hero& cible) const override {
        float bonus = 1.0f;
        if (pv < 0.3f * pvMax) bonus = 1.2f;
        int degats = (attaque * bonus) / std::max(1, cible.getDefense());
        return std::max(1, degats);
    }
};

class Mage : public Hero {
public:
    Mage(std::string nom, int pv, int attaque, int defense, int vitesse)
        : Hero(nom, pv, attaque, defense, vitesse) {}

    int getClasse() const override { return 2; }

    int calculerDegats(const Hero& cible) const override {
        int defenseReduite = cible.getDefense() * 0.7;
        float facteur = 0.8f + (rand() % 41) / 100.0f; // 0.8 à 1.2
        int degats = (attaque / std::max(1, defenseReduite)) * facteur;
        return std::max(1, degats);
    }
};

class Archer : public Hero {
public:
    Archer(std::string nom, int pv, int attaque, int defense, int vitesse)
        : Hero(nom, pv, attaque, defense, vitesse) {}

    int getClasse() const override { return 3; }

    int calculerDegats(const Hero& cible) const override {
        int degats = attaque / std::max(1, cible.getDefense());
        if (rand() % 100 < 20) degats *= 2; // coup critique
        return std::max(1, degats);
    }

    void perdrePV(int montant) override {
        if (rand() % 100 < 15) return; // chance d'esquiver
        Hero::perdrePV(montant);
    }
};

// =========================
// FONCTIONS NON MEMBRES
// =========================
Hero* genererHeroAleatoire();
int combat(Hero* h1, Hero* h2);

#endif // HERO_H
