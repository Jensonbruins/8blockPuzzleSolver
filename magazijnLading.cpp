#include <iostream>
#include <bits/stdc++.h>

class magazijnLading {
    private:

    public:
        void willekeurig(int containerArray[9]) {
            time_t t;
            srand((unsigned) time(&t));

            for (int i = 0; i < (rand() % 100 + 1); i++) {
                int rand1 = rand() % 9;
                int rand2 = rand() % 9;

                if (rand1 == rand2) {continue;};

                int tmp = containerArray[rand1];
                containerArray[rand1] = containerArray[rand2];
                containerArray[rand2] = tmp;
            }
        }

        void zetContainerLocaties(int containerArray[9]) {
            int alGebruikteCijfers[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
            int index = 0;

            for (int i = 0; i < 9; i++) {
                std::cout << "\nGeef een nummer voor positie:  " << i << " \n(0 voor de lege plek)\nAl gebruikte nummers zijn: ";
                for (int k = 0; k < 9; k++)
                    if (alGebruikteCijfers[k] != -1) {std::cout << alGebruikteCijfers[k];}
                std::cout << "\nGegeven nummer: ";

                std::string command;
                std::getline(std::cin, command);

                int gegevenNummer = stoi(command);
                int succes = true;
                if (gegevenNummer >= 0 && gegevenNummer <= 8) {
                    for (int k = 0; k < 9; k++) {
                        if (alGebruikteCijfers[k] == gegevenNummer) {succes = false; break;}
                    }
                } else {
                    succes = false;
                }

                if (succes) {
                    alGebruikteCijfers[index] = gegevenNummer;
                    index++;
                } else {
                    i--;
                }
            }

            for (int i = 0; i < 9; i++) {
                containerArray[i] = alGebruikteCijfers[i];
            }
        }
};