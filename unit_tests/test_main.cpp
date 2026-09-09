#include "external/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

int main() {

	std::ifstream f("./math_test.json");

	if (!f.is_open()) {
		std::cerr << "Failed to oepn the json file\n";
		return 1;
	}

    std::stringstream buffer;
    buffer << f.rdbuf();

    std::string contents = buffer.str();

    std::cout << "File contents:\n";
    std::cout << contents << '\n';

    if (contents.empty()) {
        std::cerr << "ERROR: File is empty!\n";
        return 1;
    }

    json data = json::parse(contents);

    for (const auto& test : data) {
        std::cout << test["name"] << '\n';
    }

    return 0;

	return 0;
}
