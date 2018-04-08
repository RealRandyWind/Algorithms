#ifndef TIFF_HPP
#define TIFF_HPP

#include <core>
#include <fstream>

#define TIFF_TYPES_SIZE 13

#define TIFF_ORDER_II 0x4949
#define TIFF_ORDER_MM 0x4D4D
#define TIFF_CHECK 42
#define TIFF_VALUE_SIZEOF 4

/* pre declarations */

typedef struct tiff_header tiff_header;
typedef union tiff_value tiff_value;
typedef union tiff_pvalue tiff_pvalue;
typedef struct tiff_field tiff_field;
typedef struct tiff_directory tiff_directory;
typedef struct tiff_t tiff_t;

inline std::istream & operator>>(std::istream &is, tiff_header &header);
inline std::istream & operator>>(std::istream &is, tiff_field &field);
inline std::istream & operator>>(std::istream &is, tiff_directory &directory);
inline std::istream & operator>>(std::istream &is, tiff_t &tiff);

/* post declarations */

static const size_t tiff_sizeof_map[TIFF_TYPES_SIZE] = 
{
	TIFF_VALUE_SIZEOF,		/*  */
	sizeof(int8_t), 		/* BYTE */
	sizeof(int8_t),			/* ASCII */
	sizeof(int16_t),		/* SHORT */
	sizeof(int32_t),		/* LONG */
	sizeof(int32_t) * 2,	/* RATIONAL */
	sizeof(uint8_t),		/* SBYTE */
	sizeof(int8_t),			/* UNDEFINED */
	sizeof(uint16_t),		/* SSHORT */
	sizeof(uint32_t),		/* SLONG */
	sizeof(uint32_t) * 2,	/* SRATIONAL */
	sizeof(float),			/* FLOAT */
	sizeof(double)			/* DOUBLE */
};

struct tiff_header
{
	boolean_t II, MM, TIFF;
	size_t offset;
};

struct tiff_field
{
	enum_t tag, type;
	size_t N, _N, size, offset;
	pointer_t pvalue;
};

struct tiff_directory
{
	size_t N, _N, offset;
	tiff_field *fields;
	struct tiff_directory *_next;
};

struct tiff_t
{
	size_t N, _N;
	tiff_header header;
	tiff_directory *directory;

	tiff_t() { N = 0; _N = 0; directory = nullptr; };

	tiff_t(char* fileName)
	{
		std::ifstream is;

		if(!fileName) { exit(EXIT_FAILURE); }
		is.open(fileName, std::ios::binary);
		is >> *this;
	};

	~tiff_t()
	{
		/*
		tiff_field field;
		size_t n, k;
		while(directory)
		{
			for (n = 0; n < directory->N; ++n)
			{
				field = directory->fields[n];
				for (k = 0; k < field.N; ++k)
				{
					if(field.REF && field.pvalue) { delete[] field.pvalue; }
				}
				if(directory->fields) { delete[] directory->fields; }
				delete directory;
			}
			directory = directory->_next;
		}
		*/
	};
};

/* helper functions */

inline size_t tiff_sizeof(enum_t type)
{
	return type >= sizeof(uint64_t) ? 1 : tiff_sizeof_map[type];
};

/* stream overloads */

inline std::istream & operator>>(std::istream &is, tiff_header &header)
{
	byte_t<2> raworder, rawcheck;
	byte_t<4> rawoffset;
	
	is >> raworder >> rawcheck >> rawoffset;
	header.II = (TIFF_ORDER_II == raworder);
	header.MM = (TIFF_ORDER_MM == raworder);
	header.TIFF = (TIFF_CHECK == rawcheck);
	header.offset = static_cast<size_t>(rawoffset);
	
	return is;
};

