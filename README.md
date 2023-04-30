# StructureToFromBuffer
C routines to convert structure elements to/from a buffer.
## How it works.
All you have to do is have a C structure that represents the elements in the packed data bytes:

```
typedef struct
{
    uint8_t  byte1;
    uint16_t word1;
    uint8_t  byte2;
    uint16_t word2;
} MessageStruct;
```
Then you create a table with entries representing each element in the structure in the *exact order* that they will be written or read from the packed data bytes:
```
ElementOffsetStruct msgTable[] =
{
    // These must be in the exact order they will be in the buffer.
    ENTRY(MessageStruct, byte1),    
    ENTRY(MessageStruct, word1),    
    ENTRY(MessageStruct, byte2),    
    ENTRY(MessageStruct, word2),
    ENTRYEND
};
```
## Writing a structure out to a buffer.
Using the populated structure variable and the matching structure entry table, all you have to do is:
```
MessageStruct msg;
    
msg.byte1 = 0x11;
msg.word1 = 0x2222;
msg.byte2 = 0x33;
msg.word2 = 0x4444;
    
bufferSize = StructureToBuffer (buffer, sizeof(buffer), &msg, msgTable);
```
`bufferSize` will return with the number of bytes written to the buffer, or negative if there was an error.

If successful, the buffer will contain the packed bytes of the structure:
```
0x11 0x22 0x22 0x33 0x44 0x44
```
## Loading structure elements from a buffer.
Using a buffer that contains the data bytes to parse in to the structure, all you have to do is:
```
uint8_t data[] =
{
    0x11, 0x22, 0x22, 0x33, 0x44, 0x44, 0x44, 0x44
};

MessageStruct msg;
    
bufferSize = BufferToStructure (data, sizeof(data), &msg, msgTable);
```
After that, the elements of the structure will be loaded values copies from the data bytes.

```bufferSize``` will return with the number of bytes read from the buffer, or negative is there was an error.
## Errors
The header files contains #defines for the negative values that represent the following errors:
* `NO_PAYLOAD_STRUCTURE` (-1) - NULL check for the passed-in element table. 
* `NO_INPUT_BUFFER` (-2) - NULL check for the source buffer (BufferToStructure).
* `NO_ROOM_IN_INPUT_BUFFER` (-3) - buffer too small to contain all the structure elements.
* `NO_OUTPUT_BUFFER` (-4) - NULL check for the output buffer (StructureToBuffer).
* `NO_ROOM_IN_OUTPUT_BUFFER` (-5) - not enough room for all the structure elements.
