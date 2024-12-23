#ifndef _TYPES_
#define _TYPES_
#define uint64_t	unsigned long long
#define uint32_t	unsigned int

#define uint16_t	unsigned short
#define uint8_t		unsigned char

#define int64_t		long long
#define int32_t		int
#define int16_t		short
#define int8_t		char

#define 	_I		volatile const	//read-only register
#define 	_O		volatile 	//write-only register
#define		_IO		volatile	//read-write register

#define		FALSE		0UL
#define		false		FALSE
#define		TRUE		1UL
#define		true		TRUE

#define		MHz		1000000UL
#define		KHz		1000UL

#define NOP()		asm inline("nop\n\t")

#endif //_TYPES_
