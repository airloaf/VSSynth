#pragma once

namespace VSynth
{
    namespace Middleware
    {
        /**
         * @brief Middleware which reads samples prior to sending it to the speakers
         * 
         * Middleware has the ability to modify any samples prior to sending it to the speaker.
         * This can allow for the creation of filters, sample analyzers or audio file writers.
         */
        class Middleware
        {
        public:
            /**
             * @brief  Process the current sample and output the modified sample
             * @param currentSample 
             * @param time 
             * @return short 
             */
            virtual short processSample(short currentSample, double time)=0;
        };
    }; // namespace Middleware

} // namespace VSynth