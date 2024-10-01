#include "Arguments.hpp"

namespace Arguments {

Arguments::Arguments()
  : input_file(""), 
	output_path(""), 
	max_iterations(0), 
	frequency(0) {}

std::string Arguments::GetInputFile() const { return input_file; }

std::string Arguments::GetOutputPath() const { return output_path; }

size_t Arguments::GetMaxIterations() const { return max_iterations; }

size_t Arguments::GetFrequency() const { return frequency; }

Arguments& Arguments::Parse(const int argc, const char** argv) {
  std::string array[argc];

  for (int i = 0; i < argc; ++i) {
    array[i] = argv[i];
  }

  Parse(argc, array);

  return *this;
}

void Arguments::Parse(const int argc, const std::string argv[]) {
  for (int idx = 1; idx < argc; ++idx) {
    if (isArg(argv[idx], "-i") || isArg(argv[idx], "--input"))
      input_file = argv[idx].substr(argv[idx].find("=") + 1);

    if (isArg(argv[idx], "-o") || isArg(argv[idx], "--output"))
      output_path = argv[idx].substr(argv[idx].find("=") + 1);

    if (isArg(argv[idx], "-m") || isArg(argv[idx], "--max-iter"))
      max_iterations = std::stoi(argv[idx].substr(argv[idx].find("=") + 1));

    if (isArg(argv[idx], "-f") || isArg(argv[idx], "--freq"))
      frequency = std::stoi(argv[idx].substr(argv[idx].find("=") + 1));
  }
}

bool Arguments::isArg(const std::string& arg, const std::string& command) {
  return arg.substr(0, command.size()) == command;
}

}  // namespace Arguments