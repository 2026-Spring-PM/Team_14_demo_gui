#pragma once
#include "UIBase.hpp"

class MapUI : public UIBase {
public:
    MapUI(const GameState* s) : UIBase(s) {}

    void Render() override {
        // 배경 고정
        auto flgs = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse;
        
        ImGui::SetNextWindowSize({1280, 620});
        ImGui::SetNextWindowPos({0, 0});

        ImGui::Begin("MapArea", nullptr, flgs);

        // 밭
        renderFields();
        
        ImGui::SameLine(400); 

        // 도로
        renderDefenseArea();

        ImGui::End();
    }

private:
    void renderFields() {
        ImGui::BeginGroup();
        ImGui::Text("[ FARM AREA ]");
        
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 3; c++) {
                char buf[16];
                sprintf(buf, "Field %d-%d", r, c);
                
                if (ImGui::Button(buf, {100, 100})) {
                    // TODO: 씨앗 심기 등 밭 클릭 상호작용 연결
                }
                if (c < 2) ImGui::SameLine();
            }
        }
        ImGui::EndGroup();
    }

    void renderDefenseArea() {
        ImGui::BeginGroup();
        ImGui::Text("[ DEFENSE AREA ]");

        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 8; c++) {
                char buf[16];
                sprintf(buf, "Tile %d-%d", r, c);

                if (ImGui::Button(buf, {80, 80})) {
                    // TODO: 함정 설치 등 타일 클릭 상호작용 연결
                }
                if (c < 7) ImGui::SameLine();
            }
        }
        ImGui::EndGroup();
    }
};
