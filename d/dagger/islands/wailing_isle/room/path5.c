// Chernobog & Titania (3/4/22)
// Wailing Isle - Path

#include <std.h>
#include "../defs.h"
inherit INH+"path";

void create(){
    ::create();
    set_exits(([
        "west" : ROOMS"path4",
        "northeast" : ROOMS"path6",
        ]));
}

