#ifndef SPACESECTORBST_H
#define SPACESECTORBST_H

#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

#include "Sector.h"

class SpaceSectorBST {
  
public:
    Sector *root;
    SpaceSectorBST();
    ~SpaceSectorBST();
    void readSectorsFromFile(const std::string& filename); 
    void insertSectorByCoordinates(int x, int y, int z);
    void deleteSector(const std::string& sector_code);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);

    Sector* searchSector(Sector* _root, const std::string& code);

private:
    void addSectorToBST(Sector* root, Sector& sector);

    void preorder(Sector* _root);
    void inorder(Sector* _root);
    void postorder(Sector* _root);

    bool traverseAndGetPath(Sector* _root, const std::string& code, std::vector<Sector*>& path);
    Sector* getInorderSuccessor(Sector* sector);

    void freeSector(Sector* sector);
};

#endif // SPACESECTORBST_H
