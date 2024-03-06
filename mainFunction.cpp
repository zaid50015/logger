#include <fstream>
#include "./logger.h"
using namespace std;

int main()
{
    // ofstream myFile_Handler;
    // // File Open
    // myFile_Handler.open("File_1.txt");

    // // Write to the file
    // myFile_Handler << "This is a sample test File. " << endl;
    // myFile_Handler << "This is the second line of the file. " << endl;

    // // File Close
    // myFile_Handler.close();
    Logger::EnableFileOutput();
    Logger::SetPriority(DebugPriority);
    // Logger::Debug("This is a debug message %d ,%d",1,2) ;
    // Logger::Trace("This is a trace messaeg");
    // Logger::Error("This is a error message");
    Logger::Trace(__LINE__, __FILE__, "This is a trace message with line number and file name");
    Logger::Debug(__LINE__, __FILE__, "This is a debug message with line number and file name");
    Logger::Info(__LINE__, __FILE__, "This is an info message with line number and file name");
    Logger::Warn(__LINE__, __FILE__, "This is a warning message with line number and file name");
    Logger::Error(__LINE__, __FILE__, "This is an error message with line number and file name");
    Logger::Critical(__LINE__, __FILE__, "This is a critical message with line number and file name");
    Logger::CloseFileOutput();
    return 0;

}