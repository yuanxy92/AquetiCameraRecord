#ifndef SWIG

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "CompressionParameters.h"

#endif //SWIG

/**

  \file Types.h

  also nifty macros for type id strings and default vals
  useful typedefs 
  good for c and c++

*/
#ifndef ATL_TYPES_H
#define ATL_TYPES_H

/**
  \defgroup ATL_TYPES atl_types
  useful typedefs for image stuff
  also for use as types for atl::Property objects

  serialization functions should be defined elsewhere
  
@{
**/

#ifdef __cplusplus
 extern "C" {
#endif


/** point type **/
typedef struct AtlPoint
{
	uint32_t x;            //!< X position
	uint32_t y;            //!< Y position
} AtlPoint;

/** float point type **/
typedef struct AtlPointNormalized
{	
	float x;               //!< X position
	float y;               //!< Y position
} AtlPointNormalized;

/** defines aligned rectangle by 4 side boundries **/
typedef struct AtlRectangle
{
	uint32_t xMin;                 //!< Min x coordinate
	uint32_t xMax;                 //!< Max x coordinate
	uint32_t yMin;                 //!< Min y coordinate
	uint32_t yMax;                 //!< Max y coordinate
} AtlRectangle;

/** defines aligned rectangle by 4 side boundries **/
typedef struct AtlRectangleNormalized
{
	float xMin;                    //!< Min x coordinate
	float xMax;                    //!< Max x coordinate
	float yMin;                    //!< Min y coordinate
	float yMax;                    //!< Max y coordinate
} AtlRectangleNormalized;

/** 2d rectangle size **/
typedef struct AtlSize
{
	int width;                     //!< Width of rectangle
	int height;                    //!< Height of rectangle
} AtlSize;

/** rectangle with int weight like argus autocontrol region **/
typedef struct AtlWeightedRegion
{
	AtlRectangle region;           //!< Region encompassed by rectangle
	uint32_t weight;               //!< Weight of rectangle
} AtlAutoControlRegion;

/** range type signed 32 bit int min and max**/
typedef struct AtlRange_32s
{
	int32_t min;                   //!< Min range
	int32_t max;                   //!< Max range
} AtlRange_32s;

/** range type unsigned 32 bit int **/
typedef struct AtlRange_32u
{
	uint32_t min;                  //!< Min range
	uint32_t max;                  //!< Max range
} AtlRange_32u;

/** range 32 bit floating point **/
typedef struct AtlRange_32f
{
	float min;                     //!< Min range
	float max;                     //!< Max range
} AtlRange_32f;

/** range min max 64 bit unsigned int **/
typedef struct AtlRange_64u
{ 
	uint64_t min;                  //!< Min range
	uint64_t max;                  //!< Max range
} AtlRange_64u;

/** range 64 bit signed int **/
typedef struct AtlRange_64s
{
	int64_t min;                   //!< Min range
	int64_t max;                   //!< Max range
} AtlRange_64s;

/** range double **/
typedef struct AtlRange_64f
{
	double min;                    //!< Min range
	double max;                    //!< Max range
} AtlRange_64f;

/** 3x3 float matrix **/
typedef float AtlMat_3x3_32f[3][3];
/** 3x4 float matrix **/
typedef float AtlMat_3x4_32f[3][4];

typedef struct AtlFloat4           //!< Contains float variables
{
	float x;                       //!< X variable
	float y;                       //!< Y variable
	float z;                       //!< Z variable
	float w;                       //!< W variable
} AtlFloat4;

typedef struct AtlWhiteBalance{
	double red;                    //!< red component of whitebalance
	double green;                  //!< green component of whitebalance
	double blue;                   //!< blue component of whitebalance
} AtlWhiteBalance;                 //!< struct that represents whitebalance

typedef struct {                
    uint64_t systemId;             //!< the camera system Id
    char moduleId[32];             //!< the class id
    char message[512];             //!< the system message
    uint64_t timestamp;            //!< the time the message was taken
} AtlMessage;                      //!< struct that contains a system message

typedef struct {                   //!< simple pair struct
    double first;                  //!< first value
    double second;                 //!< second value
} PAIR_DOUBLE;

/*typedef float Atl12thOrderCoefficeints[12];*/

/** @} **/

/* api structs. these should probably be moved eventually or combined with
 * the api header file */


/************************************************************************
*   Micro Camera Data Structures   
************************************************************************/

typedef struct {                    //!< defines micro camera in a camera system
    uint32_t mcamID;                //!< the identifier of the mcamera 
    char tegraip[20];               //!< the address of the tegra hosting this microcamera
    uint32_t camID;                 //!< the unique ID of the camera system the microcamera belongs to
} MICRO_CAMERA;

typedef struct {                    //<! defines a list of up to 256 microcameras
    uint8_t numMCams;               //<! the number of microcameras in the list
    MICRO_CAMERA mcams[256];        //<! the list of microcameras
} MCAM_LIST;

typedef struct {                    //!< frame position struct
    double          m_x;            //!< x position of the frame
    double          m_y;            //!< y position of the frame
    double          m_z;            //!< z position of the frame
    double          m_theta;        //!< theta value of the frame
    double          m_phi;          //!< phi position of the frame
    double          m_rho;          //!< the rho position of the frame
} FRAME_POSITION;                   //!< the position of the frame

typedef struct {                    //!< frame FOV struct
    double          m_minTheta;     //!< minimum theta value
    double          m_maxTheta;     //!< maximum theta value
    double          m_minPhi;       //!< minimum phi value
    double          m_maxPhi;       //!< maximum phi value
    double          m_iFOV;         //!< the frames field of view
} FRAME_FOV;                        //!< the frame field of view
    
typedef struct {                    //!< frame sensor ROI structs
    uint16_t        m_offsetX;      //!< the frame xoffset
    uint16_t        m_offsetY;      //!< the frame y offset
    uint16_t        m_roiWidth;     //!< the region of intrest width
    uint16_t        m_roiHeight;    //!< the region of intrest height
} FRAME_SENSOR_ROI;                 //!< the frame region of intrest 

typedef struct {                        //!< frame metadata struct
    uint64_t            m_id;           //!< id of the frame
    uint64_t            m_type;         //!< type of the frame
    size_t              m_size;         //!< size of the frame
    size_t              m_metaSize;     //!< size of the frames metadata
    size_t              m_offset;       //!< the offset size into the metadata
    uint64_t            m_timestamp;    //!< the timestamp 
    uint16_t            m_mode;         //!< the capture mode
    uint16_t            m_width;        //!< the frame width
    uint16_t            m_height;       //!< the frame height
    uint16_t            m_bpp;          //!< 
    uint32_t            m_camId;        //!< the mcam id
    uint16_t            m_tilingPolicy; //!< the frames tiling policy
    uint16_t            m_tile;         //!< the scale of the frame
    double              m_exposure;     //!< the exposure value
    double              m_gainR;        //!< the red gain value
    double              m_gainB;        //!< the blue gain value
    FRAME_POSITION      m_position;     //!< FRAME POSITION
    FRAME_FOV           m_fov;          //!< FRAME_FOV
    double              m_aperture;     //!< the aperture value
    double              m_focusPos;     //!< the focus position value
    double              m_framerate;    //!< the framerate captured 
    double              m_gain;         //!< the gain value
    double              m_saturation;   //!< the saturation value
    double              m_shutter;      //!< the shutter value
    double              m_pixelSize;    //!< the shutter value
    uint64_t            m_sensorType;   //!< the type of sensor
    FRAME_SENSOR_ROI    m_sensorRoi;    //!< FRAME_SENSOR_ROI
} FRAME_METADATA;                       //!< metadata for the frame

#ifndef SWIG
typedef struct {                        //!< frame struct
    FRAME_METADATA m_metadata;          //!< FRAME_METADATA
    uint8_t const* m_image;             //!< buffer containing the image data
} FRAME;                                //!< struct containing all frame information
#endif //SWIG

typedef struct {                            //!< micro_camera frame receive callback
    void (*f)(FRAME frame, void* data) ;    //!< pointer to function
    void * data;                            //!< pointer to extra data
} FRAME_CALLBACK;                           //!< callback for a micro camera new frame

typedef struct {                                                //!< mcam bool callback
    void (*f)(MICRO_CAMERA mcam, void* data, bool o, bool n) ;  //!< pointer to function
    void* data;                                                 //!< pointer to extra data
} MICRO_CAMERA_BOOL_CALLBACK ;                                  //!< callback for a micro camera with boolean type


typedef struct {                                                        //!< mcam uint64 callback
    void (*f)(MICRO_CAMERA mcam, void* data, uint64_t o, uint64_t n) ;  //!< pointer to function
    void* data;                                                         //!< pointer to extra data
} MICRO_CAMERA_UINT64_CALLBACK;                                         //!< callback for a micro camera with uint64 type

typedef struct {                                                    //!< mcam double callback
    void (*f)(MICRO_CAMERA mcam, void* data, double o, double n) ;  //!< pointer to function
    void* data;                                                     //!< pointer to extra data
} MICRO_CAMERA_DOUBLE_CALLBACK;                                     //!< callback for a micro camera with double type

typedef struct {                                                    //!< mcam double callback
    void (*f)(MICRO_CAMERA mcam, void* data, int o, int n) ;  //!< pointer to function
    void* data;                                                     //!< pointer to extra data
} MICRO_CAMERA_INT_CALLBACK;                                     //!< callback for a micro camera with int type

typedef struct {                                                                //!< mcampair of doubles callback
    void (*f)(MICRO_CAMERA mcam, void* data, PAIR_DOUBLE o, PAIR_DOUBLE n);     //!< pointer to function
    void* data;                                                                 //!< pointer to extra data
} MICRO_CAMERA_PAIR_DOUBLE_CALLBACK;                                            //!< callback for a micro camera with pair double type

typedef struct {                                                                        //!< mcampair of doubles callback
    void (*f)(MICRO_CAMERA mcam, void* data, AtlWhiteBalance o, AtlWhiteBalance n);     //!< pointer to function
    void* data;                                                                         //!< pointer to extra data
} MICRO_CAMERA_WHITEBALANCE_CALLBACK;                                                   //!< callback for a micro camera with whitebalance type

typedef struct {                                                                        //!< mcampair of doubles callback
    void (*f)(MICRO_CAMERA mcam, void* data, AtlCompressionParameters o, AtlCompressionParameters n);     //!< pointer to function
    void* data;                                                                         //!< pointer to extra data
} MICRO_CAMERA_COMPRESSION_CALLBACK;                                                   //!< callback for a micro camera with AtlCompressionParameters type

typedef struct {                                    //!< Micro_camera frame receive callback
    void (*f)(FRAME frame, void* data);             //!< pointer to function
    void * data;                                    //!< pointer to extra data
} MICRO_CAMERA_FRAME_CALLBACK;                      //!< callback for a micro camera new frame

typedef struct {                                    //!< Camera callback struct
    void (*f)(MICRO_CAMERA mcam, void* data);       //!< pointer to function with camera and pointer to data
    void* data;                                     //!< pointer to data
} NEW_MICRO_CAMERA_CALLBACK;


/*
Microcamera Property Callbacks
These callback functions are triggered when the corresponding microcamera
property changes its value, and all take 4 arguments:
    1) the mcam that triggered the callback
    2) the data pointer associated with the callback
    3) the old value of the property before the change
    4) the new value of the property after the change
*/                                                                
typedef struct {                                                //!< Micro camera callback struct
    
    // boolean callbacks
    MICRO_CAMERA_BOOL_CALLBACK autoGainCallback;                //!< Gain callback
    MICRO_CAMERA_BOOL_CALLBACK autoFramerateCallback;           //!< Framerate callback
    MICRO_CAMERA_BOOL_CALLBACK autoSaturationCallback;          //!< Saturation callback
    MICRO_CAMERA_BOOL_CALLBACK autoShutterCallback;             //!< Shutter callback
    MICRO_CAMERA_BOOL_CALLBACK autoWhiteBalanceCallback;        //!< White balance callback
    MICRO_CAMERA_BOOL_CALLBACK autoJpegQualityCallback;         //!< JPEG quality callback
    MICRO_CAMERA_BOOL_CALLBACK autoDenoiseCallback;             //!< Denoise callback
    MICRO_CAMERA_BOOL_CALLBACK autoContrastCallback;            //!< Contrast callback
    MICRO_CAMERA_BOOL_CALLBACK autoSharpeningCallback;          //!< Sharpening callback
    MICRO_CAMERA_BOOL_CALLBACK autoExposureCallback;            //!< Exposure callback
    MICRO_CAMERA_BOOL_CALLBACK irFilterCallback;                //!< Filter callback

    // double callbacks 
    MICRO_CAMERA_DOUBLE_CALLBACK exposureCallback;              //!< Exposure callback
    MICRO_CAMERA_DOUBLE_CALLBACK focusCallback;                 //!< Focus callback
    MICRO_CAMERA_DOUBLE_CALLBACK framerateCallback;             //!< Framerate callback
    MICRO_CAMERA_DOUBLE_CALLBACK gainCallback;                  //!< Gain callback
    MICRO_CAMERA_DOUBLE_CALLBACK saturationCallback;            //!< Saturation callback
    MICRO_CAMERA_DOUBLE_CALLBACK sharpeningCallback;            //!< Sharpening callback
    MICRO_CAMERA_DOUBLE_CALLBACK deNoiseCallback;               //!< Denoise callback
    MICRO_CAMERA_DOUBLE_CALLBACK shutterCallback;               //!< Shutter callback
    MICRO_CAMERA_DOUBLE_CALLBACK contrastCallback;              //!< Contrast callback
    MICRO_CAMERA_DOUBLE_CALLBACK jpegQualityCallback;           //!< JPEG quality callback
    MICRO_CAMERA_DOUBLE_CALLBACK colorTempCallback;             //!< Color temperature callback
    MICRO_CAMERA_DOUBLE_CALLBACK focalLengthCallback;

    // int callbacks
    MICRO_CAMERA_INT_CALLBACK focusStateCallback;
    MICRO_CAMERA_INT_CALLBACK autoFocusStateCallback;

    // specialized Callbacks
    MICRO_CAMERA_WHITEBALANCE_CALLBACK whiteBalanceCallback;    //!< White balance callback
    MICRO_CAMERA_COMPRESSION_CALLBACK compressionCallback;      //!< Compression Callback

} MICRO_CAMERA_CALLBACKS;

typedef struct {                                                //!< Transmitter callback struct
    
    MICRO_CAMERA_UINT64_CALLBACK totalBytes;                    //!< Total bytes in callback
    MICRO_CAMERA_UINT64_CALLBACK sentBytes;                     //!< Bytes sent in callback
    MICRO_CAMERA_UINT64_CALLBACK sentFrames;                    //!< Frames sent in callback
    MICRO_CAMERA_UINT64_CALLBACK droppedFrames;                 //!< Frames dropped in callback
}TRANSMITTER_CALLBACKS;


/************************************************************************
*   Camera Data Structures   
************************************************************************/

typedef struct {                   //!< Camera struct
    uint32_t camID;                //!< numerical camera Identifier
    MCAM_LIST mcamList;            //!< number and list of mcams
}ACOS_CAMERA;

typedef struct{                    //!< Stream struct
    uint64_t streamID;             //!< numerical stream Identifier
    ACOS_CAMERA camera;            //!< the camera system 
    uint16_t type;                 //!< stream type (live, clip, mcam, etc.)
}ACOS_STREAM; 

typedef struct{                    //!< Stream PTZ velocity
    double pan_per_second;         //!< Pan per second
    double tilt_per_second;        //!< Tilt per second
    double zoom_per_second;        //!< Zoom per second
}ACOS_PTZ_VELOCITY;

typedef struct{                    //!< Stream PTZ absolute
    double pan_degrees;            //!< Pan degrees
    double tilt_degrees;           //!< Tilt degrees
    double zoom_factor;            //!< Zoom factor
}ACOS_PTZ_ABSOLUTE;

typedef struct{                    //!< A box of known aspect ratio in normalized coordinates
    double x;                      //!< x coordinate of the box center
    double y;                      //!< y coordinate of the box center
    double halfWidth;              //!< half-width of the box
}ACOS_NORMALIZED_BOX;

typedef struct {                   //!< Camera user struct
    char username [64];            //!< Username of camera user
    char password [64];            //!< Password of camera user
    char userLevel [64];           //!< Level of user
}CAMERA_USER;

typedef struct {                   //!< Returns device info
    char manufacturer[10];         //!< The camera Manufacturer ex. Aqueti
    char model[10];                //!< The camera model ex. Mantis
    double firmwareVersion;        //!< Firmware verison (software version) ex. 1.0
    uint32_t serialNumber;         //!< Camera Serial Number ex. 21231241
    double hardwareId;             //!< Camera hardware ID 
} CAMERA_INFO;

typedef struct {                   //!< H264 stream struct
    uint16_t govLength;            //!< the group of video length of the stream
    char h264Profile[10];          //!< name of the profile ex. Main
} H264;

typedef struct {                   //!< Video source struct
    uint32_t width;                //!< width of the video stream
    uint32_t height;               //!< height of the video stream
} VIDEO_SOURCE;

typedef struct {                   //!< Video encoder struct
    uint32_t width;                //!< width of the video stream
    uint32_t height;               //!< height of the video stream
    uint16_t quality;              //!< quality of the stream ex. 4
    uint16_t sessionTimeout;       //!< session timeout for stream ex. 10
    uint16_t framerate;            //!< stream framerate ex. 25
    uint16_t encodingInterval;     //!< the encoding interval ex. 50
    uint32_t bitrateLimit;         //!< the bitrate limit of stream ex. 2048
    char encoding[10];             //!< encoding type ex. H264
    H264 h264;                     //!< H.264 profile
} VIDEO_ENCODER;

typedef struct {                   //!< onvif camera profile struct
    VIDEO_SOURCE videoSource;      //!< Video source info
    VIDEO_ENCODER videoEncoder;    //!< Video Encoder info
    char streamUri[80];            //!< stream Uri
} STREAM_PROFILE;

typedef struct{                    //!< ACOS clip struct
    ACOS_CAMERA cam;               //!< camera system 
    char name[80];                 //!< identifier of the clip
    uint64_t startTime;            //!< clip begins recording
    uint64_t endTime;              //!< clip ends recording
    double framerate;              //!< the rate of the clip 
    uint16_t encoding;              //!< encoding scheme of the frame data
} ACOS_CLIP;

typedef struct {                   //!< Stream creation request struct
    uint64_t streamId;             //!< ID of stream
    uint32_t mcamId;               //!< ID of camera
    ACOS_CLIP clip;                //!< Clip
    STREAM_PROFILE profile;        //!< Stream profile
} STREAM_REQUEST;

typedef struct {                                                        //!< Cam bool callback
    void (*f)(ACOS_CAMERA cam, void* data, bool o, bool n);             //!< The function framework
    void* data;                                                         //!< Extra data passed with the callback
} CAMERA_BOOL_CALLBACK;

typedef struct {                                                        //!< Cam double callback
    void (*f)(ACOS_CAMERA cam, void* data, double o, double n);         //!< The function framework
    void* data;                                                         //!< Extra data passed with the callback
} CAMERA_DOUBLE_CALLBACK;

typedef struct {                                                        //!< Cam uint64 callback
    void (*f)(ACOS_CAMERA cam, void* data, uint64_t o, uint64_t n);     //!< The function framework
    void* data;                                                         //!< Extra data passed with the callback
} CAMERA_UINT64_CALLBACK;

typedef struct {                                                        //!< Cam uint32 callback
    void (*f)(ACOS_CAMERA cam, void* data, uint32_t o, uint32_t n);     //!< The function framework
    void* data;                                                         //!< Extra data passed with the callback
} CAMERA_UINT32_CALLBACK;

typedef struct {                                                        //!< Cam uint16 callback
    void (*f)(ACOS_CAMERA cam, void* data, uint16_t o, uint16_t n);     //!< The function framework
    void* data;                                                         //!< Extra data passed with the callback
} CAMERA_UINT16_CALLBACK;

typedef struct {                                                        //!< Cam uint16 callback
    void (*f)(ACOS_CAMERA cam, void* data, int16_t o, int16_t n);       //!< The function framework
    void* data;                                                         //!< Extra data passed with the callback
} CAMERA_INT16_CALLBACK;

typedef struct {                                                        //!< Cam char callback
    void (*f)(ACOS_CAMERA cam, void* data, char o [10], char n [10]);   //!< The function framework
    void* data;                                                         //!< Extra data passed with the callback
} CAMERA_CHAR10_CALLBACK;


typedef struct {                                                        //!< ACOS clip callback struct
    void (*f)(ACOS_CLIP n, void* data);                                 //!< The function framework
    void* data;                                                         //!< Extra data passed with the callback
} ACOS_CLIP_CALLBACK;                                                   //!< struct that represents a acos clip

typedef struct {                   //!< ACOS image request struct
    char ipstr[80];                //!< Char array
    uint64_t time;                 //!< Time 
    uint32_t mcamId;               //!< Camera ID
    uint16_t tilingPolicy;         //!< Tiling policy
    uint16_t tile;                 //!< Tile
} ACOS_IMAGE_REQUEST;

// Camera callback Structs
typedef struct {                                            //!< new cam struct
    void (*f)(ACOS_CAMERA cam, void* data);                 //!< The function framework
    void* data;                                             //!< pointer to data
} NEW_CAMERA_CALLBACK;

typedef struct {                                            //!< deleted cam struct
    void (*f)(uint32_t cameraId, void* data);               //!< The callback function
    void* data;                                             //!< optional callback data
} CAMERA_DELETED_CALLBACK;

/*
Camera Property Callbacks
These callback functions are triggered when the corresponding Camera
property changes its value, and all take 4 arguments:
    1) the cam that triggered the callback
    2) the data pointer associated with the callback
    3) the old value of the property before the change
    4) the new value of the property after the change
*/    
typedef struct {                                                //!< Camera callback struct
    // encoder properties
    CAMERA_UINT32_CALLBACK videoEncoderWidth;                   //!< Width of video encoder
    CAMERA_UINT32_CALLBACK videoEncoderHeight;                  //!< Height of video encoder
    CAMERA_UINT16_CALLBACK videoEncoderQuality;                 //!< Quality of video encoder
    CAMERA_UINT16_CALLBACK videoEncoderSessionTimeout;          //!< Length of time before timeout
    CAMERA_UINT16_CALLBACK videoEncoderFramerate;               //!< Frame rate of video encoder
    CAMERA_UINT16_CALLBACK videoEncoderEncodingInterval;        //!< Interval of encoding
    CAMERA_UINT32_CALLBACK videoEncoderBitrateLimit;            //!< Bitrate limit of encoder
    CAMERA_CHAR10_CALLBACK videoEncoderEncoding;                //!< Encoding of video encoder

    // video source properties
    CAMERA_UINT32_CALLBACK videoSourceWidth;                    //!< Width of source video
    CAMERA_UINT32_CALLBACK videoSourceHeight;                   //!< Height of source video

    //TODO what are these things above? are they actually implemented?

    // Status of connection between virtual camera object and physical camera
    CAMERA_INT16_CALLBACK cameraConnectionCallback;

    // Status of data flow from physical camera to virtual camera object
    CAMERA_INT16_CALLBACK dataFlowStatusCallback;

    // Virtual camera recording state
    CAMERA_INT16_CALLBACK recordingStateCallback;
    
    // Camera time sync status
    CAMERA_UINT64_CALLBACK cameraTimeSyncCallback;        //!< Called when camera sync time changes.
                                                          //   Gives the largest time difference 
                                                          //   between any 2 microcameras in 
                                                          //   microseconds

    // Camera auto loop state callbacks, called when auto loops are enabled/disabled
    CAMERA_BOOL_CALLBACK globalWhiteBalanceCallback;
    CAMERA_BOOL_CALLBACK globalGainCallback;
    CAMERA_BOOL_CALLBACK globalShutterCallback;
}CAMERA_CALLBACKS;


/****************************************************************
* System level structs
****************************************************************/

/**
 * Defines for printing a specific Error state
 */
/* General errors */
#define AQ_SUCCESS_STRING                                       "Function successfully completed."
#define AQ_ERROR_INVALID_VALUE_STRING                           "Function was passed an invalid argument."
#define AQ_ERROR_TIMEOUT_STRING                                 "Function timed out waiting for an event."

/* PropertyManager errors */
#define AQ_ERROR_PROPERTYMANAGER_NOT_FOUND_STRING               "Function requires a PropertyManager that does not exist."
#define AQ_ERROR_PROPERTY_NOT_FOUND_STRING                      "Function requires a Property that does not exist."
#define AQ_ERROR_INTERRUPT_NOT_FOUND_STRING                     "Function requires an Interrupt that does not exist."
#define AQ_ERROR_FAILED_TO_BIND_PM_CALLBACK_STRING              "Failed to bind a callback to a Property or Interrupt."
#define AQ_ERROR_FAILED_TO_SET_PROPERTY_VALUE_STRING            "Failed to set the value of a Property."
#define AQ_ERROR_FAILED_TO_CALL_INTERRUPT_STRING                "Failed to call an Interrupt."
#define AQ_ERROR_PROPERTYMANAGER_TIMEOUT_STRING                 "Timed out waiting for a PropertyManager event."

/* Camera state errors */
#define AQ_ERROR_CAMERA_NOT_CURRENTLY_CONNECTED_STRING          "Function cannot be called when the given camera is not connected."
#define AQ_ERROR_CAMERA_NOT_CURRENTLY_RECEIVING_STRING          "Function cannot be called when the given camera is not receiving data."

/* function-specific errors */
#define AQ_ERROR_RENDER_CONNECT_FAILURE_STRING                  "Failed to connect to the specified render server address."
#define AQ_ERROR_RENDER_DISCONNECT_FAILURE_STRING               "Failed to disconnect from the current render server."
#define AQ_ERROR_RENDER_CONNECTION_NOT_FOUND_STRING             "Not currently connected to a render server."

#define AQ_ERROR_CAMERA_CONNECT_FAILURE_STRING                  "Failed to connect to the specified camera system."
#define AQ_ERROR_CAMERA_DISCONNECT_FAILURE_STRING               "Failed to disconnect from the specified camera system."
#define AQ_ERROR_CAMERA_CONNECTION_NOT_FOUND_STRING             "No existing connection to the specified camera system."
#define AQ_ERROR_CAMERA_RECEIVE_DATA_FAILURE_STRING             "Failed to start receiving frame data from the specified camera system."
#define AQ_ERROR_CAMERA_STOP_RECEIVING_DATA_FAILURE_STRING      "Failed to stop receiving frame data from the specified camera system."
#define AQ_ERROR_CAMERA_START_RECORDING_FAILURE_STRING          "Failed to start recording the specified camera system."
#define AQ_ERROR_CAMERA_STOP_RECORDING_FAILURE_STRING           "Failed to stop recording the specified camera system."

#define AQ_ERROR_TEGRA_CONNECTION_FAILURE_STRING                "Failed to connect to the specified Tegra address."
#define AQ_ERROR_TEGRA_DISCONNECT_FAILURE_STRING                "Failed to disconnect from the specified Tegra address."
#define AQ_ERROR_TEGRA_CONNECTION_NOT_FOUND_STRING              "Not existing connection to the specified Tegra address."

#define AQ_ERROR_STREAM_NOT_FOUND_STRING                        "Could not find the specified stream."
#define AQ_ERROR_INVALID_STREAM_TYPE_STRING                     "Function cannot be called on a stream of the given type."

#define AQ_ERROR_LOCATION_DOES_NOT_EXIST_STRING                 "Unable to write to specified location, does not exist."
#define AQ_ERROR_NO_WRITE_PERMISSION_STRING                     "Unable to write to specified location, no write permission."
#define AQ_ERROR_LOCATION_NOT_DIRECTORY_STRING                  "Unable to write to specified location, not a directory."

#define AQ_ERROR_UNKNOWABLE_STRING                              "Undefined error!"

/**
 * Defines for printing a specific connection state
 */

#define AQ_SERVER_CONNECTED_STRING                             "Connected to render server"
#define AQ_SERVER_DISCONNECTED_STRING                          "Disconnected from render server"
#define AQ_CAMERA_CONNECTED_STRING                             "Connected to all Tegras in camera system"
#define AQ_CAMERA_DISCONNECTED_STRING                          "Disconnected from all Tegras in camera system"
#define AQ_CAMERA_PARTIALLY_CONNECTED_STRING                   "Connected to some Tegras in camera system"
#define AQ_CAMERA_CONNECTION_UNKNOWABLE_STRING                 "Undefined camera connection state!"

#define AQ_CAMERA_RECEIVING_DATA_STRING                        "Receiving data from all microcameras in camera system"
#define AQ_CAMERA_NOT_RECEIVING_DATA_STRING                    "Not receiving data from any microcameras in camera system"
#define AQ_CAMERA_PARTIALLY_RECEIVING_DATA_STRING              "Receiving data from some microcameras in camera system"
#define AQ_CAMERA_RECEIVING_DATA_UNKNOWABLE_STRING             "Undefined camera data state!"

#define AQ_CAMERA_RECORDING_STRING                             "Recording data from camera system"
#define AQ_CAMERA_NOT_RECORDING_STRING                         "Not recording data from camera system"
#define AQ_CAMERA_STORAGE_FULL_STRING                          "Unable to record data, storage system is full"
#define AQ_CAMERA_RECORDING_UNKNOWABLE_STRING                  "Undefined camera recording state"

#define AQ_TEGRA_CONNECTED_STRING                              "Connected directly to Tegra"
#define AQ_TEGRA_DISCONNECTED_STRING                           "Disconnected from Tegra"
#define AQ_TEGRA_NOT_FOUND_STRING                              "Unable to find Tegra"
#define AQ_TEGRA_STREAMING_STRING                              "Streaming data from Tegra"
#define AQ_TEGRA_NOT_STREAMING_STRING                          "Not streaming data from Tegra"

#define AQ_STATE_UNKNOWABLE_STRING                             "Undefined state!"

/**
 * Return codes
 **/
typedef enum {
    /**
     * The API function executed successfully
     **/
    AQ_SUCCESS                                      = 0,
    

    /**
     * General API Error Codes
     **/
    /* The API function failed due to being given an invalid parameter */
    AQ_ERROR_INVALID_VALUE                          = 10,

    /* The API function timed out waiting for some event */
    AQ_ERROR_TIMEOUT                                = 11,

    /* The API function failed because the API instance 
     * is not currently connected to a camera server */
    AQ_ERROR_NOT_CONNECTED_TO_CAMERA_SERVER               = 12,


    /**
     * PropertyManager error codes
     **/
    /* The API function could not find (or timed out waiting for) 
     * a critical Property, Interrupt or PropertyManager */
    AQ_ERROR_PROPERTYMANAGER_NOT_FOUND              = 30,
    AQ_ERROR_PROPERTY_NOT_FOUND                     = 31,
    AQ_ERROR_INTERRUPT_NOT_FOUND                    = 32,

    /* The API function failed to bind to, set the value of, or call
     * a critical Property or Interrupt */
    AQ_ERROR_FAILED_TO_BIND_PM_CALLBACK             = 35,
    AQ_ERROR_FAILED_TO_SET_PROPERTY_VALUE           = 36,
    AQ_ERROR_FAILED_TO_CALL_INTERRUPT               = 37,

    /* The API function timed out waiting for a PropertyManager event */
    AQ_ERROR_PROPERTYMANAGER_TIMEOUT                = 40,


    /**
     * State-dependent error codes
     **/
    /* The API function cannot be called while the specified camera is not
     * connected to its physical camera system */
    AQ_ERROR_CAMERA_NOT_CURRENTLY_CONNECTED         = 50,

    /* The API function cannot be called while the specified camera is not
     * receiving data from its physical camera system */
    AQ_ERROR_CAMERA_NOT_CURRENTLY_RECEIVING         = 51,


    /**
     * Error codes for API to Render Server connection functions
     **/
    AQ_ERROR_RENDER_CONNECT_FAILURE                 = 100,
    AQ_ERROR_RENDER_DISCONNECT_FAILURE              = 101,
    AQ_ERROR_RENDER_CONNECTION_NOT_FOUND            = 102,


    /**
     * Error codes for Render Server to Tegra connection functions
     **/
    AQ_ERROR_CAMERA_CONNECT_FAILURE                 = 110,
    AQ_ERROR_CAMERA_DISCONNECT_FAILURE              = 111,
    AQ_ERROR_CAMERA_CONNECTION_NOT_FOUND            = 112,

    /**
     * Error codes for Render Server to Tegra data flow functions
     **/
    AQ_ERROR_CAMERA_RECEIVE_DATA_FAILURE            = 120,
    AQ_ERROR_CAMERA_STOP_RECEIVING_DATA_FAILURE     = 121,

    /**
     * Error codes for API to Tegra connection functions
     **/
    AQ_ERROR_TEGRA_CONNECTION_FAILURE               = 150,
    AQ_ERROR_TEGRA_DISCONNECT_FAILURE               = 151,
    AQ_ERROR_TEGRA_CONNECTION_NOT_FOUND             = 152,

    /**
     * Error codes for Camera System recording functions
     **/
    AQ_ERROR_CAMERA_START_RECORDING_FAILURE         = 200,
    AQ_ERROR_CAMERA_STOP_RECORDING_FAILURE          = 201,

    /**
     * Error codes for stream control functions
     **/
    AQ_ERROR_STREAM_NOT_FOUND                       = 300,
    AQ_ERROR_INVALID_STREAM_TYPE                    = 301,

    /**
     * Error codes for disk write access
     **/
    AQ_ERROR_LOCATION_DOES_NOT_EXIST                = 400,
    AQ_ERROR_NO_WRITE_PERMISSION                    = 401,
    AQ_ERROR_LOCATION_NOT_DIRECTORY                 = 402,

    /**
     * Whatever is left
     **/
    AQ_ERROR_UNKNOWABLE                             = 999
} AQ_RETURN_CODE;


/**
 * States returned by callback functions
 **/
typedef enum {
    /**
     * Connection states
     **/
    /* API to camera server connection states */
    AQ_SERVER_CONNECTED                             = 100,
    AQ_SERVER_DISCONNECTED                          = 101,

    /* Virtual camera (AquetiCam) to camera system (Tegras) connection states */
    AQ_CAMERA_CONNECTED                             = 110,
    AQ_CAMERA_DISCONNECTED                          = 111,
    AQ_CAMERA_PARTIALLY_CONNECTED                   = 112,
    AQ_CAMERA_CONNECTION_UNKNOWABLE                 = 113,

    /* Camera system (Tegras) to virtual camera (AquetiCam) data stream states */
    AQ_CAMERA_RECEIVING_DATA                        = 120,
    AQ_CAMERA_NOT_RECEIVING_DATA                    = 121,
    AQ_CAMERA_PARTIALLY_RECEIVING_DATA              = 122,
    AQ_CAMERA_RECEIVING_DATA_UNKNOWABLE             = 123,
    
    /* Individual Tegra to server connection states */
    AQ_TEGRA_CONNECTED                              = 150,
    AQ_TEGRA_DISCONNECTED                           = 151,
    AQ_TEGRA_NOT_FOUND                              = 152,

    /* Individual Tegra to server data stream states */
    AQ_TEGRA_STREAMING                              = 170,
    AQ_TEGRA_NOT_STREAMING                          = 171,

    /* Recording states */
    AQ_CAMERA_RECORDING                             = 200,
    AQ_CAMERA_NOT_RECORDING                         = 201,
    AQ_CAMERA_STORAGE_FULL                          = 202,
    AQ_CAMERA_RECORDING_UNKNOWABLE                  = 203,

    /**
     * extra stuff 'n' things
     **/
    AQ_STATE_UNKNOWABLE                             = 999
} AQ_SYSTEM_STATE;


typedef struct {
    void (*f)(void* data, AQ_SYSTEM_STATE o, AQ_SYSTEM_STATE n);//!< The function
    void* data;                                         //!< Data pointer
} AQ_SYSTEM_STATE_CALLBACK;


/**
 * Callback struct definition for log messages
 **/
typedef struct {                                        //!< Message callback struct
    void (*f)(void* data, AtlMessage n);                //!< The function framework
    void* data;                                         //!< Data pointer
} MESSAGE_CALLBACK;

/** 
 * Callback and notification structs for system-level events
 **/
typedef struct {                                       //!< Cam char interrupt for string notifications
    void (*f)(void* data, char msg[256]);              //!< The function framework
    void* data;                                        //!< Extra data passed with the callback
} ACOS_CHAR256_INTERRUPT;

typedef struct {                                       //!< System double callback for property callbacks
    void (*f)(void* data, double old, double n);       //!< The function framework
    void* data;                                        //!< Extra data passed with the callback
} ACOS_DOUBLE_CALLBACK;


typedef struct {                                        //!< System callback struct
    MESSAGE_CALLBACK infoCallback;                      //!< Information callback
    MESSAGE_CALLBACK warningCallback;                   //!< Warning callback
    MESSAGE_CALLBACK errorCallback;                     //!< Error callback
    MESSAGE_CALLBACK criticalErrorCallback;             //!< Critical error callback
    ACOS_CHAR256_INTERRUPT storageFullCallback;         //!< Storage drive full callback
    ACOS_DOUBLE_CALLBACK driveUsageCallback;            //!< Percentage of drive usage
} SYSTEM_CALLBACKS;


#ifdef __cplusplus
}
#endif


#endif

