#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "LOG.h"

int gl_log_channel = LOG_OUT_CONSOLE;
LOG_enuSeverityLevel_t gl_min_severity = info;
FILE *gl_fptr = NULL;

/**
 * @brief Select where to generate log messages
 * 
 * @param[in] outputChannel: LOG_OUT_FILE: log the messages in a file
 *                           LOG_OUT_CONSOLE: log the messages to the console
 * 
 * @return
*/
void LOG_setOutputChannel(int outputChannel)
{
    gl_log_channel = outputChannel;
}

/**
 * @brief Select the file to log to (in case the output channel is set to LOG_OUT_FILE)
 * 
 * @param[in] fileName: the name of the file to log messages to
 * 
 * @return
*/
void LOG_fileCfg(char* fileName)
{
    if(LOG_OUT_FILE == gl_log_channel)
    {
        /* Open file in append mode */
        gl_fptr = fopen(fileName, "a");
    }
}

/**
 * @brief display message on the output channel according to the set severity level
 *         (if no minimum severity level is set then all messages are displayed)
 * 
 * @param[in] severity: the message's severity level
 * @param[in] message : the message text
 * 
 * @return
*/
void LOG_write(LOG_enuSeverityLevel_t severity, const char* message, ...)
{
    if(severity >= gl_min_severity)
    {
        va_list valist;

        time_t mytime = time(NULL);
        char * time_str = ctime(&mytime);
        time_str[strlen(time_str)-1] = '\0';

        /* initialize valist */
        va_start(valist, message);
   
        if(gl_log_channel == LOG_OUT_FILE)
        {
            fprintf(gl_fptr, "[%s] ", time_str);
            vfprintf(gl_fptr, message, valist);
            fprintf(gl_fptr, "\n");
        }
        else if(gl_log_channel == LOG_OUT_CONSOLE)
        {
            printf("[%s] ", time_str);
            vprintf(message, valist);
            printf("\n");
        }

        /* clean memory reserved for valist */
        va_end(valist);
    }
    else
    {
        /* neglect the message */
    }
}

/**
 * @brief Select the minimum severity level to be logged to the output channel
 * 
 * @param[in] severity: the minimum severity level
 * 
 * @return
*/
void LOG_setSeverity(LOG_enuSeverityLevel_t severity)
{
    if((unsigned int)severity <= error)
    {
        gl_min_severity = severity;
    }
    else
    {

    }
}