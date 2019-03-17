//
// Created by morfeush22 on 06.03.19.
//

#ifndef LOAD_BALANCER_LOGGER_H
#define LOAD_BALANCER_LOGGER_H

#include <iostream>
#include <mutex>
#include <sstream>
#include <string>

#define SET_LOGGING_LEVEL logger::Logger::Instance().SetLevel
#define DEBUG logger::Logger::Instance().Print<logger::SeverityType::debug>
#define ERROR logger::Logger::Instance().Print<logger::SeverityType::error>
#define WARNING logger::Logger::Instance().Print<logger::SeverityType::warning>


namespace logger {

    enum SeverityType {
        debug = 1,
        warning,
        error
    };

    class Logger {
    public:
        /**
         * Returns singleton instance of Logger class.
         * @return Reference to singleton instance of Logger class
         */
        static auto &Instance() {
            static Logger logger;
            return logger;
        }

        Logger(const Logger &) = delete;

        Logger &operator=(const Logger &) = delete;

        Logger(Logger &&) = delete;

        Logger &operator=(Logger &&) = delete;

        /**
         * Template function that prints log string to stdout, only prints logs with higher than set severity level.
         * @tparam severity
         * @tparam Args
         * @param args
         */
        template<SeverityType severity, typename ...Args>
        void Print(Args ...args);

        /**
         * Sets severity level of Logger instance.
         * @param severity One of: debug, warning, error
         */
        void SetLevel(const std::string &severity) {
            if (severity == "debug") {
                severity_ = SeverityType::debug;
            } else if (severity == "warning") {
                severity_ = SeverityType::warning;
            } else if (severity == "error") {
                severity_ = SeverityType::error;
            }
        }

    private:
        unsigned int log_line_number_;
        std::stringstream log_stream_;
        SeverityType severity_ = SeverityType::warning;

        std::string Time() {
            std::string time_str;
            time_t raw_time;
            time(&raw_time);
            time_str = ctime(&raw_time);
            return time_str.substr(0, time_str.size() - 1);
        }

        std::string Header() {
            std::stringstream header;
            header.str("");
            header.fill('0');
            header.width(7);
            header << log_line_number_++ << " < " << Time() << " - ";
            header.fill('0');
            header.width(7);
            header << clock() << " > ~ ";
            return header.str();
        }

        void PrintImpl() {
            std::cout << (Header() + log_stream_.str()) << "\n";
            log_stream_.str("");
        }

        template<typename First, typename ...Rest>
        void PrintImpl(First parm1, Rest ...parm);

        Logger() {
            log_line_number_ = 0;
        }


    };

    template<typename First, typename ...Rest>
    void Logger::PrintImpl(First parm1, Rest ...parm) {
        log_stream_ << parm1;
        PrintImpl(parm...);
    }


    template<SeverityType severity, typename ...Args>
    void Logger::Print(Args ...args) {
        if (severity < severity_) {
            return;
        }

        switch (severity) {
            case SeverityType::debug:
                log_stream_ << "<DEBUG>   : ";
                break;
            case SeverityType::warning:
                log_stream_ << "<WARNING> : ";
                break;
            case SeverityType::error:
                log_stream_ << "<ERROR>   : ";
                break;
        };

        PrintImpl(args...);
    }

}


#endif //LOAD_BALANCER_LOGGER_H
