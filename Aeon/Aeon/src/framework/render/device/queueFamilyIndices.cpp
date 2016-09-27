#pragma once
#include "queueFamilyIndices.hpp"

namespace Aeon {

	namespace framework {

		namespace render {

			namespace device {


				bool QueueFamilyIndices::isComplete() {
					return graphicsFamily >= 0 && presentFamily >= 0;
				}

			}

		}

	}

}