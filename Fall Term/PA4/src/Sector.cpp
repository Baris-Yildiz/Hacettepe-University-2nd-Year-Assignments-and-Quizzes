#include "Sector.h"
#include "sstream"
#include "unordered_map"
#include "cmath"

// Constructor implementation

Sector::Sector(int x, int y, int z) : x(x), y(y), z(z), left(nullptr), right(nullptr), parent(nullptr), color(RED), visited(false) {
        // TODO: Calculate the distance to the Earth, and generate the sector code
    coordinateSymbols['x'] = {'R', 'L'};
    coordinateSymbols['y'] = {'U', 'D'};
    coordinateSymbols['z'] = {'F', 'B'};
    setDistance();
    setSectorCode();
}

Sector::~Sector() {
    // TODO: Free any dynamically allocated memory if necessary
}

Sector& Sector::operator=(const Sector& other) {
    // TODO: Overload the assignment operator

    if (this == &other) {
        return *this;
    }

    auto* otherSector = new Sector(other.x, other.y, other.z);
    resetCoordinates(other.x, other.y, other.z);

    this->color = otherSector->color;
    
    this->left = otherSector->left;
    this->right = otherSector->right;
    this->parent = otherSector->parent;

    return *this;
}

bool Sector::operator==(const Sector& other) const {
    return (x == other.x && y == other.y && z == other.z);
}

bool Sector::operator!=(const Sector& other) const {
    return !(*this == other);
}

int Sector::compareTo(const Sector& other) const {
    if (other.x != x) {
        return x - other.x;
    } 

    if (other.y != y) {
        return y - other.y;
    } 

    if (other.z != z) {
        return z - other.z;
    } 

    return 0;
}

void Sector::setDistance() {
    distance_from_earth = std::sqrt(x*x + y*y + z*z);
}

void Sector::setSectorCode() {
    std::stringstream code;
    code << std::floor(distance_from_earth);
    code << getCoordinateCode('x') << getCoordinateCode('y') << getCoordinateCode('z');
    sector_code = code.str();
}

void Sector::resetCoordinates(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;

    setDistance();
    setSectorCode();
}

char Sector::getCoordinateCode(const char& coordinate) {
    
    int value = 0;
    switch (coordinate)
    {
        case 'x':
            value = x;
            break;
        case 'y':
            value = y;
            break;
        case 'z':
            value = z;
            break;
        default:
            break;
    }
    
    if (value == 0) {
        return 'S';
    } else if (value > 0) {
        return coordinateSymbols[coordinate].first;
    } else {
        return coordinateSymbols[coordinate].second;
    }
}

