/*
  SparkFun SBF in SPARTN test example sketch

  The mosaic-X5 can output raw L-Band (LBandBeam1) data, interspersed with SBF messages

  This example demonstrates how to use two parsers to extract the SBF from the L-Band stream

  License: MIT. Please see LICENSE.md for more details
*/

#include <SparkFun_Extensible_Message_Parser.h> //http://librarymanager/All#SparkFun_Extensible_Message_Parser

//----------------------------------------
// Constants
//----------------------------------------

// Build the table listing all of the parsers
SEMP_PARSE_ROUTINE const parserTable1[] =
{
    sempSbfPreamble
};
const int parserCount1 = sizeof(parserTable1) / sizeof(parserTable1[0]);

const char * const parser1Names[] =
{
    "SBF parser"
};
const int parser1NameCount = sizeof(parser1Names) / sizeof(parser1Names[0]);

SEMP_PARSE_ROUTINE const parserTable2[] =
{
    sempSpartnPreamble
};
const int parserCount2 = sizeof(parserTable2) / sizeof(parserTable2[0]);

const char * const parser2Names[] =
{
    "SPARTN parser"
};
const int parser2NameCount = sizeof(parser2Names) / sizeof(parser2Names[0]);

// Provide some valid L-Band SPARTN data, interspersed with valid SBF messages
const uint8_t rawDataStream[] =
{
    // Invalid data - must skip over
    0, 1, 2, 3, 4, 5, 6, 7,                         //     0

    // SPARTN HPAC 0 - first ~half
    0x73, 0x03, 0x12, 0x6C, 0x08, 0xBF, 0x33, 0xD0, 0xF0, 0x6C, 0x2E, 0x88, 0xFA, 0xE5, 0x9B, 0x61,
    0x1B, 0x55, 0x79, 0x31, 0x7C, 0x12, 0x89, 0xE6, 0xE6, 0x91, 0x39, 0xA4, 0x65, 0x70, 0xC4, 0xB7,
    0xDD, 0x01, 0xE0, 0x64, 0xFE, 0x15, 0xED, 0x9C, 0x0C, 0x3B, 0xC0, 0xBE, 0xA9, 0x1A, 0xF6, 0xB6,
    0x72, 0xC5, 0x01, 0xDF, 0x17, 0xC2, 0xF6, 0x1B, 0xDD, 0x7B, 0x65, 0x8D, 0xD6, 0xB0, 0xCF, 0x03,
    0x04, 0xB3, 0x14, 0x46, 0xC0, 0x0B, 0x71, 0x93, 0xDC, 0x22, 0xCF, 0x3D, 0x6B, 0x98, 0xB9, 0xD0,
    0x26, 0x9C, 0xA4, 0xEC, 0xE7, 0xBD, 0x54, 0x47, 0x85, 0x46, 0x78, 0x0F, 0xDA, 0x73, 0x8B, 0xBB,
    0xD5, 0xEA, 0x7F, 0xE4, 0x55, 0xEE, 0x4C, 0x71, 0xA7, 0x77, 0x93, 0x89, 0x31, 0xE1, 0x64, 0x44,
    0xA6, 0xBB, 0xB3, 0xF9, 0x1E, 0x5A, 0xF0, 0xE9, 0xEC, 0xD5, 0x08, 0x6C, 0x59, 0x0D, 0x8C, 0xF6,
    0x95, 0x8B, 0x1B, 0x12, 0x3D, 0x52, 0x88, 0xA8, 0xD0, 0x4E, 0x20, 0x5F, 0x88, 0x31, 0x64, 0xD2,
    0xDE, 0xDE, 0x97, 0x15, 0xFD, 0x5A, 0x35, 0xF0, 0xC0, 0xBC, 0x28, 0x14, 0xE2, 0x90, 0x40, 0x27,
    0x17, 0xFC, 0x3C, 0x5E, 0xFD, 0x52, 0xA8, 0xF2, 0xBB, 0x9E, 0x0B, 0x9E, 0x96, 0x63, 0xB9, 0x75,
    0x47, 0xC7, 0xDC, 0x95, 0xF0, 0xEB, 0x5B, 0x91, 0x66, 0xAA, 0xCB, 0x67, 0xAF, 0x86, 0xCC, 0x29,
    0xC4, 0x8A, 0xB3, 0xE2, 0x2F, 0xF9, 0xAA, 0xC8, 0x35, 0x21, 0xD3, 0x9E, 0x93, 0x5B, 0x6D, 0xB6,
    0x41, 0xD9, 0xDD, 0x12, 0x38, 0x5C, 0xA7, 0x8B, 0xDE, 0x9A, 0xCC, 0x56, 0x0F, 0xBE, 0x7D, 0x5D,
    0x22, 0xA1, 0x11, 0x52, 0x83, 0x1A, 0xD8, 0xFD, 0xEF, 0x92, 0xFB, 0x04, 0x2F, 0xF1, 0x28, 0x59,
    0xE5, 0x66, 0x40, 0x51, 0xF1, 0x7F, 0xE6, 0x21, 0x38, 0x21, 0x2D, 0x51, 0x80, 0xF6, 0x53, 0x99,
    0x46, 0x76, 0xAD, 0x69, 0xC1, 0xE1, 0xF7, 0x7B, 0xF0, 0x0F, 0xDD, 0xAC, 0xC4, 0x22, 0x15, 0x1D,


    // SBF Block 4007 (PVTGeodetic)
    0x24, 0x40, 0xC4, 0x86, 0xA7, 0x4F, 0x60, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x20, 0x5F, 0xA0, 0x12, 0xC2, 0x00, 0x00, 0x00, 0x20, 0x5F, 0xA0, 0x12, 0xC2,
    0x00, 0x00, 0x00, 0x20, 0x5F, 0xA0, 0x12, 0xC2, 0xF9, 0x02, 0x95, 0xD0, 0xF9, 0x02, 0x95, 0xD0,
    0xF9, 0x02, 0x95, 0xD0, 0xF9, 0x02, 0x95, 0xD0, 0xF9, 0x02, 0x95, 0xD0, 0x00, 0x00, 0x00, 0x20,
    0x5F, 0xA0, 0x12, 0xC2, 0xF9, 0x02, 0x95, 0xD0, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,


    // SPARTN HPAC 0 - second ~half
    0x2A, 0x4D, 0x6C, 0xA3, 0x17, 0xE3, 0x7B, 0x99, 0xF1, 0xC8, 0xCB, 0xC0, 0x4B, 0x75, 0x1E, 0xE4,
    0x5B, 0x14, 0x90, 0x13, 0xC7, 0x19, 0x11, 0xFA, 0xDD, 0x57, 0x1A, 0xCF, 0x63, 0x02, 0x13, 0x45,
    0x83, 0x72, 0xA4, 0x56, 0x40, 0xD8, 0xD7, 0xAC, 0x7A, 0xA4, 0x83, 0xD9, 0xA9, 0x2B, 0x42, 0x77,
    0x12, 0xCF, 0xFB, 0xFA, 0xBD, 0x3E, 0x4D, 0xFA, 0x3C, 0x79, 0xC1, 0xD5, 0xE8, 0x73, 0x09, 0x9C,
    0xB4, 0x36, 0x7C, 0xCC, 0x46, 0x5B, 0x4D, 0x8D, 0xC5, 0xF1, 0xAA, 0xEB, 0x2B, 0x1E, 0xCF, 0xB1,
    0xE5, 0x74, 0xE3, 0x75, 0xD4, 0x77, 0x8F, 0x6A, 0x1B, 0xE8, 0x5D, 0x56, 0xEB, 0xB6, 0xE9, 0x95,
    0x88, 0x13, 0x97, 0xA2, 0x19, 0x7B, 0xE3, 0x2B, 0xEA, 0x17, 0x01, 0x7E, 0xCB, 0x81, 0x81, 0x21,
    0x95, 0xD1, 0x0E, 0x55, 0x3D, 0xA2, 0xC1, 0x75, 0xAF, 0x03, 0x4B, 0x28, 0x10, 0x47, 0x20, 0x58,
    0xA4, 0x9F, 0x95, 0x05, 0x5F, 0x51, 0x3A, 0x39, 0x94, 0xAA, 0xD7, 0xBF, 0x88, 0x61, 0xCF, 0x7B,
    0x99, 0x38, 0x6A, 0xBD, 0xA8, 0xEA, 0xE0, 0x2A, 0xBC, 0x04, 0x84, 0xF2, 0xC1, 0xD2, 0xB8, 0x86,
    0xC3, 0x07, 0x1C, 0x3B, 0x42, 0x49, 0xDC, 0xC3, 0x65, 0x29, 0x81, 0x8C, 0x17, 0x7A, 0xD0, 0x92,
    0x47, 0x16, 0xB7, 0x53, 0xB9, 0x67, 0x98, 0x57, 0x9A, 0xCD, 0x15, 0x98, 0x27, 0x52, 0x0D, 0x4F,
    0x4B, 0x49, 0xBA, 0x74, 0xE0, 0x4D, 0x37, 0x8B, 0x23, 0xB3, 0x69, 0x2B, 0xA4, 0x73, 0x68, 0x9B,
    0xA9, 0xEC, 0x71, 0xCF, 0x13, 0x17, 0x63, 0xC9, 0x49, 0xD9, 0x5A, 0xAC, 0x22, 0xDC, 0x5F, 0xD2,
    0x43, 0xC0, 0x0A, 0x4F, 0xF8, 0xD6, 0x18, 0x34, 0x4F, 0x3D, 0xF4, 0xC1, 0x84, 0x97, 0xE5, 0x68,
    0xBB, 0x44, 0x00, 0xEF, 0xB0, 0x10, 0x75, 0xA0, 0xFF, 0xE6, 0x3E, 0x83, 0x53, 0x58, 0x56, 0x5E,
    0x56, 0x60, 0xB0, 0xFE, 0x18, 0x94, 0x40, 0xB3, 0xC1, 0x6E, 0x5D, 0x5D, 0x90, 0xD7, 0x72, 0x46,
    0x58, 0x95, 0x5C, 0x69, 0x1C, 0x64, 0x1A, 0xA6, 0x5C, 0xF3, 0xCD, 0x32, 0xFA, 0x00, 0xCE, 0xD7,
    0x71, 0x5E, 0x8D,
    
};

