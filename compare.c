#include <cstruct/comparator.h>
#include "fixedstr.h"
#include "detail.h"

int fstr_cmp(const struct fstr *a, const struct fstr *b)
{
	return compare_lex(fstr_cbuf(a), fstr_len(a), fstr_cbuf(b), fstr_len(b));
}

int fstr_cmp_upto(const struct fstr *a, const struct fstr *b, char end)
{
	return compare_lex_to(fstr_cbuf(a), fstr_len(a), fstr_cbuf(b), fstr_len(b), end);
}
