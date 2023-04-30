/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>  // for printf()
#include <stdint.h>
#include <string.h> // for memset()

#include "StructureToFromBuffer.h"


/*---------------------------------------------------------------------------*/
// Prototypes
/*---------------------------------------------------------------------------*/
void HexDump (char *text, void *ptr, size_t size);


/*---------------------------------------------------------------------------*/
// Message structure and offset table.
/*---------------------------------------------------------------------------*/
typedef struct
{
    uint8_t  byte1;
    uint16_t word1;
    uint8_t  byte2;
    uint16_t word2;
} MessageStruct;

ElementOffsetStruct msgTable[] =
{
    // These must be in the exact order they will be in the buffer.
    ENTRY(MessageStruct, byte1),    
    ENTRY(MessageStruct, word1),    
    ENTRY(MessageStruct, byte2),    
    ENTRY(MessageStruct, word2),
    ENTRYEND
};

/*---------------------------------------------------------------------------*/
// Date/Time structure and offset table.
/*---------------------------------------------------------------------------*/
typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    char    asciiTime[26];
} DateTimeStruct;

ElementOffsetStruct dateTimeTable[] =
{
    // These must be in the exact order they will be in the buffer.
    ENTRY(DateTimeStruct, year),    
    ENTRY(DateTimeStruct, month),
    ENTRY(DateTimeStruct, day),    
    ENTRY(DateTimeStruct, hour),    
    ENTRY(DateTimeStruct, minute),    
    ENTRY(DateTimeStruct, second),    
    ENTRY(DateTimeStruct, asciiTime),    
    ENTRYEND
};


/*---------------------------------------------------------------------------*/
// Functions
/*---------------------------------------------------------------------------*/
int main()
{
    uint32_t        buffer[80] = { 0 };
    int             bufferSize = 0;
    
    MessageStruct   msg;
    
    msg.byte1 = 0x11;
    msg.word1 = 0x2222;
    msg.byte2 = 0x33;
    msg.word2 = 0x4444;
    
    HexDump ("Structure", &msg, sizeof(msg));
    bufferSize = StructureToBuffer (buffer, sizeof(buffer), &msg, msgTable);
    HexDump ("Buffer   ", &buffer, bufferSize);

    memset (buffer, 0x0, sizeof(buffer));

    DateTimeStruct dateTime = { 2022, 8, 19, 4, 20, 42, "ascii time" };
    HexDump ("Structure", &dateTime, sizeof(dateTime));
    bufferSize = StructureToBuffer (buffer, sizeof(buffer), &dateTime, dateTimeTable);
    HexDump ("Buffer   ", &buffer, bufferSize);

    typedef struct
    {
        uint8_t     u8;
        uint16_t    u16;
        uint32_t    u32;
        char        text[6];
    } TestStruct;
    
    ElementOffsetStruct testTable[] =
    {
        ENTRY(TestStruct, u8),    
        ENTRY(TestStruct, u16),    
        ENTRY(TestStruct, u32),    
        ENTRY(TestStruct, text),    
        ENTRYEND
    };

    uint8_t data[] =
    {
      0x42,                         // U8
      0x11, 0x11,                   // U16
      0x22, 0x22, 0x22, 0x22,       // U32
      'H', 'e', 'l', 'l', 'o', 0x0, // char[6]
    };
    
    HexDump ("Data     ", &data, sizeof(data));
    
    TestStruct test;
    
    BufferToStructure (data, sizeof(data), &test, testTable);
    printf ("u8=0x%02x  u16=0x%04x  u32=0x%08x  '%s'\n",
            test.u8, test.u16, test.u32, test.text);

    return 0;
}


/*---------------------------------------------------------------------------*/
// HexDump
/*---------------------------------------------------------------------------*/
void HexDump (char *text, void *ptr, size_t size)
{
    printf ("%s: ", text);

    for (unsigned int idx=0; idx<size; idx++)
    {
        printf ("%02x ", ((uint8_t*)ptr)[idx]);
    }

    printf ("\n");
}

// End of main.c
