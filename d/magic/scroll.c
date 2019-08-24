#include <std.h>
#include <spellsbylevel.h>
#include <daemons.h>
inherit OBJECT;

string spell, *readpassed;
mapping readfailed;

#define SCRL_CLASSES ({"paladin","ranger","cleric","druid","mage"})

/**
 * @file
 * @brief Magic scroll
 */

int level, usable;
void set_spell_name(string str);
void set_spell(int level);
void set_av_spell(int level);
int do_back_fire(object myuser);
void crumble(object targ);
int query_readable_by(object env, object viewer);//added by Lujke 13/05/05
void set_is_newbie(int x);  //newbie stuff added by Circe 6/6/07
int query_is_newbie();
int is_newbie;

int is_scroll(){ return 1;}

void create(){
    ::create();
    set_name("scroll");
    set_id(({"scrollx", "scroll"}));
    set_long((:TO,"long_desc":));
    set_short("a scroll");
    set_spell(1);
    set_weight(2);
    set_value(10);
}

void init() {
    ::init();
    set_long((:TO, "long_desc":));
    if (ETO == TP && interactive(TP)) {
        if(wizardp(TP))
            add_action("set_scroll", "set");
        if(TP->is_class("mage") || avatarp(TP)) {
            add_action("transcribe", "transcribe");
        }
        add_action("use_scroll", "use");
    }
}

string long_desc() {
    string long;
    if(!objectp(TP))
        return("This is a scroll with some undecipherable writing on it.");
    if(!query_readable_by(TP,TP))
        return("This is a scroll with some undecipherable writing on it.");
    if(base_name(TO) == "/d/magic/safe_scroll" ||
       base_name(TO) == "/d/magic/newbie_scroll")
    {
        long = "%^ORANGE%^This is a magic scroll of "+spell+".
You can <use> it directly in order to properly study and learn more about the effects of the spell. It cannot be transcribed.%^RESET%^";
        return long;
    }
    return("%^ORANGE%^This is a magic scroll of "+spell+". You can <transcribe> it into your spell book or <use> it directly.%^RESET%^");
}

string query_short()
{
    if(!objectp(TP))
        return("%^RESET%^%^ORANGE%^scr%^BOLD%^o%^RESET%^%^ORANGE%^ll%^RESET%^");
    if(!query_readable_by(TP,TP))
        return("%^RESET%^%^ORANGE%^scr%^BOLD%^o%^RESET%^%^ORANGE%^ll%^RESET%^");
    return("%^RESET%^%^ORANGE%^scr%^BOLD%^o%^RESET%^%^ORANGE%^ll of "+spell+"%^RESET%^");
}

void crumble(object targ) {
    if(!objectp(TO))
        return;
    if(targ->query_true_invis()) return;
    tell_room(ETP, "The scroll crumbles to dust, perhaps from age or improper handling.");
    if(!random(20)) {
        tell_room(environment(targ),"%^YELLOW%^As the scroll crumbles it explodes from the release of the magical energy, shocking "+targ->QCN+"!", targ);
        if(!"/daemon/saving_d"->saving_throw(targ,"spell")) {
            tell_object(targ,"%^YELLOW%^As the scroll crumbles it explodes from the release of the magic energy and you get a serious jolt!");
            if(newbiep(targ)) targ->do_damage("torso",roll_dice(2,4));
            else targ->do_damage("torso",roll_dice(4,6));
        }
        else {
            tell_object(targ,"%^YELLOW%^As the scroll crumbles it explodes from the release of the magic energy and you get a harmful jolt!");
            targ->do_damage("torso",roll_dice(2,6));
        }
    }
    remove();
}

void set_spell(int mylevel){
    mylevel=mylevel-2+roll_dice(1,4);
    set_av_spell(mylevel);
}

void set_av_spell(int mylevel){
    string *whichspells,str;
    int num,i;
    mapping allspells=([]);
    mylevel=mylevel>9?9:mylevel;
    mylevel=mylevel<1?1:mylevel;
    for (i = 0; i< sizeof(SCRL_CLASSES); i++)
    {
        allspells+=MAGIC_D->query_index(SCRL_CLASSES[i]);
    }
    whichspells = keys(filter_mapping(
            allspells,
            (:$2==$3:),mylevel));
    num = random(sizeof(whichspells));
    str = whichspells[num];
    if (!str)
        set_spell_name("magic missile");
    else
        set_spell_name(str);
}

set_spell_level(int l){
	level = l;
}

void set_scroll(string str){
    string scroll_id, scroll_spell;
    if (!str) return 0;
    if (sscanf(str,"%s to %s",scroll_id,scroll_spell) != 2)
        return 0;
    if (present(scroll_id,TP)!=TO)
        return 0;
    set_spell_name(scroll_spell);
    write("Scroll altered.");
}

void set_spell_name(string str)
{

    //////////////////////////////////////////////////////////////////////
    //This section added by Lujke May 31/05 to prevent scrolls
    // retaining the name of their old spell when the spell name is changed.
    ///////////////////////////////////////////////////////////////////////
    string * old_id_list, tmp;
    int x;
    old_id_list = query_id();
    old_id_list -= ({ spell,"" }) ;
    set_id(old_id_list);
    // End of added section //
    spell = str;
    if(sscanf(spell, "%s%d", tmp, x) == 2)
    {
        tmp = tmp + consolidate_number(x);
        add_id(tmp);
    }
    add_id(spell);
    set_long("This is a magic scroll of "+spell+".  You can "+
             "<transcribe> it into your spell book or <use> it directly.");
    return 1;
}

