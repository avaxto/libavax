#include "provider_utils.hpp"

namespace wallet {
namespace ledger {

bool is_obsidian_app(const std::shared_ptr<transport>& t) {
    try {
        // Try to get configuration from Obsidian app first
        t->get_app_configuration();
        return true;
    } catch (...) {
        return false;
    }
}

std::shared_ptr<provider> get_ledger_provider(const std::shared_ptr<transport>& t) {
    return is_obsidian_app(t) ? 
        std::static_pointer_cast<provider>(obsidian_provider::instance()) :
        std::static_pointer_cast<provider>(zondax_provider::instance());
}

} // namespace ledger
} // namespace wallet