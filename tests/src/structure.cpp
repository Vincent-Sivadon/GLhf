/* Example of the basic structure
 * to see the output, executes the binary
 * independantly from ctest */

#include <GLtemplate/GLtemplate.h>

#include <iostream>

class StructureExample : public App
{
public:
    void startup() override
    {
        std::cout << "============================== Startup ==============================\n";
    }

    void render(double time) override
    {
        std::cout << "|Rendering|";
    }

    void processInput() override
    {
        std::cout << "|Processing Input|";

        exit(0); // leaving that message makes so we don't test shutdown, but it's more convenient
    }

    void shutdown() override
    {
        std::cout << "\n============================== Shutdown ==============================\n";
    }

private:
    GLuint member;
};

DECLARE_MAIN(StructureExample);