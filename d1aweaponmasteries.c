#include "d1aweaponmasteries.h"

#include <hammer/glue.h>

HParser *d1aweaponmastery;
HTokenType TT_WeaponMastery;

static int initialized = 0;

void pp_weaponmastery(FILE *stream, const HParsedToken *tok, int indent, int delta)
{
	WeaponMastery wm = *(H_CAST(WeaponMastery, tok));
	if(wm == 0)
	{
		fprintf(stream, "N/A");
	}
	else if(wm > 0 && wm < 5)
	{
		fprintf(stream, "%d (E)", wm);
	}
	else if(wm >= 5 && wm < 10)
	{
		fprintf(stream, "%d (D)", wm);
	}
	else if(wm >= 10 && wm < 15)
	{
		fprintf(stream, "%d (C)", wm);
	}
	else if(wm >= 15 && wm < 20)
	{
		fprintf(stream, "%d (B)", wm);
	}
	else if(wm >= 20 && wm < 25)
	{
		fprintf(stream, "%d (A)", wm);
	}
	else
	{
		fprintf(stream, "%d (S)", wm);
	}
}

HParsedToken* act_weaponmastery(const HParseResult *p, void *u)
{
	WeaponMastery *wm = H_ALLOC(WeaponMastery);

	*wm = (uint8_t) H_CAST_UINT(p->ast);

	return H_MAKE(WeaponMastery, wm);
}

void weaponmasteries_init_parsers(void)
{
	TT_WeaponMastery = h_allocate_token_new("WeaponMastery", NULL, pp_weaponmastery);
	H_ARULE(weaponmastery, h_uint8());
	d1aweaponmastery = weaponmastery;
	initialized = 1;
}

int weaponmasteries_initialized(void)
{
	return initialized;
}
