#include <VSynth/middleware/WAVWriter.h>

void writeUint16ToFile_LE(std::ofstream &file, uint16_t value);
void writeUint32ToFile_LE(std::ofstream &file, uint32_t value);

namespace VSynth
{

    namespace Middleware
    {

        WAVWriter::WAVWriter(unsigned long int samplingRate, unsigned int channels)
            : mNumWritten(0),
              mNumChannels(channels),
              mSamplingRate(samplingRate)
        {
        }

        WAVWriter::~WAVWriter() {}

        void WAVWriter::open(std::string filePath)
        {
            // Open up the WAV file
            mWAVFile.open(filePath, std::ios::out | std::ios::binary);

            writeRIFFHeader();
            writeFormatSubChunk();
            writeDataSubChunkHeader();
        }

        void WAVWriter::close()
        {
            writeChunkSizes();

            mWAVFile.close();
        }

        short WAVWriter::processSample(short sample, double time)
        {
            for (unsigned int i = 0; i < mNumChannels; i++)
            {
                mWAVFile.write((char *)&sample, sizeof(short));
                mNumWritten += sizeof(short);
            }
            return sample;
        }

        void WAVWriter::writeRIFFHeader()
        {
            mWAVFile.write("RIFF", 4);
            writeUint32ToFile_LE(mWAVFile, 0);
            mWAVFile.write("WAVE", 4);
        }

        void WAVWriter::writeFormatSubChunk()
        {
            uint32_t byteRate = mSamplingRate * mNumChannels * sizeof(short);
            mWAVFile.write("fmt ", 4);
            writeUint32ToFile_LE(mWAVFile, 16u);
            writeUint16ToFile_LE(mWAVFile, 1u);
            writeUint16ToFile_LE(mWAVFile, mNumChannels);
            writeUint32ToFile_LE(mWAVFile, mSamplingRate);
            writeUint32ToFile_LE(mWAVFile, byteRate);
            writeUint16ToFile_LE(mWAVFile, (uint16_t) mNumChannels * sizeof(short));
            writeUint16ToFile_LE(mWAVFile, sizeof(short) * 8);
        }
        void WAVWriter::writeDataSubChunkHeader()
        {
            mWAVFile.write("data", 4);
            writeUint32ToFile_LE(mWAVFile, 0u);
        }

        void WAVWriter::writeChunkSizes()
        {
            mWAVFile.seekp(4, std::ios::beg);
            writeUint32ToFile_LE(mWAVFile, 44u + mNumWritten);
            mWAVFile.seekp(40, std::ios::beg);
            writeUint32ToFile_LE(mWAVFile, mNumWritten);
        }

    }; // namespace Middleware

} // namespace VSynth

void writeUint16ToFile_LE(std::ofstream &file, uint16_t value)
{
    file.put((value & 0x000000FF) >> 0);
    file.put((value & 0x0000FF00) >> 8);
}

void writeUint32ToFile_LE(std::ofstream &file, uint32_t value)
{
    file.put((value & 0x000000FF) >> 0);
    file.put((value & 0x0000FF00) >> 8);
    file.put((value & 0x00FF0000) >> 16);
    file.put((value & 0xFF000000) >> 24);
}