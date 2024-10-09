#include "../includes/includes.h"

class Profile {
private:
    std::string name;
    double action, horreur, policier, romantique, dessin_anime;
    int age, bac, sexe;
    std::string like, dislike, neutral;

public:
    Profile(std::string name, double action, double horreur, double policier, double romantique, double dessin_anime, int age, int bac, int sexe)
        : name(name), action(action), horreur(horreur), policier(policier), romantique(romantique), dessin_anime(dessin_anime), age(age), bac(bac), sexe(sexe) {}

    void film(double test, const std::string& element) {
        test = (std::round(test * 10000) / 10000 - 0.5) * 200;
        if (test == 100) {
            if (like.empty()) {
                like = (sexe ? "Il aime " : "Elle aime ") + element + ", ";
            } else {
                like += element + ", ";
            }
        } else if (test == -100) {
            if (dislike.empty()) {
                dislike = (sexe ? "Il n'aime pas " : "Elle n'aime pas ") + element + ", ";
            } else {
                dislike += element + ", ";
            }
        } else if (test > 10) {
            if (like.empty()) {
                like = (sexe ? "Il aime " : "Elle aime ") + element + " (" + std::to_string(static_cast<int>(test)) + " %), ";
            } else {
                like += element + " (" + std::to_string(static_cast<int>(test)) + " %), ";
            }
        } else if (test < -10) {
            test = -test;
            if (dislike.empty()) {
                dislike = (sexe ? "Il n'aime pas " : "Elle n'aime pas ") + element + " (" + std::to_string(static_cast<int>(test)) + " %), ";
            } else {
                dislike += element + " (" + std::to_string(static_cast<int>(test)) + " %), ";
            }
        } else {
            if (neutral.empty()) {
                neutral = "Je ne sais pas pour " + element + " (" + std::to_string(static_cast<int>(test)) + " %), ";
            } else {
                neutral += element + " (" + std::to_string(static_cast<int>(test)) + " %), ";
            }
        }
    }

    void affich() {
        std::string bacStr = (bac > 0) ? "possede l'occupation n°" + std::to_string(bac) : "ne possede pas d'activitée";
        std::string sexeStr = (sexe == 1) ? "un homme" : "une femme";

        film(action, "les films d'action");
        film(horreur, "les films d'horreur");
        film(policier, "les films policier");
        film(romantique, "les films romantique");
        film(dessin_anime, "les dessins animes");

        std::string affich = name + " a " + std::to_string(age) + " ans, est " + sexeStr + ", et " + bacStr + ".\n";
        if (!like.empty()) {
            like = like.substr(0, like.size() - 2) + ". ";
            affich += like + "\n";
        }
        if (!dislike.empty()) {
            dislike = dislike.substr(0, dislike.size() - 2) + ". ";
            affich += dislike + "\n";
        }
        if (!neutral.empty()) {
            neutral = neutral.substr(0, neutral.size() - 2) + ". ";
            affich += neutral + "\n";
        }
        std::cout << affich;
    }
};
