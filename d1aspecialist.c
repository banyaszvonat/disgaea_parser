#include "d1aspecialist.h"

#include <hammer/glue.h>

HTokenType TT_SpecialistLevel;
HParser *d1aspecialistlevel;

HParsedToken* act_specialistlevel(const HParseResult *p, void *u)
{
	SpecialistLevel *sl = H_ALLOC(SpecialistLevel);

	uint16_t lvl = H_CAST_UINT(p->ast);
	if(lvl > 9999)
	{
		sl->level = (lvl - 10000) * 2;
		sl->subdued = true;
	}
	else
	{
		sl->level = lvl;
		sl->subdued = false;
	}

	return H_MAKE(SpecialistLevel, sl);
}

void pp_specialistlevel(FILE *stream, const HParsedToken *tok, int indent, int delta)
{
	SpecialistLevel *sl = H_CAST(SpecialistLevel, tok);
	fprintf(stream, "%d %s", sl->level, sl->subdued ? "(subdued)" : "");
}

void specialists_init_parsers()
{
	TT_SpecialistLevel = h_allocate_token_new("SpecialistLevel", NULL, pp_specialistlevel);
	H_ARULE(specialistlevel, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	d1aspecialistlevel = specialistlevel;
}

