#include <iostream>

#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>


int main(int argc, char *argv[]) {

  boost::program_options::options_description description("HelloBoost");
  description.add_options()
    ("hello", "hello, world.");

  boost::program_options::variables_map map;
  try {
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(description).run(), map);
    boost::program_options::notify(map);
  } catch (std::exception &exception) {
    std::cerr << exception.what() << std::endl;
  }

  if (map.count("hello")) {
    std::cout << "hello, world" << std::endl;
  } else {
    std::cout << description << std::endl;
  }

  return 0;
}
