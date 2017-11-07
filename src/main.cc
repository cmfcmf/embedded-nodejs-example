#include <stdio.h>
#include "node.h"

int main(int argc, char* argv[]) {

    if (argc <= 1)
    {
        // TOOD: print usage
        return 1;
    }

    printf("Hello World from embedding C++!\n");
    node::Start(argc, argv);
    return 0;
}
