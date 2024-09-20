#include "SpaceSectorBST.h"
#include "fstream"

using namespace std;

SpaceSectorBST::SpaceSectorBST() : root(nullptr) {}

SpaceSectorBST::~SpaceSectorBST() {
    freeSector(root);
    // Free any dynamically allocated memory in this class.
}

void SpaceSectorBST::freeSector(Sector *sector) {

    if (sector == nullptr) {
        return;
    }

    freeSector(sector->left);
    freeSector(sector->right);
    delete sector;
}

void SpaceSectorBST::readSectorsFromFile(const std::string& filename) {
    // TODO: read the sectors from the input file and insert them into the BST sector map
    // according to the given comparison critera based on the sector coordinates.
    
    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }

    std::string line,x,y,z;
    getline(file, line);
    
    while (getline(file, x, ',')) {
        getline(file, y, ',');
        getline(file, z);

        insertSectorByCoordinates(stoi(x), stoi(y), stoi(z));
    }
}

// Instantiate and insert a new sector into the space sector BST map according to the
// coordinates-based comparison criteria.
void SpaceSectorBST::insertSectorByCoordinates(int x, int y, int z) {
    Sector* sector = new Sector(x,y,z);
    addSectorToBST(root, *sector);
}

void SpaceSectorBST::addSectorToBST(Sector* _root, Sector& sector) {

    if (root == nullptr) {
        root = &sector;
        return;
    }

    int comparison = _root->compareTo(sector);

    if (comparison > 0) {
        if (_root->left == nullptr) {
            _root->left = &sector;
            sector.parent = _root;
        } else {
            addSectorToBST(_root->left, sector);
        }
    } else if (comparison < 0) {
        if (_root->right == nullptr) {
            _root->right = &sector;
            sector.parent = _root;
        } else {
            addSectorToBST(_root->right, sector);
        }
    } else {
        return;
    }

}

void SpaceSectorBST::deleteSector(const std::string& sector_code) {
    Sector* deleteSector = searchSector(root, sector_code);
    if (deleteSector == nullptr) {
        return;
    }

    if (deleteSector->left == nullptr && deleteSector->right == nullptr) {
        if (deleteSector->parent) {
            if (deleteSector == deleteSector->parent->left) {
                deleteSector->parent->left = nullptr;
            } else {
                deleteSector->parent->right = nullptr;
            }
        } else {
            root = nullptr;
        }
        delete deleteSector;
        return;
    }

    if (deleteSector->left == nullptr || deleteSector->right == nullptr) {

        Sector* parent = deleteSector->parent;
        Sector* grandChild = (deleteSector->left == nullptr) ? deleteSector->right : deleteSector->left;

        if (!parent) {

            if (deleteSector->left == nullptr) {
                root = deleteSector->right;
            } else {
                root = deleteSector->left;
            }

            delete deleteSector;
            return;
        }

        if (parent->left == deleteSector) {
            parent->left = grandChild;
        } else {
            parent->right = grandChild;
        }

        grandChild->parent = parent;
        delete deleteSector;
        return;
    }

    Sector* inorderSuccessor = getInorderSuccessor(deleteSector->right);
    Sector* rightChildren = inorderSuccessor->right;

    deleteSector->resetCoordinates(inorderSuccessor->x, inorderSuccessor->y, inorderSuccessor->z);

    if (rightChildren != nullptr) {
        rightChildren->parent = inorderSuccessor->parent;

        if (inorderSuccessor == inorderSuccessor->parent->left) {
            inorderSuccessor->parent->left = rightChildren;
        } else {
            inorderSuccessor->parent->right = rightChildren;
        }

        delete inorderSuccessor;
        return;
    }


    if (inorderSuccessor == inorderSuccessor->parent->left) {
        inorderSuccessor->parent->left = nullptr;
    } else {
        inorderSuccessor->parent->right = nullptr;
    }

    delete inorderSuccessor;

    // TODO: Delete the sector given by its sector_code from the BST.
}

Sector* SpaceSectorBST::searchSector(Sector *_root, const string &code) {
    if (_root == nullptr) {
        return nullptr;
    }

    if (_root->sector_code == code) {
        return _root;
    }

    Sector* searchLeft = searchSector(_root->left, code);
    if (searchLeft) {
        return searchLeft;
    }

    Sector* searchRight = searchSector(_root->right, code);
    if (searchRight) {
        return searchRight;
    }

    return nullptr;
}

Sector *SpaceSectorBST::getInorderSuccessor(Sector *sector) {
    if (sector->left == nullptr) {
        return sector;
    }

    return getInorderSuccessor(sector->left);
}

void SpaceSectorBST::displaySectorsInOrder() {
    std::cout << "Space sectors inorder traversal:\n";
    inorder(root);
    std::cout << std::endl;
    // TODO: Traverse the space sector BST map in-order and print the sectors
    // to STDOUT in the given format.
}

void SpaceSectorBST::displaySectorsPreOrder() {
    std::cout << "Space sectors preorder traversal:\n";
    preorder(root);
    std::cout << std::endl;
    // TODO: Traverse the space sector BST map in pre-order traversal and print
    // the sectors to STDOUT in the given format.
}

void SpaceSectorBST::displaySectorsPostOrder() {
    std::cout << "Space sectors postorder traversal:\n";
    postorder(root);
    std::cout << std::endl;
    // TODO: Traverse the space sector BST map in post-order traversal and print
    // the sectors to STDOUT in the given format.
}

std::vector<Sector*> SpaceSectorBST::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;

    if (root == nullptr) {
        return path;
    }

    traverseAndGetPath(root, sector_code, path);
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    return path;
}

bool SpaceSectorBST::traverseAndGetPath(Sector *_root, const std::string& code, vector<Sector *> &path) {
    if (_root == nullptr) {
        return false;
    }

    path.push_back(_root);

    if (_root->sector_code == code) {
        return true;
    }

    if (!traverseAndGetPath(_root->left, code, path) && !traverseAndGetPath(_root->right, code, path)) {
        path.pop_back();
        return false;
    } else {
        return true;
    }

}

void SpaceSectorBST::printStellarPath(const std::vector<Sector*>& path) {

    if (path.empty()) {
        std::cout << "A path to Dr. Elara could not be found.\n";
    } else {
        std::cout << "The stellar path to Dr. Elara: ";
        for (int i = 0; i < path.size()-1; i++) {
            std::cout << path[i]->sector_code << "->";
        }
        std::cout << path[path.size()-1]->sector_code << std::endl;
    }

    // TODO: Print the stellar path obtained from the getStellarPath() function 
    // to STDOUT in the given format.
}

void SpaceSectorBST::preorder(Sector *_root) {
    if (_root == nullptr) {return;}

    std::cout << _root->sector_code << "\n";
    preorder(_root->left);
    preorder(_root->right);
}

void SpaceSectorBST::inorder(Sector *_root) {
    if (_root == nullptr) {return;}

    inorder(_root->left);
    std::cout << _root->sector_code << "\n";
    inorder(_root->right);
}

void SpaceSectorBST::postorder(Sector *_root) {
    if (_root == nullptr) {return;}

    postorder(_root->left);
    postorder(_root->right);
    std::cout << _root->sector_code << "\n";
}