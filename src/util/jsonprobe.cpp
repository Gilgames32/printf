#include "jsonprobe.hpp"
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

ProbeList jsonprobe::probe_presets(const std::string& preset_dir_path, const std::string& display, const std::string& extension) {
    std::filesystem::path preset_dir(preset_dir_path); // TODO: make this configurable

    ProbeList presets; // TODO: shared pointer

    if (std::filesystem::exists(preset_dir) && std::filesystem::is_directory(preset_dir)) {
        for (const auto& entry : std::filesystem::directory_iterator(preset_dir)) {
            if (entry.is_regular_file() && entry.path().extension() == ".json") {
                json json_data;
                std::ifstream file(entry.path());
                json_data = json::parse(file);
                file.close();
                if (json_data.contains("name")) {
                    presets.push_back({json_data["name"], entry.path().string()});
                }
            }
        }
    }
    else {
        // TODO: handle error
    }

    // sort by name
    std::sort(presets.begin(), presets.end());

    std::cout << "Found " << presets.size() << " presets in " << preset_dir_path << std::endl;

    return presets;
}