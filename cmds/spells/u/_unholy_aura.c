#include <priest.h>
#include <magic.h>
#include <spell.h>

inherit SPELL;

int timer,flag,stage,toggle,counter;

void create()
{
    ::create();
    set_spell_name("unholy aura");
    set_spell_level(([ "cleric" : 8, "sorcerer" : 8 ]));
    set_spell_sphere("abjuration");
    set_bonus_type(({ "resistance", "deflection" }));
    set_syntax("cast CLASS unholy aura");
    set_damage_desc("divine damage, 4 AC, 4 to all saves");
    set_description("You are surrounded by an aura of evil that will harm all your opponents and will slightly protect you. This is nimbus-family spell that won't work with other nimbuses.");
    set_property("magic",1);
    traveling_aoe_spell(1);
    evil_spell(1);
}

int preSpell()
{
    int align = caster->query_true_align();
    if (caster->query_property("nimbus")) {
        tell_object(caster, "You are still affected by shield of law or another nimbus spell.");
        return 0;
    }
    if(caster->query_property("protection from spells"))
    {
        tell_object(caster, "You are already affected by similar magic.");
        return 0;
    }
    if (!(align == 3 || align == 6 || align == 9)) {
        tell_object(caster, "You are of improper alignment to use this spell!");
        return 0;
    }
    return 1;
}

void spell_effect(int prof)
{
    int duration;
    duration = (ROUND_LENGTH * 10) * clevel;

    tell_object(caster,"%^BOLD%^%^MAGENTA%^You feel fell powers power warding you from the good!");
    tell_room(place,"%^BOLD%^%^MAGENTA%^"+caster->QCN+" is suddenly surrounded by halo of darkness!",caster);

    caster->set_property("spelled", ({TO}));
    caster->set_property("nimbus",1);
    caster->set_property("protection from spells", 1);
    caster->set_property("added short",({"%^BOLD%^%^BLACK%^ (in a fell halo)%^RESET%^"}));
    addSpellToCaster();
    spell_successful();
    caster->add_saving_bonus("all",4);
    caster->add_ac_bonus(4);
    execute_attack();
    spell_duration = duration;
    set_end_time();
    call_out("dest_effect",spell_duration);
    call_out("room_check",ROUND_LENGTH);
}

void room_check()
{
    if(!objectp(caster) || !objectp(ENV(caster)))
    {
        dest_effect();
        return;
    }

    prepend_to_combat_cycle(ENV(caster));

    call_out("room_check",ROUND_LENGTH*2);
    return;
}

void execute_attack(){
    object *attackers;
    int i;

    if(!flag)
    {
        flag = 1;
        ::execute_attack();
        return;
    }

    place      = environment(caster);
    if(!objectp(caster) || !objectp(place))
    {
        dest_effect();
        return;
    }

    attackers = filter_array(caster->query_attackers(),(:objectp($1):));
    attackers = filter_array(attackers,(:$1->is_living():));

    if(sizeof(attackers))
    {
        define_base_damage(0);
        tell_room(place,"%^BOLD%^%^BLACK%^The unholy darkness around "+caster->QCN+" falls upon "+caster->QP+" enemies!",({caster,target}));
        tell_object(caster,"%^BOLD%^%^BLACK%^The unholy darkness around you falls upon your enemies!");
        for(i=0;i<sizeof(attackers);i++){
            tell_object(attackers[i],"%^BOLD%^%^BLACK%^You are scorched by the unholy darkness as you strike "
                        ""+caster->QCN+"!");
            damage_targ(attackers[i],attackers[i]->return_target_limb(),sdamage,"divine");
        }
    }
    prepend_to_combat_cycle(place);
}

void dest_effect()
{
    remove_call_out("room_check");
    if(objectp(caster))
    {
        tell_object(caster,"%^RESET%^%^BOLD%^The halo around you fades.");
        caster->remove_property("nimbus");
        caster->remove_property("protection from spells");
        caster->add_ac_bonus(-4);
        caster->add_saving_bonus("all",-4);
	    caster->remove_property_value("added short",({"%^BOLD%^%^BLACK%^ (in a fell halo)%^RESET%^"}));
    }
    ::dest_effect();
    if(objectp(TO)) { TO->remove(); }
}
