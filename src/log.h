//
// Created by jhlod cui on 2023/1/20.
//

#ifndef FINN_SERVER_LOG_H
#define FINN_SERVER_LOG_H

#include<string>
#include<cstdint>
#include<memory>
#include<list>
#include<vector>
#include<fstream>
#include<sstream>
#include<vector>


namespace finn {
    class logEvent {
    public:
        typedef std::shared_ptr<logEvent> ptr;

        logEvent();

    private:
        const char *m_file = nullptr; // 文件名
        uint32_t m_line = 0; // 行号
        uint32_t m_elapse = 0;// 程序的毫秒数
        uint32_t m_thread_id = 0;
        uint32_t m_fiber_t = 0;// 协程id
        uint32_t m_time = 0; // 时间戳
        std::string content = "";

    };

    class LogLevel {
    public:
        enum Level {
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            FATAL = 5
        };
    };

    class LogFormatter {
    public:
        typedef std::shared_ptr<LogFormatter> ptr;
        explicit LogFormatter(std::string& pattern);
        std::string format(logEvent::ptr event);

    private:
        class FormatItem {
        public:
            typedef std::shared_ptr<FormatItem> ptr;
            virtual ~FormatItem() {};
            virtual std::string format(logEvent::ptr event) = 0;
            virtual void format(const std::ostream& os,const logEvent::ptr&  event)=0;
        };

        void init();

    private:
        std::string m_pattern;
        std::vector<FormatItem::ptr> m_items;


    };

    // 不同输出方式的日志
    class LogAppender {
    public:
        typedef std::shared_ptr<LogAppender> ptr;

        virtual ~LogAppender() {};

        virtual void log(LogLevel::Level, logEvent::ptr event) = 0;

        const LogFormatter::ptr &getFormatter() const {
            return m_formatter;
        }

        void setFormatter(const LogFormatter::ptr &formatter) {
            m_formatter = formatter;
        }

    protected:
        LogLevel::Level m_level;
        LogFormatter::ptr m_formatter;

    };

    /**
     * logger
     */
    class Logger {
    public:
        typedef std::shared_ptr<Logger> ptr;

        explicit Logger(std::string name = "root");

        void log(LogLevel::Level level, const logEvent::ptr &event);

        void debug(const logEvent::ptr &event);

        void warn(const logEvent::ptr &event);

        void info(const logEvent::ptr &event);

        void error(const logEvent::ptr &event);

        void fatal(const logEvent::ptr &event);

        void addAppender(const LogAppender::ptr &appender);

        void removeAppender(const LogAppender::ptr &appender);

        [[nodiscard]] LogLevel::Level getLevel() const { return m_level; };

        void setLevel(LogLevel::Level level) { m_level = level; };

    private:
        std::string m_name; // 日志名称
        LogLevel::Level m_level;
        std::list<LogAppender::ptr> m_appender; // appender 集合 代表输出目的地的列表

    };

    class StdoutLogAppender : public LogAppender {
        typedef std::shared_ptr<StdoutLogAppender> ptr;

        void log(LogLevel::Level level, logEvent::ptr event) override;

    };

    class FileLogAppender : public LogAppender {
        typedef std::shared_ptr<FileLogAppender> ptr;

        explicit FileLogAppender(const std::string &file_name);

        void log(LogLevel::Level level, logEvent::ptr event) override;

        bool reopen();

    private:
        std::string m_file_name;
        std::ofstream m_file_stream;
    };
}

#endif //FINN_SERVER_LOG_H
