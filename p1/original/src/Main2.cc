#include <iostream>
#include <fstream>
#include <getopt.h>

int main (int argc, char* argv[]) {
  int c;

  int option_index = 0;
  static struct option long_options[] = {
      {"size",    required_argument, 0,  0 },
      {"border",  required_argument,  0,  0 },
      {"init",  required_argument, 0,  0 },
      {"help", no_argument,       0,  'h' },
      {0,         0,                 0,  0 }
  };

  while (true) {
    int this_option_optind = optind ? optind : 1;
    c = getopt_long_only(argc, argv, "h",
            long_options, &option_index);

    if (c == -1) {
      break;
    }

    switch (c)
    {
    case 'h':
      break;
    case 0:
      long_options[option_index].name == "size";
      break;
    
    default:
      break;
    }
  }
}