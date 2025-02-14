#include "../../newbie.h"
inherit ROOM;

void create() {
   ::create();
   set_property("indoors",0);
   set_property("light",2);
   set_terrain(CITY);
   set_travel(PAVED_ROAD);
   set_name("Sunset Way in Offestry");
   set_short("%^RESET%^%^GREEN%^Sunset Way in Offestry");
   set_long("%^RESET%^%^GREEN%^Sunset Way in Offestry%^RESET%^\n"
"You are standing on Sunset Way, which leads east back to the Offestry town square and continues west. The cobblestone %^ORANGE%^streets %^RESET%^are smooth beneath your feet, granting passage to the light but "
"steady stream of %^CYAN%^traffic %^RESET%^that passes through the town on a daily basis.  The street is bordered on both "
"sides by a jumble of %^RED%^buildings%^RESET%^. To the north the closest of which is a clothing store with its doors open to welcome customers. "
"To the south the closest of which is the general store with its doors open to welcome customers.%^RESET%^\n");
   set("night long", ""+TO->query_long()+"\n%^BOLD%^The street light glows brightly to light your way.");
   set_listen("default","You hear snatches of conversation from passersby.");
   set_smell("default","The air is fresh and clean.");
   set_items(([
     "streets":"%^ORANGE%^The streets are newly cobbled and well-kept, polished smooth by the passage of so many "
"travellers.  Sunset Way trails east, back towards the square which serves as the heart of this town.  West, it "
"curves away towards the western town gate.%^RESET%^",
     "traffic":"%^CYAN%^A light but steady stream of traffic passes along this street.  Chatter so often fills the air, "
"varying in topic from price bartering, through to tales of grand adventures beyond the gates of the town.%^RESET%^",
     "buildings":"%^RED%^A hodgepodge of buildings rise up along both sides of the street.  Their age and vastly "
"varied styles give a unique appearance to the cosy town around you, where no two buildings are the same.  Nearest is the "
"clothing and general stores.%^RESET%^",
   ]));
   set_exits(([
      "west":MAINTOWN"wstreet2",
      "east":MAINTOWN"square",
      "north":MAINTOWN"clothing",
      "south":MAINTOWN"general",
   ]));
}

void reset(){
   ::reset();
   if(!present("street_light",TO)) new(MISCDIR+"street_light")->move(TO);
}