string query_spell_name() { return spell;}

int transcribe(string str)
{
    object book;
    int prev;
    int after;
    if (TP->light_blind(0))
        return notify_fail("You cannot see well enough to read this.\n");
    if(TP->query_blind())
        return notify_fail("How could you transcribe something you can't see??\n");
    if (!stringp(str))
        return notify_fail("Transcribe what?\n");
    if (present(str,TP) != TO)
        return 0;
    book = present("bookx",TP);
    if (!book)
    {
        notify_fail("You don't have a spell book to transcribe the spell into!\n");
        return 0;
    }
    if(member_array(spell,keys(MAGIC_D->query_index("mage")))==-1)
    {
        notify_fail("You can only transcribe aracne spells");
    }
    if(!query_readable_by(TP,TP))
        return notify_fail("You can't understand that scroll!\n");
    write("%^ORANGE%^You carefully file "+spell+" into your spellbook.\n");
    book->set_spellbook(spell);
    TO->remove();
    return 1;
}

int use_scroll(string str){
    int lev, back,num;
    string caster, targ, what,what2;
    object ob;

    caster = TP->query_name();
    if (!str)
        return notify_fail("Use what?\n");
    if (!(sscanf(str,"%s on %s",what,targ)==2))
        if (!(sscanf(str,"%s at %s",what,targ)==2))
            if (!(sscanf(str,"%s to %s",what,targ)==2)) {
                what = str;
            }
	//Added by Saide so the user can just use 'me' as a target to use a scroll on
	//themselves - 3/18/2007 - comment out if someone thinks it shouldnt be this way.
    if(targ == "me") targ = TP->query_name();
    if (!present(what,TP)) return 0;
    if (present(what,TP) != TO) return 0;

    if(TP->query_property("shapeshifted"))
    {
        tell_object(TP,"You can't read scrolls while shapeshifted.");
        return 1;
    }

    if(TP->query_bound() || TP->query_paralyzed() || TP->query_unconscious())
    {
        TP->send_paralyzed_message("info",TP);
        return 1;
    }
    if(TP->query_gagged())
    {
        tell_object(TP,"You can't properly use a scroll while gagged!");
        return 1;
    }
    lev = (int)TP->query_skill("spellcraft");
    if(lev < 1) lev = 1;
    if(lev-10+roll_dice(1,20)<query_spell_level()*3)
        if(!random(5))
        {
            tell_object(TP,"%^BOLD%^Unable to control the magic, the scroll explodes into your face!%^RESET%^");
            tell_room(TP,"%^BOLD%^Unable to control the magic, the scroll explodes into "+TP->QCN+"'s face!%^RESET%^",TP);
            TP->do_damage("torso",roll_dice(1,20));
            remove();
            return 1;
        }
    if(TP->query_casting()) {
        tell_object(TP,"You are already casting a spell");
        return 1;
    }
    ob = new("/cmds/spells/"+spell[0..0]+"/_"+replace_string(spell," ","_"));
    if (ob->query_target_required() && !targ)
        return notify_fail("You need to specify a target to use that spell!\n");
    TP->set_property("spell_casting",ob);
    ob->use_spell(TP, targ, lev);
    remove();
    return 1;
}

int query_spell_level(){
    return max(map_array(SCRL_CLASSES,
                         (:MAGIC_D->query_spell_level($1,spell):)));
}

int query_scroll_level(){
    return level;
}

int do_back_fire(object myuser)
{
    return 0;
}

int query_value(){
    int level = query_spell_level();
    return (level*level)*100;
}

int query_usable() {return usable;}
//Added by Saide to test to make sure the query_readable_by() function is working
//correctly - 3/18/2007
void set_usable(int x) { usable = x; }

/**
 * Whether reader should be able to see what spell is on the scroll
 *
 * @return 0 if the reader is not allowed to see
 */
int query_readable_by(object env, object viewer)
{
    string viewername;
    int skill, diff;

    if(!userp(TP))
        return 1;
    viewername = (string)viewer->query_name();
    if(!readpassed)
        readpassed = ({});
    if(!readfailed)
        readfailed = ([]);
    if(member_array(viewername,readpassed) != -1)
        return 1;
    if(!mapp(readfailed))
        return 0;
    skill = viewer->query_skill("spellcraft");
    if(readfailed[viewername])
    {
        if(skill <= readfailed[viewername])
            return 0;
        map_delete(readfailed,viewername);
    }
    if(skill > query_spell_level()*3)
    {
        readpassed += ({viewername});
        return 1;
    }
    readfailed[viewername] = skill;
    return 0;
}

void set_passed(string charname) {
    if(!readpassed) readpassed = ({});
    if(!readfailed) readfailed = ([]);
    if(member_array(charname,readpassed) == -1) readpassed += ({charname});
    if(readfailed[charname]) map_delete(readfailed,charname);
}

string * query_passed() { return readpassed; }
mapping query_failed() { return readfailed; }

string query_scroll_spell() { return spell;}

void set_is_newbie(int x){
    is_newbie = x;
}

int query_is_newbie(){
    return is_newbie;
}
