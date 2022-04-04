#include <iostream>
#include "magazijnLading.cpp"
#include "magazijnHerindeler.cpp"
#include "kraan.cpp"

class magazijn {
    private:
        int containerLocaties[9] = {1,2,3,4,5,6,7,8,0};

        magazijnLading magazijnLadingObj;
        magazijnHerindeler magazijnHerindelerObj;
        kraan kraanObj;
        
        void toonMagazijn() {
            std::cout << "-------\n";
            int g = 0;
            for (int i = 0; i < 3; i++) {
                std::cout << "| ";
                for (int j = 0; j < 3; j++) {
                    
                    if (containerLocaties[g] == 0) {
                        std::cout << " ";
                    } else {
                        std::cout << containerLocaties[g];
                    }
                    g++;
                }
                std::cout << " |\n";
            }
            std::cout << "-------\n";
        }
    public:
        magazijn() {

        }
        
        ~magazijn() {

        }

        void haalMagazijnLading() {
            std::cout << "Wil je zelf een lading opgeven? ja of nee?\n";

            std::string command; 
            std::getline(std::cin, command);

            if (command == "ja") {
                std::cout << "\nEr word nu een aanvraag gedaan aan de magazijnLader om zelf data in te voeren\n";
                magazijnLadingObj.zetContainerLocaties(containerLocaties);
                if (!magazijnHerindelerObj.isHerindeelbaar(containerLocaties)) {
                    std::cout << "\n Deze puzzel is niet op te lossen\n";
                }
            } else {
                std::cout << "\nEr word nu een aanvraag gedaan aan de magazijnLader voor willekeurige data\n";
                while (true) {
                    magazijnLadingObj.willekeurig(containerLocaties);
                    if (magazijnHerindelerObj.isHerindeelbaar(containerLocaties)) break;
                }
            }

            toonMagazijn();
        }
        void vraagManierVanOplossen() {
            std::cout << "\nWil je de puzzel handmatig oplossen? ja of nee?\n";

            std::string command; 
            std::getline(std::cin, command);

            if (command == "ja") {
                while (!magazijnHerindelerObj.isHeringedeeld(containerLocaties)) {
                    kraanObj.beweegContainerHandmatig(containerLocaties);
                    toonMagazijn();
                }
                std::cout << "\n Gefeliciteerd je hebt de puzzel opgelost\n";
            } else {
                magazijnHerindelerObj.herIndeler(containerLocaties);
            }


        }
};

int main() {
    magazijn magazijnObj;
    magazijnObj.haalMagazijnLading();
    magazijnObj.vraagManierVanOplossen();

    return 0;
}