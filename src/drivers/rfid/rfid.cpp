#include "rfid.h"
#include "drivers/rfid/mfrc522.h"

#include <cstring>

#include <msp430.h>

void Mfrc522Rfid::initialise()
{
    PCD_Init(m_uart);
}


bool Mfrc522Rfid::readCard(uint8_t * id, size_t idMaxLen)
{
    if (PICC_IsNewCardPresent() && PICC_ReadCardSerial()) {
        memcpy(id, uid.uidByte, idMaxLen < 4 ? idMaxLen : 4);
        return true;
    }

    return false;
}
