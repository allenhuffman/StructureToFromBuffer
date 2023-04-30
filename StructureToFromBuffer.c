#include <stdint.h>
#include <string.h> // for memcpy()

#include "StructureToFromBuffer.h"

/*---------------------------------------------------------------------------*/
// Structure to Buffer
/*---------------------------------------------------------------------------*/
int StructureToBuffer (void *bufferPtr, unsigned int bufferSize,
					   void *structurePtr, ElementOffsetStruct *elementOffsetTablePtr)
{
    int dataSize = 0;
    unsigned int offset = 0;

    if ((bufferPtr == NULL) || (bufferSize == 0))
    {
        // No destination buffer.
        dataSize = NO_INPUT_BUFFER;
    }
    else if ((structurePtr == NULL) || (elementOffsetTablePtr == NULL))
    {
        // No payload structure.
        dataSize = NO_PAYLOAD_STRUCTURE;
    }
    else
    {
		offset = 0;
        for (int idx = 0; elementOffsetTablePtr[idx].size != 0; idx++)
        {
            if ((offset + elementOffsetTablePtr[idx].size) > bufferSize)
            {
                // Not enough room in output buffer.
                dataSize = NO_ROOM_IN_OUTPUT_BUFFER;
                break;
            }

			// Copy bytes from structure element to output buffer.
            memcpy(((uint8_t*)bufferPtr + offset),
                   ((uint8_t*)structurePtr + elementOffsetTablePtr[idx].offset),
				   elementOffsetTablePtr[idx].size);
            
            offset += elementOffsetTablePtr[idx].size;
        }
        
        dataSize = offset;
    }
  	
	return dataSize;
}


/*---------------------------------------------------------------------------*/
// Buffer to Structure
/*---------------------------------------------------------------------------*/
int BufferToStructure (void *bufferPtr, unsigned int bufferSize,
 					   void *structurePtr, ElementOffsetStruct *elementOffsetTablePtr)
{
    int             dataSize = 0;
    unsigned int	offset = 0;

	if ((bufferPtr == NULL) || (bufferSize == 0))
	{
		// No input buffer.
        dataSize = NO_INPUT_BUFFER;
	}
    else if ((structurePtr == NULL) || (elementOffsetTablePtr == NULL))
    {
        // No payload structure.
        dataSize = NO_PAYLOAD_STRUCTURE;
    }
	else
	{
	    offset = 0;
	    for (int idx = 0; elementOffsetTablePtr[idx].size != 0; idx++)
	    {
			if ((offset + elementOffsetTablePtr[idx].size) > bufferSize)
			{
				// Not enough room in input buffer.
                dataSize = NO_ROOM_IN_INPUT_BUFFER;
				break;
			}

			// Copy bytes from input buffer to structure element.
	        memcpy (((uint8_t*)structurePtr + elementOffsetTablePtr[idx].offset),
	                (bufferPtr + offset),
				    elementOffsetTablePtr[idx].size);
        
			offset += elementOffsetTablePtr[idx].size;
	    }
	    
	    dataSize = offset;
	}
	
	return dataSize;
}

// End of StructureToBuffer.c
