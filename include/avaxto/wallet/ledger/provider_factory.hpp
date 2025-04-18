#pragma once

#include "provider.hpp"
#include "transport.hpp"
#include <memory>

namespace wallet {
namespace ledger {

class provider_factory {
public:
    static provider_factory& instance();
    
    std::shared_ptr<provider> create_provider(const std::shared_ptr<transport>& t);
    std::shared_ptr<provider> get_provider(provider_type type);

private:
    provider_factory() = default;
    provider_factory(const provider_factory&) = delete;
    provider_factory& operator=(const provider_factory&) = delete;
};

} // namespace ledger
} // namespace wallet