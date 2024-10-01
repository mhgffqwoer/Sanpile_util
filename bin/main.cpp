#include "lib/Arguments/Arguments.hpp"
#include "lib/Table/Table.hpp"
#include "lib/Image/Image.hpp"


int main(const int argc, const char** argv) {
  Arguments::Arguments args = Arguments::Arguments().Parse(argc, argv);

  Sandpile::Table table = Sandpile::Table(args.GetInputFile());

  Sandpile::Image image = Sandpile::Image();

  for (int idx = 1; !table.Stable(); ++idx) {
    table.Iteration();
    if (idx == args.GetMaxIterations()) {
      break;
    }
    if (args.GetFrequency() != 0 && idx % args.GetFrequency() == 0) {
      std::string output_file = "_" + std::to_string(idx) + ".bmp";
      image.CreateImage(table, std::string(args.GetOutputPath()) + output_file);
    }
  }

  image.CreateImage(table, std::string(args.GetOutputPath()) + "result.bmp");

  return 0;
}