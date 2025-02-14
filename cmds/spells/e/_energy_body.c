// for life mystery.
#include <priest.h>
inherit SPELL;

void create() {
    ::create();     
    set_spell_name("energy body");
    set_spell_level(([ "innate" : 9 ]));
    set_mystery("life");
    set_spell_sphere("alteration");
    set_syntax("cast innate energy body");
    set_description("This innate ability allows a Life oracle to transform into a Life Elemental.");
    set_verbal_comp();
    set_somatic_comp();
    set_peace_needed(1);
    set_helpful_spell(1);
}

int preSpell(){
      object shape;
      if(objectp(shape = caster->query_property("shapeshifted")) || objectp(shape = caster->query_property("altered"))) {
        tell_object(caster,"You are already in an alternative form!");
        return 0;
      }
      return 1;
}

string query_cast_string() {
	return "%^BOLD%^%^WHITE%^"+YOU+" closes "+MINE+" eyes and concentrates deeply.";
}

void spell_effect(int prof) {
      if (!objectp(caster)){
        TO->remove();
        return;
      }
      new("/std/races/shapeshifted_races/life_elemental.c")->init_shape(caster,"elemental"); 
      spell_successful();
      addSpellToCaster();
}

void dest_effect() {
      object shape;
	if(objectp(caster)) {
        if(objectp(shape = caster->query_property("shapeshifted"))) shape->reverse_shape(caster);
	}
    	::dest_effect();
      if(objectp(TO)) TO->remove();
}
