#include "provider_factory.hpp"
#include "zondax_provider.hpp"
#include "obsidian_provider.hpp"
#include "provider_utils.hpp"

namespace wallet {
namespace ledger {

provider_factory& provider_factory::instance() {
    static provider_factory instance;
    return instance;
}

std::shared_ptr<provider> provider_factory::create_provider(const std::shared_ptr<transport>& t) {
    return get_ledger_provider(t);
}

std::shared_ptr<provider> provider_factory::get_provider(provider_type type) {
    switch (type) {
        case provider_type::obsidian:
            return std::static_pointer_cast<provider>(obsidian_provider::instance());
        case provider_type::zondax:
            return std::static_pointer_cast<provider>(zondax_provider::instance());
        default:
            throw std::runtime_error("Unknown provider type");
    }
}

} // namespace ledger
} // namespace wallet