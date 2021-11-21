/**
 * @file crc8.h
 * @author Gonzalo Nahuel Vaca
 * @date 2021
 * @brief File containing the interface of a Sarwate implementation.
 *
 */

#ifndef crc8_h
#define crc8_h

#include <stdint.h>

/**
 * @brief Structure to implement the Sarwate's Algorithm.
 *
 * This structure holds the polynomial for the CRC and it's
 * generated lookup table.
 */
typedef struct {
  unsigned char polynomial;
  unsigned char table[0x100] = { 0 };
} Sarwate;

/**
 * @brief Initialization of the Sarwate structure.
 *
 * @param[out] crc The Sarwate structure to initialize.
 * @param[in] polynomial The hexadecimal representation of the coefficients.
 * @param[in] table The memory needed to hold the lookup table. 
 */
void init_sarwate(Sarwate *crc, unsigned char polynomial);

/**
 * @brief Construction of a CRC byte from an input frame.
 *
 * @param[in] crc The Sarwate structure needed to calculate the CRC.
 * @param[in] bufferPtr The frame's payload.
 * @param[in] bufferLenght The frame's lenght.
 * @return CRC byte solved from the frame's payload.
 */
unsigned char buildCRC8(Sarwate *crc, unsigned char *bufferPtr,
                        uint32_t bufferLenght);

#endif
