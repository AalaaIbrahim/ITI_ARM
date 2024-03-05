#ifndef LOG_H_
#define LOG_H_

#define LOG_OUT_FILE        0
#define LOG_OUT_CONSOLE     1

typedef enum
{
    info ,
    warning ,
    error
}LOG_enuSeverityLevel_t;


/**
 * @brief Select where to generate log messages
 * 
 * @param[in] outputChannel: LOG_OUT_FILE: log the messages in a file
 *                           LOG_OUT_CONSOLE: log the messages to the console
 * 
 * @return
*/
void LOG_setOutputChannel(int outputChannel);

/**
 * @brief Select the file to log to (in case the output channel is set to LOG_OUT_FILE)
 * 
 * @param[in] fileName: the name of the file to log messages to
 * 
 * @return
*/
void LOG_fileCfg(char* fileName);

/**
 * @brief display message on the output channel according to the set severity level
 *         (if no minimum severity level is set then all messages are displayed)
 * 
 * @param[in] severity: the message's severity level
 * @param[in] message : the message text
 * 
 * @return
*/
void LOG_write(LOG_enuSeverityLevel_t severity, const char* message, ...);

/**
 * @brief Select the minimum severity level to be logged to the output channel
 * 
 * @param[in] severity: the minimum severity level
 * 
 * @return
*/
void LOG_setSeverity(LOG_enuSeverityLevel_t severity);

#endif