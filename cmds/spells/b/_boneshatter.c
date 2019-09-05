#include <spell.h>
#include <magic.h>
inherit SPELL;

int bonus;

void create()
{
    ::create();
    set_spell_name("boneshatter");
    set_spell_level(([ "mage" : 4, "cleric" : 4 ]));
    set_spell_sphere("necromancy");
    set_syntax("cast CLASS boneshatter on TARGET");
    set_damage_desc("on living only, untyped, -4 or -2 on save to str and dex");
    set_description("With mere will you splinter you enemies skeleton or external shell. The enemy fights the change and if they fail, they become exhausted, taking damage to their strength and dexterity. If they Successfully overcome the pain, they instead become fatigued for a short while. This spell will work only on living beings, and will cause stat damage just once per target.");
    set_save("fort");
    set_target_required(1);
}

string query_cast_string()
{
    return "%^BOLD%^%^BLUE%^"+caster->QCN+" makes a cage out of "+TP->QP+" fingers while chanting intently.%^RESET%^";
}

void spell_effect(int prof)
{
    int duration;
    spell_successful();
    if(target->is_undead())
    {
        tell_object(caster,"%^BOLD%^%^WHITE%^You will crushing of "+target->QCN+"'s internals, but nothing seems to happen!");
        TO->dest_effect();
        return;
    }
    tell_object(caster,"%^BOLD%^%^WHITE%^You will crushing of "+target->QCN+"'s internals!");
    tell_room(place,"%^BOLD%^%^WHITE%^"+target->QCN+" staggers as you hear a rushing sound!", ({caster, target}) );
    tell_object(target,"%^BOLD%^%^WHITE%^Your bones ache of pain as the spell hits you!");
    damage_targ(target, target->query_target_limb(), sdamage,"untyped");
    if(!target->query_property("boneshattered"))
    {
        bonus = -4;
        if(do_save(target,0))
            bonus = -2;

        tell_object(target,"%^BOLD%^%^WHITE%^You feel fatigued...");
        target->add_stat_bonus("strength",bonus);
        target->add_stat_bonus("dexterity",bonus);
        target->set_property("boneshattered");
        call_out("dest_effect",duration);
        duration = (ROUND_LENGTH) * clevel;
    }
    else
        TO->dest_effect();
    spell_successful();
}

void dest_effect()
{
    ::dest_effect();

    if(objectp(target))
    {
        tell_object(target,"%^BOLD%^%^WHITE%^Your fatigue recedes, you feel power and finesse returning.");
        target->add_stat_bonus("strength",-bonus);
        target->add_stat_bonus("dexterity",-bonus);
    }
    if(objectp(TO))
        TO->remove();
}
