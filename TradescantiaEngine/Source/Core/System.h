#pragma once

#include "Core/Core.h"
#include "EventSystem/Event.h"

namespace TradescantiaEngine
{
	class System
	{
	public:

		System() = default;
		virtual ~System() = default;

		virtual void Init() {}
		virtual void Terminate() {}
		virtual void Update(float deltaTime) {}
		virtual void FixedUpdate(float deltaTime) {}
		virtual void ImGuiRender() {}
		virtual void OnEvent(Event& event) {}
	};

	class SystemStack
	{
	public:
		SystemStack() = default;
		~SystemStack();

		void PushSystem(System* System);
		void PopSystem(System* System);

		std::vector<System*>::iterator begin() { return _Systems.begin(); }
		std::vector<System*>::iterator end() { return _Systems.end(); }

	private:
		std::vector<System*> _Systems;
	};
}