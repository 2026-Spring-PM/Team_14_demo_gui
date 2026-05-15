#pragma once
#include "UIBase.hpp"
#include <string>

class MapUI : public UIBase {
public:
    MapUI(const GameState* s) : UIBase(s) {}

    void Render() override {
        auto flgs = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse;
        
        ImGui::SetNextWindowSize({1280, 620});
        ImGui::SetNextWindowPos({0, 0});

        bool isNight = (gs->state.farm.Hour >= 18 || gs->state.farm.Hour < 6);
        ImVec4 bgCol = isNight ? ImVec4(0.15f, 0.15f, 0.22f, 1.0f) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        
        ImGui::PushStyleColor(ImGuiCol_WindowBg, bgCol);
        ImGui::Begin("MapArea", nullptr, flgs);

        renderIntegratedMap();

        ImGui::End();
        ImGui::PopStyleColor();
    }

private:
    void renderIntegratedMap() {
        int layout[5][9] = {
            {1, 1, 1, 0, 0, 0, 0, 0, 0}, 
            {1, 1, 1, 0, 0, 0, 0, 0, 0}, 
            {7, 7, 7, 2, 2, 2, 2, 2, 2}, 
            {1, 1, 1, 0, 0, 0, 0, 0, 0}, 
            {1, 1, 1, 0, 0, 0, 0, 0, 0}  
        };

        const float tileWidth = 130.0f; 
        const float tileHeight = 110.0f; 

        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 9; c++) {
                int tileType = layout[r][c]; 

                if (tileType == 7) {
                    if (c == 0) { 
                        float spacingX = ImGui::GetStyle().ItemSpacing.x; 
                        float mergedWidth = (tileWidth * 3.0f) + (spacingX * 2.0f); 
                        
                        ImGui::PushID(r * 9 + c); 
                        
                        ImVec2 posBefore = ImGui::GetCursorPos(); 
                        
                        ImGui::Dummy({mergedWidth, tileHeight}); 
                        
                        ImGui::SameLine();
                        ImVec2 posNextTile = ImGui::GetCursorPos();
                        
                        sf::Sprite houseSprite;
                        houseSprite.setTexture(gs->houseTexture);
                        
                        float hOrigW = gs->houseTexture.getSize().x;
                        float hOrigH = gs->houseTexture.getSize().y;
                        float hScale = (tileHeight * 0.8f) / hOrigH; 
                        houseSprite.setScale({hScale, hScale}); 
                        
                        float hScaledH = hOrigH * hScale;
                        
                        ImGui::SetCursorPos({posBefore.x + 10.0f, posBefore.y + (tileHeight - hScaledH) * 0.5f}); 
                        ImGui::Image(houseSprite); 
                        
                        sf::Sprite doorSprite;
                        doorSprite.setTexture(gs->DoorTexture);
                        
                        float dOrigW = gs->DoorTexture.getSize().x;
                        float dOrigH = gs->DoorTexture.getSize().y;
                        float dScale = (tileHeight * 0.8f) / dOrigH; 
                        doorSprite.setScale({dScale, dScale});
                        
                        float dScaledW = dOrigW * dScale;
                        float dScaledH = dOrigH * dScale;
                        
                        ImGui::SetCursorPos({posBefore.x + mergedWidth - dScaledW - 10.0f, posBefore.y + (tileHeight - dScaledH) * 0.5f});
                        ImGui::Image(doorSprite); 
                        
                        ImGui::SetCursorPos(posNextTile); 

                        ImGui::PopID(); 
                    }
                    continue; 
                }

                ImGui::PushID(r * 9 + c);

                if (tileType == 1 || tileType == 2 || tileType == 0) {
                    ImVec2 currentCursorPos = ImGui::GetCursorPos();
                    
                    sf::Sprite tileSprite;
                    float scaleX = 1.0f;
                    float scaleY = 1.0f;
                    
                    if (tileType == 1) {
                        tileSprite.setTexture(gs->fieldTexture);
                        scaleX = tileWidth / gs->fieldTexture.getSize().x;
                        scaleY = tileHeight / gs->fieldTexture.getSize().y;
                    } else if (tileType == 2) {
                        tileSprite.setTexture(gs->roadTexture);
                        scaleX = tileWidth / gs->roadTexture.getSize().x;
                        scaleY = tileHeight / gs->roadTexture.getSize().y;
                    } else if (tileType == 0) {
                        tileSprite.setTexture(gs->outsideTexture);
                        scaleX = tileWidth / gs->outsideTexture.getSize().x;
                        scaleY = tileHeight / gs->outsideTexture.getSize().y;
                    }
                    
                    tileSprite.setScale({scaleX, scaleY});
                    ImGui::Image(tileSprite);
                    
                    ImGui::SetCursorPos(currentCursorPos);
                    
                    if (tileType == 1 || tileType == 0) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
                        if (ImGui::Button("##tile", {tileWidth, tileHeight})) {
                            if (tileType == 1) {
                                // TODO: 씨앗 심기 등 밭 클릭 상호작용 연결
                            } else if (tileType == 0) {
                                // TODO: 함정 설치 등 빈칸(Outside) 클릭 상호작용 연결
                            }
                        }
                        ImGui::PopStyleColor();
                    } else if (tileType == 2) {
                        ImGui::Dummy({tileWidth, tileHeight});
                    }
                }

                ImGui::PopID();

                if (c < 8) ImGui::SameLine();
            }
        }
    }
};