// Number of bytes in the rawDataStream
#define RAW_DATA_BYTES      (sizeof(rawDataStream) / sizeof(rawDataStream[0]))

// Account for the largest SBF messages
#define BUFFER_LENGTH   2048

//----------------------------------------
// Locals
//----------------------------------------

uint32_t dataOffset1;
SEMP_PARSE_STATE *parse1;
uint32_t dataOffset2;
SEMP_PARSE_STATE *parse2;

//----------------------------------------
// Test routine
//----------------------------------------

// Initialize the system
void setup()
{
    delay(1000);

    Serial.begin(115200);
    Serial.println();
    Serial.println("SBF_in_SPARTN_Test example sketch");
    Serial.println();

    // Initialize the parsers
    parse1 = sempBeginParser(parserTable1, parserCount1,
                            parser1Names, parser1NameCount,
                            0, BUFFER_LENGTH, processSbfMessage, "SBF_Test");
    if (!parse1)
        reportFatalError("Failed to initialize parser 1");

    parse2 = sempBeginParser(parserTable2, parserCount2,
                            parser2Names, parser2NameCount,
                            0, BUFFER_LENGTH, processSpartnMessage, "SPARTN_Test");
    if (!parse2)
        reportFatalError("Failed to initialize parser 2");

    // Obtain a raw data stream from somewhere
    Serial.printf("Raw data stream: %d bytes\r\n", RAW_DATA_BYTES);

    // The raw data stream is passed to the SBF parser one byte at a time
    sempEnableDebugOutput(parse1);

    // Any data which is not SBF is passed to the SPARTN parser
    sempEnableDebugOutput(parse2);

    for (dataOffset1 = 0; dataOffset1 < RAW_DATA_BYTES; dataOffset1++)
    {
        // Update the SBF parser state based on the incoming byte
        sempParseNextByte(parse1, rawDataStream[dataOffset1]);

        // If the data is not SBF, the state will return to sempFirstByte
        if (parse1->state == sempFirstByte)
        {
            // Data is not SBF, so pass it to the SPARTN parser
            for (dataOffset2 = 0; dataOffset2 < parse1->length; dataOffset2++)
            {
                // Update the SPARTN parser state based on the non-SBF byte
                sempParseNextByte(parse2, parse1->buffer[dataOffset2]);
            }
        }
    }

    // Done parsing the data
    sempStopParser(&parse1);
    sempStopParser(&parse2);
}

