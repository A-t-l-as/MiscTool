#ifndef MISC_TOOLAPP_HPP
#define MISC_TOOLAPP_HPP

#include "System/HybridApp.hpp"
#include "MiscExporterApp.hpp"
#include "MiscImporterApp.hpp"

class MiscToolApp : public HybridApp
{
public:
    MiscToolApp()
    {}

protected:

    void ShowStartScreen() override
    {
        CONSOLE_OUT.PrintLn("*******************", Mess::endl,
                            "|MiscTool by ATLAS|", Mess::endl,
                            "********2026*******");
    }

    void RunExporter(int my_argc, char* my_argv[]) override
    {
        MiscExporterApp().Run(my_argc, my_argv);
    }

    void RunImporter(int my_argc, char* my_argv[]) override
    {
        MiscImporterApp().Run(my_argc, my_argv);
    }

};


#endif // MISC_TOOLAPP_HPP end
