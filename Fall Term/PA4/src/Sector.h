#ifndef SECTOR_H
#define SECTOR_H

#include <string>
#include "unordered_map"

// Define color constants for Red-Black Tree
const bool RED = true;
const bool BLACK = false;

class Sector {
public:

    Sector(int x, int y, int z); // Constructor declaration
    ~Sector(); // Destructor

    int x, y, z; // Coordinates of the sector 
    double distance_from_earth; // Calculated Euclidean distance from the Earth
    std::string sector_code; // Unique identifier based on coordinates and distance
    Sector *left, *right, *parent; // Pointers to child and parent nodes
    bool color; // Node color for Red-Black Tree

    bool visited;


    // Overloaded operators
    Sector& operator=(const Sector& other);
    bool operator==(const Sector& other) const;
    bool operator!=(const Sector& other) const;

    int compareTo(const Sector& other) const;

    void resetCoordinates(int x, int y, int z);


private:
    void setDistance();
    void setSectorCode();
    std::unordered_map<char, std::pair<char, char>> coordinateSymbols;
    char getCoordinateCode(const char& coordinate);
    
};

#endif // SECTOR_H
