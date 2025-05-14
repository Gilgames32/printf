#include "jsonprobe.hpp"

#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

std::unique_ptr<ProbeList> jsonprobe::probe_presets(const std::string& preset_dir_path, const std::string& display,
                                                    const std::string& extension) {
    std::filesystem::path preset_dir(preset_dir_path);

    std::unique_ptr<ProbeList> presets = std::make_unique<ProbeList>();

    if (std::filesystem::exists(preset_dir) && std::filesystem::is_directory(preset_dir)) {
        for (const auto& entry : std::filesystem::directory_iterator(preset_dir)) {
            if (entry.is_regular_file() && entry.path().extension() == ".json") {
                json j;
                std::ifstream f(entry.path());
                j = json::parse(f);
                f.close();
                if (j.contains("name")) {
                    presets->push_back({j["name"], entry.path().string()});
                }
            }
        }
    } else {
        std::cerr << "Preset directory not found" << preset_dir_path << std::endl;
    }

    // sort by name
    std::sort(presets->begin(), presets->end());

    return presets;
}