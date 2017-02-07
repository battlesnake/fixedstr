#include "fixedstr.h"
#include "detail.h"

/* Zero-filled initialiser */
const struct fstr FSTR_INIT;

void fstr_init(struct fstr *inst)
{
	inst->data = NULL;
	inst->length = 0;
	inst->owns = false;
	fstr_alloc(inst, 0);
}

void fstr_init_null(struct fstr *inst)
{
	fstr_init_buf(inst, NULL, 0);
}

void fstr_init_from(struct fstr *inst, const char *src)
{
	fstr_init(inst);
	fstr_set(inst, src);
}

void fstr_init_copy(struct fstr *inst, const struct fstr *src)
{
	fstr_init(inst);
	fstr_copy(inst, src);
}

void fstr_init_ref(struct fstr *inst, const char *src)
{
	fstr_init(inst);
	fstr_set_ref(inst, src);
}

void fstr_init_buf(struct fstr *inst, const char *src, size_t srclen)
{
	fstr_init(inst);
	fstr_set_ref_n(inst, src, srclen);
}

void fstr_init_takeown(struct fstr *inst, char *src)
{
	fstr_init_takeown_n(inst, src, strlen(src));
}

void fstr_init_takeown_n(struct fstr *inst, char *src, size_t srclen)
{
	/* TODO: Test, does everything still work if srclen < FSTR_FIXED */
	fstr_init(inst);
	inst->owns = true;
	inst->data = src;
	inst->length = srclen;
	inst->data[inst->length] = 0;
}

void fstr_init_repeat(struct fstr *inst, char ch, size_t count)
{
	fstr_init(inst);
	fstr_alloc(inst, count);
	memset(fstr_buf(inst), ch, count);
}
