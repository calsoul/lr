#include <stdlib.h>
#include <stdio.h>

#include "lr/handler.h"
#include "lr/line.h"

int main(const int argc, const char **argv) {
    Line l;
    Handler handler;

    l.set_lr_handlers(
        &handler, &handler
    );

    if ( l.init("line.conf") < 0 ) {
        printf("%s %s %d\n",
            __FILE__, __func__, __LINE__
        );
        return -1;
    }
    if ( l.start() < 0 ) {
        printf("%s %s %d\n",
            __FILE__, __func__, __LINE__
        );
        return -1;
    }

    l.wait();

    printf("%s %s %d %s\n",
        __FILE__, __func__, __LINE__,
        "line stop."
    );
    return 0;
}
