/* Example of the basic structure
 * to see the output, executes the binary
 * independantly from ctest */

#include <GLhf/GLhf.h>

#include <iostream>

class StructureExample : public GLhf::App
{
public:
    void Startup() override
    {
        std::cout << "============================== Startup ==============================\n";
    }

    void Render(double ct) override
    {
        std::cout << "|Rendering|";
    }

    void PollEvents(double ct) override
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