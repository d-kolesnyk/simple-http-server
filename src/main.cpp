#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <path to config>" << std::endl;
        return 1;
    }

    return 0;
}
// TEST
