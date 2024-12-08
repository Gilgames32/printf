#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

int main() {
    std::ifstream f("./presets/sample.json");
    json data = json::parse(f);
    std::cout << data.dump(4) << std::endl;
}
