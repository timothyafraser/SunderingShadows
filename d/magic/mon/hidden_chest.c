#include <std.h>
inherit WEAPONLESS;

object caster;

void create(){
    ::create();
    set_name("chest");
    set_id(({"chest","secret chest","floating wooden chest","greater summon"}));
    set_short("%^RESET%^%^CYAN%^Floating %^ORANGE%^wooden %^BOLD%^c%^RESET%^%^ORANGE%^h%^BOLD%^e%^RESET%^%^ORANGE%^s%^BOLD%^t%^RESET%^");
    set_long("%^RESET%^%^ORANGE%^This is an %^BOLD%^%^ORANGE%^iro%^BLACK%^n%^ORANGE%^-bound%^RESET%^%^ORANGE%^ wooden chest that appears to float. It is quite large and could probably fit a lot of things inside.%^RESET%^");
    set_attacks_num(1);
    set_exp(1);
    set_gender("neuter");
    set_hp(40);
    set_hd(4,1);
    set_race("chest");
    set_stats("constitution",24);
    set_stats("dexterity",2);
    set_stats("strength",24);
    set_body_type("humanoid");
    remove_limb("left hand");
    remove_limb("right hand");
    remove_limb("left foot");
    remove_limb("right foot");
    remove_limb("left leg");
    remove_limb("right leg");
    add_limb("chest",0,0,0,0);
    set_attack_limbs(({"chest"}));
}
init()
{
  ::init();
  add_action("dismiss","dismiss");
  add_action("open","open");
}

int open(string str){
	
	if (str=="chest") {
        tell_object(ETO,"%^RESET%^%^ORANGE%^You open the chest and its contents materialize!%^RESET%^");
		//seteuid(getuid());
		 "/daemon/yuck_d"->load_inventory(this_object(),"/d/save/summons/fart/chest");
    }
}

int dismiss(string str){
	
	if (str=="chest") {
        tell_object(ETO,"%^RESET%^%^ORANGE%^Floating %^BOLD%^%^ORANGE%^Ch%^BLACK%^e%^BLACK%^s%^ORANGE%^t%^RESET%^%^ORANGE%^ simply vanishes!%^RESET%^");
		//seteuid(getuid())
		//mkdir("/d/save/summons/fart");
		//mkdir("/d/save/summons/fart/chest");
		      move("/d/shadowgate/void");
		 "/daemon/yuck_d"->save_inventory(this_object(),"/d/save/summons/fart/chest");
    }
}

