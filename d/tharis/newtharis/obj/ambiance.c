#include <std.h>
#include <magic.h>
inherit OBJECT;

void notify_me();

void create() {
   ::create();
   set_name("tharisambiance");
   set_id(({"tharisambiancexxx"}));
   set_short("");
   set_long("");
   set_weight(0);
   set_property("no animate",1);
   set_heart_beat(1);
}

void init() {
   ::init();
   if(userp(ETO)) call_out("notify_me",1);
}

void heart_beat() {
   string roomname;
   int i, playershere, chance;
   object *userobs;
   if(!objectp(ETO)) { TO->remove(); return; }
   if(!userp(ETO)) { TO->remove(); return; }
   if(!objectp(EETO)) { TO->remove(); return; }

   roomname = base_name(EETO);
   if(strsrch(roomname,"/d/tharis/newtharis/") == -1) {
     tell_object(ETO,"%^BLUE%^You can't help but relax just a little on leaving the confines of Tharis City.%^RESET%^");
     TO->remove();
     return;
   }

// here is the place to put eventual reactions to the area -> eg/ a fight may call guards
//   if(sizeof(ETO->query_attackers())) do_guard_stuff;

// now let's run ambiance! This is just to make the city feel lively.
   userobs = all_living(EETO);
   if(!sizeof(userobs)) return; // noone's here? This shouldn't trigger but just to be safe.
   playershere = 0;
   for(i=0;i<sizeof(userobs);i++) {
     if(userp(userobs[i])) playershere++; // playershere = makes it go off less often if there's more players potentially hitting emotes.
   }
   
   if(strsrch(roomname,"rooms/eastplaza") != -1) {
     chance = 90*playershere;
     if(random(chance)) return;
     switch(random(75)) {
       case 0..24:
       tell_room(EETO,"%^RESET%^%^CRST%^%^C244%^One of the %^C241%^sleek black %^C244%^horseless carriages glides along the c%^RESET%^%^C022%^o%^RESET%^%^C249%^b%^C247%^b%^C246%^l%^C245%^e%^C246%^s%^C247%^t%^RESET%^%^C028%^o%^RESET%^%^C250%^n%^C244%^e street toward the %^C241%^tunnel %^C244%^to the south.%^CRST%^");
       break;
       case 25..49:
       tell_room(EETO,"%^RESET%^%^CRST%^%^C136%^A %^RESET%^%^C094%^supply cart %^RESET%^%^C136%^carrying goods from the %^RESET%^%^C058%^docks%^RESET%^%^C136%^ rumbles past, taking the west exit of the roundabout to head toward the city bazaar.%^CRST%^");
       break;
       default:
       tell_room(EETO,"%^RESET%^%^CRST%^%^C123%^A %^C045%^young boy %^RESET%^%^C123%^runs up to one of the %^RESET%^%^C241%^statues%^RESET%^%^C123%^, his %^RESET%^%^C218%^mother %^RESET%^%^C123%^giving chase and scooping him into her arms, %^RESET%^%^C088%^s%^C124%^c%^C160%^o%^C196%^l%^C160%^d%^C124%^i%^C088%^n%^C124%^g %^RESET%^%^C123%^him for running so close to the street.%^CRST%^");
       break;
     }
     return;
   }
   if(strsrch(roomname,"rooms/east") != -1) {
     chance = 240*playershere;
     if(random(chance)) return;
     switch(random(100)) {
       case 0..24:
       tell_room(EETO,"%^RESET%^%^CRST%^%^C141%^A %^RESET%^%^C099%^young woman %^RESET%^%^C141%^pushes a stroller down the sidewalk.%^CRST%^");
       break;
       case 25..49:
       tell_room(EETO,"%^RESET%^%^CRST%^%^C123%^An older gentleman makes his way from tree to tree, picking the ripe %^C196%^f%^C197%^r%^C203%^u%^C202%^i%^C208%^t %^RESET%^%^C123%^and placing it in a %^C094%^wicker basket%^RESET%^%^C123%^.%^CRST%^");
       break;
       case 50..74:
       tell_room(EETO,"%^RESET%^%^CRST%^%^C028%^A gentle %^C027%^b%^C033%^r%^C039%^e%^C033%^e%^C039%^z%^C027%^e%^RESET%^%^C028%^ blows through the area, rustling the leaves of the %^C196%^f%^C197%^r%^C203%^u%^C202%^i%^C208%^t %^C214%^t%^C131%^r%^C132%^e%^C126%^e%^C127%^s%^RESET%^%^C028%^.%^CRST%^");
       break;
       default:
       tell_room(EETO,"%^RESET%^%^CRST%^%^C105%^A handsome young man and graceful older woman walk arm-in-arm down the sidewalk, chatting and laughing %^RESET%^%^C171%^h%^C183%^a%^C189%^p%^RESET%^%^C231%^p%^C225%^i%^C219%^l%^C213%^y%^RESET%^%^C105%^.%^CRST%^");
       break;
     }
     return;
   }
   if(strsrch(roomname,"rooms/elf1") != -1 || strsrch(roomname,"rooms/elf2") != -1) {
     chance = 240*playershere;
     if(random(chance)) return;
     switch(random(100)) {
       case 0..24:
       tell_room(EETO,"%^RESET%^%^CRST%^C241%^A lithe shadowy figure slips between the buildings and disappears from view.%^CRST%^");
       break;
       case 25..49:
       tell_room(EETO,"%^RESET%^%^CRST%^%^C094%^A %^C088%^h%^C124%^o%^C088%^bg%^C124%^o%^C088%^blin %^C094%^in %^RESET%^%^C241%^dark s%^C246%^t%^C248%^u%^C250%^dd%^C248%^e%^C241%^d leathers %^RESET%^%^C094%^and carrying a large %^RESET%^%^C248%^sword %^RESET%^%^C094%^departs the compound to the north, traipsing eastward.%^CRST%^");
       break;
       case 50..74:
       tell_room(EETO,"%^RESET%^%^CRST%^%^C028%^A gentle %^C027%^b%^C033%^r%^C039%^e%^C033%^e%^C039%^z%^C027%^e%^RESET%^%^C028%^ blows through the area, causing the large %^C124%^f%^C196%^l%^C241%^a%^C124%^g %^RESET%^%^C028%^flying high above the compound to snap sharply.%^CRST%^");
       break;
       default:
       tell_room(EETO,"%^RESET%^%^CRST%^%^C100%^A %^RESET%^%^C058%^cart %^C100%^carrying supplies rumbles up to the great wooden gates of the %^RESET%^%^C241%^compound%^RESET%^%^C100%^. A moment later the gates open, allowing it to roll in and providing the briefest glimpse of the courtyard beyond, full of training %^RESET%^%^C244%^soldiers%^C100%^.%^CRST%^");
       break;
     }
     return;
   }
   if(strsrch(roomname,"rooms/elf3") != -1) {
     chance = 240*playershere;
     if(random(chance)) return;
     switch(random(75)) {
       case 0..24:
       tell_room(EETO,"%^RESET%^%^CRST%^%^C081%^A group of %^RESET%^%^C058%^students %^C081%^passes by, prattling on about the %^RESET%^%^C202%^p%^C208%^h%^C214%^y%^C220%^s%^C214%^i%^C208%^c%^C202%^s %^RESET%^%^C081%^of %^C057%^d%^C056%^e%^C055%^m%^C054%^i%^C053%^pl%^C054%^a%^C055%^n%^C056%^e%^C057%^s%^RESET%^%^C081%^.%^CRST%^");
       break;
       case 25..49:
       tell_room(EETO,"%^RESET%^%^CRST%^%^C045%^The %^RESET%^%^C241%^iron gate %^C045%^swings open and out steps a man with a long %^RESET%^%^C247%^gr%^C250%^a%^C247%^y b%^C250%^e%^C252%^a%^C247%^rd %^RESET%^%^C045%^and a %^C027%^third eye %^RESET%^%^C045%^painted upon his %^RESET%^%^C058%^swarthy brow%^C045%^. He touches a finger to his temple and begins to %^C087%^levitate%^C045%^, turning to glide westward.%^CRST%^");
       break;
       default:
       tell_room(EETO,"%^RESET%^%^CRST%^%^C061%^A sleek %^RESET%^%^C241%^horseless carriage %^RESET%^%^C061%^comes to a stop outside the %^C241%^iron gates %^RESET%^%^C061%^and a woman draped in %^C123%^s%^C159%^t%^C195%^a%^C230%^r%^C159%^r%^C123%^y %^C045%^b%^C051%^l%^C087%^u%^C123%^e %^C159%^r%^C123%^o%^C087%^b%^C051%^e%^C045%^s %^RESET%^%^C061%^climbs out, followed by a small retinue that %^RESET%^%^C036%^h%^C037%^u%^C038%^s%^C039%^t%^C038%^l%^C037%^e%^C036%^s %^RESET%^%^C061%^to keep up with her as she heads toward the academy.%^CRST%^");
       break;
     }
     return;
   }
   if(strsrch(roomname,"rooms/square") != -1 || strsrch(roomname,"rooms/fountain") != -1) {
     chance = 90*playershere;
     if(random(chance)) return;
     switch(random(100)) {
       case 0..5:
       tell_room(EETO,"%^CYAN%^A well-dressed woman bustles past, multiple bags of shopping on each arm.%^RESET%^");
       break;
       case 6..10:
       tell_room(EETO,"%^BOLD%^%^BLACK%^A small child jostles past you and goes running off into the crowd. You quickly check that your coins are still in your pocket!%^RESET%^");
       break;
       case 11..15:
       tell_room(EETO,"%^YELLOW%^You can't help but jump as a stall-keeper at the stall beside you raises his voice to shout! Fine wares! Great bargains! Come see!%^RESET%^");
       break;
       case 16..20:
       tell_room(EETO,"%^BOLD%^%^GREEN%^A nearby stall-keeper gives you a greasy smile and motions to his wares.%^RESET%^");
       break;
       case 21..30:
       tell_room(EETO,"%^BLUE%^A squadron of guards stride past, and the citizens are quick to get out of their way. Unlike the rest of the people here, they seem to have no trouble clearing a path.%^RESET%^");
       break;
       case 31..35:
       tell_room(EETO,"%^BOLD%^%^MAGENTA%^A sharp wail goes up, a few stalls over, as a child starts throwing a great tantrum. His mother looks terribly embarassed as she hurries away, the youngster in tow.%^RESET%^");
       break;
       case 36..40:
       tell_room(EETO,"%^GREEN%^A young, scruffy woman glances warily side to side, slinking through the crowd and disappearing. You're sure you saw her filch something from that stall!%^RESET%^");
       break;
       case 41..45:
       tell_room(EETO,"%^BOLD%^%^BLUE%^A gang of young, rough-looking youths strut into the area and peer about with hard expressions and arrogant sneers. The rest of the citizenry give them a wary berth as they move on through the bazaar.%^RESET%^");
       break;
       case 46..50:
       tell_room(EETO,"%^MAGENTA%^A rowdy group of young men, probably nobles, laugh and banter as they push through the crowds.%^RESET%^");
       break;
       case 51..55:
       tell_room(EETO,"%^BOLD%^%^BLACK%^A shadowy, cowled figure passes you, confident strides carrying him swiftly elsewhere. All eyes seem to be on him as he passes, despite his unassuming appearance.%^RESET%^");
       break;
       case 56..60:
       tell_room(EETO,"%^MAGENTA%^A raven-haired woman passes, openly bearing the symbol of Lord Shadow upon a pendant at her throat. Several citizens murmur a few words and bow as she passes, making at least a show of respect.%^RESET%^");
       break;
       case 61..65:
       tell_room(EETO,"%^ORANGE%^A ragged youth is grabbed forcefully by one of several passing guards, and dragged unwillingly down the street, even as he loudly proclaims his innocence to anything and everything.%^RESET%^");
       break;
       case 66..70:
       tell_room(EETO,"%^BOLD%^%^CYAN%^Leaping and shouting like a thing possessed, a madman staggers down the road. Most ignore him, though some push him away forcefully until he moves on.%^RESET%^");
       break;
       case 71..75:
       tell_room(EETO,"%^ORANGE%^Just off to the side, a dirty street-child stands by a fruit cart, staring longingly at the produce being sold. The stern glare of the stall-keeper seems enough, however, to keep him at bay. Eventually he gives up and runs off.%^RESET%^");
       break;
       case 76..80:
       tell_room(EETO,"%^CYAN%^Well-dressed and impeccably groomed, you can't help but be surprised to see a young man a few feet away surrepticiously lift the purse of another citizen. He doesn't even break stride as he slips it into his pocket and vanishes into the crowds.%^RESET%^");
       break;
       case 81..85:
       tell_room(EETO,"%^GREEN%^A well-groomed merchant speaks in hushed tones with a nearby stall-keeper, attempting to haggle a price down to his likings.%^RESET%^");
       break;
       case 86..90:
       tell_room(EETO,"%^BLUE%^Voices are raised as haggling at a nearby stall becomes more of an argument. The irate customer comes storming past, muttering imprecations to the air.%^RESET%^");
       break;
       default:
       tell_room(EETO,"%^ORANGE%^The crowd thickens momentarily as several groups converge and attempt to pass all at once, jostling you about.%^RESET%^");
       break;
     }
     return;
   }
   if(strsrch(roomname,"rooms/tunnel") != -1) {
     chance = 360*playershere;
     if(random(chance)) return;
     switch(random(60)) {
       case 0..10:
       tell_room(EETO,"%^CYAN%^The silence here bears an almost tangible weight that makes you feel uncomfortable.%^RESET%^");
       break;
       case 11..20:
       tell_room(EETO,"%^ORANGE%^A shadowy form slinks along further up the winding tunnel and is lost to view.%^RESET%^");
       break;
       case 21..30:
       tell_room(EETO,"%^BOLD%^%^BLACK%^You hear a few muffled noises from the city far above.%^RESET%^");
       break;
       case 31..40:
       tell_room(EETO,"%^GREEN%^You only see the shadowy form at the very last moment, as it flits past you and vanishes again, almost one with the shadows.%^RESET%^");
       break;
       case 41..50:
       tell_room(EETO,"%^BLUE%^A furtive figure slinks closer, keeping well to the other side of the dimly lit tunnel as it passes you and quickly disappears into the darkness.%^RESET%^");
       break;
       default:
       tell_room(EETO,"%^YELLOW%^The echo of distant shouting sounds down the length of the winding tunnel.%^RESET%^");
       break;
     }
     return;
   }
   if(strsrch(roomname,"sewers") != -1) {
     chance = 360*playershere;
     if(random(chance)) return;
     switch(random(90)) {
       case 0..10:
       tell_room(EETO,"%^CYAN%^Liquid drips from somewhere in the darkness above.%^RESET%^");
       break;
       case 11..20:
       tell_room(EETO,"%^ORANGE%^A rodent (or something else?) screeches somewhere further along the sewers.%^RESET%^");
       break;
       case 21..30:
       tell_room(EETO,"%^BOLD%^%^BLACK%^You catch a glimpse of movement further up the sewer tunnel.%^RESET%^");
       break;
       case 31..40:
       tell_room(EETO,"%^GREEN%^A waft of choking stench filters past you, even worse than the usual smell of the filth here.%^RESET%^");
       break;
       case 41..50:
       tell_room(EETO,"%^BLUE%^A furtive figure slinks closer, keeping well to the other side of the sewer tunnel as it passes you and quickly disappears into the darkness.%^RESET%^");
       break;
       case 51..60:
       tell_room(EETO,"%^YELLOW%^The clang of a distant gate or sewer cover echoes along the tunnel.%^RESET%^");
       break;
       case 61..70:
       tell_room(EETO,"%^CYAN%^You hear a sudden surge and crash of water somewhere in the distance.%^RESET%^");
       break;
       case 71..80:
       tell_room(EETO,"%^BLUE%^A low hiss sounds off to the side, and gleaming eyes briefly peer back at you from the darkness.%^RESET%^");
       break;
       default:
       tell_room(EETO,"%^MAGENTA%^Scratching and scrabbling sounds from a small drainage grate nearby.%^RESET%^");
       break;
     }
     return;
   }
}

int save_me(string file) { return 1; }

void notify_me() {
   if(objectp(EETO)) {
     if(!EETO->query_property("indoors")) {
       tell_object(ETO,"%^BOLD%^%^BLACK%^As the looming shadow of the great sky fortress falls across you, you can't help but grow a little more cautious.%^RESET%^");
       return;
     }
   }
   tell_object(ETO,"%^CYAN%^As you set foot into the City of Shadows, you can't help but grow a little more cautious.%^RESET%^");
}