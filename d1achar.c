#include <hammer/hammer.h>
#include <hammer/glue.h>


HParser *d1achar; // character data, not the specially encoded text
HParser *d1aitem;
HParser *d1aspecialist;
HParser *d1atxtchar;

void init_specialist_parser()
{
	H_RULE(spec_level, h_uint16());
	H_RULE(spec_job, h_uint8());
	H_RULE(spec_uniquer, h_uint8());

	d1aspecialist = h_sequence(spec_level, spec_job, spec_uniquer, NULL);
}

void init_item_parser()
{
	H_RULE(item_specialists, h_repeat_n(d1aspecialist, 16));

	H_RULE(item_basesalep, h_uint32());
	H_RULE(item_unk_1, h_uint32());

	H_RULE(item_hp, h_uint32());
	H_RULE(item_sp, h_uint32());
	H_RULE(item_atk, h_uint32());
	H_RULE(item_def, h_uint32());
	H_RULE(item_int, h_uint32());
	H_RULE(item_spd, h_uint32());
	H_RULE(item_hit, h_uint32());
	H_RULE(item_res, h_uint32());

	H_RULE(item_hp_base, h_uint16());
	H_RULE(item_sp_base, h_uint16());
	H_RULE(item_atk_base, h_uint16());
	H_RULE(item_def_base, h_uint16());
	H_RULE(item_int_base, h_uint16());
	H_RULE(item_spd_base, h_uint16());
	H_RULE(item_hit_base, h_uint16());
	H_RULE(item_res_base, h_uint16());

	H_RULE(item_type, h_uint16());
	H_RULE(item_level, h_uint16());
	H_RULE(item_unk2, h_uint16());
	H_RULE(item_rarity, h_uint8());

	H_RULE(item_unk3, h_uint8());
	H_RULE(item_unk4, h_uint8()); // Possbily the item's range

	H_RULE(item_spec_slots, h_uint8());

	H_RULE(item_unk5, h_repeat_n(h_uint8(), 14));

	d1aitem = h_sequence(item_specialists, item_basesalep, item_unk_1, item_hp,
				item_sp, item_atk, item_def, item_int, item_spd, item_hit,
				item_res, item_hp_base, item_sp_base, item_atk_base,
				item_def_base, item_int_base, item_spd_base, item_hit_base,
				item_res_base, item_type, item_level, item_unk2, item_rarity,
				item_unk3, item_unk4, item_spec_slots, item_unk5, NULL);
}

void init_char_parser()
{
	H_RULE(exp, h_uint64());

	d1achar = exp;

}

int main(int argc, char *argv[])
{
	return 0;
}
