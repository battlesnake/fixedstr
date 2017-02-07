#include "fixedstr.h"
#include "detail.h"

void fstr_append(struct fstr *inst, const struct fstr *src)
{
	fstr_append_n(inst, fstr_get(src), fstr_len(src));
}

void fstr_append_from(struct fstr *inst, const char *src)
{
	fstr_append_n(inst, src, strlen(src));
}

void fstr_append_n(struct fstr *inst, const char *src, size_t srclen)
{
	const size_t pos = fstr_len(inst);
	fstr_resize(inst, pos + srclen);
	memcpy(fstr_buf(inst) + pos, src, srclen);
}
