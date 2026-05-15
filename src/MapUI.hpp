#pragma once
#include "UIBase.hpp"
#include <string>
#include <utility>

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

        renderItemPreview();
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

                    if (tileType == 1 && gs->state.farm.SeedField[r][c] != nullptr) {
                        SeedType sType = gs->state.farm.SeedField[r][c]->Type;
                        sf::Texture* cropTex = nullptr;
                        
                        if (sType == SeedType::SEED1) cropTex = const_cast<sf::Texture*>(&gs->immatureRiceTexture);
                        else if (sType == SeedType::SEED2) cropTex = const_cast<sf::Texture*>(&gs->immaturePotatoTexture);
                        else if (sType == SeedType::SEED3) cropTex = const_cast<sf::Texture*>(&gs->immatureCarrotTexture);

                        if (cropTex) {
                            sf::Sprite cropSprite(*cropTex);
                            // 칸 크기에 맞춰 스케일 조절
                            cropSprite.setScale({tileWidth / cropTex->getSize().x, tileHeight / cropTex->getSize().y});
                            ImGui::Image(cropSprite);
                            ImGui::SetCursorPos(currentCursorPos);
                        }
                    } 
                    else if (tileType == 0 && gs->state.farm.TrapField[r][c] != nullptr) {
                        TrapType tType = gs->state.farm.TrapField[r][c]->Type;
                        sf::Texture* tTex = nullptr;
                        if (tType == TrapType::ANIMAL1) tTex = const_cast<sf::Texture*>(&gs->cowTrapTexture);
                        else if (tType == TrapType::ANIMAL2) tTex = const_cast<sf::Texture*>(&gs->pigTrapTexture);
                        else if (tType == TrapType::ANIMAL3) tTex = const_cast<sf::Texture*>(&gs->horseTrapTexture);

                        if (tTex) {
                            sf::Sprite tSprite(*tTex);
                            // 칸 크기에 맞춰 스케일 조절
                            tSprite.setScale({tileWidth / tTex->getSize().x, tileHeight / tTex->getSize().y});
                            ImGui::Image(tSprite);
                            ImGui::SetCursorPos(currentCursorPos);
                        }
                    }

                    if (tileType == 1 || tileType == 0) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
                        if (ImGui::Button("##tile", {tileWidth, tileHeight})) {
                            GameState* mgs = const_cast<GameState*>(gs);

                            if (tileType == 1 && mgs->selectedSeed != SeedType::NONE && mgs->state.farm.SeedField[r][c] == nullptr) {
                                SeedType heldSeed = mgs->selectedSeed;
                                mgs->targetRow = r;
                                mgs->targetCol = c;
                                mgs->wantToPlantSeed = true;

                                // TODO: 브릿지 연동 완료 시 GameData를 사용하도록 수정 필요
                                mgs->state.farm.SeedField[r][c] = new Seed("Test", 0, 0, 0, heldSeed);
                                mgs->selectedSeed = SeedType::NONE;
                            } 
                            else if (tileType == 0 && mgs->selectedTrap != TrapType::NONE && mgs->state.farm.TrapField[r][c] == nullptr) {
                                TrapType heldTrap = mgs->selectedTrap;
                                mgs->targetRow = r;
                                mgs->targetCol = c;
                                mgs->wantToInstallTrap = true;

                                // TODO: 브릿지 연동 완료 시 GameData를 사용하도록 수정 필요
                                mgs->state.farm.TrapField[r][c] = new Trap("Test", 0, 0, 0, std::make_pair(r, c), std::make_pair(0, 0), heldTrap);
                                mgs->selectedTrap = TrapType::NONE;
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

    void renderItemPreview() {
        if (gs->selectedTrap == TrapType::NONE && gs->selectedSeed == SeedType::NONE) return;

        ImVec2 mousePos = ImGui::GetMousePos();
        ImGui::SetNextWindowPos({mousePos.x - 40.0f, mousePos.y - 40.0f});
        ImGui::SetNextWindowBgAlpha(0.0f); 

        ImGuiWindowFlags previewFlags = 
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | 
            ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | 
            ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

        ImGui::Begin("ItemPreviewWindow", nullptr, previewFlags);

        sf::Texture* tex = nullptr;
        
        // 아이템 선택 시, 해당 아이템의 텍스처를 지정
        if (gs->selectedTrap != TrapType::NONE) {
            if (gs->selectedTrap == TrapType::ANIMAL1) tex = const_cast<sf::Texture*>(&gs->cowTrapTexture);
            else if (gs->selectedTrap == TrapType::ANIMAL2) tex = const_cast<sf::Texture*>(&gs->pigTrapTexture);
            else if (gs->selectedTrap == TrapType::ANIMAL3) tex = const_cast<sf::Texture*>(&gs->horseTrapTexture);
        } else if (gs->selectedSeed != SeedType::NONE) {
            if (gs->selectedSeed == SeedType::SEED1) tex = const_cast<sf::Texture*>(&gs->riceSeedTexture);
            else if (gs->selectedSeed == SeedType::SEED2) tex = const_cast<sf::Texture*>(&gs->potatoSeedTexture);
            else if (gs->selectedSeed == SeedType::SEED3) tex = const_cast<sf::Texture*>(&gs->carrotSeedTexture);
        }

        if (tex && tex->getSize().x > 0) {
            sf::Sprite previewSprite(*tex);
            float scaleX = 80.0f / tex->getSize().x;
            float scaleY = 80.0f / tex->getSize().y;
            previewSprite.setScale({scaleX, scaleY});
            previewSprite.setColor(sf::Color(255, 255, 255, 100)); 
            ImGui::Image(previewSprite);
        }

        ImGui::End();
    }
};
