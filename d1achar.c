#include <hammer/hammer.h>
#include <hammer/glue.h>
#include <err.h>
#include <fcntl.h> /* open() */
#include <unistd.h> /* lseek() */
#include <sys/mman.h> /* mmap() */

#include "d1aitemtypes.h"
#include "d1aspecialist.h"
#include "d1askills.h"

HParser *d1achar; // character data, not the specially encoded text
HParser *d1aitem;
HParser *d1atxtstring;

typedef struct {
	HBytes name;
	HBytes class;
	int level;
	int mana;
	int exp;
	ItemType weapon;
	ItemType equipment[3];

	int skills_known;
	SkillID skills[96];
} D1ACharSummary;

HParsedToken*
act_d1atxtchar(const HParseResult *p, void *u)
{
	uint16_t enc_char = H_CAST_UINT(p->ast);
	uint8_t dec_char;
	// Uppercase letters
	if (enc_char >= 0x8260 && enc_char <= 0x827A)
	{
		dec_char = (uint8_t) ((enc_char - 0x8260) + 'A');
	}
	// Lowercase letters
	else if (enc_char >= 0x8281 && enc_char <= 0x829A)
	{
		dec_char = (uint8_t) ((enc_char - 0x8281) + 'a');
	}
	else if (enc_char == 0x8140)
	{
		dec_char = ' ';
	}
	else if (enc_char == 0x8146)
	{
		dec_char = ':';
	}
	else if (enc_char == 0x817C)
	{
		dec_char = '-';
	}
	else if (enc_char == 0x8166)
	{
		dec_char = 0x27; // the ' character
	}
	else if (enc_char == 0x8144)
	{
		dec_char = '.';
	}
	// Assuming other values in the range not handled above are unknown but valid characters
	// Rendering them as space for now
	else if (enc_char >= 0x8140 && enc_char <= 0x829A)
	{
		dec_char = ' ';
	}
	// Presumed invalid
	// This can be handled and rejected using a validation, but for now it is permissive
	else
	{
		dec_char = '.';
	}

	return H_MAKE_UINT(dec_char);
}

// Takes a sequence of characters (uints) and creates an array of bytes from them
// decoding the characters and merging them into a byte array probably can also be done via a monadic bind
HParsedToken*
act_d1asavestring(const HParseResult *p, void *u)
{
	HCountedArray *seq = H_CAST_SEQ(p->ast);
	uint8_t *bytes;

	bytes = h_arena_malloc(p->arena, seq->used);
	for (size_t i = 0; i < seq->used; ++i)
		bytes[i] = H_CAST_UINT(seq->elements[i]);

	return H_MAKE_BYTES(bytes, seq->used);
}

void init_text_string_parser()
{
	//H_RULE(text_string, h_repeat_n(h_uint16(), 16));
	//HACK: strings generally seem to be two bytes per character, terminated by a single null byte.
	//	although the size reserved for it in the character data seems to be 32+1 bytes, so we can get away with assuming fixed size
	//	need to test: h_choice(h_ch('\0'), h_many1(h_butnot(h_uint16(), h_ch('\0')), NULL), NULL);
	H_ARULE(d1atxtchar, h_uint16());
	H_ARULE(d1asavestring, h_repeat_n(d1atxtchar, 16));

	//d1atxtstring = text_string;
	d1atxtstring = d1asavestring;
}

