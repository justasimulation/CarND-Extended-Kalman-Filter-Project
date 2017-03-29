//
// Created by sergey on 29.03.17.
//

#ifndef EXTENDEDKF_APP_H
#define EXTENDEDKF_APP_H

#include <iostream>
#include <memory>

#include "storage.h"
#include "measurement_device.h"
#include "tracker.h"

class App
{
    private:
        Storage storage_;
        MeasurementDevice measurement_device_;
        Tracker tracker_;

    public:
        App(std::string &input_file_name, std::string &output_file_name);
        void Run();
};

#endif //EXTENDEDKF_APP_H
