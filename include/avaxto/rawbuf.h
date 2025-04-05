#ifndef AVAXTO_RAWBUF
#define AVAXTO_RAWBUF

typedef struct avax_rawbuf {
	unsigned char *buf;
	long unsigned int buffer_size; // allocated size
	long unsigned int used_size; // used size
} avax_rawbuf;

avax_rawbuf *avax_rawbuf_new(long unsigned int size);
int avax_rawbuf_copy(avax_rawbuf *dest, avax_rawbuf *src);
void avax_rawbuf_free(avax_rawbuf *buf);

#endif
