#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <iterator>
#include <fstream>

namespace config {
	void load(const std::string name);
	void save(const std::string name);
	void reset();
	void import_cfg();
	void export_cfg();
}