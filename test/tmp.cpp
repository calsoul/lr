
#include <iostream>

int main() {
    for (int i = 1; i < 100; ++i) {
        std::cout << i<<"%"<<16<<"="<< (i & (15)) << " ";
        if ( i % 10 == 0 ) {
      std::cout << std::endl;
        }
    }

    return 0;
}
