#include <std.h>


/*
  Deva Acquired Template
*/

string *races_allowed()
{
    return ({"human", "elf", "half-elf", "drow", "half-drow", "half-orc", "beastkin", "dwarf", "half-dwarf"});
}

int is_rollable() { return 0; } // not rollable in creation

mapping innate_spells()
{
    return ([ "holy smite"     : (["type" : "spell", "daily uses" : -1, "level required" : 0, ]),
              "dimension door" : (["type" : "spell", "daily uses" : -1, "level required" : 0, ]),
              "invisibility"   : (["type" : "spell", "daily uses" : -1, "level required" : 0, ]),
              "light"          : (["type" : "spell", "daily uses" : -1, "level required" : 0, ]),
              "aura of healing" : (["type" : "spell", "daily uses" : -1, "level required" : 0, ]),
              "true seeing"    : (["type" : "spell", "daily uses" : -1, "level required" : 0, ]),             
           ]);
}

int query_unbound_age()
{
    return 1;
}

int apply_template(object ob)
{
    ob->set_acquired_template("deva");
    return 1;
}

int remove_template(object ob)
{
    ob->set_acquired_template(0);
    return 1;
}
