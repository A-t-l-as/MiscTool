#ifndef MISC_IMPORTER_APP_HPP
#define MISC_IMPORTER_APP_HPP

#include <string>
#include <filesystem>
#include "Compilator/HashMapsBase.hpp"
#include "Console/Console.hpp"
#include "Utils/Formats.hpp"

#include "../MiscCompilator/MiscCompilator.hpp"

#include "System/IApp.hpp"
#include "Utils/Globals.hpp"


class MiscImporterApp : public IApp
{
public:

    constexpr const unsigned int static c_correct_number_of_args = 4;

    MiscImporterApp()
    {}

    int Run(int my_argc, char* my_argv[]) override
    {
        std::filesystem::path input_file_path;
        std::string output_file_format;

        if (my_argc == c_correct_number_of_args)
        {
            input_file_path  = my_argv[2];
            output_file_format = my_argv[3];
            CONSOLE_OUT.PrintLn("Input file path  = ", input_file_path);
            CONSOLE_OUT.PrintLn("Output file format = ", output_file_format);
        }
        else
        {
            StandardProgramExecution(input_file_path, output_file_format);
        }

        const std::string input_file_extension_with_dot = input_file_path.extension().string();
        // rozszerzenie pliku z kropka

        if (input_file_extension_with_dot != Formats::cpp_format_str_with_dot)
        {
            CONSOLE_OUT.PrintLn
                ("The specified input file is not a .cpp file. The program terminates with an error.");
            exit(EXIT_FAILURE);
        }

        if(!std::filesystem::exists(input_file_path))
        {
            CONSOLE_OUT.PrintLn("The file with the path ", input_file_path.string(), " does not exist!");
            exit(EXIT_FAILURE);
        }

        bool error_handler = Globals::success_code;

        if (input_file_extension_with_dot == Formats::cpp_format_str_with_dot)
        {
            BinFile output_bin_file;

            try
            {
                HashMapsBase hash_maps;
                hash_maps.Init();

                MiscCompilator(output_bin_file, hash_maps, error_handler).CompileFile(input_file_path);
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

            const std::filesystem::path output_bin_file_path =
                input_file_path.parent_path() / ( input_file_path.stem().string() + '.' + output_file_format );

            DEBUG_PRINT("ParentPath: ", input_file_path.parent_path().string(), Mess::endl);
            DEBUG_PRINT("output_file_path: ", output_bin_file_path.string(), Mess::endl);

            CONSOLE_OUT.PrintLn("Output file path = ", output_bin_file_path.string());
            output_bin_file.SaveTo(output_bin_file_path);
        }

        if(error_handler == Globals::success_code)
        {
            CONSOLE_OUT.PrintLn(Mess::endl, "The ", input_file_path.string(), " was compiled successfully...");
        }
        else
        {
            CONSOLE_OUT.PrintLn
            (
                "An error occurred during compilation ",
                input_file_path,
                ". The compiler has been terminated."
            );

            exit(EXIT_FAILURE);
        }

        return EXIT_SUCCESS;
    }


private:

    void StandardProgramExecution
        (std::filesystem::path& input_file_path, std::string& output_file_format)
    {
        CONSOLE_OUT.Print("Enter the path to the input file: "); CONSOLE_IN.Scan(input_file_path);
        CONSOLE_OUT.Print("Enter the output file format: "); CONSOLE_IN.Scan(output_file_format);
    }

};

#endif // MISC_IMPORTER_APP_HPP end
