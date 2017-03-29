#include <iostream>
#include <memory>
#include "app.h"

using namespace std;

void check_arguments(int argc, char* argv[])
{
    string usage_instructions = "Usage instructions: ";
    usage_instructions += argv[0];
    usage_instructions += " path/to/input.txt output.txt";

    bool has_valid_args = false;

    // make sure the user has provided input and output files

    if (argc == 1)
    {
        cerr << usage_instructions << endl;
    }
    else if (argc == 2)
    {
        cerr << "Please include an output file.\n" << usage_instructions << endl;
    }
    else if (argc == 3)
    {
        has_valid_args = true;
    }
    else if (argc > 3)
    {
        cerr << "Too many arguments.\n" << usage_instructions << endl;
    }

    if (!has_valid_args)
    {
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[])
{
    //check_arguments(argc, argv);

    string in_file_name_ = "../data/sample-laser-radar-measurement-data-2.txt";//argv[1];
    string out_file_name_ = "output.txt";//argv[2];

    App app(in_file_name_, out_file_name_);
    app.Run();

    return 0;
}
