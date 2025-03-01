#ifndef D1AITEMTYPES_H
#define D1AITEMTYPES_H

#include <hammer/hammer.h>

typedef uint16_t ItemType;

extern HTokenType TT_ItemType;

void itemtypes_init_parser(void);
const char* itemtypes_get_name(ItemType id);

bool validate_itemtype(HParseResult *p, void *u);
HParsedToken* act_itemtype(const HParseResult *p, void *u);
void pp_itemtype(FILE *stream, const HParsedToken *tok, int indent, int delta);

// TODO
/*
extern HParser *d1aitem; // Specialists[16], sale price, stats ...

void items_init_parsers(HParser *specialists);

*/
#endif // D1AITEMTYPES_H

