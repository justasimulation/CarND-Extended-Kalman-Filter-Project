#include "app.h"

App::App(std::string &input_file_name, std::string &output_file_name): storage_(input_file_name, output_file_name), measurement_device_(storage_)
{
}

void App::Run()
{
    while(MeasurementPackage* package = measurement_device_.GetNextMeasurement())
    {
        tracker_.ProcessMeasurement(*package);
        delete package;
    }
}