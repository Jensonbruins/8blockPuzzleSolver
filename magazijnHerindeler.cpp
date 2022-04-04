#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <map>
#include <unistd.h>
#include "magazijnRegels.cpp"

class magazijnHerindeler {
    private:
        magazijnRegels magazijnRegelsObj;

        int uiteindelijkeContainerLocaties[9] = {1,2,3,4,5,6,7,8,0};

        void toonMagazijn(int containerLocaties[9]) {
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

        int berekenFoutGeplaatst(int containerArray[9]) {
            int counter = 0;
            for (int k = 0; k < 9; k++) {
                if (containerArray[k] && containerArray[k] != magazijnRegelsObj.uiteindelijkeContainerLocaties[k]) {
                    counter++;
                }
            }
            // std::cout << "Fout geplaatsde: " << counter << std::endl;
            return counter;
        }

        struct Node {
            Node* parent;
            int containerLocaties[9];
            int legeContainerID;
            int verplaatsNaarID;
            int aantalVerkeerdeContainers;
            int aantalVerplaatsingen;
        };


        Node* newNode(int containerLocaties[9], int legeContainerID, int verplaatsNaarID, int aantalVerplaatsingen, Node* parent) {
            // setup the loopie thingie
            Node* node = new Node;
            node->parent = parent;

            for (int k = 0; k < 9; k++)
                node->containerLocaties[k] = containerLocaties[k];

            std::swap(node->containerLocaties[legeContainerID], node->containerLocaties[verplaatsNaarID]);
            // int tmpStorage = containerLocaties[]

            node->legeContainerID = verplaatsNaarID;
            // node->verplaatsNaarID = verplaatsNaarID;
            node->aantalVerkeerdeContainers = -1;
            node->aantalVerplaatsingen = aantalVerplaatsingen;
            
            // std::cout << "ContainerLocaties: ";
            // for (int k = 0; k < 9; k++) {
            //     std::cout << node->containerLocaties[k];
            // }
            // std::cout << "\n";
            // std::cout << "LegeContainerID: " << node->legeContainerID << "\n";
            // std::cout << "verplaatsNaarID: " << node->verplaatsNaarID << "\n";
            // std::cout << "aantalVerplaatsingen: " << node->aantalVerplaatsingen << "\n";

            return node;
        }

        struct comp {
            bool operator()(const Node* lhs, const Node* rhs) const {
                return (lhs->aantalVerkeerdeContainers + lhs->aantalVerplaatsingen) > (rhs->aantalVerkeerdeContainers + rhs->aantalVerplaatsingen);
            }
        };

        void printPath(Node* root) {
            if (root == NULL)
                return;
            printPath(root->parent);
            toonMagazijn(root->containerLocaties);

            // std::cout << "nodeInfo:\n  " << root->legeContainerID << "\n  "  << root->verplaatsNaarID << "\n  " << root->aantalVerkeerdeContainers << "\n";
        }
    
    public:
        magazijnHerindeler() {
            std::cout << "[CONSTRUCTED][magazijnHerindeler]\n";
        }
        
        ~magazijnHerindeler() {

        }

        bool isHerindeelbaar(int containerArray[9]) {
            int n = 36 / sizeof(containerArray[0]);

            int inv_count = 0;
            for (int i = 0; i < n - 1; i++)
                for (int j = i + 1; j < n; j++)
                    if (containerArray[i] > containerArray[j])
                        inv_count++;
        
            return ((inv_count -1) % 2 == 0);
        }

        bool isHeringedeeld(int containerArray[9]) {
            for (int k = 0; k < 9; k++) {
                if (containerArray[k] != magazijnRegelsObj.uiteindelijkeContainerLocaties[k]) {
                    return false;
                }
            }
            return true;
        };

        int herIndeler(int containerArray[9]) {
            int legeplekIndex = -1;
            for (legeplekIndex = 0; legeplekIndex < 9; legeplekIndex++)
                if (containerArray[legeplekIndex] == 0) break;

            std::priority_queue<Node*, std::vector<Node*>, comp> pq;

            Node* root = newNode(containerArray, legeplekIndex, legeplekIndex, 0, NULL);
            root->aantalVerkeerdeContainers = berekenFoutGeplaatst(containerArray);

            pq.push(root);

            while (!pq.empty()) {
                Node* tmpNode = pq.top();
                pq.pop();


                if (tmpNode->aantalVerkeerdeContainers == 0) {
                    printPath(tmpNode);
                    return 0;
                }                    

                const std::vector<int> aangrenzendArray = magazijnRegelsObj.haalAangrenzendOp(tmpNode->legeContainerID);

                for (auto &aangrenzend : aangrenzendArray) {
                    Node* childNode = newNode(tmpNode->containerLocaties, tmpNode->legeContainerID, aangrenzend, tmpNode->aantalVerplaatsingen + 1, tmpNode);
                    childNode->aantalVerkeerdeContainers = berekenFoutGeplaatst(childNode->containerLocaties);
                    pq.push(childNode);
                }
            }

            return 0;
        }
};