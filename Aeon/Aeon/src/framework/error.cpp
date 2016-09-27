#include "error.hpp"

namespace Aeon {

	namespace framework {

		exception::exception(const std::string& what_arg) :
			runtime_error(what_arg)
		{

		}

		exception::exception(const char* what_arg) :
			runtime_error(what_arg)
		{

		}

	}

}

