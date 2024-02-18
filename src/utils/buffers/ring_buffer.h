
#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <cstdint>

class RingBuffer
{
public:
    RingBuffer(uint8_t * buffer, uint16_t bufferSize);

    bool write(uint8_t byte);
    bool read(uint8_t &byte);
    void reset();

    uint16_t getAvailable() const;

private:
    const uint16_t m_BufferLength;
    uint8_t * const m_bufferData;
    uint16_t m_writeIndex;
    uint16_t m_readIndex;
    uint16_t m_filled;
};

#endif // RING_BUFFER_H_
