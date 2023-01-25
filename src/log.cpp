//
// Created by jhlod cui on 2023/1/20.
//

#include "log.h"
#include<iostream>
#include <utility>

namespace finn {

    Logger::Logger(std::string name) : m_name(std::move(name)) {};

    void Logger::addAppender(const LogAppender::ptr &appender) {
        this->m_appender.push_back(appender);
    }

    void Logger::removeAppender(const LogAppender::ptr &appender) {
        for (auto it = m_appender.begin(), end = m_appender.end(); it != end; it++) {
            if (*it == appender) {
                m_appender.erase(it);
                break;
            }
        }
    }

    void Logger::log(LogLevel::Level level, const logEvent::ptr &event) {
        if (level >= m_level) {
            for (auto &it: m_appender) {
                it->log(level, event);
            }
        }

    }

    void Logger::warn(const logEvent::ptr &event) {
        log(LogLevel::WARN, event);

    }

    void Logger::info(const logEvent::ptr &event) {
        log(LogLevel::INFO, event);
    }


    void Logger::fatal(const logEvent::ptr &event) {
        log(LogLevel::FATAL, event);
    }

    void Logger::error(const logEvent::ptr &event) {
        log(LogLevel::ERROR, event);
    }

    void Logger::debug(const logEvent::ptr &event) {
        log(LogLevel::DEBUG, event);
    }

    FileLogAppender::FileLogAppender(const std::string &file_name) : m_file_stream(file_name) {

    }

    void FileLogAppender::log(LogLevel::Level level, logEvent::ptr event) {
        if (level > m_level) {
            m_file_stream << m_formatter->format(event);
        }

    }

    bool FileLogAppender::reopen() {
        if (m_file_stream) {
            m_file_stream.close();
        }
        m_file_stream.open(m_file_name);
        return !!m_file_stream;
    }

    void StdoutLogAppender::log(LogLevel::Level level, logEvent::ptr event) {
        if (level >= m_level) {
            std::cout << m_formatter->format(event) << '\n';
        }
    }


    LogFormatter::LogFormatter(std::string &pattern) : m_pattern(pattern) {

    }

    std::string LogFormatter::format(logEvent::ptr event) {
        std::stringstream ss;
        for (auto &i: m_items) {
            i->format(ss, event);
        }
        return ss.str();
    }

    void LogFormatter::init() {
        std::vector<std::pair<std::string,int>> vec;
        size_t last_pos=0;
        std::string str;
        for(size_t index = 0;index<m_pattern.size();index++){
            if(m_pattern[index]!='%'){
                str.append(1,m_pattern[index]);
                continue;
            }
            std::string str;


        }
    }
}