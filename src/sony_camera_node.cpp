#include "ros/ros.h"
#include "std_msgs/String.h"   // For the topic message type
#include "CameraRemote_SDK.h"  // Include the Sony Camera SDK header
#include "CrError.h"
#include "CrImageDataBlock.h"
#include "ICrCameraObjectInfo.h"

namespace SCRSDK
{
    bool capturePhoto()
    {
        // Ensure the SDK is initialized
        if (!SCRSDK::Init())  // Use the correct class
        {
            ROS_ERROR("Failed to initialize the SDK");
            return false;
        }

        // Enumerate connected cameras
        ICrEnumCameraObjectInfo* cameraList = nullptr;
        if (EnumCameraObjects(&cameraList) != CrError_None || cameraList == nullptr)
        {
            ROS_ERROR("No cameras found.");
            return false;
        }

        // Select the first camera from the list
        ICrCameraObjectInfo* cameraInfo = const_cast<ICrCameraObjectInfo*>(cameraList->GetCameraObjectInfo(0));


        CrDeviceHandle deviceHandle;

        // Connect to the camera
        if (Connect(cameraInfo, nullptr, &deviceHandle) != CrError_None)
        {
            ROS_ERROR("Failed to connect to the camera.");
            return false;
        }

        // Capture image
        CrImageDataBlock imageData;
        if (GetLiveViewImage(deviceHandle, &imageData) != CrError_None)
        {
            ROS_ERROR("Failed to capture image.");
            Disconnect(deviceHandle);
            return false;
        }

        ROS_INFO("Image captured successfully.");

        // Release the resources
        ReleaseDevice(deviceHandle);
        Release();
        return true;
    }
    
    // Callback function when the topic '/camera_cmd' receives a message
    void cameraCommandCallback(const std_msgs::String::ConstPtr& msg)
    {
        // Ensure the command is "capture"
        if (msg->data == "capture")
        {
            ROS_INFO("Received capture command, starting photo capture...");

            // Capture photo logic
            if (!capturePhoto())  // Use the correct namespace
            {
                ROS_ERROR("Failed to capture the image.");
            }
        }
    }

} // namespace SCRSDK

int main(int argc, char **argv)
{
    // Initialize the ROS system and create a node handle
    ros::init(argc, argv, "sony_camera_node");
    ros::NodeHandle nh;

    // Subscribe to the camera command topic
    ros::Subscriber sub = nh.subscribe("/camera_cmd", 1000, SCRSDK::cameraCommandCallback);

    ROS_INFO("Sony Camera Node is running...");

    // Keep the node running
    ros::spin();

    return 0;
}
