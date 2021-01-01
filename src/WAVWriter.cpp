#include <VSynth/WAVWriter.h>
#include <iostream>

#define BUFFER_SIZE 96000

namespace VSynth
{

    WAVWriter::WAVWriter()
        : mWriterThread(nullptr),
          mReadyToWrite(false),
          mEndSampling(false),
          mSampleBuffer(0),
          mSampleBufferIndex(0)
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
        writeWAVHeader();

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

        // Close the WAV file
        mWAVFile.close();
    }

    void WAVWriter::writeSample(int sample)
    {
        mAudioBuffers[mSampleBuffer][mSampleBufferIndex++] = sample;
        if(mSampleBufferIndex >= BUFFER_SIZE){
            mSampleBufferIndex = 0;
            mSampleBuffer = (mSampleBuffer+1) % 2;
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

    void WAVWriter::writeWAVHeader()
    {
    }

    void WAVWriter::writeSamplesToFile()
    {
        std::cout << "Writing samples to file!" << std::endl;
        // Possible ENDIAN issue. May be unsuitable for some platforms
        unsigned int writeBuffer = (mSampleBuffer + 1) % 2;
        mWAVFile.write((char *) mAudioBuffers[writeBuffer].data(), 2 * BUFFER_SIZE);

    }

}; // namespace VSynth