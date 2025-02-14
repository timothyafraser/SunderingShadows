#include <std.h>
#include <daemons.h>

inherit SPELL;

void create()
{
    ::create();
    set_spell_name("shadow evocation");
    set_spell_level(([ "mage" : 5, "bard" : 5, "innate" : 5, "magus" : 5 ]));
    set_spell_sphere("illusion");
    set_syntax("cast CLASS shadow evocation on SPELL_NAME [on SPELL_ARGS]");
    set_description("You create an illusory version of an evocation spell of 4th level or lower. The source of the illusion can differ based on the caster.

%^BOLD%^%^RED%^E.G.%^RESET%^ <cast mage shadow evocation on fireball on goblin>");
    set_arg_needed(1);
    set_silent_casting(1);
}

string shadow_school()
{
    return "invocation_evocation";
}

int preSpell()
{
    int max_level = query_spell_level(spell_type) - 1;
    int slevel;
    string *reqs;
    object spell_to_cast;
    string spl, sargs;
    string splfn;

    if (!stringp(arg)) {
        tell_object(caster, "You must provide arguments to this spell!");
        return 0;
    }

    tell_room(place, "%^WHITE%^" + caster->QCN + " %^BOLD%^%^BLACK%^w%^RESET%^%^WHITE%^h%^BOLD%^i%^RESET%^%^WHITE%^sp%^BOLD%^%^BLACK%^e%^RESET%^%^WHITE%^r%^BOLD%^%^WHITE%^s %^RESET%^%^WHITE%^in%^BOLD%^%^BLACK%^c%^RESET%^%^WHITE%^o%^BOLD%^h%^RESET%^%^WHITE%^er%^BOLD%^%^BLACK%^e%^RESET%^%^WHITE%^ntly.%^WHITE%^");
    if (sscanf(arg, "%s on %s", spl, sargs) != 2) {
        spl = arg;
    }

    if (!stringp(spl)) {
        tell_object(caster, "You must provide another spell to this spell!");
        return 0;
    }

    spl = replace_string(spl, " ", "_");
    splfn = "/cmds/spells/" + spl[0..0] + "/_" + spl + ".c";

    if (!file_exists(splfn)) {
        tell_object(TP, "Either that spell does not exist, or you do not know it!");
        return 0;
    }
    if (!sargs || sargs == "" || !stringp(sargs)) {
        sargs = "";
    }
    spell_to_cast = new(splfn);
    if (spell_to_cast->query_spell_sphere() != shadow_school()) {
        tell_object(TP, "Only " + replace_string(shadow_school(), "_", "/") + " school spells are allowed!");
        return 0;
    }
    
    reqs = keys(spell_to_cast->query_feats_required("mage"));
    
    if(sizeof(reqs) && member_array(spell_type, reqs) >= 0)
    {
        if(!FEATS_D->usable_feat(caster, reqs[0]))
        {
            tell_object(caster, "You don't have the correct feats to cast that spell.");
            return 0;
        }
    }
    
    slevel = spell_to_cast->query_spell_level("mage");
    if (slevel > max_level || slevel == 0) {
        tell_object(TP, "This spell is too powerful for " + spell_name + "!");
        return 0;
    }
    spell_to_cast->set_shadow_spell(max_level);
    caster->remove_property("spell_casting");
    caster->set_property("spell_casting", spell_to_cast);
    spell_to_cast->use_spell(TP, sargs, clevel, 100, "mage");
    call_out("dest_effect", 2);
    return 1;
}

void dest_effect()
{
    ::dest_effect();
    if (objectp(TO)) {
        TO->remove();
    }
}
