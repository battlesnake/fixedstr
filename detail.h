#include "fixedstr.h"

inline static const char *fstr_cbuf(const struct fstr *inst)
{
	return inst->data ? inst->data : inst->fixed;
}

inline static char *fstr_buf(struct fstr *inst)
{
	return inst->data ? inst->data : inst->fixed;
}
