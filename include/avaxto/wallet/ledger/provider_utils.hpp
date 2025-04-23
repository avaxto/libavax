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
#include "zondax_provider.hpp"
#include "obsidian_provider.hpp"
#include <memory>

namespace wallet {
    namespace ledger {

    std::shared_ptr<provider> get_ledger_provider(const std::shared_ptr<transport>& t);
    bool is_obsidian_app(const std::shared_ptr<transport>& t);

    } // namespace ledger
} // namespace wallet