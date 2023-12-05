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

            float interpolationSpeed = 10.0f; 

            float spinePitchMult = 3.0f;

            float headPitchMult = 1.0f; 

            float spineRollMult = 3.0f; 

            float headRollMult = 1.0f; 
        };

        struct MountPoseConfig
        {
            public: 

            float spinePitchMin = -40.0f; 
            float spinePitchMax = 40.0f;

            float headPitchMin = -40.0f; 
            float headPitchMax = 40.0f;

            float saddlePitchMin = -40.0f; 
            float saddlePitchMax = 40.0f;

            float interpolationSpeed = 3.0f; 

            float headPitchMult = 0.0f; 
            float spinePitchMult = 0.0f;
            float saddlePitchMult = 1.0f;

            
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

            RiderPoseOptions.spinePitchMin = (float)ini.GetDoubleValue("Rider Slope Correction", "SpinePitchMin",-40.0);
            RiderPoseOptions.spinePitchMax = (float)ini.GetDoubleValue("Rider Slope Correction", "SpinePitchMax",40.0);
            
            RiderPoseOptions.headPitchMin = (float)ini.GetDoubleValue("Rider Slope Correction", "HeadPitchMin",-30.0); 
            RiderPoseOptions.headPitchMax = (float)ini.GetDoubleValue("Rider Slope Correction", "HeadPitchMax",30.0);

            // RiderPoseOptions.spineRollMin = (float)ini.GetDoubleValue("Rider Slope Correction", "SpineRollMin",-50.0);
            // RiderPoseOptions.spineRollMax = (float)ini.GetDoubleValue("Rider Slope Correction", "SpineRollMax",50.0);

            // RiderPoseOptions.headRollMin = (float)ini.GetDoubleValue("Rider Slope Correction", "HeadRollMin",-50.0);
            // RiderPoseOptions.headRollMax = (float)ini.GetDoubleValue("Rider Slope Correction", "HeadRollMax",50.0);

            RiderPoseOptions.interpolationSpeed = (float)ini.GetDoubleValue("Rider Slope Correction", "InterpolationSpeed",10.0);

            RiderPoseOptions.spinePitchMult = (float)ini.GetDoubleValue("Rider Slope Correction", "SpinePitchMult",1.0);

            RiderPoseOptions.headPitchMult = (float)ini.GetDoubleValue("Rider Slope Correction", "HeadPitchMult",1.0);

            // RiderPoseOptions.spineRollMult = (float)ini.GetDoubleValue("Rider Slope Correction", "SpineRollMult",30.0);

            // RiderPoseOptions.headRollMult = (float)ini.GetDoubleValue("Rider Slope Correction", "HeadRollMult",10.0);


            MountPoseOptions.spinePitchMin = (float)ini.GetDoubleValue("Horse Slope Correction", "SpinePitchMin",-40.0);
            MountPoseOptions.spinePitchMax = (float)ini.GetDoubleValue("Horse Slope Correction", "SpinePitchMax",40.0);

            MountPoseOptions.headPitchMin = (float)ini.GetDoubleValue("Horse Slope Correction", "HeadPitchMin", -40.0);
            MountPoseOptions.headPitchMax = (float)ini.GetDoubleValue("Horse Slope Correction", "HeadPitchMax", 40.0);



            MountPoseOptions.interpolationSpeed = (float)ini.GetDoubleValue("Horse Slope Correction", "InterpolationSpeed",3.0);

            MountPoseOptions.spinePitchMult = (float)ini.GetDoubleValue("Horse Slope Correction", "SpinePitchMult",0.0);

            MountPoseOptions.headPitchMult = (float)ini.GetDoubleValue("Horse Slope Correction", "HeadPitchMult",0.0);



            
            
        }

        static inline RiderPoseConfig RiderPoseOptions; 

        static inline MountPoseConfig MountPoseOptions; 

    };
}