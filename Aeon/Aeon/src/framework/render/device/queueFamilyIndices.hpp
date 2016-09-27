#pragma once

namespace Aeon {

	namespace framework {

		namespace render {

			namespace device {

				struct QueueFamilyIndices {
					int graphicsFamily = -1;
					int presentFamily = -1;

					bool isComplete();
				};


			}

		}

	}

}