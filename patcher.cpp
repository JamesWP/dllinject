#include <iostream>
#include <LIEF/PE/Parser.hpp>
#include <LIEF/PE/Builder.hpp>
#include <LIEF/PE/Binary.hpp>
#include <LIEF/version.h>
#include <cstdlib>

const std::string lief_version{HUMAN_VERSION};
using namespace std::string_literals;

int main(int argc, const char* argv[]){
    std::cout << "Hello world!" << std::endl;
    std::cout << "LIEF_VERSION: " << lief_version << std::endl;

    auto parse_arg = [&argc, &argv](const std::string& var_name) -> std::string {
        if (argc < 2) {
            std::cout << "specify " << var_name << std::endl;
            return {};
        }
        argv++;
        argc--;
        return std::string{argv[0]};
    };

    const std::string binary_name = parse_arg("name of binary to modify"s);

    if (binary_name.size() == 0) {
        return 1;
    }

    std::cout << "Opening: " << binary_name << std::endl;
    std::unique_ptr<LIEF::PE::Binary> binary_up = LIEF::PE::Parser::parse(binary_name);

    if (!static_cast<bool>(binary_up)) {
        std::cout << "unable to parse" << std::endl;
        return 2;
    }

    const std::string library_name = parse_arg("name of library to link"s);

    for (const auto& import : binary_up->imports()) {
        std::cout << "\t" << import.name() << std::endl;
    } 

    if (library_name.size() == 0) {
        return 0;
    }

    if (binary_up->has_import(library_name)) {
        std::cout << "Library already imports: " << library_name << std::endl;
    } else {
        std::cout << "Adding import to: " << library_name << std::endl;

        auto& library = binary_up->add_library(library_name);
        library.add_entry("blah"s);
    }

    const std::string output_name = parse_arg("name of output"s);

    if (output_name.size() == 0) {
        return 0;
    }

    std::cout << "Writing output to: " << output_name << std::endl;

    LIEF::PE::Builder builder{*binary_up};

    builder
        .build_imports(true)
        .patch_imports(true);

    builder.build();

    builder.write(output_name);
}