#pragma once

#include <bdn/String.h>
#include <sstream>

namespace bdn
{
    enum class Severity
    {
        Error,
        Info,
        Debug,
        None,
    };

    void log(Severity severity, const String &message) noexcept;

    /** Logs an exception as an error entry to the global logging facility.
     *  additionalInfo is a string message that can be used to add additional
     * information about how and when the error occurred.
     * */
    void logError(const std::exception &e, const String &additionalInfo) noexcept;

    /** Logs an error message to the global logging facility.*/
    void logError(const String &message) noexcept;

    /** Logs an info message to the global logging facility.*/
    void logInfo(const String &message) noexcept;

    class logstream : public std::ostringstream
    {
        static std::mutex _globalMutex;
        bool locked = false;

      public:
        logstream(bool lock = false)
        {
            locked = lock;
            if (lock)
                _globalMutex.lock();
        }
        ~logstream() override
        {
            logInfo(str());
            if (locked)
                _globalMutex.unlock();
        }
    };

    inline void logAndIgnoreException(const std::function<void()> &function, const String &errorContextMessage)
    {
        try {
            function();
        }
        catch (std::exception &e) {
            bdn::logError(e, errorContextMessage);
        }
        catch (...) {
            bdn::logError(errorContextMessage);
        }
    }
}
