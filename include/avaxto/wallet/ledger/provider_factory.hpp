/*
 * Copyright (C) 2025 REKTBuilder 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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