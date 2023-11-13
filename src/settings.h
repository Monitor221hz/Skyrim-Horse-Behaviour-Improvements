#pragma once 

#include "SimpleIni.h"

namespace HorsePoseCorrection
{
    class Settings
    {
        public:

        struct RiderPoseConfig
        {
            public: 

            float spinePitchMin = -50.0f;
            float spinePitchMax = 50.0f; 

            float headPitchMin = -50.0f; 
            float headPitchMax = 50.0f;
            
            float spineRollMin = -50.0f;  
            float spineRollMax= 50.0f; 

            float headRollMin = -50.0f;  
            float headRollMax= 50.0f;

            float interpolationSpeed = 1.0f; 

            float spinePitchMult = 30.0f;

            float headPitchMult = 10.0f; 

            float spineRollMult = 30.0f; 

            float headRollMult = 10.0f; 
        };

        struct MountPoseConfig
        {
            public: 

            float spinePitchMin = -50.0f; 
            float spinePitchMax = 50.0f;

            float headPitchMin = -50.0f; 
            float headPitchMax = 50.0f;

            float interpolationSpeed = 1.0f; 

            float headPitchMult = 1.0f; 
            float spinePitchMult = 0.0f;
        };

        static void Load()
        {
            constexpr auto path = L"Data/SKSE/Plugins/Horse_Pose_Correction/Settings.ini";
            CSimpleIniA ini;
            ini.SetUnicode();

            if (const auto rc = ini.LoadFile(path); rc < 0)
            {
                return;
            }

            RiderPoseOptions.spinePitchMin = (float)ini.GetDoubleValue("Rider Pose Correction", "SpinePitchMin",-50.0);
            RiderPoseOptions.spinePitchMax = (float)ini.GetDoubleValue("Rider Pose Correction", "SpinePitchMax",50.0);
            
            RiderPoseOptions.headPitchMin = (float)ini.GetDoubleValue("Rider Pose Correction", "HeadPitchMin",-50.0); 
            RiderPoseOptions.headPitchMax = (float)ini.GetDoubleValue("Rider Pose Correction", "HeadPitchMax",50.0);

            RiderPoseOptions.spineRollMin = (float)ini.GetDoubleValue("Rider Pose Correction", "SpineRollMin",-50.0);
            RiderPoseOptions.spineRollMax = (float)ini.GetDoubleValue("Rider Pose Correction", "SpineRollMax",50.0);

            RiderPoseOptions.headRollMin = (float)ini.GetDoubleValue("Rider Pose Correction", "HeadRollMin",-50.0);
            RiderPoseOptions.headRollMax = (float)ini.GetDoubleValue("Rider Pose Correction", "HeadRollMax",50.0);

            RiderPoseOptions.interpolationSpeed = (float)ini.GetDoubleValue("Rider Pose Correction", "InterpolationSpeed",1.0);

            RiderPoseOptions.spinePitchMult = (float)ini.GetDoubleValue("Rider Pose Correction", "SpinePitchMult",30.0);

            RiderPoseOptions.headPitchMult = (float)ini.GetDoubleValue("Rider Pose Correction", "HeadPitchMult",10.0);

            RiderPoseOptions.spineRollMult = (float)ini.GetDoubleValue("Rider Pose Correction", "SpineRollMult",30.0);

            RiderPoseOptions.headRollMult = (float)ini.GetDoubleValue("Rider Pose Correction", "HeadRollMult",10.0);


            MountPoseOptions.spinePitchMin = (float)ini.GetDoubleValue("Mount Pose Correction", "SpinePitchMin",-50.0);
            MountPoseOptions.spinePitchMax = (float)ini.GetDoubleValue("Mount Pose Correction", "SpinePitchMax",50.0);

            MountPoseOptions.headPitchMin = (float)ini.GetDoubleValue("Mount Pose Correction", "HeadPitchMin", -50.0);
            MountPoseOptions.headPitchMax = (float)ini.GetDoubleValue("Mount Pose Correction", "HeadPitchMax", 50.0);

            MountPoseOptions.interpolationSpeed = (float)ini.GetDoubleValue("Mount Pose Correction", "InterpolationSpeed",1.0);
            MountPoseOptions.spinePitchMult = (float)ini.GetDoubleValue("Mount Pose Correction", "SpinePitchMult",30.0);

            MountPoseOptions.headPitchMult = (float)ini.GetDoubleValue("Mount Pose Correction", "HeadPitchMult",10.0);

            
            
        }

        static inline RiderPoseConfig RiderPoseOptions; 

        static inline MountPoseConfig MountPoseOptions; 

    };
}