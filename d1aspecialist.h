#ifndef D1ASPECIALIST_H
#define D1ASPECIALIST_H

#include <hammer/hammer.h>

typedef struct {
	uint16_t level;
	bool subdued;
} SpecialistLevel;

extern HParser *d1aspecialistlevel;
extern HTokenType TT_SpecialistLevel;

HParsedToken* act_specialistlevel(const HParseResult *p, void *u);
void pp_specialistlevel(FILE *stream, const HParsedToken *tok, int indent, int delta);

//TODO

/*
typedef uint8_t SpecialistJob;

extern HParser *d1aspecialistjob;
extern HTokenType TT_SpecialistJob;

HParsedToken *act_specialistjob(const HParseResult *tok, void *u);
void pp_specialistjob(FILE *stream, const HParsedToken *p, int indent, int delta);

typedef struct {
	SpecialistLevel *level;
	SpecialistJob job;
	uint8_t uniquer;
} Specialist;

extern HParser *d1aspecialist;
extern HTokenType TT_Specialist;

HParsedToken *act_specialist(const HParseResult *tok, void *u);
void pp_specialist(FILE *stream, const HParsedToken *p, int indent, int delta);
*/


void specialists_init_parsers();

#endif // D1ASPECIALIST_H

