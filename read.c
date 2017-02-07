#include "fixedstr.h"
#include "detail.h"

size_t fstr_read(const struct fstr *inst, char *buf, size_t bufsize)
{
	size_t len = bufsize <= inst->length ? bufsize - 1 : inst->length;
	strncpy(buf, fstr_cbuf(inst), len);
	buf[len] = 0;
	return len;
}

long fstr_read_l(const struct fstr *inst)
{
	return strtol(fstr_cbuf(inst), NULL, 0);
}

long long fstr_read_ll(const struct fstr *inst)
{
	return strtoll(fstr_cbuf(inst), NULL, 0);
}

float fstr_read_f(const struct fstr *inst)
{
	return strtof(fstr_cbuf(inst), NULL);
}

double fstr_read_d(const struct fstr *inst)
{
	return strtod(fstr_cbuf(inst), NULL);
}
