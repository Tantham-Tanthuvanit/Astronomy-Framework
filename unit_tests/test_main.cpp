#include "external/json.hpp"
#include "include/core/math.h"

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

typedef std::map<std::string, nlohmann::basic_json<>> Object;

using json = nlohmann::json;

void check_multiply(Object test);
void check_divide(Object test);

int main() {

	std::unordered_map<std::string, std::function<void(Object)>> function_map = {
		{"sn:multiply",check_multiply},
		{"sn:divide"  ,check_divide},
	};

	std::ifstream f("./math_test.json");

	if (!f.is_open()) {
		std::cerr << "Failed to oepn the json file\n";
		return 1;
	}

    std::stringstream buffer;
    buffer << f.rdbuf();

    std::string contents = buffer.str();

    if (contents.empty()) {
        std::cerr << "ERROR: File is empty!\n";
        return 1;
    }

    json data = json::parse(contents);

    for (const auto& test : data) {
		check_multiply(test);
    }

	return 0;
}

void check_multiply(Object test) {
	std::cout << test["name"] << std::endl;

	sciNo a,b;

	// first input
	a.n = test["input"][0][0];
	a.exponent = test["input"][0][1];

	// second input
	b.n = test["input"][1][0];
	b.exponent = test["input"][1][1];

	std::cout << "Input 1: " << a.n << "*10^" << a.exponent << '\n';
	std::cout << "Input 2: " << b.n << "*10^" << b.exponent << '\n';

	sciNo res = multiply_sciNo(a, b);

	std::cout << "Output: " << res.n << "*10^" << res.exponent << '\n';

	if (res.n == test["output"][0] && res.exponent == test["output"][1]) {
		std::cout << "Test succesful!\n\n\n";
	} else {
		std::cout << "Test failed!\n\n\n";
	}
}
