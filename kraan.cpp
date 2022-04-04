#include <iostream>
#include <vector>
#include <map>
#include "magazijnRegels.cpp"

class kraan {
    private:
        magazijnRegels magazijnRegelsObj;

    public:
        kraan() {
            std::cout << "[CONSTRUCTED][kraan]\n";
        }

        void beweegContainer(int containerArray[9], int c1, int c2) {
            int tmp = containerArray[c1];
            containerArray[c1] = containerArray[c2];
            containerArray[c2] = tmp;
        }

        void beweegContainerHandmatig(int containerArray[9]) {
            int legeplekIndex = -1;
            for (int k = 0; k < 9; k++)
                if (containerArray[k] == 0) {legeplekIndex = k; break;}
            
            const std::vector<int> aangrenzendArray = magazijnRegelsObj.haalAangrenzendOp(legeplekIndex);
            
            std::cout << "Aangrenzende vakken zijn: ";
            for (auto &aangrenzend : aangrenzendArray) {
                std::cout << aangrenzend << ", ";
            }
            std::cout << "\n Naar welk vlak wil je het lege vlak verplaatsen: " << std::endl;

            std::string command; 
            std::getline(std::cin, command);

            int verplaatsIndex = stoi(command);

            bool succes = false;
            for (auto &aangrenzend : aangrenzendArray)
                if (verplaatsIndex == aangrenzend) {succes = true; break;}

            if (succes == false) {return;}
            
            beweegContainer(containerArray, legeplekIndex, verplaatsIndex);
        }
};