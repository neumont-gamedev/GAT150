#pragma once

namespace viper {
	class IObserver {
		virtual ~IObserver() = default;

		virtual void OnNotify(const Event& event) = 0;
	};
}
