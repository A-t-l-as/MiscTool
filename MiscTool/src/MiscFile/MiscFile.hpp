#ifndef MISC_FILE_HPP
#define MISC_FILE_HPP

#include "Compilator/HashMapsBase.hpp"
#include "File/BinFile.hpp"
#include "File/TextFile.hpp"
#include "IMisc.hpp"
#include "../MiscCompilator/MiscCompilator.hpp"
#include "Utils/Globals.hpp"
#include "../MiscGlobals.hpp"

class MiscFile
{
public:

    explicit MiscFile(std::unique_ptr<IMisc> misc_strategy = nullptr) :
        m_misc_strategy(std::move(misc_strategy)),
        m_error_handler(Globals::success_code)
    {}

    void ParseFrom(const std::filesystem::path& arg_input_file_path)
    {
        if (!this->m_misc_strategy)
            throw std::logic_error(MiscGlobals::misc_file_error_str);

        if(!std::filesystem::exists(arg_input_file_path))
            throw std::invalid_argument("The file with the path " + arg_input_file_path.string()
                                        + " does not exist!");

        BinFile bin_file;

        HashMapsBase hash_maps;
        hash_maps.Init();

        MiscCompilator(bin_file, hash_maps, this->m_error_handler).CompileFile(arg_input_file_path);

        if(this->m_error_handler == Globals::success_code)
        {
            try
            {
                this->m_misc_strategy->ReadFrom(bin_file);
            }
            catch(const std::out_of_range& e_out_of_range)
            {
                throw std::runtime_error
                    ("The parsed " + arg_input_file_path.string() +
                    " file was empty or contained invalid information!");
            }
        }
    }


    void LoadFrom(const std::filesystem::path& arg_input_file_path)
    {
        if (!this->m_misc_strategy)
            throw std::logic_error(MiscGlobals::misc_file_error_str);

        if(!std::filesystem::exists(arg_input_file_path))
            throw std::invalid_argument
                ("The file with the path " + arg_input_file_path.string() + " does not exist!");

        BinFile input_bin_file;
        input_bin_file.LoadFrom(arg_input_file_path);

        try
        {
            this->m_misc_strategy->ReadFrom(input_bin_file);
        }
        catch(const std::out_of_range& e_out_of_range)
        {
            throw std::runtime_error
                ("The loaded " + arg_input_file_path.string()
                                     + " file is empty or contains invalid information!");
        }
    }

    void SaveTo(const std::filesystem::path& arg_output_file_path)
    {
        if (!this->m_misc_strategy)
            throw std::logic_error(MiscGlobals::misc_file_error_str);

        if(this->m_error_handler == Globals::success_code)
        {
            BinFile output_bin_file;
            this->m_misc_strategy->WriteTo(output_bin_file);
            output_bin_file.SaveTo(arg_output_file_path);
        }
    }

    void ExportTo( const std::filesystem::path& arg_output_file_path)
    {
        if (!this->m_misc_strategy)
            throw std::logic_error(MiscGlobals::misc_file_error_str);

        TextFile output_text_file;

        output_text_file << m_misc_strategy->ToString();

        output_text_file.SaveOnlyStringStream(arg_output_file_path);
    }


    bool GetErrorHandler() const { return this->m_error_handler; }

private:
    std::unique_ptr<IMisc> m_misc_strategy;
    bool m_error_handler;
};


#endif // MISC_FILE_HPP end
