#include "d1aspecialist.h"

#include <hammer/glue.h>

HTokenType TT_SpecialistLevel;
HParser *d1aspecialistlevel;

const char *specialist_job_names[0x87] = { "!!Invalid Job ID!!!" };

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

HTokenType TT_SpecialistJob;
HParser *d1aspecialistjob;

const char *specialists_get_job_name(SpecialistJob job)
{
	return specialist_job_names[job];
}

/*
  TODO: With this and all the other IDs (item type, skill), a more stringent validation would check that there is actually an entry corresponding to the ID
  Because so far we're only printing the results, and we're prefilling the array with a fallback string for IDs below the highest valid value, it's not a problem yet to only check for the ID being less or equal than the highest valid ID.
*/
bool validate_specialistjob(HParseResult *p, void *u)
{
	fprintf(stderr, "Token type: %d, expected %d\n", p->ast->token_type, TT_USER);
	return *(H_CAST(SpecialistJob, p->ast)) < 0x87;
}

HParsedToken *act_specialistjob(const HParseResult *p, void *u)
{
	// Ultimately, the Specialist structure has a field the job ID will be
	// copied to in a semantic action. So it's a bit wasteful to allocate
	// this on the heap
	SpecialistJob *sj = H_ALLOC(SpecialistJob);

	*sj = (uint8_t) H_CAST_UINT(p->ast);

	return H_MAKE(SpecialistJob, sj);
}

void pp_specialistjob(FILE *stream, const HParsedToken *tok, int indent, int delta)
{
	SpecialistJob *sj = H_CAST(SpecialistJob, tok);
	fprintf(stream, "%s", specialists_get_job_name(*sj));
}

void fill_specialist_job_names();

void specialists_init_parsers()
{
	TT_SpecialistLevel = h_allocate_token_new("SpecialistLevel", NULL, pp_specialistlevel);
	H_ARULE(specialistlevel, h_with_endianness(BYTE_LITTLE_ENDIAN|BIT_BIG_ENDIAN, h_uint16()));
	d1aspecialistlevel = specialistlevel;

	fill_specialist_job_names();

	TT_SpecialistJob = h_allocate_token_new("SpecialistJob", NULL, pp_specialistjob);
	H_VARULE(specialistjob, h_uint8());
	d1aspecialistjob = specialistjob;
}


void fill_specialist_job_names()
{
	specialist_job_names[0x01] = "Dietician";
	specialist_job_names[0x02] = "Master";
	specialist_job_names[0x03] = "Gladiator";
	specialist_job_names[0x04] = "Sentry";
	specialist_job_names[0x05] = "Teacher";
	specialist_job_names[0x06] = "Coach";
	specialist_job_names[0x07] = "Marksman";
	specialist_job_names[0x08] = "Physician";

	specialist_job_names[0x15] = "Alchemist";
	specialist_job_names[0x16] = "Hypnotist";
	specialist_job_names[0x17] = "Witch Doctor";
	specialist_job_names[0x18] = "Amnesiac";
	specialist_job_names[0x19] = "Gangster";

	specialist_job_names[0x1A] = "Professional";

	specialist_job_names[0x29] = "Pharmacist";
	specialist_job_names[0x2A] = "Coffee Maker";
	specialist_job_names[0x2B] = "Medicine Man";
	specialist_job_names[0x2C] = "Psychologist";
	specialist_job_names[0x2D] = "Social Worker";

	specialist_job_names[0x2E] = "Firefighter";
	specialist_job_names[0x2F] = "Aeronaut";
	specialist_job_names[0x30] = "Cryophile";

	specialist_job_names[0x3D] = "Broker";
	specialist_job_names[0x3E] = "Statistician";
	specialist_job_names[0x3F] = "Manager";
	specialist_job_names[0x40] = "Armsmaster";

	specialist_job_names[0x41] = "Artisan";
	specialist_job_names[0x79] = "Troublemaker";
	specialist_job_names[0x7A] = "Villain";
	specialist_job_names[0x83] = "Item General";
	specialist_job_names[0x84] = "Item King";
	specialist_job_names[0x85] = "Item God";
	specialist_job_names[0x86] = "Item God 2";
}
