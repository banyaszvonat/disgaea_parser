#ifndef D1ASKILLS_H
#define D1ASKILLS_H

#include <hammer/hammer.h>

typedef uint16_t SkillID;

extern HParser *d1askillid;
extern HTokenType TT_SkillID;

void skills_init_parsers();
const char *skills_get_name(SkillID id);

bool validate_skillid(HParseResult *p, void *u);
HParsedToken* act_skillid(const HParseResult *p, void *u);
void pp_skillid(FILE *stream, const HParsedToken *tok, int indent, int delta);

//TODO
/*
extern HParser *d1askillsblock; // skillEXP[96], skillID[96], skillLevel[96]

*/
#endif // D1ASKILLS_H
