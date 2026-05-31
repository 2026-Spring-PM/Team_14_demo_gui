#pragma once
#include "GameState.hpp"
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <string>

class UIBase {
protected:
    const GameState* gs; 

public:
    UIBase(const GameState* s) : gs(s) {}
    virtual ~UIBase() = default; 

    virtual void Render() = 0; 

    virtual std::string GetName() const {return "UIBase";}
};
