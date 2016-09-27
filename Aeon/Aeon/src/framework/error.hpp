#pragma once
#include <stdexcept>

namespace Aeon {

	namespace framework {

		class exception : public std::runtime_error {
		public:
			exception(const std::string& what_arg);
			exception(const char* what_arg);
		};


	}

}
