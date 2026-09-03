#ifndef MISC_EXPORTER_APP_HPP
#define MISC_EXPORTER_APP_HPP

#include <string>
#include <filesystem>
#include "Console/Console.hpp"
#include "System/IApp.hpp"
#include "Utils/Formats.hpp"
#include "../MiscFile/MiscFactory.hpp"
#include "../MiscFile/MiscFile.hpp"
#include "../MiscGlobals.hpp"
#include "Utils/Misc.hpp"


class MiscExporterApp : public IApp
{
public:
    constexpr const unsigned int static c_correct_number_of_args = 4;

    MiscExporterApp()
    {}

    int Run(int my_argc, char* my_argv[]) override
    {
        std::filesystem::path input_file_path;
        std::string file_type = {};

        if (my_argc == c_correct_number_of_args)
        {
            input_file_path = my_argv[2];
            file_type = my_argv[3];
            ArgcAndArgvExecution( my_argv[0], file_type );
        }
        else
        {
            StandardProgramExecution(input_file_path, file_type);
        }

        if(!std::filesystem::exists(input_file_path))
        {
            CONSOLE_OUT.PrintLn("The file with the path ", input_file_path.string(), " does not exist!");
            exit(EXIT_FAILURE);
        }


        MiscFile input_misc_file( MiscFactory().Create(file_type) );


        try
        {
            input_misc_file.LoadFrom(input_file_path);
        }
        catch(const std::invalid_argument& e)
        {
            CONSOLE_OUT.PrintLn(e.what());
            exit(EXIT_FAILURE);
        }
        catch(const std::runtime_error& r_e)
        {
            CONSOLE_OUT.PrintLn(r_e.what());
            exit(EXIT_FAILURE);
        }

        CONSOLE_OUT.PrintLn("Input file path = ", input_file_path.string());

        const std::filesystem::path output_file_path =
        input_file_path.parent_path()
        /
        (input_file_path.stem().string() + Formats::cpp_format_str_with_dot);

        DEBUG_PRINT("ParentPath = ", input_file_path.parent_path().string(), Mess::endl);

        CONSOLE_OUT.PrintLn("Output file path = ", output_file_path.string());

        input_misc_file.ExportTo(output_file_path);

        CONSOLE_OUT.PrintLn("DONE!");

        return EXIT_SUCCESS;
    }



private:

    void StandardProgramExecution(std::filesystem::path& input_file_path, std::string& file_type)
    {
        const std::vector<std::string> correct_file_types = { MiscGlobals::ks_terrain_dat_file_type_name };

        CONSOLE_OUT.PrintLn("Enter the path to the input file: ");
        CONSOLE_IN.Scan(input_file_path);

        CONSOLE_OUT.PrintLn("Choose file type [", MiscGlobals::ks_terrain_dat_file_type_name, "]: ");

        do
        {
            CONSOLE_IN.Scan(file_type);

            if (!Misc::CheckThatElementExistInVec(file_type, correct_file_types))
            {
                CONSOLE_OUT.PrintLn("Choose from the given file types...");
            }

        } while (!Misc::CheckThatElementExistInVec(file_type, correct_file_types));
    }


    void ArgcAndArgvExecution(const std::string& program_name, std::string& file_type)
    {
        const std::vector<std::string> correct_file_types =
        {
            MiscGlobals::ks_terrain_dat_file_type_name,
            '-' + std::string(MiscGlobals::ks_terrain_dat_file_type_name)
        };

        if (!Misc::CheckThatElementExistInVec(file_type, correct_file_types))
        {
            CONSOLE_OUT.PrintLn("You have entered an incorrect input file type.", Mess::endl,
                                "Use: ", program_name, " -e <misc_file> <",
                                correct_file_types[0], ",", correct_file_types[1], ">");

            exit(EXIT_FAILURE);
        }

        if (file_type == correct_file_types[1])
        {
            file_type = MiscGlobals::ks_terrain_dat_file_type_name;
        }
    }



};


#endif // MISC_EXPORTER_APP_HPP end
