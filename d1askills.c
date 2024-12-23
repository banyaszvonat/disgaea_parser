#include "d1askills.h"

#include <hammer/glue.h>

HParser *d1askillid;
HTokenType TT_SkillID;

const char* skill_names[0xF0F] = { "!!Invalid Skill ID!!" };

bool validate_skillid(HParseResult *p, void *u)
{
	return *(H_CAST(SkillID, p->ast)) < 0xF0F;
}

HParsedToken *act_skillid(const HParseResult *p, void *u)
{
	SkillID *si = H_ALLOC(SkillID);

	*si = (uint16_t) H_CAST_UINT(p->ast);

	return H_MAKE(SkillID, si);
}

void pp_skillid(FILE *stream, const HParsedToken *tok, int indent, int delta)
{
	SkillID *si = H_CAST(SkillID, tok);
	fprintf(stream, "%s", skills_get_name(*si));
}

const char* skills_get_name(SkillID id)
{
	return skill_names[id];
}

void fill_skill_names();

void skills_init_parsers()
{
	TT_SkillID = h_allocate_token_new("SkillID", NULL, pp_skillid);
	H_VARULE(skillid, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	d1askillid = skillid;
	fill_skill_names();
}

/*
  Because some skill IDs share names, the ID number is included in the name.
  Source of the data: https://gamefaqs.gamespot.com/ps2/589678-disgaea-hour-of-darkness/faqs/35073
*/
void fill_skill_names()
{
	skill_names[0] = "0000 - None";

	//FIST ATTACKS
	skill_names[0x0065] = "0065 - Triple Strike";
	skill_names[0x0066] = "0066 - Tiger Charge";
	skill_names[0x0067] = "0067 - Lion's Roar";
	skill_names[0x0068] = "0068 - King of Beasts";
	skill_names[0x0069] = "0069 - Rising Dragon";
	skill_names[0x006A] = "006A - Big Bang";

	//SWORD ATTACKS
	skill_names[0x00C9] = "00C9 - Blade Rush";
	skill_names[0x00CA] = "00CA - Hurricane Slash";
	skill_names[0x00CB] = "00CB - Wind Cutter";
	skill_names[0x00CC] = "00CC - Winged Slayer";
	skill_names[0x00CD] = "00CD - Nightsever";
	skill_names[0x00CE] = "00CE - Dimension Slash";

	//SPEAR ATTACKS
	skill_names[0x012D] = "012D - Impaler";
	skill_names[0x012E] = "012E - Sky Lunge";
	skill_names[0x012F] = "012F - Asteroid Drop";
	skill_names[0x0130] = "0130 - Avalanche";
	skill_names[0x0131] = "0131 - Turbulence";
	skill_names[0x0132] = "0132 - Spear Storm";

	//ARROW ATTACKS
	skill_names[0x0191] = "0191 - Poison Arrow";
	skill_names[0x0192] = "0192 - Dark Flash";
	skill_names[0x0193] = "0193 - Delta Split";
	skill_names[0x0194] = "0194 - Sturmhimmel";
	skill_names[0x0195] = "0195 - Zielregen";
	skill_names[0x0196] = "0196 - Doppelganger";

	//GUN ATTACKS
	skill_names[0x01F5] = "01F5 - Tri-Burst";
	skill_names[0x01F6] = "01F6 - Rapidfire";
	skill_names[0x01F7] = "01F7 - Proximal Shot";
	skill_names[0x01F8] = "01F8 - Bullet Storm";
	skill_names[0x01F9] = "01F9 - Totenkreuz";
	skill_names[0x01FA] = "01FA - Inferno";

	//AXE ATTACKS
	skill_names[0x0259] = "0259 - Boulder Crush";
	skill_names[0x025A] = "025A - Skull Splitter";
	skill_names[0x025B] = "025B - Colossal Fissure";
	skill_names[0x025C] = "025C - Violent Storm";
	skill_names[0x025D] = "025D - Graviton Bomb";
	skill_names[0x025E] = "025E - Calamity Drive";

	//RED MAGIC
	skill_names[0x02BD] = "02BD - Fire";
	skill_names[0x02BE] = "02BE - Mega Fire";
	skill_names[0x02BF] = "02BF - Giga Fire";
	skill_names[0x02C0] = "02C0 - Omega Fire";
	skill_names[0x02C1] = "02C1 - Tera Fire";

	//GREEN MAGIC
	skill_names[0x02C7] = "02C7 - Wind";
	skill_names[0x02C8] = "02C8 - Mega Wind";
	skill_names[0x02C9] = "02C9 - Giga Wind";
	skill_names[0x02CA] = "02CA - Omega Wind";
	skill_names[0x02CB] = "02CB - Tera Wind";

	//BLUE MAGIC
	skill_names[0x02D1] = "02D1 - Ice";
	skill_names[0x02D2] = "02D2 - Mega Ice";
	skill_names[0x02D3] = "02D3 - Giga Ice";
	skill_names[0x02D4] = "02D4 - Omega Ice";
	skill_names[0x02D5] = "02D5 - Tera Ice";

	//STAR MAGIC
	skill_names[0x02DB] = "02DB - Star";
	skill_names[0x02DC] = "02DC - Mega Star";
	skill_names[0x02DD] = "02DD - Giga Star";
	skill_names[0x02DE] = "02DE - Omega Star";
	skill_names[0x02DF] = "02DF - Tera Star";

	//HEAL MAGIC
	skill_names[0x0321] = "0321 - Heal";
	skill_names[0x0322] = "0322 - Mega Heal";
	skill_names[0x0323] = "0323 - Giga Heal";
	skill_names[0x0324] = "0324 - Omega Heal";

	//MISC. MAGIC
	skill_names[0x0325] = "0325 - Espoir";
	skill_names[0x032B] = "032B - Braveheart";
	skill_names[0x032C] = "032C - Shield";
	skill_names[0x032D] = "032D - Magic Boost";
	skill_names[0x032E] = "032E - Magic Wall";

	//?????
	skill_names[0x032F] = "032F - Enfeeble";
	skill_names[0x0330] = "0330 - Armor Break";

	//SCOUT SPECIALS
	skill_names[0x0385] = "0385 - Geo Change";
	skill_names[0x0386] = "0386 - Dark Cannon";

	//DEMON PRINCE/TYRANT (LAHARL) SPECIALS
	skill_names[0x03E9] = "03E9 - Blazing Knuckle";
	skill_names[0x03EA] = "03EA - Overlord's Wrath";
	skill_names[0x03EB] = "03EB - Meteor Impact";

	//VASSAL SPECIALS
	skill_names[0x03F3] = "03F3 - Prinny Raid";
	skill_names[0x03F4] = "03F4 - Sexy Beam";
	skill_names[0x03F5] = "03F5 - Chaos Impact";

	//ANGEL (FLONNE) SPECIALS
	skill_names[0x03FD] = "03FD - Power of Love";
	skill_names[0x03FE] = "03FE - Holy Arrows";
	skill_names[0x03FF] = "03FF - Divine Ray";

	//DEFENDER SPECIALS
	skill_names[0x0407] = "0407 - Gordon Spark";
	skill_names[0x0408] = "0408 - Gordon Punch";
	skill_names[0x0409] = "0409 - Gordon Blitz";

	//SIDEKICK SPECIALS
	skill_names[0x0411] = "0411 - Star Buster";
	skill_names[0x0412] = "0412 - Cosmic Arrow";
	skill_names[0x0413] = "0413 - Terminus Omega";

	//FAERIE SPECIALS
	skill_names[0x07D1] = "07D1 - Petit Flare";
	skill_names[0x07D2] = "07D2 - Demon's Breath";
	skill_names[0x07D3] = "07D3 - Camaraderie";
	skill_names[0x07D4] = "07D4 - Chomper Combo";

	//SPIRIT SPECIALS
	skill_names[0x07DB] = "07DB - Pixie Magic";
	skill_names[0x07DC] = "07DC - Shock Magic";
	skill_names[0x07DD] = "07DD - Bomb Magic";
	skill_names[0x07DE] = "07DE - Ice Magic";

	//GOLEM SPECIALS
	skill_names[0x07E5] = "07E5 - Golem Dunk";
	skill_names[0x07E6] = "07E6 - Golem Cannon";
	skill_names[0x07E7] = "07E7 - Psionic Wave";
	skill_names[0x07E8] = "07E8 - Golem Smash";

	//TREANT SPECIALS
	skill_names[0x07EF] = "07EF - Putrid Breath";
	skill_names[0x07F0] = "07F0 - Stomp-o-rama";
	skill_names[0x07F1] = "07F1 - Pounding Spree";
	skill_names[0x07F2] = "07F2 - Paranoia";

	//WINGED SPECIALS
	skill_names[0x07F9] = "07F9 - Hell Pepper";
	skill_names[0x07FA] = "07FA - Holy Dust";
	skill_names[0x07FB] = "07FB - Ionize";
	skill_names[0x07FC] = "07FC - Air Assault";

	//DARK KNIGHT SPECIALS
	skill_names[0x0803] = "0803 - Power Slice";
	skill_names[0x0804] = "0804 - Lightning Slash";
	skill_names[0x0805] = "0805 - Gigantic Slash";
	skill_names[0x0806] = "0806 - Blade Frenzy";

	//LANTERN SPECIALS
	skill_names[0x080D] = "080D - Jackknife";
	skill_names[0x080E] = "080E - Jack the Ripper";
	skill_names[0x080F] = "080F - Jack Rush";
	skill_names[0x0810] = "0810 - Jackpot";

	//GARGOYLE SPECIALS
	skill_names[0x0817] = "0817 - Minimize";
	skill_names[0x0818] = "0818 - Soul Eater";
	skill_names[0x0819] = "0819 - Cannonball";
	skill_names[0x081A] = "081A - Eruption";

	//SHADOW SPECIALS
	skill_names[0x0821] = "0821 - Fire Dance";
	skill_names[0x0822] = "0822 - Ice Dance";
	skill_names[0x0823] = "0823 - Light Dance";
	skill_names[0x0824] = "0824 - Fire & Ice";

	//UNDEAD SPECIALS
	skill_names[0x0849] = "0849 - Zombie Puke";
	skill_names[0x084A] = "084A - Zombie Twister";
	skill_names[0x084B] = "084B - Zombie Gatling";
	skill_names[0x084C] = "084C - Zombie Swarm";

	//NETHER NOBLE SPECIALS
	skill_names[0x0853] = "0853 - Spinning Slash";
	skill_names[0x0854] = "0854 - Darkness Slash";
	skill_names[0x0855] = "0855 - Earthshaker";
	skill_names[0x0856] = "0856 - Megaton Crush";

	//TYRANT (BAAL) SPECIALS
	skill_names[0x085D] = "085D - Sword Rain";
	skill_names[0x085E] = "085E - Gran Sword";

	//BEAST SPECIALS
	skill_names[0x0867] = "0867 - Stinger Strike";
	skill_names[0x0868] = "0868 - Beast Rend";
	skill_names[0x0869] = "0869 - Devour";
	skill_names[0x086A] = "086A - Beast Ray";

	//SUCCUBUS SPECIALS
	skill_names[0x0871] = "0871 - Hip Attack";
	skill_names[0x0872] = "0872 - Thunderbolt";
	skill_names[0x0873] = "0873 - Evil Healing";
	skill_names[0x0874] = "0874 - Flying Sparks";

	//KITKAT SPECIALS
	skill_names[0x087B] = "087B - Rapid Kick";
	skill_names[0x087C] = "087C - Fists of Fury";
	skill_names[0x087D] = "087D - Mystic Blast";
	skill_names[0x087E] = "087E - Delta Kick";

	//NOSFERATU SPECIALS
	skill_names[0x0885] = "0885 - Chaos Fire";
	skill_names[0x0886] = "0886 - Chaos Swarm";
	skill_names[0x0887] = "0887 - Chaos Force";
	skill_names[0x0888] = "0888 - Chaos Plasma";

	//SUPER ROBOT SPECIALS
	skill_names[0x0899] = "0899 - Robo Attack";
	skill_names[0x089A] = "089A - Robo Crush";
	skill_names[0x089B] = "089B - Robo Bazooka";
	skill_names[0x089C] = "089C - Arigato Roboto";

	//PRINNY SPECIALS
	skill_names[0x08A3] = "08A3 - Prinny Barrage";
	skill_names[0x08A4] = "08A4 - Prinny Dance";
	skill_names[0x08A5] = "08A5 - Prinny Bomb";
	skill_names[0x08A6] = "08A6 - Pringer Beam";

	//RIVAL (PRINNY KURTIS) SPECIALS
	skill_names[0x08AD] = "08AD - Rocket Punch";
	skill_names[0x08AE] = "08AE - Final Punch";
	skill_names[0x08AF] = "08AF - Nuclear Fusion";
	skill_names[0x08B0] = "08B0 - Pringer Beam";

	//UBER PRINNY SPECIALS
	skill_names[0x097F] = "097F - Prinny Barrage";
	skill_names[0x0980] = "0980 - Prinny Dance";
	skill_names[0x0981] = "0981 - Prinny Bomb";
	skill_names[0x0982] = "0982 - Pringer Beam";

	//MID-BOSS SPECIALS
	skill_names[0x09C5] = "09C5 - Adonic Shot";
	skill_names[0x09CF] = "09CF - Adonic Blast";
	skill_names[0x09D9] = "09D9 - Adonic Fury";
	skill_names[0x09E3] = "09E3 - Adonic Buster";

	//ARCHANGEL SPECIALS
	skill_names[0x0A0B] = "0A0B - Divine Anger";
	skill_names[0x0A0C] = "0A0C - Angelic Gospel";
	skill_names[0x0A0D] = "0A0D - Holy Lightning";

	//SERAPH SPECIALS
	skill_names[0x0A15] = "0A15 - Judgment";
	skill_names[0x0A16] = "0A16 - Armageddon";

	//RIVAL (HUMAN KURTIS) SPECIALS
	skill_names[0x0A1F] = "0A1F - Rocket Punch";
	skill_names[0x0A20] = "0A20 - Final Punch";
	skill_names[0x0A21] = "0A21 - Nuclear Fusion";

	//1ST DEFENDER SPECIALS
	skill_names[0x0A29] = "0A29 - Hero Slash";
	skill_names[0x0A2A] = "0A2A - Galactic Power";

	//PRISM RANGER SPECIAL
	skill_names[0x0A33] = "0A33 - Swift Justice";

	//OVERLORD (PRIERE) SPECIALS
	skill_names[0x0BB9] = "0BB9 - Dragon's Rage";
	skill_names[0x0BBA] = "0BBA - Requiem Aeternam ";

	//WITCH SPECIAL
	skill_names[0x0BC3] = "0BC3 - Dark Conjuration";

	//SERPENT SPECIALS
	skill_names[0x0DAD] = "0DAD - Flap Dance";
	skill_names[0x0DAE] = "0DAE - Quadra Nosedive";
	skill_names[0x0DAF] = "0DAF - Death Drop";
	skill_names[0x0DB0] = "0DB0 - Supernova";

	skill_names[0x0DB7] = "0DB7 - Flap Dance";
	skill_names[0x0DB8] = "0DB8 - Quadra Nosedive";
	skill_names[0x0DB9] = "0DB9 - Death Drop";
	skill_names[0x0DBA] = "0DBA - Supernova";

	skill_names[0x0DC1] = "0DC1 - Flap Dance";
	skill_names[0x0DC2] = "0DC2 - Quadra Nosedive";
	skill_names[0x0DC3] = "0DC3 - Death Drop";
	skill_names[0x0DC4] = "0DC4 - Supernova";

	skill_names[0x0DCB] = "0DCB - Flap Dance";
	skill_names[0x0DCC] = "0DCC - Quadra Nosedive";
	skill_names[0x0DCD] = "0DCD - Death Drop";
	skill_names[0x0DCE] = "0DCE - Supernova";

	skill_names[0x0DD5] = "0DD5 - Flap Dance";
	skill_names[0x0DD6] = "0DD6 - Quadra Nosedive";
	skill_names[0x0DD7] = "0DD7 - Death Drop";
	skill_names[0x0DD8] = "0DD8 - Supernova";

	skill_names[0x0DDF] = "0DDF - Flap Dance";
	skill_names[0x0DE0] = "0DE0 - Quadra Nosedive";
	skill_names[0x0DE1] = "0DE1 - Death Drop";
	skill_names[0x0DE2] = "0DE2 - Supernova";

	//GALACTIC DEMON SPECIALS
	skill_names[0x0E11] = "0E11 - Magnetic Wave";
	skill_names[0x0E12] = "0E12 - Magnetic Blast";
	skill_names[0x0E13] = "0E13 - Magnetic Field";
	skill_names[0x0E14] = "0E14 - Magnetic Flash";

	skill_names[0x0E1B] = "0E1B - Magnetic Wave";
	skill_names[0x0E1C] = "0E1C - Magnetic Blast";
	skill_names[0x0E1D] = "0E1D - Magnetic Field";
	skill_names[0x0E1E] = "0E1E - Magnetic Flash";

	skill_names[0x0E25] = "0E25 - Magnetic Wave";
	skill_names[0x0E26] = "0E26 - Magnetic Blast";
	skill_names[0x0E27] = "0E27 - Magnetic Field";
	skill_names[0x0E28] = "0E28 - Magnetic Flash";

	skill_names[0x0E2F] = "0E2F - Magnetic Wave";
	skill_names[0x0E30] = "0E30 - Magnetic Blast";
	skill_names[0x0E31] = "0E31 - Magnetic Field";
	skill_names[0x0E32] = "0E32 - Magnetic Flash";

	skill_names[0x0E39] = "0E39 - Magnetic Wave";
	skill_names[0x0E3A] = "0E3A - Magnetic Blast";
	skill_names[0x0E3B] = "0E3B - Magnetic Field";
	skill_names[0x0E3C] = "0E3C - Magnetic Flash";

	skill_names[0x0E43] = "0E43 - Magnetic Wave";
	skill_names[0x0E44] = "0E44 - Magnetic Blast";
	skill_names[0x0E45] = "0E45 - Magnetic Field";
	skill_names[0x0E46] = "0E46 - Magnetic Flash";

	//DRAGON SPECIALS
	skill_names[0x0E75] = "0E75 - Bloody Talons";
	skill_names[0x0E76] = "0E76 - Ice Breath";
	skill_names[0x0E77] = "0E77 - Blue Nova";
	skill_names[0x0E78] = "0E78 - Dragonic Furor";

	skill_names[0x0E7F] = "0E7F - Bloody Talons";
	skill_names[0x0E80] = "0E80 - Ice Breath";
	skill_names[0x0E81] = "0E81 - Blue Nova";
	skill_names[0x0E82] = "0E82 - Dragonic Freeze";

	skill_names[0x0E89] = "0E89 - Bloody Talons";
	skill_names[0x0E8A] = "0E8A - Fire Breath";
	skill_names[0x0E8B] = "0E8B - Red Nova";
	skill_names[0x0E8C] = "0E8C - Dragonic Flare";

	skill_names[0x0E93] = "0E93 - Bloody Talons";
	skill_names[0x0E94] = "0E94 - Fire Breath";
	skill_names[0x0E95] = "0E95 - Red Nova";
	skill_names[0x0E96] = "0E96 - Dragonic Flare";

	skill_names[0x0E9D] = "0E9D - Bloody Talons";
	skill_names[0x0E9E] = "0E9E - Ice Breath";
	skill_names[0x0E9F] = "0E9F - Blue Nova";
	skill_names[0x0EA0] = "0EA0 - Dragonic Flare";

	skill_names[0x0EA7] = "0EA7 - Bloody Talons";
	skill_names[0x0EA8] = "0EA8 - Ice Breath";
	skill_names[0x0EA9] = "0EA9 - Red Nova";
	skill_names[0x0EAA] = "0EAA - Dragonic Flare";

	//GREAT WYRM SPECIALS
	skill_names[0x0ED9] = "0ED9 - Fiery Dance";
	skill_names[0x0EDA] = "0EDA - Fiery Column";
	skill_names[0x0EDB] = "0EDB - Fiery Roar";
	skill_names[0x0EDC] = "0EDC - Fiery Burst";

	skill_names[0x0EE3] = "0EE3 - Raging Dance";
	skill_names[0x0EE4] = "0EE4 - Raging Column";
	skill_names[0x0EE5] = "0EE5 - Raging Roar";
	skill_names[0x0EE6] = "0EE6 - Raging Burst";

	skill_names[0x0EED] = "0EED - Frigid Dance";
	skill_names[0x0EEE] = "0EEE - Frigid Column";
	skill_names[0x0EEF] = "0EEF - Frigid Roar";
	skill_names[0x0EF0] = "0EF0 - Frigid Burst";

	skill_names[0x0EF7] = "0EF7 - Astral Dance";
	skill_names[0x0EF8] = "0EF8 - Astral Column";
	skill_names[0x0EF9] = "0EF9 - Astral Roar";
	skill_names[0x0EFA] = "0EFA - Astral Burst";

	skill_names[0x0F01] = "0F01 - Diabolic Dance";
	skill_names[0x0F02] = "0F02 - Diabolic Column";
	skill_names[0x0F03] = "0F03 - Diabolic Roar";
	skill_names[0x0F04] = "0F04 - Diabolic Burst";

	skill_names[0x0F0B] = "0F0B - Fiery Dance";
	skill_names[0x0F0C] = "0F0C - Fiery Column";
	skill_names[0x0F0D] = "0F0D - Fiery Roar";
	skill_names[0x0F0E] = "0F0E - Fiery Burst";
}
