#pragma once

#include <iostream>

#include "../api/api.hpp"
#include "../scheduler/scheduler.hpp"

#include "../Compiler/include/Compiler.h"
#include "../Compiler/include/BytecodeBuilder.h"
#include "../Compressor/include/zstd.h"
#include "../Compressor/include/xxhash.h"

class bytecode_encoder_t : public Luau::BytecodeEncoder {
	inline std::uint8_t encodeOp(const std::uint8_t opcode) {
		return (opcode * 227);
	}
};

inline auto compress(std::string_view data) { // Changed variable names to match naming convention.
	std::string output{ "RSB1" };
	std::size_t data_size = data.size();
	std::size_t max_size = ZSTD_compressBound(data_size);
	std::vector<char> compressed(max_size);
	std::size_t compression_size = ZSTD_compress(&compressed[0], max_size, data.data(), data_size, ZSTD_maxCLevel());

	output.append(reinterpret_cast<char*>(&data_size), sizeof(data_size));
	output.append(&compressed[0], compression_size);

	std::uintptr_t first_hash = XXH32(&output[0], output.size(), 42U);
	std::uint8_t hashed_bytes[4]{};

	std::memcpy(hashed_bytes, &first_hash, sizeof(first_hash));
	for (std::size_t i = 0; i < output.size(); ++i)
		output[i] ^= (hashed_bytes[i % 4] + i * 41);

	return output;
}

namespace execution {
	inline auto execute_script(int lua_state, std::string_view script) {
		// Compile script > compress bytecode > pass compressed bytecode to luavm_load address.
		bytecode_encoder_t encoder{};
		auto bytecode = Luau::compile(script.data(), {}, {}, &encoder);
		auto compressed_bytecode{ compress(bytecode) };

		if (!bytecode[0]) {
			luavm_load(lua_state, &compressed_bytecode, "Maven", 0);
			task_defer(lua_state);
			r_decrement_top(lua_state);
		}
	}
}