// Main loop processing after system is initialized
void loop()
{
    // Nothing to do here...
}

// Call back from within parser, for end of message
// Process a complete message incoming from parser
void processSbfMessage(SEMP_PARSE_STATE *parse, uint16_t type)
{
    SEMP_SCRATCH_PAD *scratchPad = (SEMP_SCRATCH_PAD *)parse->scratchPad;
    
    uint32_t offset;

    // Display the raw message
    Serial.println();
    offset = dataOffset1 + 1 - parse->length;
    Serial.printf("Valid SBF message block %d : %d bytes at 0x%08lx (%ld)\r\n",
                  scratchPad->sbf.sbfID,
                  parse->length, offset, offset);
    dumpBuffer(parse->buffer, parse->length);

    // Display Block Number
    Serial.print("SBF Block Number: ");
    Serial.println(sempSbfGetBlockNumber(parse));

    // Display the parser state
    static bool displayOnce = true;
    if (displayOnce)
    {
        displayOnce = false;
        Serial.println();
        sempPrintParserConfiguration(parse, &Serial);
    }
}

// Call back from within parser, for end of message
// Process a complete message incoming from parser
void processSpartnMessage(SEMP_PARSE_STATE *parse, uint16_t type)
{
    SEMP_SCRATCH_PAD *scratchPad = (SEMP_SCRATCH_PAD *)parse->scratchPad;
    
    static bool displayOnce = true;
    uint32_t offset;

    // Display the raw message
    Serial.println();
    offset = dataOffset2 + 1 - parse->length;
    Serial.printf("Valid SPARTN message, type %d, subtype %d : %d bytes at 0x%08lx (%ld)\r\n",
                  scratchPad->spartn.messageType,
                  scratchPad->spartn.messageSubtype,
                  parse->length, offset, offset);
    dumpBuffer(parse->buffer, parse->length);

    // Display the parser state
    if (displayOnce)
    {
        displayOnce = false;
        Serial.println();
        sempPrintParserConfiguration(parse, &Serial);
    }
}

