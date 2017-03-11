#pragma once
#include <cstd/std.h>

#if ! defined FSTR_FIXED
#define FSTR_FIXED 32
#endif

#define PRIfs "%.*s"
#define prifs(inst) ((int) fstr_len(inst)), fstr_get(inst)

struct fstr {
	char *data;
	size_t length;
	bool owns;
	char fixed[FSTR_FIXED];
};

/*
 * NOTE: When initialising as reference, string MUST be null-terminated i.e.
 * src[srclen]==0 otherwise functions which use the string as a C string (e.g.
 * via fstr_get, fstr_get_mutable will not work).
 */

/* Null string */
extern const struct fstr FSTR_INIT;

/* Constructors (a zero-filled string / FSTR_INIT is already constructed) */
void fstr_init(struct fstr *inst);

/* Sets as referencing NULL */
void fstr_init_null(struct fstr *inst);

/* Initialise from C string (copy) */
void fstr_init_from(struct fstr *inst, const char *src);

/* Initialise from another (copy) */
void fstr_init_copy(struct fstr *inst, const struct fstr *src);

/* Assign as refernce (does not copy original) */
void fstr_init_ref(struct fstr *inst, const char *src);
void fstr_init_buf(struct fstr *inst, const char *src, size_t srclen);

/* Take ownership of a buffer (sets src[srclen] <- 0, buffer must have size >= srclen+1 )*/
void fstr_init_takeown(struct fstr *inst, char *src);
void fstr_init_takeown_n(struct fstr *inst, char *src, size_t srclen);

/* Initialise as repetition of char */
void fstr_init_repeat(struct fstr *inst, char ch, size_t count);

/* Equality */
bool fstr_eq(const struct fstr *a, const struct fstr *b);
bool fstr_eq2(const struct fstr *a, const char *b);
bool fstr_eq2_n(const struct fstr *a, const char *b, const size_t blen);

/* Partial equality */
#define FSTR_NOTFOUND ((size_t) -1)
bool fstr_contains(const struct fstr *haystack, const struct fstr *needle, size_t start);
size_t fstr_locate(const struct fstr *haystack, const struct fstr *needle, size_t start);
bool fstr_match_start(const struct fstr *haystack, const struct fstr *needle);
bool fstr_match_end(const struct fstr *haystack, const struct fstr *needle);

bool fstr_contains2(const struct fstr *haystack, const char *needle, size_t start);
size_t fstr_locate2(const struct fstr *haystack, const char *needle, size_t start);
bool fstr_match_start2(const struct fstr *haystack, const char *needle);
bool fstr_match_end2(const struct fstr *haystack, const char *needle);

bool fstr_contains2_n(const struct fstr *haystack, const char *needle, size_t needle_len, size_t start);
size_t fstr_locate2_n(const struct fstr *haystack, const char *needle, size_t needle_len, size_t start);
bool fstr_match_start2_n(const struct fstr *haystack, const char *needle, size_t needle_len);
bool fstr_match_end2_n(const struct fstr *haystack, const char *needle, size_t needle_len);

bool fstr_contains_ch(const struct fstr *haystack, char ch, size_t start);
size_t fstr_locate_ch(const struct fstr *haystack, char ch, size_t start);

/* Allocates an uninitialised, null-appended buffer which stores at least len bytes */
void fstr_alloc(struct fstr *inst, size_t len);

/* Like alloc, but preserves contents (aside from truncation) */
void fstr_resize(struct fstr *inst, size_t len);

/* Set to zero length */
void fstr_clear(struct fstr *inst);

/* sprintf into a fstr */
void fstr_format(struct fstr *inst, const char *format, ...) __attribute__((format(printf, 2, 3)));
void fstr_format_append(struct fstr *inst, const char *format, ...) __attribute__((format(printf, 2, 3)));

void fstr_append(struct fstr *inst, const struct fstr *src);
void fstr_append_from(struct fstr *inst, const char *src);
void fstr_append_n(struct fstr *inst, const char *src, size_t srclen);

/* If string is a reference to another, copy data into this string */
void fstr_break_ref(struct fstr *inst);

/* Set value from null-terminated or fixed-length string */
void fstr_set_null(struct fstr *inst);
void fstr_set(struct fstr *inst, const char *src);
void fstr_set_ref(struct fstr *inst, const char *src);
void fstr_set_n(struct fstr *inst, const char *src, size_t srclen);
void fstr_set_ref_n(struct fstr *inst, const char *src, size_t srclen);

/* Copy */
void fstr_copy(struct fstr *inst, const struct fstr *src);
void fstr_substr(struct fstr *inst, const struct fstr *src, size_t start, size_t count);
void fstr_substr_ref(struct fstr *inst, const struct fstr *src, size_t start, size_t count);

/* Read into buffer */
size_t fstr_read(const struct fstr *inst, char *buf, size_t bufsize);

/* Parse */
long fstr_read_l(const struct fstr *inst);
long long fstr_read_ll(const struct fstr *inst);
float fstr_read_f(const struct fstr *inst);
double fstr_read_d(const struct fstr *inst);

/* Get pointer to buffer (NULL if null) */
const char *fstr_ptr(const struct fstr *inst);

/* Get pointer to buffer (empty string if null) */
const char *fstr_get(const struct fstr *inst);

/* Chat at pos (NULL char if out of range) */
char fstr_at(const struct fstr *inst, size_t pos);

/* Will copy data in if instance is a reference */
char *fstr_get_mutable(struct fstr *inst);

/* Get length */
size_t fstr_len(const struct fstr *inst);

/* Length is zero */
size_t fstr_empty(const struct fstr *inst);

/* String is NULL */
size_t fstr_null(const struct fstr *inst);

/* Destructor */
void fstr_destroy(struct fstr *inst);

/* Lexicographical comparison */
int fstr_cmp(const struct fstr *a, const struct fstr *b);

/* Lexicographical comparison up to (but not including) given char */
int fstr_cmp_upto(const struct fstr *a, const struct fstr *b, char end);
