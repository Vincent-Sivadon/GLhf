/* Example of the basic structure
 * to see the output, executes the binary
 * independantly from ctest */

#include <GLtemplate/GLtemplate.h>

#include <iostream>

class StructureExample : public App
{
public:
    void Startup() override
    {
        std::cout << "============================== Startup ==============================\n";
    }

    void Render(double time) override
    {
        std::cout << "|Rendering|";
    }

    void ProcessInput() override
    {
        std::cout << "|Processing Input|\n";

        exit(0); // leaving that message makes so we don't test shutdown, but it's more convenient
    }

    void Shutdown() override
    {
        std::cout << "\n============================== Shutdown ==============================\n";
    }

private:
    GLuint member;
};

DECLARE_MAIN(StructureExample);