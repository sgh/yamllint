
#include <yaml-cpp/yaml.h>

#include <unistd.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>


using namespace std;

void print_usage() {
	cout << "Usage: yamlint [options] [filename]               " << endl;
	cout << "  -q   - Quiet operation. Do not output processed yaml." << endl;
	cout << "  -v   - Verbose operation. Ouput status information." << endl;
}

int main(int argc, char* const argv[]) {
	bool quiet = false;
	bool verbose = false;
	int opt;
	fstream fin;
	istream* inputstream = &cin;

	while ((opt = getopt(argc, argv, "qv")) != -1) {
		switch (opt) {
			case 'q':
				quiet = true;
				break;
			case 'v':
				verbose = true;
				break;
			default:
				print_usage();
				return EXIT_FAILURE;
		}
	}

	if (optind < argc) {
		const char* filename = argv[optind];
		fin.open(filename, fstream::in);
		if (!fin.is_open()) {
			cerr << "Unable to open " << filename << " for reading." << endl;
			return EXIT_FAILURE;
		}
		inputstream = &fin;
		if (verbose)
			cerr << "Reading from file: " << filename << endl;
	} else {
		if (verbose)
			cerr << "Reading from stdin" << endl;
	}

	try {
		YAML::Node config = YAML::Load(*inputstream);
		if (!quiet) {
			cout << config;
			cout << endl;
		}
	} catch (YAML::ParserException e) {
		cerr << "Error parsing file at line at position " << e.mark.pos << endl;
		cerr << e.mark.line << ":" << e.mark.column << " " << e.msg << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}