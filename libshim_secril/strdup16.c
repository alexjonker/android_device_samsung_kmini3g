/* strdup8to16 / strdup16to8, removed from libcutils, still used by Samsung's libsec-ril */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef uint16_t char16_t_;

/* UTF-8 -> UTF-16. *out_len = number of UTF-16 units (no terminator). */
char16_t_ *strdup8to16(const char *s, size_t *out_len) {
    if (s == NULL) return NULL;
    size_t n = strlen(s);
    char16_t_ *out = malloc((n + 1) * 2 * sizeof(char16_t_));
    if (out == NULL) return NULL;
    const unsigned char *p = (const unsigned char *)s, *end = p + n;
    size_t o = 0;
    while (p < end) {
        uint32_t c = *p++;
        int extra = 0;
        if (c >= 0xF0) { c &= 0x07; extra = 3; }
        else if (c >= 0xE0) { c &= 0x0F; extra = 2; }
        else if (c >= 0xC0) { c &= 0x1F; extra = 1; }
        else if (c >= 0x80) { c = 0xFFFD; }
        while (extra-- > 0 && p < end && (*p & 0xC0) == 0x80) c = (c << 6) | (*p++ & 0x3F);
        if (c > 0xFFFF) {
            c -= 0x10000;
            out[o++] = (char16_t_)(0xD800 | (c >> 10));
            out[o++] = (char16_t_)(0xDC00 | (c & 0x3FF));
        } else {
            out[o++] = (char16_t_)c;
        }
    }
    out[o] = 0;
    if (out_len) *out_len = o;
    return out;
}

/* UTF-16 -> UTF-8, NUL-terminated. */
char *strdup16to8(const char16_t_ *s, size_t len) {
    if (s == NULL) return NULL;
    char *out = malloc(len * 3 + 1);
    if (out == NULL) return NULL;
    size_t o = 0;
    for (size_t i = 0; i < len; i++) {
        uint32_t c = s[i];
        if (c >= 0xD800 && c < 0xDC00 && i + 1 < len && s[i + 1] >= 0xDC00 && s[i + 1] < 0xE000) {
            c = 0x10000 + ((c - 0xD800) << 10) + (s[++i] - 0xDC00);
        }
        if (c < 0x80) out[o++] = (char)c;
        else if (c < 0x800) { out[o++] = 0xC0 | (c >> 6); out[o++] = 0x80 | (c & 0x3F); }
        else if (c < 0x10000) { out[o++] = 0xE0 | (c >> 12); out[o++] = 0x80 | ((c >> 6) & 0x3F); out[o++] = 0x80 | (c & 0x3F); }
        else { out[o++] = 0xF0 | (c >> 18); out[o++] = 0x80 | ((c >> 12) & 0x3F); out[o++] = 0x80 | ((c >> 6) & 0x3F); out[o++] = 0x80 | (c & 0x3F); }
    }
    out[o] = 0;
    return out;
}
