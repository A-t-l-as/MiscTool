#ifndef KS_TERRAIN_DAT_HPP
#define KS_TERRAIN_DAT_HPP

#include <cstdint>
#include <string>
#include <vector>
#include "File/BinFile.hpp"
#include "IMisc.hpp"

class KsTerrainDat : public IMisc
{
public:

    KsTerrainDat() :
        m_tile_set_name(std::string()),
        m_guid(std::string()),
        m_terrain_name(std::string())
    {}

    ~KsTerrainDat()
    {}

    void ReadFrom(BinFile& bin_file) override;

    void WriteTo(BinFile& output_bin_file) override;

    std::string ToString() override;

private:

    constexpr const unsigned int static file_signature_size = 4;
    uint8_t m_file_signature[file_signature_size] = { 0 };

    std::string m_tile_set_name;

    constexpr const unsigned int static const_values_size = 3;
    uint32_t m_const_values[const_values_size] = { 0 };

    std::string m_guid;

    constexpr const size_t static data_segment_size = 0x3DB;
    std::vector<uint8_t> m_data_segment = {};

    std::string m_terrain_name;


};



#endif // KS_TERRAIN_DAT_HPP end
