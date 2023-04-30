#include <stddef.h> // for offsetf()

/*---------------------------------------------------------------------------*/
// Constants
/*---------------------------------------------------------------------------*/
#define ENTRY(s, v) { sizeof(((s*)0)->v), offsetof(s, v) }
#define ENTRYEND 	{0, 0}

// Error codes
enum
{
    NO_PAYLOAD_STRUCTURE = -1,
    NO_INPUT_BUFFER = -2,
    NO_ROOM_IN_INPUT_BUFFER = -3,
    NO_OUTPUT_BUFFER = -4,
    NO_ROOM_IN_OUTPUT_BUFFER = -5
};


/*---------------------------------------------------------------------------*/
// Typedefs
/*---------------------------------------------------------------------------*/
typedef struct
{
    size_t size;   // size of structure element
    size_t offset; // offset from start of structure to that element
} ElementOffsetStruct;


/*---------------------------------------------------------------------------*/
// Prototypes
/*---------------------------------------------------------------------------*/
int StructureToBuffer (void *bufferPtr, unsigned int bufferSize,
					   void *structurePtr,
					   ElementOffsetStruct *elementOffsetTablePtr);

int BufferToStructure (void *bufferPtr, unsigned int bufferSize,
 					   void *structurePtr,
 					   ElementOffsetStruct *elementOffsetTablePtr);
 					   
// End of StructureToBuffer.h
