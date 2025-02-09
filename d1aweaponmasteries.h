#ifndef D1AWEAPONMASTERIES_H
#define D1AWEAPONMASTERIES_H

#include <hammer/hammer.h>

typedef uint8_t WeaponMastery;

extern HParser *d1aweaponmastery;
extern HTokenType TT_WeaponMastery;

HParsedToken* act_weaponmastery(const HParseResult *p, void *u);
void pp_weaponmastery(FILE *stream, const HParsedToken *tok, int indent, int delta);

void weaponmasteries_init_parsers(void);
int weaponmasteries_initialized(void);


#endif // D1AWEAPONMASTERIES_H
