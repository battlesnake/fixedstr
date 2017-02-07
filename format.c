#include "fixedstr.h"
#include "detail.h"

void fstr_format(struct fstr *inst, const char *format, ...)
{
	va_list args;
	va_list args2;

	va_start(args, format);
	va_copy(args2, args);
	size_t len = vsnprintf(NULL, 0, format, args);
	va_end(args);

	fstr_alloc(inst, len);

	va_start(args2, format);
	vsnprintf(fstr_buf(inst), len + 1, format, args2);
	va_end(args2);
}

void fstr_format_append(struct fstr *inst, const char *format, ...)
{
	va_list args;
	va_list args2;

	va_start(args, format);
	va_copy(args2, args);
	const size_t len = vsnprintf(NULL, 0, format, args);
	va_end(args);

	const size_t pos = fstr_len(inst);
	fstr_resize(inst, pos + len);

	va_start(args2, format);
	vsnprintf(fstr_buf(inst) + pos, len + 1, format, args2);
	va_end(args2);
}
