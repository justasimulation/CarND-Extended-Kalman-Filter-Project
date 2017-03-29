//
// Created by sergey on 29.03.17.
//

#ifndef EXTENDEDKF_STORAGE_H
#define EXTENDEDKF_STORAGE_H

#include <fstream>

#include "measurement_package.h"

class Storage
{
    private:
        std::ifstream input_file_;
        std::ofstream output_file_;

        void CheckFiles(std::string &input_file_name, std::string &output_file_name);

    public:
        Storage(std::string &input_file_name, std::string &output_file_name);
        MeasurementPackage* GetNextMeasurement();
};

#endif //EXTENDEDKF_STORAGE_H
