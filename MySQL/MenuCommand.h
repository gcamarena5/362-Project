#pragma once
// Ethan: abstraction

#include <string>

// Ethan: OCP (Open-Closed Principle).
class MenuCommand
{
public:
	virtual ~MenuCommand() = default;

	virtual std::string label() const = 0;

	virtual void run() = 0;
};
