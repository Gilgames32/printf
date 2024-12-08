#include <cups/cups.h>
#include <stdio.h>

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// For CUPS
int print_dest(void *user_data, unsigned flags, cups_dest_t *dest) {
    if (dest->instance)
        printf("%s/%s\n", dest->name, dest->instance);
    else
        puts(dest->name);

    return (1);
}

int main(void) {
    // JSON
    std::ifstream f("./presets/sample.json");
    json data = json::parse(f);
    std::cout << "JSON:" << std::endl
              << data.dump(4) << std::endl
              << std::endl;

    // CUPS: lists all available printers
    std::cout << "CUPS:" << std::endl
              << "Printers in area: " << cupsEnumDests(CUPS_DEST_FLAGS_NONE, 1000, NULL, 0, 0, print_dest, NULL) << std::endl
              << std::endl;
}
