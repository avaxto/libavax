#pragma once

#include "provider.hpp"
#include "zondax_provider.hpp"
#include "obsidian_provider.hpp"
#include <memory>

namespace wallet {
namespace ledger {

std::shared_ptr<provider> get_ledger_provider(const std::shared_ptr<transport>& t);
bool is_obsidian_app(const std::shared_ptr<transport>& t);

} // namespace ledger
} // namespace wallet