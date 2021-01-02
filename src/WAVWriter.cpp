#include <VSynth/WAVWriter.h>

#define BUFFER_SIZE 480000

void writeUint32ToFile_LE(std::ofstream &file, uint32_t value)
{
    file.put((value & 0x000000FF) >> 0);
    file.put((value & 0x0000FF00) >> 8);
    file.put((value & 0x00FF0000) >> 16);
    file.put((value & 0xFF000000) >> 24);
}

void writeUint16ToFile_LE(std::ofstream &file, uint16_t value)
{
    file.put((value & 0x000000FF) >> 0);
    file.put((value & 0x0000FF00) >> 8);
}

namespace VSynth
{

    WAVWriter::WAVWriter()
        : mWriterThread(nullptr),
          mReadyToWrite(false),
          mEndSampling(false),
          mSampleBuffer(0),
          mSampleBufferIndex(0),
          mNumWritten(0)
    {
        // Create two large buffers
        for (int i = 0; i < 2; i++)
        {
            mAudioBuffers.push_back(std::vector<short int>(BUFFER_SIZE, 0));
        }
    }

    WAVWriter::~WAVWriter()
    {
        if (mWriterThread)
        {
            mWriterThread->join();
            delete mWriterThread;
        }
    }

    void WAVWriter::open(std::string filePath)
    {
        // Open up the WAV file
        mWAVFile.open(filePath);

        writeRIFFHeader();
        writeFormatSubChunk();
        writeDataSubChunkHeader();

        // Create WAVWriter Thread
        mWriterThread = new std::thread(
            [this]() {
                this->writerThreadFunction();
            });
    }

    void WAVWriter::close()
    {
        // Tell the thread to end
        mWriteLock.lock();
        mReadyToWrite = true;
        mEndSampling = true;
        mWriteLock.unlock();
        // mWriteCondition.notify_all();

        // Join the WAVWriter Thread and free it
        mWriterThread->join();
        delete mWriterThread;
        mWriterThread = nullptr;

        writeChunkSizes();

        // Close the WAV file
        mWAVFile.close();
    }

    void WAVWriter::writeSample(int16_t sample)
    {
        // short int le_sample = ((sample & 0x00FF) << 8) | ((sample &0xFF00) >> 8);
        mAudioBuffers[mSampleBuffer][mSampleBufferIndex++] = sample;
        mAudioBuffers[mSampleBuffer][mSampleBufferIndex++] = sample;
        if (mSampleBufferIndex >= BUFFER_SIZE)
        {
            mSampleBufferIndex = 0;
            mSampleBuffer = (mSampleBuffer + 1) % 2;
            mReadyToWrite = true;
            // mWriteCondition.notify_all();
        }
    }

    void WAVWriter::writerThreadFunction()
    {
        bool doneWriting = false;
        while (!doneWriting)
        {
            mWriteLock.lock();
            if (mReadyToWrite)
            {
                mWriteLock.unlock();
                writeSamplesToFile();
                mWriteLock.lock();
                mReadyToWrite = false;
            }
            else if (!mEndSampling)
            {
                // std::unique_lock<std::mutex> uniqueLock;
                // mWriteCondition.wait(uniqueLock);
            }

            doneWriting = mEndSampling;
            mWriteLock.unlock();
        }
    }

    void WAVWriter::writeRIFFHeader()
    {
        mWAVFile.write("RIFF", 4);
        // TODO: Write Chunk Size properly. For now I will write 36
        writeUint32ToFile_LE(mWAVFile, 36u);
        mWAVFile.write("WAVE", 4);
    }

    void WAVWriter::writeFormatSubChunk()
    {
        uint32_t samplingRate = 24000u;
        uint32_t byteRate = samplingRate * 2u * 2u;
        mWAVFile.write("fmt ", 4);
        writeUint32ToFile_LE(mWAVFile, 16u);
        writeUint16ToFile_LE(mWAVFile, 1u);
        writeUint16ToFile_LE(mWAVFile, 2u);
        writeUint32ToFile_LE(mWAVFile, samplingRate);
        writeUint32ToFile_LE(mWAVFile, byteRate);
        writeUint16ToFile_LE(mWAVFile, 4u);
        writeUint16ToFile_LE(mWAVFile, 16u);
    }
    void WAVWriter::writeDataSubChunkHeader()
    {
        mWAVFile.write("data", 4);
        // TODO: Write Data Chunk Size properly. For now I will write 0
        writeUint32ToFile_LE(mWAVFile, 0u);
    }

    void WAVWriter::writeChunkSizes()
    {
        mWAVFile.seekp(4, std::ios::beg);
        writeUint32ToFile_LE(mWAVFile, 60u + mNumWritten);
        mWAVFile.seekp(40, std::ios::beg);
        writeUint32ToFile_LE(mWAVFile, mNumWritten);
    }

    void WAVWriter::writeSamplesToFile()
    {
        // Possible ENDIAN issue. May be unsuitable for some platforms
        unsigned int writeBuffer = (mSampleBuffer + 1) % 2;
        mWAVFile.write((char *)mAudioBuffers[writeBuffer].data(), sizeof(short int) * BUFFER_SIZE);
        mNumWritten += 2 * BUFFER_SIZE;
    }

}; // namespace VSynth