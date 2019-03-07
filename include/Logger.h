//
// Created by morfeush22 on 06.03.19.
//

#ifndef LOAD_BALANCER_LOGGER_H
#define LOAD_BALANCER_LOGGER_H

#include <string>
#include <sstream>
#include <mutex>
#include <iostream>

#define SET_LOGGING_LEVEL logger::Logger::instance().SetLevel
#define DEBUG logger::Logger::instance().print<logger::severity_type::debug>
#define ERROR logger::Logger::instance().print<logger::severity_type::error>
#define WARNING logger::Logger::instance().print<logger::severity_type::warning>


namespace logger {

    enum severity_type
    {
        debug = 1,
        warning,
        error
    };

    class Logger {
        unsigned int log_line_number;

        std::string get_time() {
            std::string time_str;
            time_t raw_time;
            time( & raw_time );
            time_str = ctime( &raw_time );
            //without the newline character
            return time_str.substr( 0 , time_str.size() - 1 );
        }

        std::string get_logline_header() {
            std::stringstream header;
            header.str("");
            header.fill('0');
            header.width(7);
            header << log_line_number++ <<" < "<<get_time()<<" - ";
            header.fill('0');
            header.width(7);
            header <<clock()<<" > ~ ";
            return header.str();
        }
        std::stringstream log_stream;
        severity_type severity_ = severity_type::error;

        //Core printing functionality
        void print_impl() {
            std::cout << ( get_logline_header() + log_stream.str() ) << "\n";
            log_stream.str("");
        }
        template<typename First, typename...Rest>
        void print_impl(First parm1, Rest...parm);
        Logger() {
            log_line_number = 0;
        }

        public:
        static auto& instance(){
            static Logger logger;
            return logger;
        }

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger &) = delete;
        Logger(Logger &&) = delete;
        Logger & operator=(Logger &&) = delete;


        template<severity_type severity, typename...Args>
        void print(Args...args);

        void SetLevel(const std::string &severity) {
            if (severity == "debug") {
                severity_ = severity_type::debug;
            }
            else if (severity == "error") {
                severity_ = severity_type::error;
            }
            else if (severity == "warning") {
                severity_ = severity_type::warning;
            }
        }

    };

    template<typename First, typename...Rest >
    void Logger::print_impl(First parm1, Rest...parm)
    {
        log_stream<<parm1;
        print_impl(parm...);
    }


    template<severity_type severity, typename... Args>
    void Logger::print(Args... args) {
        if (severity < severity_) {
            return;
        }

        switch( severity )
        {
            case severity_type::debug:
                log_stream<<"<DEBUG>   : ";
                break;
            case severity_type::warning:
                log_stream<<"<WARNING> : ";
                break;
            case severity_type::error:
                log_stream<<"<ERROR>   : ";
                break;
        };
        print_impl( args... );
    }

}


#endif //LOAD_BALANCER_LOGGER_H
