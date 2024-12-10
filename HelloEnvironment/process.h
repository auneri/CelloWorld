#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>
#ifdef _WIN32
#  include <direct.h>
#else
#  include <unistd.h>
#endif


FILE* process_open(const std::string& command, const std::string& mode="r") {
#ifdef _WIN32
  return _popen(command.data(), mode.data());
#else
  return popen(command.data(), mode.data());
#endif
}


void process_close(FILE* pipe) {
#ifdef _WIN32
  _pclose(pipe);
#else
  pclose(pipe);
#endif
}


void process_run(const std::string& command, const std::string& directory="") {
#ifdef _WIN32
  if (!directory.empty()) _chdir(directory.data());
#else
  if (!directory.empty()) chdir(directory.data());
#endif
  std::system(command.data());
}


std::string process_output(const std::string& command) {
  std::string output = "";
  char buffer[128];
  auto pipe = process_open(command.data());
  if (!pipe) throw std::runtime_error("popen failed!");
  try {
    while (std::fgets(buffer, sizeof buffer, pipe) != nullptr) {
      output += buffer;
    }
  } catch (...) {
    process_close(pipe);
    throw;
  }
  process_close(pipe);
  return output;
}
