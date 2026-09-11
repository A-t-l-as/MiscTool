#include "KsTerrainDat.hpp"
#include "../MiscCompilator/MiscCompilatorStrings.hpp"
#include "Utils/CppWriter.hpp"
#include "Compilator/CompilatorValueTypes.hpp"

using namespace std;

void KsTerrainDat::ReadFrom(BinFile& bin_file)
{
    bin_file.ReadArray(this->m_file_signature, this->file_signature_size);

    this->m_tile_set_name = bin_file.ReadShortString();

    bin_file.ReadValue(this->m_const_values[0]);

    this->m_guid = bin_file.ReadGuid();

    this->m_data_segment = bin_file.ReadBuffer(KsTerrainDat::data_segment_size);

    this->m_terrain_name = bin_file.ReadString();

    for(int i = 1 ; i < KsTerrainDat::const_values_size; ++i)
        bin_file.ReadValue(this->m_const_values[i]);

}

void KsTerrainDat::WriteTo(BinFile& output_bin_file)
{
    output_bin_file.WriteValue(this->m_file_signature);

    output_bin_file.WriteShortStringWithLen(this->m_tile_set_name);

    output_bin_file.WriteValue(this->m_const_values[0]);

    output_bin_file.WriteGuid(this->m_guid);

    output_bin_file.WriteBuffer(this->m_data_segment);

    output_bin_file.WriteStringWithLen(this->m_terrain_name);

    for(int i = 1 ; i < KsTerrainDat::const_values_size; ++i)
        output_bin_file.WriteValue(this->m_const_values[i]);
}


string KsTerrainDat::ToString()
{
    stringstream ss;

    for (int i = 0; i < file_signature_size; ++i)
    {
        CW::WriteTrivialValue(ss, MiscCompilatorStrings::file_signature_value_name_str + to_string(i), this->m_file_signature[i], false);

        if (isalpha(this->m_file_signature[i]))
            ss << " // " << this->m_file_signature[i];

        ss << endl;
    }

    ss << endl;

    CW::WriteShortString(ss, MiscCompilatorStrings::tile_set_name_str, this->m_tile_set_name);

    CW::WriteTrivialValue
    (
        ss,
        MiscCompilatorStrings::const_value_name_str + std::to_string(0),
        m_const_values[0]
    );

    CW::WriteGuid(ss, MiscCompilatorStrings::guid_name_str, this->m_guid);

    size_t i = 0;
    for(uint8_t byte : this->m_data_segment)
    {
        CW::WriteTrivialValue
        (
            ss,
            MiscCompilatorStrings::data_name_str + std::to_string(i),
            byte
        );
        ++i;
    }

    CW::WriteString(ss, MiscCompilatorStrings::terrain_name_str, this->m_terrain_name);

    for(int i = 1; i < KsTerrainDat::const_values_size; ++i)
    {
        CW::WriteTrivialValue
        (
            ss,
            MiscCompilatorStrings::const_value_name_str + std::to_string(i),
            m_const_values[i]
        );
    }

    return ss.str();
}

