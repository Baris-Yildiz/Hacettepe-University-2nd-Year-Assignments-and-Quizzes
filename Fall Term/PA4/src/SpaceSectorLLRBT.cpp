#include "SpaceSectorLLRBT.h"

using namespace std;

SpaceSectorLLRBT::SpaceSectorLLRBT() : root(nullptr) {}

// Remember to handle memory deallocation properly in the destructor.
SpaceSectorLLRBT::~SpaceSectorLLRBT() {
    freeSector(root);
    // TODO: Free any dynamically allocated memory in this class.
}

void SpaceSectorLLRBT::freeSector(Sector *sector) {

    if (sector == nullptr) {
        return;
    }

    freeSector(sector->left);
    freeSector(sector->right);
    delete sector;
}

void SpaceSectorLLRBT::readSectorsFromFile(const std::string& filename) {

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

    // TODO: read the sectors from the input file and insert them into the LLRBT sector map
    // according to the given comparison critera based on the sector coordinates.
}

void SpaceSectorLLRBT::insertSectorByCoordinates(int x, int y, int z) {
    //todo origin her zaman ilk olmayabilir (0,0,0)
    Sector* sector = new Sector(x,y,z);
    addSectorToLLRBT(root, *sector);
    Sector* temp = sector;

    while (temp != nullptr) {
        optimizeTree(temp);
        temp = temp->parent;
    }

    // TODO: Instantiate and insert a new sector into the space sector LLRBT map 
    // according to the coordinates-based comparison criteria.
}

void SpaceSectorLLRBT::addSectorToLLRBT(Sector *_root, Sector &sector) {
    if (root == nullptr) {
        sector.color = BLACK;
        root = &sector;
        origin = root;
        return;
    }

    int comparison = _root->compareTo(sector);

    if (comparison > 0) {
        if (_root->left == nullptr) {
            _root->left = &sector;
            sector.parent = _root;
        } else {
            addSectorToLLRBT(_root->left, sector);
        }
    } else if (comparison < 0) {
        if (_root->right == nullptr) {
            _root->right = &sector;
            sector.parent = _root;
        } else {
            addSectorToLLRBT(_root->right, sector);
        }
    } else {
        return;
    }
}

void SpaceSectorLLRBT::displaySectorsInOrder() {
    std::cout << "Space sectors inorder traversal:\n";
    inorder(root);
    std::cout << std::endl;
    // TODO: Traverse the space sector LLRBT map in-order and print the sectors
    // to STDOUT in the given format.
}

void SpaceSectorLLRBT::displaySectorsPreOrder() {
    std::cout << "Space sectors preorder traversal:\n";
    preorder(root);
    std::cout << std::endl;
    // TODO: Traverse the space sector LLRBT map in pre-order traversal and print
    // the sectors to STDOUT in the given format.
}

void SpaceSectorLLRBT::displaySectorsPostOrder() {
    std::cout << "Space sectors postorder traversal:\n";
    postorder(root);
    std::cout << std::endl;
    // TODO: Traverse the space sector LLRBT map in post-order traversal and print
    // the sectors to STDOUT in the given format.
}

void SpaceSectorLLRBT::preorder(Sector *_root) {
    if (_root == nullptr) {return;}

    std::cout << (_root->color ? "RED" : "BLACK") << " sector: " << _root->sector_code << "\n";
    preorder(_root->left);
    preorder(_root->right);
}

void SpaceSectorLLRBT::inorder(Sector *_root) {
    if (_root == nullptr) {return;}

    inorder(_root->left);
    std::cout << (_root->color ? "RED" : "BLACK") << " sector: " << _root->sector_code << "\n";
    inorder(_root->right);
}

void SpaceSectorLLRBT::postorder(Sector *_root) {
    if (_root == nullptr) {return;}

    postorder(_root->left);
    postorder(_root->right);
    std::cout << (_root->color ? "RED" : "BLACK") << " sector: " << _root->sector_code << "\n";
}

std::vector<Sector*> SpaceSectorLLRBT::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;

    if (root == nullptr) {
        return path;
    }

    traverseAndGetPath(origin, sector_code, path);
    clearVisitedFlags(root);
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    return path;
}

bool SpaceSectorLLRBT::traverseAndGetPath(Sector *_root, const std::string& code, vector<Sector *> &path) {
    if (_root == nullptr || _root->visited) {
        return false;
    }

    path.push_back(_root);
    _root->visited = true;

    if (_root->sector_code == code) {
        return true;
    }

    if (!traverseAndGetPath(_root->parent, code, path) && !traverseAndGetPath(_root->left, code, path)&& !traverseAndGetPath(_root->right, code, path)) {
        path.pop_back();
        _root->visited = false;
        return false;
    } else {
        return true;
    }

}

void SpaceSectorLLRBT::printStellarPath(const std::vector<Sector*>& path) {

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

void SpaceSectorLLRBT::optimizeTree(Sector *_root) {

    if (_root->left && _root->left->left && _root->left->color && _root->left->left->color) {
        rotateRight(_root);
        flipColors(_root->parent);
        return;
    }

    if (_root->right && _root->left && _root->right->color && _root->left->color) {
        flipColors(_root);
        return;
    }


    if (_root->right && _root->right->color) {
        rotateLeft(_root);
        return;
    }
}

void SpaceSectorLLRBT::flipColors(Sector *parent) {
    parent->left->color = parent->right->color = BLACK;
    parent->color = (parent == root) ? BLACK : RED;
}

void SpaceSectorLLRBT::rotateLeft(Sector *sector) {
    Sector* oldParent = sector;
    Sector* newParent = sector->right;
    Sector* newRightChild = newParent->left;

    newParent->color = oldParent->color;
    //todo: root için optimize et.
    if (oldParent->parent) {

        if (oldParent->parent->left == oldParent) {
            oldParent->parent->left = newParent;
        } else {
            oldParent->parent->right = newParent;
        }
    }

    newParent->parent = oldParent->parent;
    newParent->left = oldParent;
    oldParent->parent = newParent;

    oldParent->right = newRightChild;
    if (newRightChild) {
        newRightChild->parent = oldParent;
    }

    oldParent->color = RED;

    if (sector == root) {
        root = newParent;
        root->color = BLACK;
        root->parent = nullptr;
    }
}

void SpaceSectorLLRBT::rotateRight(Sector *sector) {
    Sector* oldParent = sector;
    Sector* newParent = sector->left;
    Sector* newLeftChild = newParent->right;
    newParent->color = oldParent->color;

    if (oldParent->parent) {

        if (oldParent->parent->left == oldParent) {
            oldParent->parent->left = newParent;
        } else {
            oldParent->parent->right = newParent;
        }
    }

    newParent->parent = oldParent->parent;
    newParent->right = oldParent;
    oldParent->parent = newParent;

    oldParent->left = newLeftChild;
    if (newLeftChild) {
        newLeftChild->parent = oldParent;
    }

    oldParent->color = RED;

    if (sector == root) {
        root = newParent;
        root->color = BLACK;
        root->parent = nullptr;
    }
}

void SpaceSectorLLRBT::clearVisitedFlags(Sector *sector) {
    if (sector == nullptr) {
        return;
    }

    sector->visited = false;
    clearVisitedFlags(sector->left);
    clearVisitedFlags(sector->right);
}

