#pragma once
#include"../windowInterface/windowInterface.h"

class RendererInterface
{
public:

	RendererInterface() = default;
	virtual ~RendererInterface() = default;

	RendererInterface(const RendererInterface&) = delete;
	RendererInterface& operator=(const RendererInterface&) = delete;
	RendererInterface(RendererInterface&&) = delete;
	RendererInterface& operator=(RendererInterface&&) = delete;

	[[nodiscard]] bool create_renderer();
};