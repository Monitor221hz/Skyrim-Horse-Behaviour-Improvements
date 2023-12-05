#include "hook.h"


namespace HorsePoseCorrection
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
        auto& options = Settings::RiderPoseOptions; 
        auto& moptions = Settings::MountPoseOptions;

        if (a_mount == nullptr) return; 

        auto* controller = a_mount->GetCharController();
        if (controller == nullptr) return;

        float quad[4];
		_mm_store_ps(quad, controller->forwardVec.quad);
		RE::NiPoint3 velocity{ -quad[0], -quad[1], 0.f };
        float speed = velocity.Length();
        RE::NiPoint3 refVector{ 0.0f, 0.0f, 1.0f };

        NiPoint3 eyeOrig, eyeDir;

        a_mount->GetEyeVector(eyeOrig, eyeDir, false);
        float maxSlopeCosine = 0.0f;
        float supportDistance = 0.0f; 
        float hardSupportDistance = 0.0f;
        auto surfaceNormal = MathUtil::GetNiPoint3(controller->surfaceInfo.surfaceNormal);
        if (auto* rigidBodyController = skyrim_cast<RE::bhkCharRigidBodyController *>(controller))
        {
            auto* rigidBody = static_cast<RE::hkpCharacterRigidBody *>(rigidBodyController->rigidBody.referencedObject.get());
            rigidBody->maxSlopeCosine = 0.700f;
            maxSlopeCosine = rigidBody->maxSlopeCosine;
            supportDistance = rigidBody->supportDistance; 
            hardSupportDistance = rigidBody->hardSupportDistance;
        }

        MathUtil::Angle::AngleZX angle;      
        MathUtil::Angle::GetAngle(refVector,surfaceNormal,  angle);


        float baseMult = 1.0f;

        if (eyeDir.y < 0) 
        {
            angle.x = -angle.x;
        }
        else if (!a_mount->IsMoving()) baseMult = 0.0f;

        // angle.x = std::atan2(eyeDir.y, eyeDir.x);

        float desiredSpinePitch = MathUtil::Angle::RadianToDegree(-angle.x)*options.spinePitchMult*baseMult;
        float desiredHeadPitch = MathUtil::Angle::RadianToDegree(-angle.x)*options.headPitchMult*baseMult;

        float desiredMountSpinePitch = MathUtil::Angle::RadianToDegree(angle.x)*moptions.spinePitchMult*baseMult;
        float desiredMountHeadPitch = MathUtil::Angle::RadianToDegree(angle.x)*moptions.headPitchMult*baseMult;

        desiredSpinePitch = MathUtil::Clamp(desiredSpinePitch, options.spinePitchMin, options.spinePitchMax);
        desiredHeadPitch = MathUtil::Clamp(desiredHeadPitch, options.headPitchMin, options.headPitchMax);

        desiredMountSpinePitch = MathUtil::Clamp(desiredMountSpinePitch, moptions.spinePitchMin, moptions.spinePitchMax);
        desiredMountHeadPitch = MathUtil::Clamp(desiredMountHeadPitch, moptions.headPitchMin, moptions.headPitchMax);

        // desiredMountFemurPitch = MathUtil::Clamp(desiredMountFemurPitch, -40.0f, 40.0f);
        // desiredMountHumerusPitch = MathUtil::Clamp(desiredMountHumerusPitch, -40.0f, 40.0f);

        #ifndef Debug
        if (lastAngle != angle.x && !logLock)
        {
            lastAngle = angle.x; 
            SKSE::log::info("Angle {}\nHead Pitch {}\nSpine Pitch {}\nEye {} {} {}", MathUtil::Angle::RadianToDegree(lastAngle), desiredHeadPitch, desiredSpinePitch, eyeDir.x, eyeDir.y, eyeDir.z);
            SKSE::log::info("Max Slope Cosine {} SupportDistance {} HardSupportDistance {}", maxSlopeCosine, supportDistance, hardSupportDistance);
            std::jthread lthread(LogDelayed); 
            lthread.detach();
        } 
        #endif
        // auto point3 = MathUtil::GetNiPoint3(controller->surfaceInfo.surfaceNormal);

        // MathUtil::Angle::AngleZX angle; 
        
        // MathUtil::Angle::GetAngle(point3,refVector,  angle);
        // // angle.x = std::atan2(point3.y, point3.z);
        
        // float desiredPitch = angle.x*40.0f;
        // if (lastAngle != angle.x&& !logLock)
        // {
        //     lastAngle = angle.x;
        //     SKSE::log::info("Angle {}", MathUtil::Angle::RadianToDegree(lastAngle));
        //     std::jthread lthread(LogDelayed); 
        //     lthread.detach();
        // }

        float playerDeltaTime = *deltaTime;

        spinePitch = MathUtil::Interp::InterpTo(spinePitch, desiredSpinePitch, playerDeltaTime, options.interpolationSpeed); 
        headPitch = MathUtil::Interp::InterpTo(headPitch, desiredHeadPitch, playerDeltaTime, options.interpolationSpeed);
        mountSpinePitch = MathUtil::Interp::InterpTo(mountSpinePitch, desiredMountSpinePitch, playerDeltaTime, moptions.interpolationSpeed);
        mountHeadPitch = MathUtil::Interp::InterpTo(mountHeadPitch, desiredMountHeadPitch, playerDeltaTime, moptions.interpolationSpeed);

        
	    a_actor->SetGraphVariableFloat("HSRD_SpinePitch", spinePitch);
        a_actor->SetGraphVariableFloat("HSRD_HeadPitch", headPitch);

        a_mount->SetGraphVariableFloat("HSPS_SpinePitch", mountSpinePitch); 
        a_mount->SetGraphVariableFloat("HSPS_HeadPitch", mountHeadPitch);




    }
}