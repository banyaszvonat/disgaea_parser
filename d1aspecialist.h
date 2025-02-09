#ifndef D1ASPECIALIST_H
#define D1ASPECIALIST_H

#include <hammer/hammer.h>

/* Specialist level */

typedef struct {
	uint16_t level;
	bool subdued;
} SpecialistLevel;

extern HParser *d1aspecialistlevel;
extern HTokenType TT_SpecialistLevel;

HParsedToken* act_specialistlevel(const HParseResult *p, void *u);
void pp_specialistlevel(FILE *stream, const HParsedToken *tok, int indent, int delta);

/* Specialist job */

typedef uint8_t SpecialistJob;

const char* specialists_get_job_name(SpecialistJob job);

extern HParser *d1aspecialistjob;
extern HTokenType TT_SpecialistJob;

bool validate_specialistjob(HParseResult *p, void *u);
HParsedToken *act_specialistjob(const HParseResult *p, void *u);
void pp_specialistjob(FILE *stream, const HParsedToken *tok, int indent, int delta);

/* Specialist */

typedef struct {
	SpecialistLevel *level;
	SpecialistJob job;
	uint8_t uniquer;
} Specialist;

extern HParser *d1aspecialist;
extern HTokenType TT_Specialist;

HParsedToken *act_specialist(const HParseResult *p, void *u);
void pp_specialist(FILE *stream, const HParsedToken *tok, int indent, int delta);

/* Initialization, check init status */

void specialists_init_parsers(void);
//TODO: other parsers should allow checking initialization status too
int specialists_initialized(void);

#endif // D1ASPECIALIST_H

