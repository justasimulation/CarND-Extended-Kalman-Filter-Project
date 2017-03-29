#include <iostream>
#include <fstream>

#include "storage.h"

using namespace std;
using namespace Eigen;

void Storage::CheckFiles(string& input_file_name, string& output_file_name)
{
    if (!input_file_.is_open())
    {
        cerr << "Cannot open input file: " << input_file_name << endl;
        exit(EXIT_FAILURE);
    }

    if (!output_file_.is_open())
    {
        cerr << "Cannot open output file: " << output_file_name << endl;
        exit(EXIT_FAILURE);
    }
}

Storage::Storage(std::string &input_file_name, std::string &output_file_name):
        input_file_(input_file_name.c_str(), ifstream::in),
        output_file_(output_file_name.c_str(), ofstream::out)
{
    CheckFiles(input_file_name, output_file_name);
}

MeasurementPackage* Storage::GetNextMeasurement()
{
    string line;
    if(getline(input_file_, line))
    {
        string sensor_type;
        istringstream iss(line);
        long long timestamp;

         MeasurementPackage* package = new MeasurementPackage();

        // reads first element from the current line
        iss >> sensor_type;
        if (sensor_type.compare("L") == 0)
        {
            // LASER MEASUREMENT

            // read measurements at this timestamp
            package->sensor_type_ = MeasurementPackage::LASER;
            package->raw_measurements_ = VectorXd(2);
            float x;
            float y;
            iss >> x;
            iss >> y;
            package->raw_measurements_ << x, y;
            iss >> timestamp;
            package->timestamp_ = timestamp;
        }
        else if (sensor_type.compare("R") == 0)
        {
            // RADAR MEASUREMENT

            // read measurements at this timestamp
            package->sensor_type_ = MeasurementPackage::RADAR;
            package->raw_measurements_ = VectorXd(3);
            float ro;
            float phi;
            float ro_dot;
            iss >> ro;
            iss >> phi;
            iss >> ro_dot;
            package->raw_measurements_ << ro, phi, ro_dot;
            iss >> timestamp;
            package->timestamp_ = timestamp;
        }
        else
        {
            cerr << "Uknown sensor type: " << sensor_type << endl;
            exit(EXIT_FAILURE);
        }

        // read ground truth data to compare later
        float x_gt;
        float y_gt;
        float vx_gt;
        float vy_gt;
        iss >> x_gt;
        iss >> y_gt;
        iss >> vx_gt;
        iss >> vy_gt;
        package->ground_truth_ = VectorXd(4);
        package->ground_truth_ << x_gt, y_gt, vx_gt, vy_gt;

        return package;
    }
    else
    {
        return NULL;
    }
}