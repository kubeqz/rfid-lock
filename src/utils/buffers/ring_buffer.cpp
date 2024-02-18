
#include "ring_buffer.h"

namespace mmod { namespace common {

RingBuffer::RingBuffer(uint8_t * buffer, uint16_t bufferSize)
  : m_BufferLength(bufferSize)
  , m_bufferData(buffer)
  , m_writeIndex(0)
  , m_readIndex(0)
  , m_filled(0)
{
}


bool RingBuffer::write(uint8_t byte)
{
    if (m_filled < m_BufferLength) {
        m_bufferData[m_writeIndex] = byte;
        ++m_writeIndex;
        ++m_filled;

        if (m_writeIndex >= m_BufferLength) {
            m_writeIndex = 0;
        }

        return true;
    }

    return false;
}


bool RingBuffer::read(uint8_t &byte)
{
    if (m_filled) {
        byte = m_bufferData[m_readIndex];
        ++m_readIndex;
        --m_filled;

        if (m_readIndex >= m_BufferLength) {
            m_readIndex = 0;
        }

        return true;
    }

    return false;
}


uint16_t RingBuffer::getAvailable() const
{
    return m_filled;
}


void RingBuffer::reset()
{
    m_filled = 0;
    m_readIndex = 0;
    m_writeIndex = 0;
}


}} /* namespace common */
