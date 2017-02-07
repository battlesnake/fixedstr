#if ! defined _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include "fixedstr.h"
#include "detail.h"

bool fstr_contains(const struct fstr *haystack, const struct fstr *needle, size_t start)
{
	return fstr_locate(haystack, needle, start) != FSTR_NOTFOUND;
}

size_t fstr_locate(const struct fstr *haystack, const struct fstr *needle, size_t start)
{
	const char *p = memmem(fstr_cbuf(haystack) + start, fstr_len(haystack) - start, fstr_cbuf(needle), fstr_len(needle));
	if (p == NULL) {
		return FSTR_NOTFOUND;
	}
	return (size_t) (p - fstr_cbuf(haystack));
}

bool fstr_match_start(const struct fstr *haystack, const struct fstr *needle)
{
	size_t hlen = fstr_len(haystack);
	size_t nlen = fstr_len(needle);
	if (nlen > hlen) {
		return false;
	}
	return memcmp(fstr_cbuf(haystack), fstr_cbuf(needle), nlen) == 0;
}

bool fstr_match_end(const struct fstr *haystack, const struct fstr *needle)
{
	size_t hlen = fstr_len(haystack);
	size_t nlen = fstr_len(needle);
	if (nlen > hlen) {
		return false;
	}
	return memcmp(fstr_cbuf(haystack) + (hlen - nlen), fstr_cbuf(needle), nlen) == 0;
}


bool fstr_contains2(const struct fstr *haystack, const char *needle, size_t start)
{
	struct fstr ref;
	fstr_init_ref(&ref, (char *) needle);
	return fstr_contains(haystack, &ref, start);
}

size_t fstr_locate2(const struct fstr *haystack, const char *needle, size_t start)
{
	struct fstr ref;
	fstr_init_ref(&ref, (char *) needle);
	return fstr_locate(haystack, &ref, start);
}

bool fstr_match_start2(const struct fstr *haystack, const char *needle)
{
	struct fstr ref;
	fstr_init_ref(&ref, (char *) needle);
	return fstr_match_start(haystack, &ref);
}

bool fstr_match_end2(const struct fstr *haystack, const char *needle)
{
	struct fstr ref;
	fstr_init_ref(&ref, (char *) needle);
	return fstr_match_end(haystack, &ref);
}


bool fstr_contains2_n(const struct fstr *haystack, const char *needle, size_t needle_len, size_t start)
{
	struct fstr ref;
	fstr_init_buf(&ref, (char *) needle, needle_len);
	return fstr_contains(haystack, &ref, start);
}

size_t fstr_locate2_n(const struct fstr *haystack, const char *needle, size_t needle_len, size_t start)
{
	struct fstr ref;
	fstr_init_buf(&ref, (char *) needle, needle_len);
	return fstr_locate(haystack, &ref, start);
}

bool fstr_match_start2_n(const struct fstr *haystack, const char *needle, size_t needle_len)
{
	struct fstr ref;
	fstr_init_buf(&ref, (char *) needle, needle_len);
	return fstr_match_start(haystack, &ref);
}

bool fstr_match_end2_n(const struct fstr *haystack, const char *needle, size_t needle_len)
{
	struct fstr ref;
	fstr_init_buf(&ref, (char *) needle, needle_len);
	return fstr_match_end(haystack, &ref);
}

bool fstr_contains_ch(const struct fstr *haystack, char ch, size_t start)
{
	return fstr_contains2_n(haystack, &ch, 1, start);
}

size_t fstr_locate_ch(const struct fstr *haystack, char ch, size_t start)
{
	return fstr_locate2_n(haystack, &ch, 1, start);
}
