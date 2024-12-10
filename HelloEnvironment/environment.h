#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
  const std::string PATHSEP = ";";
#else
  const std::string PATHSEP = ":";
#endif


std::string environment_get(const std::string& name) {
  char *buffer = nullptr;
  std::string value;
#ifdef _WIN32
  size_t num_elements = 0;
  _dupenv_s(&buffer, &num_elements, name.data());
#else
  buffer = std::getenv(name.data());
#endif
  if (buffer != nullptr) value = buffer;
#ifdef _WIN32
  free(buffer);
#endif
  return value;
}


void environment_set(const std::string& name, const std::string& value) {
#ifdef _WIN32
  _putenv_s(name.data(), value.data());
#else
  setenv(name.data(), value.data(), 1);
#endif
}


void environment_append(const std::string& name, const std::string& value) {
  environment_set(name, environment_get(name) + PATHSEP + value);
}


void environment_prepend(const std::string& name, const std::string& value) {
  environment_set(name, value + PATHSEP + environment_get(name));
}


std::vector<std::string> environment_split(const std::string& input) {
  std::vector<std::string> output;
  std::istringstream elements(input);
  std::string element;
  while (std::getline(elements, element, PATHSEP[0])) output.push_back(element);
  return output;
}


std::string environment_join(const std::vector<std::string> &input) {
  std::string output;
  for (const auto& element : input) {
    if (element != input[0]) output += PATHSEP[0];
    output += element;
  }
  return output;
}
