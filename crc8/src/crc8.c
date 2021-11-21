/**
 * @file crc8.cpp
 * @author Gonzalo Nahuel Vaca
 * @date 2021
 * @brief File containing the implementation of the Sarwate's algorithm.
 *
 */

#include "crc8.h"

/**
 * @brief It calculates the lookup table from the desired polynomial.
 *
 * @param[in] crc The structure with the polynomial and table's memory space.
 */
void generate_table(Sarwate *crc);

void init_sarwate(Sarwate *crc, unsigned char polynomial)
{
    crc->polynomial = polynomial;
    generate_table(crc);
}

unsigned char buildCRC8(Sarwate *crc, unsigned char *bufferPtr,
                        uint32_t bufferLenght)
{
    uint32_t i = 0;
    unsigned char crcValue = 0x00;
    uint32_t tableIndex = 0;

    for (i = 0; i < bufferLenght; ++i) {
        tableIndex = crcValue ^ bufferPtr[i];
        crcValue = crc->table[tableIndex];
    }
    return crcValue;
}

void generate_table(Sarwate *crc)
{
    const uint32_t TABLE_LENGTH = 0X100;

    unsigned char crcValue = 0x00;
    uint32_t i, j = 0;

    for (i = 0; i < TABLE_LENGTH; ++i)
    {
        crcValue = i;
        for (j = 0; j < 8; ++j)
        {
            if (crcValue & 0x80) {
                crcValue = (crcValue << 1);
                crcValue = crcValue ^ crc->polynomial;
            } else {
                crcValue = crcValue << 1;
            }
        }
        crc->table[i] = crcValue;
    }
}
