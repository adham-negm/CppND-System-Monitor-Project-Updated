#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

//create constructor
Process::Process(int pid):
			  pid_(pid),
			  user_(LinuxParser::User(pid))
{};

// TODO: Return this process's ID
int Process::Pid() const{ return pid_; } //return pid_;

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const {
	float totaltime = LinuxParser::ActiveJiffies(Pid());  // In jiffies
	float uptime = LinuxParser::UpTime();                 // In seconds
	float secondsactive = uptime - (Process::UpTime() / sysconf(_SC_CLK_TCK));  // In seconds
	float cpu_usage = (totaltime / sysconf(_SC_CLK_TCK)) / secondsactive;  // In seconds
	return cpu_usage;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_) ; }//

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Pid()); }

// TODO: Return the user (name) that generated this process
string Process::User() { return user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() const{
	long int uptime_=LinuxParser::UpTime() - LinuxParser::UpTime(Pid()); //subtract process starttime from system uptime to get process uptime
	return uptime_;



}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return (CpuUtilization() > a.CpuUtilization());
}