// Display the contents of a buffer
void dumpBuffer(const uint8_t *buffer, uint16_t length)
{
    int bytes;
    const uint8_t *end;
    int index;
    uint32_t offset;

    end = &buffer[length];
    offset = 0;
    while (buffer < end)
    {
        // Determine the number of bytes to display on the line
        bytes = end - buffer;
        if (bytes > (16 - (offset & 0xf)))
            bytes = 16 - (offset & 0xf);

        // Display the offset
        Serial.printf("0x%08lx: ", offset);

        // Skip leading bytes
        for (index = 0; index < (offset & 0xf); index++)
            Serial.printf("   ");

        // Display the data bytes
        for (index = 0; index < bytes; index++)
            Serial.printf("%02x ", buffer[index]);

        // Separate the data bytes from the ASCII
        for (; index < (16 - (offset & 0xf)); index++)
            Serial.printf("   ");
        Serial.printf(" ");

        // Skip leading bytes
        for (index = 0; index < (offset & 0xf); index++)
            Serial.printf(" ");

        // Display the ASCII values
        for (index = 0; index < bytes; index++)
            Serial.printf("%c", ((buffer[index] < ' ') || (buffer[index] >= 0x7f)) ? '.' : buffer[index]);
        Serial.printf("\r\n");

        // Set the next line of data
        buffer += bytes;
        offset += bytes;
    }
}

// Print the error message every 15 seconds
void reportFatalError(const char *errorMsg)
{
    while (1)
    {
        Serial.print("HALTED: ");
        Serial.print(errorMsg);
        Serial.println();
        sleep(15);
    }
}
