#ifndef I_MISC_HPP
#define I_MISC_HPP

#include "File/BinFile.hpp"

class IMisc
{
public:
    virtual ~IMisc() = default;
    virtual void ReadFrom(BinFile& bin_file) = 0;
    virtual void WriteTo(BinFile& output_bin_file) = 0;
    virtual std::string ToString() = 0;
};

#endif // I_MISC_HPP end