inline std::istream & operator>>(std::istream &is, tiff_field &field)
{
	byte_t<2> rawtag, rawtype;
	byte_t<4> rawN, rawoffset;
	size_t nbytes;

	is >> rawtag >> rawtype >> rawN >> rawoffset;
	field.tag = static_cast<enum_t>(rawtag);
	field.type = static_cast<enum_t>(rawtype);
	field.N = field._N = rawN ? static_cast<size_t>(rawN) : 1;
	field.size = tiff_sizeof(field.type);
	field.offset = static_cast<size_t>(rawoffset);
	field.pvalue = nullptr;
	if(!field.offset) { return is; }
	nbytes = field.N ? field.N * field.size : sizeof(rawoffset);
	field.offset = nbytes > sizeof(rawoffset) 
		? static_cast<size_t>(rawoffset) 
		: static_cast<size_t>(is.tellg()) - sizeof(rawoffset);
	
	return is;
};

inline std::istream & operator>>(std::istream &is, tiff_directory &directory)
{
	byte_t<2> rawN;
	byte_t<4> rawoffset;
	size_t n;

	is >> rawN;
	directory._N = directory.N = static_cast<size_t>(rawN);
	directory.fields = new tiff_field[directory.N];
	for (n = 0; n < directory.N; ++n) { is >> directory.fields[n]; }
	is >> rawoffset;
	directory.offset = static_cast<size_t>(rawoffset);

	return is;
};

inline std::istream & operator>>(std::istream &is, tiff_t &tiff)
{
	size_t offset;
	tiff_directory *directory;

	is >> tiff.header;
	offset = tiff.header.offset;
	if(!offset) { tiff.directory = nullptr; return is; }

	is.seekg(offset);
	tiff.directory = new tiff_directory();
	directory = tiff.directory;
	is >> *directory;

	while(directory->offset)
	{	
		std::cout << "    offset: " << offset << std::endl;
		is.seekg(directory->offset);
		offset = directory->offset;
		directory->_next = new tiff_directory();
		directory = directory->_next;
		is >> *directory;
	}

	return is;
};

/* debug functions */

void print(const tiff_t &tiff)
{
	tiff_field field;
	tiff_directory *next;
	size_t n;

	next = tiff.directory;
	std::cout << "tiff_t {" << std::endl;
	std::cout << " header: tiff_header {" << std::endl;
	std::cout << "  II: " << SBOOLEAN(tiff.header.II) << std::endl;
	std::cout << "  MM: " << SBOOLEAN(tiff.header.MM) << std::endl;
	std::cout << "  TIFF: " << SBOOLEAN(tiff.header.TIFF) << std::endl;
	std::cout << "  offset: " << tiff.header.offset << std::endl;
	std::cout << " }" << std::endl;
	std::cout << " directorys: [";
	while(next)
	{
		std::cout << std::endl;
		std::cout << "  tiff_directory {" << std::endl;
		std::cout << "   N: " << next->N << std::endl;
		std::cout << "   _N: " << next->_N << std::endl;
		std::cout << "   offset: " << next->offset << std::endl;
		std::cout << "   fields: [";
		for (size_t n = 0; n < next->N; ++n)
		{
			field = next->fields[n];
			std::cout << std::endl;
			std::cout << "    tiff_field {" << std::endl;
			std::cout << "     tag: " << field.tag << std::endl;
			std::cout << "     type: " << field.type << std::endl;
			std::cout << "     N: " << field.N << std::endl;
			std::cout << "     _N: " << field._N << std::endl;
			std::cout << "     size: " << field.size << std::endl;	
			std::cout << "     offset: " << field.offset << std::endl;
			std::cout << "     pvalue: " << field.pvalue << std::endl;
			if(field.pvalue)
			{
				char *d = static_cast<char *>(field.pvalue);
				size_t K = min(field.N * sizeof(char), (size_t) 64) - 1;
				std::cout << "     (*value) [ ";
				for(size_t k = 0; k < K; ++k) { std::cout << d[k]; };
				std::cout << " ]" << std::endl;
			}
			std::cout << "    }," << std::endl;
		}
		std::cout << (next->N ? "   ]" : "]") << std::endl;
		std::cout << "  }," << std::endl;
		next = next->_next;
	}
	std::cout << (tiff.N ? " ]" : "]") << std::endl;
	std::cout << "}" << std::endl;
};

#endif