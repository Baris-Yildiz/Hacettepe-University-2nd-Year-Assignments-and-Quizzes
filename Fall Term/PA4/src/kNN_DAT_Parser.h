#ifndef KNN_DAT_PARSER_H
#define KNN_DAT_PARSER_H

#include "kNN_Data.h"

#include <fstream>
#include <sstream>
#include <string>

class kNN_Dat_Parser {
public:
    // Function to parse the .dat file and return a Dataset object
    Dataset parse(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        Dataset dataset;
        bool readingData = false;

        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << filename << std::endl;
            return dataset; // Return an empty dataset
        }

        while (getline(file, line)) {
            if (line.empty() || line[0] == '#') {
                if (line.find("Threshold") != std::string::npos) {
                    // Next line should contain the threshold value
                    if (getline(file, line)) {
                        dataset.threshold = std::stod(line);
                    }
                }
                continue;
            }

            if (!readingData) {
                // Read header
                std::istringstream iss(line);
                std::string headerItem;
                while (getline(iss, headerItem, ',')) {
                    dataset.header.push_back(headerItem);
                }
                readingData = true;
            } else {
                // Read data point
                std::istringstream iss(line);
                std::vector<double> features;
                std::string feature;
                std::string label;

                while (getline(iss, feature, ',')) {
                    if (std::istringstream(feature) >> std::ws && iss.peek() == std::istringstream::traits_type::eof()) {
                        // Last item is the label
                        label = feature;
                    } else {
                        features.push_back(std::stod(feature));
                    }
                }

                dataset.points.emplace_back(features, label);
            }
        }

        file.close();
        return dataset;
    }

private:
    // Add private member variables or methods if needed

    // Method to handle specific parsing requirements for kNN, like feature extraction, label handling, etc.
};

#endif // KNN_DAT_PARSER_H
