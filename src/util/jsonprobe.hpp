#pragma once

#include <string>
#include <vector>

typedef std::vector<std::pair<std::string, std::string>> ProbeList;

namespace jsonprobe
{
    std::unique_ptr<ProbeList> probe_presets(const std::string& preset_dir_path, const std::string& display, const std::string& extension = ".json");
}
