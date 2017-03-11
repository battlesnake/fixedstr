#if 0
(
set -euo pipefail
declare -r tmp="$(mktemp)"
gcc -Wall -Wextra -Werror -std=gnu11 -O0 -g -D_GNU_SOURCE -I./c_modules -DTEST_fixedstr -o "$tmp" $(find . -type f -name '*.c')
exec valgrind --quiet --leak-check=full --track-origins=yes "$tmp"
)
exit 0
#endif
#include "fixedstr.h"
#include "detail.h"

void fstr_alloc(struct fstr *inst, size_t len)
{
	if (!inst->owns) {
		inst->data = NULL;
	}
	if (len + 1 < FSTR_FIXED) {
		free(inst->data);
		inst->data = NULL;
	} else {
		inst->data = realloc(inst->data, len + 1);
	}
	fstr_buf(inst)[len] = 0;
	inst->length = len;
	inst->owns = true;
}

void fstr_resize(struct fstr *inst, size_t len)
{
	fstr_break_ref(inst);
	bool prev_inplace = inst->data == NULL;
	bool next_inplace = len + 1 < FSTR_FIXED;
	if (prev_inplace == next_inplace) {
		fstr_alloc(inst, len);
	} else if (prev_inplace) {
		size_t prev_len = inst->length;
		fstr_alloc(inst, len);
		memcpy(inst->data, inst->fixed, prev_len);
	} else if (next_inplace) {
		memcpy(inst->fixed, inst->data, len);
		fstr_alloc(inst, len);
	}
}

void fstr_clear(struct fstr *inst)
{
	fstr_alloc(inst, 0);
}

const char *fstr_ptr(const struct fstr *inst)
{
	return fstr_null(inst) ? NULL : fstr_get(inst);
}

const char *fstr_get(const struct fstr *inst)
{
	return fstr_cbuf(inst);
}

char *fstr_get_mutable(struct fstr *inst)
{
	fstr_break_ref(inst);
	return fstr_buf(inst);
}

size_t fstr_len(const struct fstr *inst)
{
	return inst->length;
}

void fstr_break_ref(struct fstr *inst)
{
	if (inst->owns) {
		return;
	}
	const char *data = fstr_buf(inst);
	const size_t len = fstr_len(inst);
	fstr_alloc(inst, len);
	memcpy(fstr_buf(inst), data, len);
}

char fstr_at(const struct fstr *inst, size_t pos)
{
	return pos < fstr_len(inst) ? fstr_cbuf(inst)[pos] : 0;
}

void fstr_destroy(struct fstr *inst)
{
	if (inst->owns) {
		free(inst->data);
	}
}

size_t fstr_empty(const struct fstr *inst)
{
	return fstr_len(inst) == 0;
}

size_t fstr_null(const struct fstr *inst)
{
	return inst->owns == false && inst->length == 0 && inst->data == NULL;
}

#if defined TEST_fixedstr
int main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;

	struct fstr fs = FSTR_INIT;

	if (!fstr_null(&fs) || !fstr_empty(&fs)) {
		printf("Null/empty test failed\n");
		return 1;
	}

	fstr_init_ref(&fs, "test string");
	printf("%s\n", fstr_get(&fs));
	fstr_destroy(&fs);

	fstr_init_from(&fs, "another test string");
	printf("%s\n", fstr_get(&fs));
	fstr_destroy(&fs);

	fstr_init_null(&fs);

	if (!fstr_null(&fs) || !fstr_empty(&fs)) {
		printf("Null/empty test failed\n");
		return 1;
	}

	fstr_set_ref_n(&fs, "a truncated test string", 11);
	fstr_substr_ref(&fs, &fs, 2, 9);
	printf(PRIfs "\n", prifs(&fs));

	char data[4];
	fstr_set(&fs, "and another");
	fstr_read(&fs, data, sizeof(data));
	printf("%s\n", data);

	fstr_format(&fs, "p=%p d=%d s=%s", "pointer", 42, "string");
	fstr_format_append(&fs, " appending %s %s", "more", "data");
	fstr_append_from(&fs, " and appending a raw string");
	printf(PRIfs "\n", prifs(&fs));

	fstr_set_null(&fs);
	printf(PRIfs "\n", prifs(&fs));

	fstr_destroy(&fs);

	char *c = malloc(13);
	snprintf(c, 13, "Hello world!");
	fstr_init_takeown(&fs, c);
	printf(PRIfs "\n", prifs(&fs));
	fstr_destroy(&fs);

	return 0;
}
#endif
