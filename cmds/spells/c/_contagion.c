#include <std.h>

inherit SPELL;

string diseases = ({"blinding sickness", "cackle fever", "filth fever", "mindfire", "red ache", "shakes", "slimy doom"});

void create() {
    ::create();
    set_spell_name("contagion");
    set_spell_level(([ "paladin":3, "cleric":3, "druid":3, "mage":4]));
    set_spell_sphere("necromancy");
    set_damage_desc("Random disease");
    set_syntax("cast CLASS contagion on TARGET");
    set_description("The subject contracts one of the following diseases: blinding sickness, bubonic plague, cackle fever, filth fever, leprosy, mindfire, red ache, shakes, or slimy doom. The disease is contracted immediately (the onset period does not apply). Spell's caster level used as spell power. Disease will progress then as usual.");

    set_verbal_comp();
    set_somatic_comp();

    set_target_required(1);

    set_save("fort");
    evil_spell(1);
}

string query_cast_string()
{
    return "%^BOLD%^%^BLACK%^"+caster->QCN+" steps into the shadows, then mixes something in his hands while chanting in a deep, dark tone.";
}

void spell_effect()
{
    object disease;
    string dfile;

    dfile = "/std/diseases/diseases/" + replace_string(diseases[random(sizeof(diseases))], " ", "_") + ".c";

    if(!file_exists(dfile))
    {
        tell_object(caster,"Something is wrong with disease file: " + dfile);
        return;
    }

    tell_object(caster,"%^BOLD%^%^GREEN%^You glance at " + target->QCN + ", cursing them with the disease.");
    tell_room(place, "%^BOLD%^" + caster->QCN + " glances at " + target->QCN + ".");

    disease = dfile->infect(target, clevel);
    if (objectp(disease)) {
        disease->advance_disease();
    } else {
        tell_object(caster,"%^BOLD%^%^GREEN%^You sense your curse had been repelled.");
    }

    spell_successful();
    return;

}
