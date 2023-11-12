#include "hook.h"


namespace HorseAnimationFixes
{

    void HorseRiderHook::Update(RE::Actor *actor, float a_delta)
    {
        if (actor == nullptr) return;
        if (RE::ActorPtr mountPtr = nullptr; actor->GetMount(mountPtr)) 
        {

            UpdateLeaning(actor, mountPtr.get(), a_delta); 

        }
        _Update(actor, a_delta);
    }
    void HorseRiderHook::UpdatePlayer(RE::Actor *actor, float a_delta)
    {
        if (actor == nullptr) return;
        if (RE::ActorPtr mountPtr = nullptr; actor->GetMount(mountPtr)) 
        {
            // if (const auto keywordForm = mountPtr->As<RE::BGSKeywordForm>()) {
			// 	if (HasHorseKeyword(keywordForm)) 
            //     {
            UpdateLeaning(actor, mountPtr.get(), a_delta); 
            //     }
			// }
        }
        _UpdatePlayer(actor, a_delta);
    }
    void HorseRiderHook::UpdateLeaning(RE::Actor *a_actor, RE::Actor* a_mount, float a_delta)
    {
        if (a_mount == nullptr) return; 

        auto* controller = a_mount->GetCharController();
        if (controller == nullptr) return;
        RE::NiPoint3 refVector{ 0.0f, 0.0f, 0.0f };

        auto point3 = MathUtil::GetNiPoint3(controller->surfaceInfo.surfaceNormal);

        MathUtil::Angle::AngleZX angle; 
        
        MathUtil::Angle::GetAngle(point3,refVector,  angle);
        // angle.x = std::atan2(point3.y, point3.z);
        
        float desiredPitch = angle.x*40.0f;
        if (lastAngle != angle.x&& !logLock)
        {
            lastAngle = angle.x;
            SKSE::log::info("Angle {}", MathUtil::Angle::RadianToDegree(lastAngle));
            std::jthread lthread(LogDelayed); 
            lthread.detach();
        }

        pitch = MathUtil::Interp::InterpTo(pitch, desiredPitch, a_delta, 10.0f); 
	    a_actor->SetGraphVariableFloat("HSFX_Pitch", pitch);
    }
}