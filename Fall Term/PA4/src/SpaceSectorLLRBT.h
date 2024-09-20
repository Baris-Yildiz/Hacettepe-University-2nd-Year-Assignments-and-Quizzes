#ifndef SPACESECTORLLRBT_H
#define SPACESECTORLLRBT_H

#include "Sector.h"
#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

class SpaceSectorLLRBT {
public:
    Sector* root;
    SpaceSectorLLRBT();
    ~SpaceSectorLLRBT();
    void readSectorsFromFile(const std::string& filename);
    void insertSectorByCoordinates(int x, int y, int z);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);

    Sector* origin;
private:
    void addSectorToLLRBT(Sector* _root, Sector& sector);

    void preorder(Sector *_root);
    void inorder(Sector *_root);
    void postorder(Sector *_root);

    void flipColors(Sector* parent);
    void rotateLeft(Sector* sector);
    void rotateRight(Sector* sector);

    void optimizeTree(Sector* _root);

    bool traverseAndGetPath(Sector *_root, const std::string &code, std::vector<Sector *> &path);

    void freeSector(Sector *sector);
    void clearVisitedFlags(Sector* sector);
};

#endif // SPACESECTORLLRBT_H
