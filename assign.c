#include "fixedstr.h"
#include "detail.h"

void fstr_set_null(struct fstr *inst)
{
	fstr_set_ref_n(inst, NULL, 0);
}

void fstr_set_n(struct fstr *inst, const char *src, size_t srclen)
{
	fstr_alloc(inst, srclen);
	memcpy(fstr_buf(inst), src, srclen);
}

void fstr_set(struct fstr *inst, const char *src)
{
	fstr_set_n(inst, src, src ? strlen(src) : 0);
}

void fstr_set_ref(struct fstr *inst, const char *src)
{
	fstr_set_ref_n(inst, src, src ? strlen(src) : 0);
}

void fstr_set_ref_n(struct fstr *inst, const char *src, size_t srclen)
{
	fstr_alloc(inst, 0);
	inst->data = (char *) src;
	inst->length = srclen;
	inst->owns = false;
}

void fstr_copy(struct fstr *inst, const struct fstr *src)
{
	if (fstr_null(src)) {
		fstr_set_null(inst);
	} else {
		fstr_set_n(inst, fstr_cbuf(src), fstr_len(src));
	}
}

void fstr_substr(struct fstr *inst, const struct fstr *src, size_t start, size_t count)
{
	if (start >= inst->length) {
		start = inst->length;
	}
	if (start + count >= inst->length) {
		count = inst->length - start;
	}
	fstr_set_n(inst, fstr_cbuf(src) + start, count);
}

void fstr_substr_ref(struct fstr *inst, const struct fstr *src, size_t start, size_t count)
{
	if (start >= inst->length) {
		start = inst->length;
	}
	if (start + count >= inst->length) {
		count = inst->length - start;
	}
	fstr_set_ref_n(inst, fstr_cbuf(src) + start, count);
}
