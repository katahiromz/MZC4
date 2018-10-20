#include "MWavFile.hpp"

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        printf("Usage: MWavTest file.wav\n");
        return 0;
    }

    MWavFile file(argb[1]);
    file.dump_info();
    file.play();
    return 0;
}
