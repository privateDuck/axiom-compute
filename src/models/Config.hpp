#pragma once

#include <string>
#include <variant>
#include <vector>
#include <unordered_map>

enum class ParameterType {
	Double, Option, String
};

enum class ModelObjective {
	Regression,
	Classification
};

enum class ModelType {
	Linear,
	SVM,
	KNN,
	DT,
	GB,
	FFNN
};

using ParameterValue = std::variant<double, uint64_t, std::string, bool>;

struct Parameter {
	std::string name;
	ParameterType type;
	ParameterValue value;
};

struct ModelConfig {
	std::string model_name;
	ModelObjective objective;
	ModelType model_type;
	std::unordered_map<std::string, ParameterValue> parameters;

	template<typename T>
	const T getParam(const std::string& param_name, T default_val) const {
		auto it = parameters.find(param_name);
		if (it == parameters.end()) {
			return default_val;
		}
		
		try {
			return std::get<T>(params.at(key));
		}
		catch (const std::bad_variant_access&) {
			return default_val;
		}
	}
};