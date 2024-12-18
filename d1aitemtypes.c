#include "d1aitemtypes.h"
#include <hammer/glue.h>

/*
  So far, this token type is just for handling pretty printing
  It may make sense for a more complex application to also declare
  a struct for the value to be parsed into.

  What you need for a token type:
  - A pretty printing function
  - A struct or typedef to wrap in the HParsedToken
  - A semantic action that creates the HParsedToken from the HParseResult
  - (optional) Validations
  - Declare a HTokenType variable to hold the token's number
  - Allocate the token with h_allocate_token_new()

  The Item token will eventually contain an example of that.
*/
HTokenType TT_ItemType;

static const char *item_type_names[0x89A] = { "!!Invalid item type ID!!" };

/*
  This validation is necessary because we only allocated a 0x89A long array
  to store item names. It's attached using a H_VARULE(), meaning the validation
  gets the result of act_itemtype. I think the order doesn't matter much here,
  because ItemType is just a typedef of uint16_t, but when using an H_AVRULE(),
  I'm not sure using H_CAST(ItemType, p) would still be valid.

  (The HParseResult would hold the uninterpreted AST, so with more complex
  structures, it might be a sequence, for example.)
*/
bool validate_itemtype(HParseResult *p, void *u)
{
	return *(H_CAST(ItemType, p->ast)) < 0x89A;
}

HParsedToken* act_itemtype(const HParseResult *p, void *u)
{
	ItemType *it = H_ALLOC(ItemType);

	*it = (uint16_t) H_CAST_UINT(p->ast);

	return H_MAKE(ItemType, it);
}

const char* itemtypes_get_name(ItemType id)
{
	return item_type_names[id];
}

void pp_itemtype(FILE *stream, const HParsedToken *tok, int indent, int delta)
{
	ItemType *it = H_CAST(ItemType, tok);

	// validate_itemtype ensures the parsed token's value isn't larger than 0x89A
	fprintf(stream, "%s", itemtypes_get_name(*it));
}

void itemtypes_fill_type_names();

//TODO: maybe create the HParser here, and add a HParser* to the header
void itemtypes_init_parser()
{
	TT_ItemType = h_allocate_token_new("ItemType", NULL, pp_itemtype);
	itemtypes_fill_type_names();
}

/*
  Values from https://github.com/Xkeeper0/disgaea-pc-tools/
*/

