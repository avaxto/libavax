#ifndef AVAXTO_IDS
#define AVAXTO_IDS

// long id, from 256 bit hashes
typedef unsigned char avax_id_t[32];

// short id, from 160 bit hashes
typedef unsigned char avax_short_id_t[20];

// id from short ids, e.g. NodeID-A6onFGyJjA37EZ7kYHANMR1PFRT8NmXrF
avax_short_id_t *avax_short_id_from_string(const char *str);

// id from long id string
avax_short_id_t *avax_id_from_string(const char *str);


#endif