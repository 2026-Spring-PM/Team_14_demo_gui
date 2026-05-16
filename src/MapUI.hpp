#pragma once
#include "UIBase.hpp"
#include <string>
#include <utility>
#include <SFML/Window/Keyboard.hpp>

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
        // TODO: 'G'를 누르면 성장 상태가되는 코드(디버그용). 작물 시간에 따라 성장상태가 되도록 수정 필요.
        static bool debugMatureToggle = false;
        static bool prevG = false;
        bool currG = sf::Keyboard::isKeyPressed(sf::Keyboard::G);
        if (currG && !prevG) {
            debugMatureToggle = !debugMatureToggle;
        }
        prevG = currG;

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
                    
                    if (tileType == 1 && gs->state.farm.SeedField[r][c] != nullptr) {
                        SeedType sType = gs->state.farm.SeedField[r][c]->Type;
                        sf::Texture* cropTex = nullptr;
                        
                        // TODO:임시 코드. 실제 연동 시 gs->state.farm.SeedField[r][c]->IsMature() 등의 판별 필요.
                        bool isMature = debugMatureToggle; 
                        
                        if (sType == SeedType::SEED1) cropTex = isMature ? const_cast<sf::Texture*>(&gs->matureRiceTexture) : const_cast<sf::Texture*>(&gs->immatureRiceTexture);
                        else if (sType == SeedType::SEED2) cropTex = isMature ? const_cast<sf::Texture*>(&gs->maturePotatoTexture) : const_cast<sf::Texture*>(&gs->immaturePotatoTexture);
                        else if (sType == SeedType::SEED3) cropTex = isMature ? const_cast<sf::Texture*>(&gs->matureCarrotTexture) : const_cast<sf::Texture*>(&gs->immatureCarrotTexture);

                        if (cropTex) {
                            sf::Sprite cropSprite(*cropTex);
                            float cropScale = 0.6f;
                            cropSprite.setScale({(tileWidth / cropTex->getSize().x) * cropScale, (tileHeight / cropTex->getSize().y) * cropScale});
                            
                            float offsetX = tileWidth * (1.0f - cropScale) / 2.0f;
                            float offsetY = tileHeight * (1.0f - cropScale) / 2.0f;
                            
                            ImGui::SetCursorPos({currentCursorPos.x + offsetX, currentCursorPos.y + offsetY});
                            ImGui::Image(cropSprite);
                        }

                        if (!isMature) {
                            if (gs->wateringCanTexture.getSize().x > 0) {
                                sf::Sprite wcSprite(gs->wateringCanTexture);
                                float wcScale = 0.25f; 
                                wcSprite.setScale({(tileWidth / gs->wateringCanTexture.getSize().x) * wcScale, (tileHeight / gs->wateringCanTexture.getSize().y) * wcScale});
                                
                                float wcOffsetX = 5.0f; 
                                float wcOffsetY = tileHeight - (tileHeight * wcScale) - 5.0f; 
                                
                                ImGui::SetCursorPos({currentCursorPos.x + wcOffsetX, currentCursorPos.y + wcOffsetY});
                                ImGui::Image(wcSprite);
                                
                                if (ImGui::IsItemClicked()) {
                                    // TODO : 물뿌리개 아이콘 클릭 시 작물에 물을 주는 기능 구현.
                                }
                            }

                            if (gs->clockTexture.getSize().x > 0) {
                                sf::Sprite clockSprite(gs->clockTexture);
                                float clockScale = 0.25f; 
                                clockSprite.setScale({(tileWidth / gs->clockTexture.getSize().x) * clockScale, (tileHeight / gs->clockTexture.getSize().y) * clockScale});
                                
                                float clockOffsetX = tileWidth - (tileWidth * clockScale) - 5.0f; 
                                float clockOffsetY = tileHeight - (tileHeight * clockScale) - 5.0f; 
                                
                                ImGui::SetCursorPos({currentCursorPos.x + clockOffsetX, currentCursorPos.y + clockOffsetY});
                                ImGui::Image(clockSprite);
                                
                                if (ImGui::IsItemClicked()) {
                                    // TODO : 시계 아이콘 클릭 시 작물의 남은 시간이 나타나는 기능 구현.
                                }
                            }
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
                            float trapScale = 0.8f;
                            tSprite.setScale({(tileWidth / tTex->getSize().x) * trapScale, (tileHeight / tTex->getSize().y) * trapScale});
                            
                            float offsetX = tileWidth * (1.0f - trapScale) / 2.0f;
                            float offsetY = tileHeight * (1.0f - trapScale) / 2.0f;
                            
                            ImGui::SetCursorPos({currentCursorPos.x + offsetX, currentCursorPos.y + offsetY});
                            ImGui::Image(tSprite);
                        }
                    }

                    ImGui::SetCursorPos(currentCursorPos);

                    if (tileType == 1 || tileType == 0) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
                        if (ImGui::Button("##tile", {tileWidth, tileHeight})) {
                            GameState* mgs = const_cast<GameState*>(gs);

                            if (tileType == 1 && mgs->selectedSeed != SeedType::NONE && mgs->state.farm.SeedField[r][c] == nullptr) {
                                SeedType heldSeed = mgs->selectedSeed;
                                mgs->targetRow = r;
                                mgs->targetCol = c;
                                mgs->wantToPlantSeed = true;

                                // TODO : 작물 심기 임시 코드. 수정 필요.
                                mgs->state.farm.SeedField[r][c] = new Seed("Test", 0, 0, 0, heldSeed);
                                mgs->selectedSeed = SeedType::NONE;
                            } 
                            else if (tileType == 0 && mgs->selectedTrap != TrapType::NONE && mgs->state.farm.TrapField[r][c] == nullptr) {
                                TrapType heldTrap = mgs->selectedTrap;
                                mgs->targetRow = r;
                                mgs->targetCol = c;
                                mgs->wantToInstallTrap = true;

                                // TODO: 함정 설치 임시 코드. 수정 필요.
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

        sf::Texture* tex = nullptr;
        
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
            ImVec2 mousePos = ImGui::GetMousePos();
            
            const float previewWidth = 130.0f;
            const float previewHeight = 110.0f;

            ImGui::SetNextWindowPos({mousePos.x - (previewWidth / 2.0f), mousePos.y - (previewHeight / 2.0f)});
            
            ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            
            ImGuiWindowFlags previewFlags = 
                ImGuiWindowFlags_NoDecoration | 
                ImGuiWindowFlags_NoInputs | 
                ImGuiWindowFlags_AlwaysAutoResize | 
                ImGuiWindowFlags_NoSavedSettings | 
                ImGuiWindowFlags_NoFocusOnAppearing | 
                ImGuiWindowFlags_NoNav |
                ImGuiWindowFlags_Tooltip;

            ImGui::Begin("ItemPreviewWindow", nullptr, previewFlags);

            sf::Sprite previewSprite(*tex);
            float scaleX = previewWidth / tex->getSize().x;
            float scaleY = previewHeight / tex->getSize().y;
            previewSprite.setScale({scaleX, scaleY});

            previewSprite.setColor(sf::Color(255, 255, 255, 100)); 
            
            ImGui::Image(previewSprite);

            ImGui::End();
            
            ImGui::PopStyleVar(2);
            ImGui::PopStyleColor();
        }
    }
};