void itemtypes_fill_type_names()
{
	item_type_names[0x0065] = "Wristband";
	item_type_names[0x0066] = "Rock Fist";
	item_type_names[0x0067] = "Double Slap";
	item_type_names[0x0068] = "Leather Glove";
	item_type_names[0x0069] = "Iron Claw";
	item_type_names[0x006A] = "Power Gauntlet";
	item_type_names[0x006B] = "Hyper Knuckle";
	item_type_names[0x006C] = "Lethal Knuckle";
	item_type_names[0x006D] = "Fake Fist";
	item_type_names[0x006E] = "Cross Counter";
	item_type_names[0x006F] = "Swift Knuckle";
	item_type_names[0x0070] = "Magic Cuff";
	item_type_names[0x0071] = "Poison Knuckle";
	item_type_names[0x0072] = "Megaton Punch";
	item_type_names[0x0073] = "Fist of Fury";
	item_type_names[0x0074] = "Mach Punch";
	item_type_names[0x0075] = "Spiked Glove";
	item_type_names[0x0076] = "Bagh Nakh";
	item_type_names[0x0077] = "Mystic Hand";
	item_type_names[0x0078] = "Metal Fist";
	item_type_names[0x0079] = "Silver Arm";
	item_type_names[0x007A] = "Demonic Fist";
	item_type_names[0x007B] = "Karate Chop";
	item_type_names[0x007C] = "Mistral Fist";
	item_type_names[0x007D] = "Jupiters Fist";
	item_type_names[0x007E] = "Straight Punch";
	item_type_names[0x007F] = "Mirage";
	item_type_names[0x0080] = "Kwanca";
	item_type_names[0x0081] = "Bahamuts Fist";
	item_type_names[0x0082] = "Golden Arm";
	item_type_names[0x0083] = "Crisis";
	item_type_names[0x0084] = "Diabolic Fist";
	item_type_names[0x0085] = "Platinum Arm";
	item_type_names[0x0086] = "Galactica";
	item_type_names[0x0087] = "Terra Smasher";
	item_type_names[0x0088] = "Punisher";
	item_type_names[0x0089] = "Zodiac";
	item_type_names[0x008A] = "Infernal Fist";
	item_type_names[0x008B] = "Gods Hand";
	item_type_names[0x008C] = "Ultimus";

	item_type_names[0x00C9] = "Common Sword";
	item_type_names[0x00CA] = "Short Sword";
	item_type_names[0x00CB] = "Swordbreaker";
	item_type_names[0x00CC] = "Bronze Sword";
	item_type_names[0x00CD] = "Long Sword";
	item_type_names[0x00CE] = "Ninja Sword";
	item_type_names[0x00CF] = "Sharp Edge";
	item_type_names[0x00D0] = "Bastard Sword";
	item_type_names[0x00D1] = "Broad Sword";
	item_type_names[0x00D2] = "Magic Sword";
	item_type_names[0x00D3] = "2-Pronged Blade";
	item_type_names[0x00D4] = "Great Sword";
	item_type_names[0x00D5] = "Taser Sword";
	item_type_names[0x00D6] = "Mortuus Blade";
	item_type_names[0x00D7] = "Psychic Sword";
	item_type_names[0x00D8] = "Stabbing Knife";
	item_type_names[0x00D9] = "Evil Thwarter";
	item_type_names[0x00DA] = "Hibernal Sword";
	item_type_names[0x00DB] = "Muramasa";
	item_type_names[0x00DC] = "Light Sabre";
	item_type_names[0x00DD] = "Vajra";
	item_type_names[0x00DE] = "Mistral Sword";
	item_type_names[0x00DF] = "Jupiters Sword";
	item_type_names[0x00E0] = "Bloodlust";
	item_type_names[0x00E1] = "Masamune";
	item_type_names[0x00E2] = "Bahamuts Fang";
	item_type_names[0x00E3] = "Adamant Sword";
	item_type_names[0x00E4] = "Demon Killer";
	item_type_names[0x00E5] = "Wyrmslayer";
	item_type_names[0x00E6] = "Laevateinn";
	item_type_names[0x00E7] = "Diabolic Sword";
	item_type_names[0x00E8] = "Crusade";
	item_type_names[0x00E9] = "Kusanagi";
	item_type_names[0x00EA] = "Excalibur";
	item_type_names[0x00EB] = "Shichishi-Tou";
	item_type_names[0x00EC] = "Infernal Sword";
	item_type_names[0x00ED] = "Arondight";
	item_type_names[0x00EE] = "Amano-Hahakiri";
	item_type_names[0x00EF] = "Cosmic Blade";
	item_type_names[0x00F0] = "Yoshitsuna";

	item_type_names[0x012D] = "Common Spear";
	item_type_names[0x012E] = "Iron Lance";
	item_type_names[0x012F] = "Knights Lance";
	item_type_names[0x0130] = "Bogus Spear";
	item_type_names[0x0131] = "Long Spear";
	item_type_names[0x0132] = "Koshimoto Spear";
	item_type_names[0x0133] = "Bushido Lance";
	item_type_names[0x0134] = "Trident";
	item_type_names[0x0135] = "Paralyzing Spear";
	item_type_names[0x0136] = "Falcon Lance";
	item_type_names[0x0137] = "Forgetful Spear";
	item_type_names[0x0138] = "Black Spear";
	item_type_names[0x0139] = "Silver Lance";
	item_type_names[0x013A] = "Kung Fu Spear";
	item_type_names[0x013B] = "Venomous Spear";
	item_type_names[0x013C] = "Moonlight";
	item_type_names[0x013D] = "Skewer";
	item_type_names[0x013E] = "Mistral Spear";
	item_type_names[0x013F] = "Jupiters Spear";
	item_type_names[0x0140] = "Special Lance";
	item_type_names[0x0141] = "Vile Brilliance";
	item_type_names[0x0142] = "Golden Lance";
	item_type_names[0x0143] = "Bone Lance";
	item_type_names[0x0144] = "Zephyr";
	item_type_names[0x0145] = "Bahamuts Horn";
	item_type_names[0x0146] = "Benkei";
	item_type_names[0x0147] = "Demonic Spear";
	item_type_names[0x0148] = "Pallas Athene";
	item_type_names[0x0149] = "Kiyomasa";
	item_type_names[0x014A] = "Heros Spear";
	item_type_names[0x014B] = "Platinum Lance";
	item_type_names[0x014C] = "Li Shuwen";
	item_type_names[0x014D] = "Diabolic Spear";
	item_type_names[0x014E] = "Walkeure";
	item_type_names[0x014F] = "Gungnir";
	item_type_names[0x0150] = "Gae Bolga";
	item_type_names[0x0151] = "Chaladholg";
	item_type_names[0x0152] = "Infernal Spear";
	item_type_names[0x0153] = "Longinus";
	item_type_names[0x0154] = "Glorious";

	item_type_names[0x0191] = "Common Bow";
	item_type_names[0x0192] = "Hunters Bow";
	item_type_names[0x0193] = "Longbow";
	item_type_names[0x0194] = "Big Arrow";
	item_type_names[0x0195] = "Blessed Bow";
	item_type_names[0x0196] = "Pixie Bow";
	item_type_names[0x0197] = "Enchanted Arrow";
	item_type_names[0x0198] = "Warriors Bow";
	item_type_names[0x0199] = "Sprite Bow";
	item_type_names[0x019A] = "Venomous Bow";
	item_type_names[0x019B] = "Elven Bow";
	item_type_names[0x019C] = "Spirit Bow";
	item_type_names[0x019D] = "Master Bow";
	item_type_names[0x019E] = "Bow of Havoc";
	item_type_names[0x019F] = "Bow of Justice";
	item_type_names[0x01A0] = "Silver Bow";
	item_type_names[0x01A1] = "Flex Bow";
	item_type_names[0x01A2] = "Plasma Arrow";
	item_type_names[0x01A3] = "Heros Bow";
	item_type_names[0x01A4] = "Shining Arrow";
	item_type_names[0x01A5] = "Mistral Bow";
	item_type_names[0x01A6] = "Jupiters Bow";
	item_type_names[0x01A7] = "Golden Bow";
	item_type_names[0x01A8] = "Judgment Arrow";
	item_type_names[0x01A9] = "Remote Bow";
	item_type_names[0x01AA] = "Platinum Bow";
	item_type_names[0x01AB] = "Kuki";
	item_type_names[0x01AC] = "Bow of Virtue";
	item_type_names[0x01AD] = "Arcane Bow";
	item_type_names[0x01AE] = "Yoichis Bow";
	item_type_names[0x01AF] = "Bahamuts Aim";
	item_type_names[0x01B0] = "Percival";
	item_type_names[0x01B1] = "Prometheus";
	item_type_names[0x01B2] = "Starchaser";
	item_type_names[0x01B3] = "Diabolic Bow";
	item_type_names[0x01B4] = "Ulls Bow";
	item_type_names[0x01B5] = "Fleche Enflammee";
	item_type_names[0x01B6] = "Infernal Bow";
	item_type_names[0x01B7] = "Artemis";
	item_type_names[0x01B8] = "Galaxy";

	item_type_names[0x01F5] = "RQ22 Common";
	item_type_names[0x01F6] = "Model 24";
	item_type_names[0x01F7] = "RQ38 Custom";
	item_type_names[0x01F8] = "Dolphin EX";
	item_type_names[0x01F9] = "RQ-P38";
	item_type_names[0x01FA] = "Nether 35";
	item_type_names[0x01FB] = "KLZ900";
	item_type_names[0x01FC] = "RQ44 Magnum";
	item_type_names[0x01FD] = "Model 48";
	item_type_names[0x01FE] = "Dune Eagle";
	item_type_names[0x01FF] = "Nether 58";
	item_type_names[0x0200] = "ZK Auto 13";
	item_type_names[0x0201] = "Ion 8k Ninja";
	item_type_names[0x0202] = "Model 56";
	item_type_names[0x0203] = "RQ57 Dragon";
	item_type_names[0x0204] = "LDT52-R";
	item_type_names[0x0205] = "Nether 72";
	item_type_names[0x0206] = "P50-XX";
	item_type_names[0x0207] = "Ion 9k Samurai";
	item_type_names[0x0208] = "RQ66 Saint";
	item_type_names[0x0209] = "GH401WZ";
	item_type_names[0x020A] = "H30k";
	item_type_names[0x020B] = "PS-714";
	item_type_names[0x020C] = "RQ77 Godslayer";
	item_type_names[0x020D] = "Nether 108";
	item_type_names[0x020E] = "T-199X";
	item_type_names[0x020F] = "Karlten";
	item_type_names[0x0210] = "RQ99 Omega";
	item_type_names[0x0211] = "Gilgamesh";
	item_type_names[0x0212] = "Olympus";
	item_type_names[0x0213] = "Odyssey";
	item_type_names[0x0214] = "Phillipan";
	item_type_names[0x0215] = "Fujiyama";
	item_type_names[0x0216] = "Beowulf";
	item_type_names[0x0217] = "Tiamat";
	item_type_names[0x0218] = "Brunhild";
	item_type_names[0x0219] = "Siegfried";
	item_type_names[0x021A] = "Fenrir";
	item_type_names[0x021B] = "Infernal Gun";
	item_type_names[0x021C] = "Etoile";

	item_type_names[0x0259] = "Common Axe";
	item_type_names[0x025A] = "Villagers Axe";
	item_type_names[0x025B] = "Battle Axe";
	item_type_names[0x025C] = "Bronze Axe";
	item_type_names[0x025D] = "Iron Axe";
	item_type_names[0x025E] = "Tomahawk";
	item_type_names[0x025F] = "Warriors Axe";
	item_type_names[0x0260] = "Mighty Axe";
	item_type_names[0x0261] = "Steel Axe";
	item_type_names[0x0262] = "Stamina Axe";
	item_type_names[0x0263] = "Axe of Sorcery";
	item_type_names[0x0264] = "Pixie Axe";
	item_type_names[0x0265] = "Falcon Axe";
	item_type_names[0x0266] = "Enchanted Axe";
	item_type_names[0x0267] = "Silver Axe";
	item_type_names[0x0268] = "Dwarven Axe";
	item_type_names[0x0269] = "Bloody Axe";
	item_type_names[0x026A] = "Adamant Axe";
	item_type_names[0x026B] = "Demons Axe";
	item_type_names[0x026C] = "Dream Axe";
	item_type_names[0x026D] = "Headhunter";
	item_type_names[0x026E] = "Heros Axe";
	item_type_names[0x026F] = "Mistral Axe";
	item_type_names[0x0270] = "Jupiters Axe";
	item_type_names[0x0271] = "Golden Axe";
	item_type_names[0x0272] = "Vigaros Axe";
	item_type_names[0x0273] = "Axe of Death";
	item_type_names[0x0274] = "Rune Axe";
	item_type_names[0x0275] = "Terra Firma";
	item_type_names[0x0276] = "Hellish Axe";
	item_type_names[0x0277] = "Bahamuts Talon";
	item_type_names[0x0278] = "Platinum Axe";
	item_type_names[0x0279] = "Axe of Slaughter";
	item_type_names[0x027A] = "Mercurius";
	item_type_names[0x027B] = "Diabolic Axe";
	item_type_names[0x027C] = "Empyrean Axe";
	item_type_names[0x027D] = "Balmung";
	item_type_names[0x027E] = "Infernal Axe";
	item_type_names[0x027F] = "Durandal";
	item_type_names[0x0280] = "Apocalypse";

	item_type_names[0x02BD] = "Wooden Staff";
	item_type_names[0x02BE] = "Light Staff";
	item_type_names[0x02BF] = "Witchs Staff";
	item_type_names[0x02C0] = "Mages Staff";
	item_type_names[0x02C1] = "Smiting Rod";
	item_type_names[0x02C2] = "Quality Staff";
	item_type_names[0x02C3] = "Hibernal Staff";
	item_type_names[0x02C4] = "Stamina Staff";
	item_type_names[0x02C5] = "Swordstaff";
	item_type_names[0x02C6] = "Pixie Staff";
	item_type_names[0x02C7] = "Forgetful Staff";
	item_type_names[0x02C8] = "Mortuus Staff";
	item_type_names[0x02C9] = "Staff of Sorcery";
	item_type_names[0x02CA] = "Silver Staff";
	item_type_names[0x02CB] = "Elven Staff";
	item_type_names[0x02CC] = "Blessed Staff";
	item_type_names[0x02CD] = "Sages Staff";
	item_type_names[0x02CE] = "Staff of Hope";
	item_type_names[0x02CF] = "Enchanted Staff";
	item_type_names[0x02D0] = "Mistral Staff";
	item_type_names[0x02D1] = "Jupiters Staff";
	item_type_names[0x02D2] = "Staff of Virtue";
	item_type_names[0x02D3] = "Golden Staff";
	item_type_names[0x02D4] = "Prophets Staff";
	item_type_names[0x02D5] = "Rune Staff";
	item_type_names[0x02D6] = "Rainbow Rod";
	item_type_names[0x02D7] = "Bahamuts Wit";
	item_type_names[0x02D8] = "Holy Staff";
	item_type_names[0x02D9] = "Saints Staff";
	item_type_names[0x02DA] = "Gambantein";
	item_type_names[0x02DB] = "Diabolic Staff";
	item_type_names[0x02DC] = "Tainted Staff";
	item_type_names[0x02DD] = "Polanskys Staff";
	item_type_names[0x02DE] = "Yggdrasil";
	item_type_names[0x02DF] = "Mjollnir";
	item_type_names[0x02E0] = "Dark Matter";
	item_type_names[0x02E1] = "Kerykeion";
	item_type_names[0x02E2] = "Infernal Staff";
	item_type_names[0x02E3] = "Galactic Staff";
	item_type_names[0x02E4] = "Omniscient Staff";

	item_type_names[0x0321] = "Paw Glove";
	item_type_names[0x0322] = "Scratch Claw";
	item_type_names[0x0323] = "Crab Pincer";
	item_type_names[0x0324] = "Shocking Grasp";
	item_type_names[0x0325] = "Poison Needle";
	item_type_names[0x0326] = "Bat Parasol";
	item_type_names[0x0327] = "Cats Claw";
	item_type_names[0x0328] = "Lizard Tail";
	item_type_names[0x0329] = "Porcu-Spine";
	item_type_names[0x032A] = "Electric Eel";
	item_type_names[0x032B] = "Cobra Fang";
	item_type_names[0x032C] = "Spiked Shell";
	item_type_names[0x032D] = "Wolf Fang";
	item_type_names[0x032E] = "Tentacles";
	item_type_names[0x032F] = "Vampire Fang";
	item_type_names[0x0330] = "Gorilla Foot";
	item_type_names[0x0331] = "Lionheart";
	item_type_names[0x0332] = "Bear Claw";
	item_type_names[0x0333] = "Tiger Fang";
	item_type_names[0x0334] = "Panda Claw";
	item_type_names[0x0335] = "Nessie Attack";
	item_type_names[0x0336] = "Medusa Eye";
	item_type_names[0x0337] = "Brocken";
	item_type_names[0x0338] = "Demons Hand";
	item_type_names[0x0339] = "Fiendish Claw";
	item_type_names[0x033A] = "Primal Force";
	item_type_names[0x033B] = "Goblins Fury";
	item_type_names[0x033C] = "Mystic Eye";
	item_type_names[0x033D] = "Geo Saber";
	item_type_names[0x033E] = "Destroy";
	item_type_names[0x033F] = "Lightning Fang";
	item_type_names[0x0340] = "Dragon Tooth";
	item_type_names[0x0341] = "Enigma";
	item_type_names[0x0342] = "Orichalch Claw";
	item_type_names[0x0343] = "El Dorado";
	item_type_names[0x0344] = "Dragon Heart";
	item_type_names[0x0345] = "Belial Force";
	item_type_names[0x0346] = "Amon Force";
	item_type_names[0x0347] = "Lucifer Force";
	item_type_names[0x0348] = "Nyanko Soul";
	item_type_names[0x0349] = "Nemesis";
	item_type_names[0x034A] = "Nemesis Mk-II";

	item_type_names[0x03E9] = "Amulet";
	item_type_names[0x03EA] = "Protector";
	item_type_names[0x03EB] = "Bulletproof Vest";
	item_type_names[0x03EC] = "Fancy Lid";
	item_type_names[0x03ED] = "Leather Jacket";
	item_type_names[0x03EE] = "Chain Mail";
	item_type_names[0x03EF] = "Dimensional Cape";
	item_type_names[0x03F0] = "Power Jacket";
	item_type_names[0x03F1] = "Bushido Armor";
	item_type_names[0x03F2] = "Magic Vest";
	item_type_names[0x03F3] = "Muscle Armor";
	item_type_names[0x03F4] = "Steel Armor";
	item_type_names[0x03F5] = "Fur Coat";
	item_type_names[0x03F6] = "Dandy Gown";
	item_type_names[0x03F7] = "Stealth Cape";
	item_type_names[0x03F8] = "Stinky Jacket";
	item_type_names[0x03F9] = "Ghost Cape";
	item_type_names[0x03FA] = "Prophets Robe";
	item_type_names[0x03FB] = "Silver Tux";
	item_type_names[0x03FC] = "Gritty Vest";
	item_type_names[0x03FD] = "Mistral Armor";
	item_type_names[0x03FE] = "Jupiters Armor";
	item_type_names[0x03FF] = "Cactus Armor";
	item_type_names[0x0400] = "Hero Cape";
	item_type_names[0x0401] = "Gold Tux";
	item_type_names[0x0402] = "Reapers Cloak";
	item_type_names[0x0403] = "Black Armor";
	item_type_names[0x0404] = "Nine Tail Fur";
	item_type_names[0x0405] = "Platinum Tux";
	item_type_names[0x0406] = "Dragon Jacket";
	item_type_names[0x0407] = "Orichalch Shield";
	item_type_names[0x0408] = "Bahamuts Scale";
	item_type_names[0x0409] = "Evil Armor";
	item_type_names[0x040A] = "Shield of Aegis";
	item_type_names[0x040B] = "Celestial Armor";
	item_type_names[0x040C] = "Infernal Cape";
	item_type_names[0x040D] = "Infernal Shield";
	item_type_names[0x040E] = "Infernal Armor";
	item_type_names[0x040F] = "Nirvana";
	item_type_names[0x0410] = "Super Robo Suit";

	item_type_names[0x044D] = "Quasi-Power Belt";
	item_type_names[0x044E] = "Power Belt";
	item_type_names[0x044F] = "Endeavor Belt";
	item_type_names[0x0450] = "Belt of Will";
	item_type_names[0x0451] = "Mega-Power Belt";
	item_type_names[0x0452] = "Monster Belt";
	item_type_names[0x0453] = "Super Belt";
	item_type_names[0x0454] = "Steel Belt";
	item_type_names[0x0455] = "Aura Belt";
	item_type_names[0x0456] = "Love Belt";
	item_type_names[0x0457] = "Spirit Belt";
	item_type_names[0x0458] = "Hero Belt";
	item_type_names[0x0459] = "Soul Belt";
	item_type_names[0x045A] = "Training Belt";
	item_type_names[0x045B] = "Bravery Belt";
	item_type_names[0x045C] = "Guts Belt";
	item_type_names[0x045D] = "Shaolin Belt";
	item_type_names[0x045E] = "Black Belt";
	item_type_names[0x045F] = "Chakra Belt";
	item_type_names[0x0460] = "Champion Belt";

	item_type_names[0x04B1] = "Slippers";
	item_type_names[0x04B2] = "Cross-Trainers";
	item_type_names[0x04B3] = "Ninja Shoes";
	item_type_names[0x04B4] = "Falcon Shoes";
	item_type_names[0x04B5] = "Angels Sandals";
	item_type_names[0x04B6] = "Accelerator";
	item_type_names[0x04B7] = "Hyperdrive";

	item_type_names[0x0515] = "Common Orb";
	item_type_names[0x0516] = "Psyche Orb";
	item_type_names[0x0517] = "Dark Orb";
	item_type_names[0x0518] = "Blood Orb";
	item_type_names[0x0519] = "Star Orb";
	item_type_names[0x051A] = "Moon Orb";
	item_type_names[0x051B] = "King Orb";
	item_type_names[0x051C] = "Holy Orb";
	item_type_names[0x051D] = "Chaos Orb";
	item_type_names[0x051E] = "Universal Orb";

	item_type_names[0x0579] = "Common Glasses";
	item_type_names[0x057A] = "Magnifying Glass";
	item_type_names[0x057B] = "Nerd Glasses";
	item_type_names[0x057C] = "Plastic Nose";
	item_type_names[0x057D] = "Opera Glasses";
	item_type_names[0x057E] = "Nightvision";
	item_type_names[0x057F] = "Crosshair Scope";
	item_type_names[0x0580] = "Foresight";
	item_type_names[0x0581] = "Destiny Lens";
	item_type_names[0x0582] = "Providence";

	item_type_names[0x05DD] = "Muscle Brawn";
	item_type_names[0x05DE] = "Muscle Hustle";
	item_type_names[0x05DF] = "Muscle Spirit";
	item_type_names[0x05E0] = "Muscle Fight";
	item_type_names[0x05E1] = "Muscle Ace";
	item_type_names[0x05E2] = "Muscle Victory";
	item_type_names[0x05E3] = "Muscle Dream";
	item_type_names[0x05E4] = "Muscle World";
	item_type_names[0x05E5] = "Muscle Star";
	item_type_names[0x05E6] = "Galactic Muscle";

	item_type_names[0x0709] = "Horse Wiener";
	item_type_names[0x070A] = "Mahoganys Brain";
	item_type_names[0x070B] = "Hercules Body";
	item_type_names[0x070C] = "Gaos Guts";
	item_type_names[0x070D] = "Crowdias Beauty";
	item_type_names[0x070E] = "Myao's Cat Ears";
	item_type_names[0x070F] = "Prinny Costume";
	item_type_names[0x0710] = "Astro Suit";
	item_type_names[0x0711] = "Felicitacion";
	item_type_names[0x0712] = "Oracle";

	item_type_names[0x076D] = "Imperial Seal";
	item_type_names[0x076E] = "Dark Rosary";
	item_type_names[0x076F] = "Devil Ring";
	item_type_names[0x0770] = "Feather Token";
	item_type_names[0x0771] = "Sofias Mirror";
	item_type_names[0x0772] = "Pravda Necklace";
	item_type_names[0x0773] = "Royal Ring";
	item_type_names[0x0774] = "Testament";
	item_type_names[0x0775] = "Exodus";
	item_type_names[0x0776] = "Arcadia";

	item_type_names[0x07D1] = "ABC Gum";
	item_type_names[0x07D2] = "Mint Gum";
	item_type_names[0x07D3] = "Candy";
	item_type_names[0x07D4] = "Cotton Candy";
	item_type_names[0x07D5] = "Taiyaki";
	item_type_names[0x07D6] = "Chocolate";
	item_type_names[0x07D7] = "Flan";
	item_type_names[0x07D8] = "Eclair";
	item_type_names[0x07D9] = "Shortcake";
	item_type_names[0x07DA] = "Sundae";

	item_type_names[0x07DB] = "Opened Drink";
	item_type_names[0x07DC] = "Unopened Drink";
	item_type_names[0x07DD] = "Garlic Water";
	item_type_names[0x07DE] = "Yam Starch";
	item_type_names[0x07DF] = "Barbeque Sauce";
	item_type_names[0x07E0] = "Egg Yolk";
	item_type_names[0x07E1] = "Protein Shake";
	item_type_names[0x07E2] = "Bloody Mary";
	item_type_names[0x07E3] = "Sake";
	item_type_names[0x07E4] = "Mushroom Soup";

	item_type_names[0x07EF] = "Dried Worm";
	item_type_names[0x07F0] = "Caterpillar Egg";
	item_type_names[0x07F1] = "Charred Newt";
	item_type_names[0x07F2] = "Rooster Blood";
	item_type_names[0x07F3] = "Snake Kidney";
	item_type_names[0x07F4] = "Bat Soup";
	item_type_names[0x07F5] = "Frog Sweat";
	item_type_names[0x07F6] = "Immortals Pill";
	item_type_names[0x07F7] = "Soma";
	item_type_names[0x07F8] = "Elixir";
	item_type_names[0x07F9] = "Veggie Burger";

	item_type_names[0x0803] = "Faerie Dust";

	item_type_names[0x0835] = "Stealing Hand";
	item_type_names[0x0836] = "Plunder Hand";
	item_type_names[0x0837] = "Cha-Ching Hand";
	item_type_names[0x0838] = "Bandits Hand";
	item_type_names[0x0839] = "Awesome Hand";
	item_type_names[0x083A] = "Dream Hand";

	item_type_names[0x0899] = "Mr. Gency's Exit";
}

