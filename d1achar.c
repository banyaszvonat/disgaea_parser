#include <hammer/hammer.h>
#include <hammer/glue.h>


HParser *d1achar; // character data, not the specially encoded text
HParser *d1aitem;
HParser *d1aspecialist;
HParser *d1atxtchar;

void init_char_parser()
{
	// "JSAV" magic value, unknown header fields
	//H_RULE(jsav, h_token("JSAVu", 5));
	H_RULE(exp, h_uint64());

	d1achar = exp;

}

int main(int argc, char *argv[])
{
	return 0;
}
