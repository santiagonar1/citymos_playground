#include "parser.hpp"

namespace playground::parser {
    auto is_header(const std::string_view line) -> bool { return line[0] == '*'; }
}// namespace playground::parser