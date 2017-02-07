#include "fixedstr.h"
#include "detail.h"

bool fstr_eq(const struct fstr *a, const struct fstr *b)
{
	return fstr_eq2_n(a, fstr_cbuf(b), fstr_len(b));
}

bool fstr_eq2(const struct fstr *a, const char *b)
{
	return strcmp(fstr_cbuf(a), b) == 0;
}

bool fstr_eq2_n(const struct fstr *a, const char *b, const size_t blen)
{
	return fstr_len(a) == blen && memcmp(fstr_cbuf(a), b, blen) == 0;
}

