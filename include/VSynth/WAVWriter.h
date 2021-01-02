#pragma once

#include <condition_variable>
#include <fstream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace VSynth
{

    /**
     * @brief Outputs Audio Samples to a wave file
     * 
     * WAVWriter will take audio samples and write them into a WAV file.
     * In order to accomplish this with the best performance, it will
     * delay writing to a file until a large buffer has been filled.
     * Also a separate thread will be created to write to the file.
     */
    class WAVWriter
    {
    public:
        WAVWriter();
        ~WAVWriter();

        /**
         * @brief Opens a file for writing and spawns a writer thread
         * @param filePath 
         */
        void open(std::string filePath);

        /**
         * @brief Closes a file for writing and joins the writer thread
         */
        void close();

        /**
         * @brief Writes the sample to file
         * @param sample
         */
        void writeSample(int16_t sample);

        /**
         * @brief Function for the writer thread to initialize on.
         * 
         * You should not be calling this method.
         * It is simply for initializing the writer thread.
         */
        void writerThreadFunction();

    private:
        void writeRIFFHeader();
        void writeFormatSubChunk();
        void writeDataSubChunkHeader();
        void writeChunkSizes();
        void writeSamplesToFile();

        bool mReadyToWrite;
        bool mEndSampling;

        std::condition_variable mWriteCondition;
        std::mutex mWriteLock;

        std::thread *mWriterThread;

        std::ofstream mWAVFile;

        unsigned int mSampleBufferIndex;
        unsigned int mSampleBuffer;
        std::vector<std::vector<short int>> mAudioBuffers;

        unsigned long int mNumWritten;

    };

}; // namespace VSynth