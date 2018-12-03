#pragma once
#include "Component.h"

class Material final
{
public:
	Color base_color;
	float base_transparency;
	Color edge_color;
	float edge_transparency;
	float edge_thickness;
	//std::unique_ptr<Sprite> sprite;

public:
	Material()
		: base_color(Colors::White)
		, base_transparency(0)
		, edge_color(Colors::Black)
		, edge_transparency(0) {}

public:
	Material& SetBase(Color color, float transparency = 1);
	Material& SetBorder(Color color, float transparency = 1, float thickness = 1);
};

class Renderer : public Component
{
public:
	Material material;

public:
	Renderer()
		: material(material = Material{}.SetBase(Colors::White)) {}
	virtual ~Renderer() {}

public:
	void Render() override = 0;
};

class BoxRenderer : public Renderer
{
public:
	void Render() override;
};

class CircleRenderer : public Renderer
{
public:
	void Render() override;
};

class LineRenderer : public Renderer
{
public:
	void Render() override;
};

class TextRenderer : public Component
{
public:
	std::string text;

public:
	TextRenderer(const std::string& text);

	void Render() override;
};

class FontTextRenderer : public TextRenderer
{
public:
	std::shared_ptr<FontResource> font;

public:
	FontTextRenderer(const std::shared_ptr<FontResource>& font, const std::string& text);

	void Render() override;
};
