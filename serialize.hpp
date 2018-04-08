typedef struct header_t
{
	size_t order, size, N;
} header_t;

typedef struct type_t
{
	uuid_t version, type;
} type_t;

typedef struct entry_t
{
	size_t offset, index;
} entry_t;

typedef struct table_t
{
	size_t N, *entry_t;
} table_t;