void init_item_parser()
{
	H_RULE(item_specialists, h_repeat_n(d1aspecialist, 16));

	H_RULE(item_basesalep, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(item_unk_1, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));

	H_RULE(item_hp, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(item_sp, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(item_atk, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(item_def, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(item_int, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(item_spd, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(item_hit, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(item_res, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));

	H_RULE(item_hp_base, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_RULE(item_sp_base, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_RULE(item_atk_base, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_RULE(item_def_base, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_RULE(item_int_base, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_RULE(item_spd_base, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_RULE(item_hit_base, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_RULE(item_res_base, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));

	//H_RULE(item_type, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_VARULE(itemtype, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_RULE(item_level, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_RULE(item_unk2, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_RULE(item_rarity, h_uint8());

	H_RULE(item_unk3, h_uint8());
	H_RULE(item_unk4, h_uint8()); // Possbily the item's range

	H_RULE(item_spec_slots, h_uint8());

	H_RULE(item_unk5, h_repeat_n(h_uint8(), 14));

	d1aitem = h_sequence(item_specialists, item_basesalep, item_unk_1, item_hp,
				item_sp, item_atk, item_def, item_int, item_spd, item_hit,
				item_res, item_hp_base, item_sp_base, item_atk_base,
				item_def_base, item_int_base, item_spd_base, item_hit_base,
				item_res_base, itemtype, item_level, item_unk2, item_rarity,
				item_unk3, item_unk4, item_spec_slots, item_unk5, NULL);
}

void init_char_parser()
{
	H_RULE(char_exp, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint64()));

	H_RULE(char_weapon, d1aitem);
	H_RULE(char_etc_items, h_repeat_n(d1aitem, 3));

	H_RULE(char_name, d1atxtstring);
	H_RULE(char_unk1, h_uint8());
	H_RULE(char_class, d1atxtstring);
	H_RULE(char_unk98, h_repeat_n(h_uint8(), 35));
	H_RULE(char_psn_resist, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_RULE(char_slp_resist, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_RULE(char_par_resist, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_RULE(char_fgt_resist, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_RULE(char_dpr_resist, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_RULE(char_unk91, h_repeat_n(h_uint8(), 78));
	H_RULE(char_unk90, h_uint8());
	H_RULE(char_unk81, h_uint8());
	H_RULE(char_unk80, h_uint8());
	H_RULE(char_unk79, h_uint8());
	H_RULE(char_unk78, h_uint8());
	H_RULE(char_unk77, h_uint8());
	H_RULE(char_unk2, h_repeat_n(h_uint8(), 26));
	H_RULE(char_skillexps, h_repeat_n(h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()), 96));
	//H_RULE(char_skillids, h_repeat_n(h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()), 96));
	H_RULE(char_skillids, h_repeat_n(d1askillid, 96));
	H_RULE(char_skillevels, h_repeat_n(h_uint8(), 96));

	H_RULE(char_hp_current, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_sp_current, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_hp, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_sp, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_atk, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_def, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_int, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_spd, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_hit, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_res, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));

	H_RULE(char_hp_actual, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_sp_actual, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_atk_actual, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_def_actual, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_int_actual, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_spd_actual, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_hit_actual, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_res_actual, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));

	H_RULE(char_unk68, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_unk4, h_repeat_n(h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()), 7)); // guess, seeing how all the other fields here are 4 bytes
	H_RULE(char_mana, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint32()));
	H_RULE(char_unk99, h_repeat_n(h_uint8(), 24));
	H_RULE(char_unk70, h_uint8());
	H_RULE(char_unk69, h_uint8());
	H_RULE(char_unk67, h_uint8());
	H_RULE(char_unk87, h_uint8());
	H_RULE(char_unk86, h_repeat_n(h_uint8(), 4));
	H_RULE(char_fist_aptitude, h_uint8()); // from status screen code reading these values
	H_RULE(char_sword_aptitude, h_uint8());
	H_RULE(char_spear_aptitude, h_uint8());
	H_RULE(char_bow_aptitude, h_uint8());
	H_RULE(char_gun_aptitude, h_uint8());
	H_RULE(char_axe_aptitude, h_uint8());
	H_RULE(char_staff_aptitude, h_uint8());
	H_RULE(char_monsterwep_aptitude, h_uint8());

	H_RULE(char_hp_base, h_uint8());
	H_RULE(char_sp_base, h_uint8());
	H_RULE(char_atk_base, h_uint8());
	H_RULE(char_def_base, h_uint8());
	H_RULE(char_int_base, h_uint8());
	H_RULE(char_spd_base, h_uint8());
	H_RULE(char_hit_base, h_uint8());
	H_RULE(char_res_base, h_uint8());

	H_RULE(char_level, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_RULE(char_unk89, h_repeat_n(h_uint8(), 2));
	H_RULE(char_classid, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16())); // TODO: token type, class names
	H_RULE(char_unk96, h_repeat_n(h_uint8(), 2));
	H_RULE(char_unk76, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	H_RULE(char_unk75, h_repeat_n(h_uint8(), 10));

	H_RULE(char_fire_res_base, h_int8());	// order of actual vs. base could be different here, needs more testing
	H_RULE(char_wind_res_base, h_int8());
	H_RULE(char_ice_res_base, h_int8());

	H_RULE(char_fire_res_actual, h_int8());
	H_RULE(char_wind_res_actual, h_int8());
	H_RULE(char_ice_res_actual, h_int8());

	H_RULE(char_jump_base, h_uint8());
	H_RULE(char_jump_actual, h_uint8());
	H_RULE(char_mv_base, h_uint8());
	H_RULE(char_mv_actual, h_uint8());
	H_RULE(char_counter_base, h_uint8());
	H_RULE(char_counter_actual, h_uint8());

	H_RULE(char_unk85, h_uint8());
	H_RULE(char_skillsknown, h_uint8());
	H_RULE(char_unk97, h_repeat_n(h_uint8(), 6));
	H_RULE(char_unk82, h_uint8());
	H_RULE(char_currentweapontype, h_uint8());
	H_RULE(char_unk83, h_repeat_n(h_uint8(), 3));
	H_RULE(char_assemblyrank, h_uint8());
	H_RULE(char_unk93, h_repeat_n(h_uint8(), 4));
	H_RULE(char_unk92, h_uint8());
	H_RULE(char_unk95, h_repeat_n(h_uint8(), 9));
	H_RULE(char_unk74, h_uint8());
	H_RULE(char_unk73, h_repeat_n(h_uint8(), 11));

	d1achar = h_sequence(char_exp, char_weapon, char_etc_items, char_name, char_unk1,
				char_class, char_unk98, char_psn_resist, char_slp_resist,
				char_par_resist, char_fgt_resist, char_dpr_resist,
				char_unk91, char_unk90, char_unk81, char_unk80,
				char_unk79, char_unk78, char_unk77,
				char_unk2, char_skillexps, char_skillids,
				char_skillevels, char_hp_current, char_sp_current,
				char_hp, char_sp, char_atk, char_def, char_int, char_spd,
				char_hit, char_res, char_hp_actual, char_sp_actual,
				char_atk_actual, char_def_actual, char_int_actual,
				char_spd_actual, char_hit_actual, char_res_actual,
				char_unk68,
				char_unk4, char_mana, char_unk99, char_unk70,
				char_unk69, char_unk67, char_unk87,
				char_unk86, char_fist_aptitude, char_sword_aptitude,
				char_spear_aptitude, char_bow_aptitude,
				char_gun_aptitude, char_axe_aptitude,
				char_staff_aptitude, char_monsterwep_aptitude,
				char_hp_base,
				char_sp_base, char_atk_base, char_def_base,
				char_int_base, char_spd_base, char_hit_base,
				char_res_base, char_level, char_unk89, char_classid,
				char_unk96, char_unk76, char_unk75,
				char_fire_res_base,
				char_wind_res_base, char_ice_res_base,
				char_fire_res_actual, char_wind_res_actual,
				char_ice_res_actual, char_jump_base, char_jump_actual,
				char_mv_base, char_mv_actual, char_counter_base,
				char_counter_actual, char_unk85, char_skillsknown,
				char_unk97, char_unk82,
				char_currentweapontype, char_unk83,
				char_assemblyrank, char_unk93, char_unk92,
				char_unk95, char_unk74, char_unk73, NULL);

}

void print_summary(HParseResult *char_res)
{
	D1ACharSummary summary;

	summary.name = H_INDEX_BYTES(char_res->ast, 3);
	summary.class = H_INDEX_BYTES(char_res->ast, 5);

	summary.level = H_INDEX_UINT(char_res->ast, 66);
	summary.mana = H_INDEX_UINT(char_res->ast, 43);
	summary.exp = H_INDEX_UINT(char_res->ast, 0);

	/*
	  Item's type is the 19th field of the sequence representing items.
	  Ideally the application would define a struct to deal with items,
	  but for now, only the type is interesting.
	*/
	ItemType *weapon = H_INDEX(ItemType, char_res->ast, 1, 19);
	summary.weapon = *weapon;

	for(int i = 0; i < 3; i++)
	{
		ItemType *item = H_INDEX(ItemType, char_res->ast, 2, i, 19);
		summary.equipment[i] = *item;
	}

	summary.skills_known = H_INDEX_UINT(char_res->ast, 85);
	for(int i = 0; i < summary.skills_known; i++)
	{
		summary.skills[i] = *H_INDEX(SkillID, char_res->ast, 21, i);
	}

	/*
	  Can get away with casting size_t -> int here unless the game
	  uses strings longer than INT_MAX, which would get truncated.

	  Additionally, these particular strings are a fixed 32 bytes (16 characters).
	*/
	printf("Name: %.*s\n", (int) summary.name.len, summary.name.token);
	printf("Class: %.*s\n", (int) summary.class.len, summary.class.token);

	printf("Level: %d\nMana: %d\nEXP: %d\n", summary.level, summary.mana, summary.exp);
	printf("Weapon:\n");
	printf("\t%s\n", itemtypes_get_name(summary.weapon));
	printf("Items:\n");
	for(int i = 0; i < 3; i++)
	{
		printf("\t%s\n", itemtypes_get_name(summary.equipment[i]));
	}
	printf("Skills:\n");
	for(int i = 0; i < summary.skills_known; i++)
	{
		printf("\t%s\n", skills_get_name(summary.skills[i]));
	}

	return;
}

int main(int argc, char *argv[])
{
	int fd;
	off_t sz;
	const uint8_t *input_bytes;
	HParseResult *res_d1char;


	if (argc < 2 || argc > 2)
	{
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		return 1;
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		err(1, "%s", argv[1]);
	sz = lseek(fd, 0, SEEK_END);
	if (sz == -1)
		err(1, "lseek error");
	if (sz < 0)
		err(1, "lseek: returned size less than 0");
	input_bytes = mmap(NULL, sz ? sz : 1, PROT_READ, MAP_PRIVATE, fd, 0);
	if (input_bytes == MAP_FAILED)
		err(1, "mmap error");

	init_text_string_parser();
	specialists_init_parsers();
	itemtypes_init_parser();
	init_item_parser();
	skills_init_parsers();
	init_char_parser();

	res_d1char = h_parse(d1achar, input_bytes, sz);

	if(!res_d1char || !res_d1char->ast)
	{
		fprintf(stderr, "%s: parse failed lol\n", argv[1]);
		close(fd);
		return 2;
	}

	//h_pprintln(stdout, res_d1char->ast);
	print_summary(res_d1char);

	close(fd);
	return 0;
}
