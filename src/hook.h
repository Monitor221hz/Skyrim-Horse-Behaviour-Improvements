#pragma once 

#include "util.h"
using namespace RE;

namespace HorseAnimationFixes
{
  
    
    class HorseRiderHook
    {
    public:
        static void Install()
        {
            REL::Relocation<std::uintptr_t> CharacterVtbl{ RE::VTABLE_Character[0] };
            _Update = CharacterVtbl.write_vfunc(0xAD, Update);	

            SKSE::log::info("Hook - Update Actor Installed");

            REL::Relocation<std::uintptr_t> PlayerCharacterVtbl{ RE::VTABLE_PlayerCharacter[0] };
            _UpdatePlayer = PlayerCharacterVtbl.write_vfunc(0xAD, UpdatePlayer);

            SKSE::log::info("Hook - Update Player Installed");
        }

        static void Load()
        {
            horseKeyword = TESForm::LookupByID(0x26110)->As<BGSKeyword>();
        }

        static bool HasHorseKeyword(const RE::BGSKeywordForm* a_keywordForm) 
		{
			bool bFound = false;
			a_keywordForm->ForEachKeyword([&](const RE::BGSKeyword& a_keyword) {
				if (a_keyword.GetFormID() == horseKeyword->GetFormID()) {
					bFound = true;
					return RE::BSContainer::ForEachResult::kStop;
				}
				return RE::BSContainer::ForEachResult::kContinue;
			});

			return bFound;
		}


    private:
        static void Update(RE::Actor *a_this, float a_delta);

        static void UpdatePlayer(RE::Actor *a_this, float a_delta);
        static inline bool logLock = false;
        static void LogDelayed()
        {
            logLock = true;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            logLock = false;
        }

        static inline float lastAngle = 0.0;

        static inline REL::Relocation<decltype(Update)> _Update;
        static inline REL::Relocation<decltype(UpdatePlayer)> _UpdatePlayer;

        static void UpdateLeaning(RE::Actor *a_actor, RE::Actor* a_mount, float a_delta);

        static inline BGSKeyword* horseKeyword;

        static inline float pitch = 1.0;

        
    };
}
