#pragma once

#include <fstream>
#include <string>

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
        WAVWriter(unsigned long int samplingRate, unsigned int channels);
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

    private:
        void writeRIFFHeader();
        void writeFormatSubChunk();
        void writeDataSubChunkHeader();
        void writeChunkSizes();

        std::ofstream mWAVFile;
        
        unsigned long int mNumWritten;
        unsigned long int mSamplingRate;
        unsigned int mNumChannels;

    };

}; // namespace VSynth