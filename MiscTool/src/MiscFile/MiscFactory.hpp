#ifndef MISC_FACTORY_HPP
#define MISC_FACTORY_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include <functional>
#include "KsTerrainDat.hpp"
#include "../MiscGlobals.hpp"

using MiscCreator = std::function<std::unique_ptr<IMisc>()>;

class MiscFactory
{
public:
    MiscFactory()
    {
        // Here we're mapping the next Misc:
        m_creators[MiscGlobals::ks_terrain_dat_file_type_name] =
            [](){ return std::make_unique<KsTerrainDat>(); };

        // ...

        // ---
    }

    std::unique_ptr<IMisc> Create(const std::string& type)
    {
        auto it = m_creators.find(type);
        if (it != m_creators.end())
        {
            return it->second();
        }
        return nullptr;
    }

private:
    std::unordered_map<std::string, MiscCreator> m_creators;

};

#endif // MISC_FACTORY_HPP end
