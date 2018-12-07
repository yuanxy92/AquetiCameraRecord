/***************************************************************************************
 * \file MantisAPI.h
 *
 *
 *  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
 *
 *  By downloading, copying, installing or using the software you agree to this license.
 *  If you do not agree to this license, do not download, install, copy or use the software.
 *
 *  Copyright (C) 2016, Aqueti Inc, all rights reserved.
 *
 *  Redistribution and use in binary forms, with or without modification, are permitted.
 *
 *  Unless required by applicable law or agreed to in writing, software distributed 
 *  under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 *  CONDITIONS OF ANY KIND, either express or implied. See the License for the specific
 *  language governing permissions and limitations under the License.
 *
****************************************************************************************/
#ifndef __ACOS_API_H__
#define __ACOS_API_H__

/************************************************************************
*   Declaration of Include Files  
************************************************************************/
#ifndef SWIG // Don't include system headers in SWIG wrapping
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#endif //SWIG

#include "atl/AtlTypes.h"
#include "atl/CompressionParameters.h"
#include "atl/AtlPropertyTypes.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define DEFAULT_FRAME_WAIT 1.0
#define DEFAULT_MANTIS_TIMEOUT 30

/**********************************************************************************************
 *
 * Declaration of all MantisAPI functions. This includes all functionality that the Aqueti ACOS
 * currently provides.  
 *
**********************************************************************************************/

/*************************************************************
* Configuration and Setup
*************************************************************/

/**
 * @brief Sync the API to a render server that manages an arbitrary
 *        number of cameras
 * @ip the ip address of the render server
 * @port network socket to connect to 
 * @return true on success, false on failure
 */
extern AQ_RETURN_CODE connectToCameraServer(const char* ip, uint16_t port, const char* id);

/**
 * @brief Removes the API's synced connection to the current render server
 * @return true on success, false on failure
 **/
extern AQ_RETURN_CODE disconnectFromCameraServer();

/**
 * @brief Checks whether this API instance is currently connected to an
 *        active and running render machine
 **/
extern AQ_SYSTEM_STATE isConnectedToCameraServer();

/**
 * \brief sets a callback that gets called when the status of the connection
 *        to the render server changes
 **/
extern void setNewConnectedToServerCallback( AQ_SYSTEM_STATE_CALLBACK cb );

/**
 * @brief Sends a shutdown signal to the connected camera server
 * @return AQ_SUCCESS if the command sends successfully, 
 *         else an error code specifying the mode of failure
 **/
extern AQ_RETURN_CODE shutdownCameraServer();

/**
 * @brief Sends a restart signal to the connected camera server
 *        ***CURRENTLY ONLY WORKS IF RUNNING A LOCAL INSTANCE OF THE API***
 * @return AQ_SUCCESS if the command sends successfully, 
 *         else an error code specifying the mode of failure
 **/
extern AQ_RETURN_CODE restartCameraServer();

/**
 * @brief Checks whether the specified camera object is currently
 *        connected to its physical camera system
 * @return An AQ_SYSTEM_STATE enum that gives the state of the camera connection.
 *         If the given camera is not found, returns AQ_STATE_UNKNOWABLE
 **/
extern AQ_SYSTEM_STATE isCameraConnected( ACOS_CAMERA cam );

/**
 * @brief Toggle the connection between the specified ACOS_CAMERA 
 *        object and the physical camera system that it represents.
 *        This connection is required to stream live data from the
 *        camera, but is not required to retrieve saved data.
 *        This function will return the state of the connection 
 *        after the toggle command completes, or return the current 
 *        connection state after the given timeout.
 * @cam The camera to toggle the connection for
 * @connect True to turn the connection on, false to turn it off
 * @timeout Timeout in seconds to wait for the command to succeed
 * @return AQ_SUCCESS if the set command succeeded, else an error code
 *         specifying what went wrong
 * **/
extern AQ_RETURN_CODE setCameraConnection( ACOS_CAMERA cam, bool connect, double timeout );

/**
 * \brief Removes all socket connections used to transmit data from
 *        the specified camera object to this API instance
 * \param cam The camera to disconnect from
 **/
/*TODO rename this, its waaaay too vague */
extern void disconnectCamera( ACOS_CAMERA cam );


#ifndef SWIG //This function has been re-implemented in python
/**
 * @brief This function specifies a callback that is triggered when a new 
 *        virtual camera is discovered by the API. 
 * @param callback the struct used to bind a new camera event
 */
extern void setNewCameraCallback( NEW_CAMERA_CALLBACK callback); 
#endif //SWIG

/**
 * @brief This function specifies a callback that is triggered when a 
 *        virtual camera is deleted. 
 * @param callback the struct used to bind a camera deleted event
 */
extern void setCameraDeletedCallback( CAMERA_DELETED_CALLBACK callback ); 

/**
 * @brief Returns the number of Aqueti cameras accessible through the API 
 * @return list of Aqueti cameras connected 
 */
extern uint32_t getNumberOfCameras(); 

/**
 * @brief Sets state change callbacks for the properties of a 
 *        specified camera. Callbacks and pointers to associated
 *        data structures are passed in via an CAMERA_CALLBACKS struct
 *        which contains entries for each camera property.
 *        Callbacks will only be registered to properties with non-null
 *        entries in the struct, allowing a user to choose which
 *        properties to bind callbacks to.
 * @param callbacks The struct of callbacks to register
 **/
extern void setCameraPropertyCallbacks( CAMERA_CALLBACKS callbacks );

/**
 * @brief Returns the number of microcameras for the specified camera system.
 * @cam The camera to query
 * @return The number of microcameras in the physical camera system,
 *         or 0 if the virtual camera object has never been connected
 *         to its physical camera via the toggleConnection() function
 **/
extern uint32_t getCameraNumberOfMCams( ACOS_CAMERA cam );

#ifndef SWIG //This function has been re-implemented in python
/**
 * \brief Gets te list of microcameras in a camera system;
 * \param cam The camera system to get a list for
 * \param mcamList A preallocated array of MICRO_CAMERA structs of
 *        the length of the number of microcameras in the requested camera
 * \param len The length of the preallocated list
 **/
extern void getCameraMCamList( ACOS_CAMERA cam, 
                               MICRO_CAMERA* mcamList, 
                               uint32_t len );
#endif //SWIG

/**
 * \brief Gets the list of microcameras in a camera system and fills the
 *        mcamList parameter of the given ACOS_CAMERA struct
 * \param cam A pointer to the ACOS_CAMERA object to get a list for
 **/
extern bool fillCameraMCamList( ACOS_CAMERA* cam );

/**
 * @brief  shutdown the camera system
 * 
 * @param systemId the Id of the camera
 * @return success or failure
 */
/*TODO this function needs to be implemented */
//extern bool shutdownCamera(ACOS_CAMERA cam); 

/**
 * @brief  Reboot the camera system
 * 
 * @param systemId the Id of the camera
 * @return success or failure
 */
// extern bool rebootCamera(ACOS_CAMERA cam); 

/**
 * @brief sets the camera to factory default
 * 
 * @param systemId the Id of the camera
 * @return success or failure
 */
// extern bool setCameraFactoryDefault(ACOS_CAMERA cam);

/**
 * @brief returns the required information for ONVIF complient device 
 * information.
 *
 * @return struct containing manufacturer, model, firmware, serial number, and hardware id
 */
extern CAMERA_INFO getCameraInfo(ACOS_CAMERA cam);


/*********************************************************************
 * Data Interface
 *********************************************************************/
/**
 * @\brief Checks whether the given virtual camera is set to receive data
 *        from its associated physical camera system
 * @param cam The camera to check
 * @return An AQ_SYSTEM_STATE enum that gives the state of the camera data flow.
 *         If the given camera is not found, returns AQ_STATE_UNKNOWABLE
 **/
extern AQ_SYSTEM_STATE isCameraReceivingData( ACOS_CAMERA cam );

/**
 * @brief Sets whether the specified virtual camera object is receiving 
 *        frames from its associated physical camera system
 * @param cam The camera to toggle data for
 * @param on true to turn receiving on, false to turn it off
 * @timeout timeout in seconds to wait for command to complete
 * @return AQ_SUCCESS if command succeeds, else an error code for what went wrong
 **/
extern AQ_RETURN_CODE setCameraReceivingData( ACOS_CAMERA cam, bool on, double timeout );

/**
 * @brief Returns the compression type of the given camera's frame data
 *        as compressed by the camera's Tegras on acquisition
 * @param cam The camera to query
 * @return An AtlCompressionType enum corresponding to the compression type,
 *         or ATL_COMPRESSION_TYPE_NONE if the camera does not exist
 *         or is not currently connected (check with isCameraConnected)
 **/
extern AtlCompressionType getCameraFrameCompressionType( ACOS_CAMERA cam );

/**
 * @brief gets the frame requested, accociated with a specified microcamera ID and timestamp
 * 		  if no timestamp is provided, returns the most recent frame from specified microcamera.
 * @param cam the camera system
 * @param mcamID the id of the microcamera
 * @param timestamp the timestamp requested; use 0 to request the most recent
 * @param tilingPolicy the requested tiling policy
 * @param tile the scale of the tile requested ATL_TILE_4K, ATL_TILE_HD
 * @return The requested FRAME if it is found, else it returns a default
 *         constructed FRAME which contains a null image pointer and
 *         an uninitialized metadata struct
 */
extern FRAME getFrame( ACOS_CAMERA cam, 
                       uint32_t mcamID, 
                       uint64_t timestamp,
                       uint16_t tilingPolicy, 
                       uint16_t tile );

#ifndef SWIG //This function has been re-implemented in python
/**
 * @brief saves frame data to specified location
 * @param frame the data to save to disk
 * @param the location to save to disk
 **/
extern bool saveFrame(FRAME frame, const char* location);
#endif //SWIG

/**
 * @brief set a callback for the given camera to be constatly updated
 *        with the latest available timestamp for the camera's frames
 * @param cam the camera to bind the callback for
 * @param cb the callback to bind
 **/
extern bool setLatestTimeCallback( ACOS_CAMERA cam, CAMERA_UINT64_CALLBACK cb );

/**
 * @brief sets the auto data deletion property of the current camera server
 * @param[in] on If true, the oldest recording is automatically deleted when 
 *               the storage system runs out of available space
 * @return AQ_SUCCESS if successful, else an error code
 **/
extern AQ_RETURN_CODE setAutoDataDeletion( bool on );

/*******************************************************************
*Stream management - creation and deletion of streams
********************************************************************/
/**
 * @brief Checks whether the given stream object exists on the connected server
 * @param[in] stream The struct representing the stream to check
 * @param[in] timeout Seconds to wait for the stream
 * @return true if the stream exists, else false
 **/
extern bool streamExists( ACOS_STREAM stream, double timeout );

/**
 * @brief creates a new rendering pipeline and streams the data to the specified output. 
 * @param stream the struct for the desired stream
 * @return ACOS_STREAM the stream object
 */
extern ACOS_STREAM createLiveStream( ACOS_CAMERA camera, STREAM_PROFILE profile );

/**
 * @brief creates a new clip rendering pipeline and streams the data to the specified output. 
 * @param stream the struct for the desired stream
 * @return ACOS_STREAM the stream object
 */
extern ACOS_STREAM createClipStream( ACOS_CLIP clip, STREAM_PROFILE profile );

/**
 * @brief creates a micro camera stream pipeline and streams the data to the specified output. 
 * @param stream the struct for the desired stream
 * @return ACOS_STREAM the stream object
 */
extern ACOS_STREAM createMCamStream( ACOS_CAMERA camera, MICRO_CAMERA mcam);

/**
 * @brief removes a new rendering pipeline 
 * @param stream the struct of the specified stream
 * @return the success or failure
 */
extern bool deleteStream( ACOS_STREAM stream);

/**
 * @brief Wrapper function for createStreamReceiver and connectStreamReceiver
 *        used to create and connect a stream receiver in a single call
 * @param callback the callback to give frames
 * @param stream the stream to set up the initial receiver for
 * @param clientport the port to send frames
 * @param wTime the length of time to wait for a frame
 * @return the success or failure
 **/
extern bool initStreamReceiver( FRAME_CALLBACK callback, ACOS_STREAM stream, uint16_t clientport, double wTime  );

/**
 * @brief creates a stream receiver on the given port that will pass frames 
 *        to the assigned callback
 * @param callback the callback to give frames
 * @param clientport the port to send frames
 * @param wTime the length of time to wait for a frame
 * @return the success or failure
 **/
extern bool createStreamReceiver( FRAME_CALLBACK callback, uint16_t clientport, double wTime );

/**
 * @brief connects a stream to an existing stream receiver on the given port
 * @param stream the new stream to connect
 * @param clientport the port of the stream receiver
 * @return the success or failure
 */
extern bool connectStreamReceiver(ACOS_STREAM stream, uint16_t clientport);

/**
 * @brief an optional method, disconnects a stream to an already created stream receiver
 * @param stream the new stream to disconnect
 * @param clientport the port of the stream receiver
 * @return the success or failure
 */
extern bool disconnectStreamReceiver(ACOS_STREAM stream, uint16_t clientport);

/**
 * @brief closes the stream reciever on a specific port
 * @param port network socket to connect to 
 * @return the success or failure
 */
extern bool closeStreamReceiver(uint16_t clientport);


/*******************************************************************
*Stream controls - controls a camera stream
********************************************************************/

/**
 * @brief The playStream function plays the specified stream. The speed parameter specifies the the playback speed where 0 is paused,
 * .5 plays back at half speed, 1 is full speed, and 2 is double speed. Negative speed values are used to move backwards through time. 
 *
 * @param stream the struct of the specified stream
 * @param speed to play the stream
 * @return success or failure
 */
extern bool setStreamPlaySpeed( ACOS_STREAM stream, double speed);

/**
 * @brief Pauses the stream at the current frame and steps forward
 *        or backward the specified number of frames
 * @param stream The struct of the specified stream
 * @param steps The number of frames to step forwards or backwards.
 *        Positive integers step forwards, negative integers step backwards.
 *        A step of 0 will simply pause the stream, but it is recommended
 *        to use the setPlaySpeed function to achieve this functionality.
 * @return success or failure
 **/
extern bool streamFrameStep( ACOS_STREAM stream, int steps );
//TODO should we change this to setStream... to be consistent with other methods?

/**
 * @brief Moves the current stream time to the given timestamp, if valid.
 *        Note, even if the time is technically valid, that does not guarantee 
 *        data exists or is available for the selected time
 * @param stream The struct of the specified stream
 * @param timestamp The time to jump to
 * @return success or failure
 **/
extern bool setStreamToTime( ACOS_STREAM stream, uint64_t timestamp );

/**
 * @brief Tells the stream to catch up to live data from the camera and play
 *        at the standard framerate. This function will fail if called on 
 *        a stream that is not a live camera stream
 **/
extern bool setStreamGoLive( ACOS_STREAM stream );

/**
 * @brief Goes to the first frame of the stream, if playing from a clip.
 * Note that this function will fail if we are playing a live stream,
 * because frame 0 will not have been recorded.
 */
extern bool setStreamGoToClipStart( ACOS_STREAM stream );

/**
 * @brief Retrieves the range of allowed pan degrees for the given stream
 * @param stream The handle for the specified stream
 * @return A struct containing doubles for the max and min pan degrees
 **/
extern AtlRange_64f getStreamPanRange( ACOS_STREAM stream );

/**
 * @brief Retrieves the range of allowed tilt degrees for the given stream
 * @param stream The handle for the specified stream
 * @return A struct containing doubles for the max and min tilt degrees
 **/
extern AtlRange_64f getStreamTiltRange( ACOS_STREAM stream );

/**
 * @brief Retrieves the range of allowed zoom degrees for the given stream
 * @param stream The handle for the specified stream
 * @return A struct containing doubles for the max and min zoom degrees
 **/
extern AtlRange_64f getStreamZoomRange( ACOS_STREAM stream );

/**
 * @brief Set the absolute values of the pan, tilt, and zoom of the given
 *        camera stream.
 * @param stream The struct of the specified stream
 * @param ptz A struct specifying the desired pan and tilt degrees, 
 *        and zoom factor
 * @return success or failure
 **/
extern bool setStreamPTZAbsolute( ACOS_STREAM stream, ACOS_PTZ_ABSOLUTE ptz );

/**
 * @brief Set the rate of change of the pan, tilt, and zoom of the given
 *        camera stream.
 * @param stream The struct of the specified stream
 * @param ptz A struct specifying the desired rate of change of the pan,
 *        tilt, and zoom for the given stream
 * @return success or failure
 **/
extern bool setStreamPTZVelocity( ACOS_STREAM stream, ACOS_PTZ_VELOCITY ptz );

/**
 * @brief Sets the new stream viewport to the position and zoom level
 *        specified by a box drawn on the stream in normalized coordinates.
 *        relative to the output stream images. The top left corner of the
 *        image is (0,0) and the bottom right is (1,1). The box struct contains
 *        x and y coordinates for the center of the box, and a half-width
 *        which specifies the box size (the box is always the same aspect
 *        ratio as the original image). For example, to set the stream to
 *        its current position, we would set (x,y) = (.5,.5) which is the
 *        center of the image, and the half-width to .5, which is half the
 *        width of the image.
 * @param stream The struct of the specified stream
 * @param box The box specifying the target location in normalized coordinates.
 * @return success or failure
 **/
extern AQ_RETURN_CODE setStreamBoxZoom( ACOS_STREAM stream, ACOS_NORMALIZED_BOX box );

/**
 * @brief Set the render gain of the given camera stream
 * @param stream The struct of the specified stream
 * @param gain The value to set the gain to
 * @return success or failure
 **/
extern bool setStreamGain( ACOS_STREAM stream, double gain );

/**
 * @brief Set the render offset of the given camera stream
 * @param stream The struct of the specified stream
 * @param offset The value to set the offset to
 * @return success or failure
 **/
extern bool setStreamOffset( ACOS_STREAM stream, double offset );

/**
 * @brief Set the render gamma of the given camera stream
 * @param stream The struct of the specified stream
 * @param gamma The value to set the gamma to
 * @return success or failure
 **/
extern bool setStreamGamma( ACOS_STREAM stream, double gamma );


/**
 * @brief Set the render denoise of the given camera stream
 * @param stream The struct of the specified stream
 * @param denoise The value to set the denoise to
 * @return success or failure
 **/
extern bool setStreamDenoise( ACOS_STREAM stream, bool on );

/**
 * @brief Set the render denoise of the given camera stream
 * @param stream The struct of the specified stream
 * @param denoise The value to set the denoise to
 * @return success or failure
 **/
extern bool setStreamSmoothDenoise( ACOS_STREAM stream, double denoise );

/**
 * @brief Set the render denoise of the given camera stream
 * @param stream The struct of the specified stream
 * @param denoise The value to set the denoise to
 * @return success or failure
 **/
extern bool setStreamEdgeDenoise( ACOS_STREAM stream, double denoise );

/**
 * @brief Set the encoding parameters of the given camera stream
 * @param stream The struct of the specified stream
 * @param encoder The new encoding parameters
 * @return success or failure
 **/
extern bool setStreamEncoder( ACOS_STREAM stream, VIDEO_ENCODER encoder );

/**
 * @brief sets the scale mode on the micro camera
 * @param stream the stream to set the scale for
 * @param scale the scale to set ATL_TILE_4K = 0, ATL_TILE_HD = 1 
 */
extern bool setMCamStreamScale( ACOS_STREAM stream, uint16_t scale );

/*********************************************************************
 * Stream State Getters
 *********************************************************************/

/**
 * @brief Get the range of allowed gain values for the given camera stream
 * @param stream The struct of the specified stream
 * @return A struct representing the range
 **/
extern AtlRange_32f getStreamGainRange( ACOS_STREAM stream );

/**
 * @brief Get the range of allowed offset values for the given camera stream
 * @param stream The struct of the specified stream
 * @return A struct representing the range
 **/
extern AtlRange_32f getStreamOffsetRange( ACOS_STREAM stream );

/**
 * @brief Get the range of allowed gamma values for the given camera stream
 * @param stream The struct of the specified stream
 * @return A struct representing the range
 **/
extern AtlRange_32f getStreamGammaRange( ACOS_STREAM stream );

 /**
 * @brief Get the render gain of the given camera stream
 * @param stream The struct of the specified stream
 * @return current gain
 **/
extern double getStreamGain( ACOS_STREAM stream );

/**
 * @brief Get the render offset of the given camera stream
 * @param stream The struct of the specified stream
 * @return current offset
 **/
extern double getStreamOffset( ACOS_STREAM stream );

/**
 * @brief Get the render gamma of the given camera stream
 * @param stream The struct of the specified stream
 * @param gamma The value to set the gamma to
 * @return current gamma
 **/
extern double getStreamGamma( ACOS_STREAM stream );

/**
 * @brief Get the render denoise of the given camera stream
 * @param stream The struct of the specified stream
 * @param denoise The value to set the denoise to
 * @return success or failure
 **/
extern bool getStreamDenoise( ACOS_STREAM stream );

/**
 * @brief Get the range of allowed smooth denoise values for the given camera stream
 * @param stream The struct of the specified stream
 * @return A struct representing the range
 **/
extern AtlRange_32f getStreamSmoothDenoiseRange( ACOS_STREAM stream );

/**
 * @brief Get the range of allowed edge denoise values for the given camera stream
 * @param stream The struct of the specified stream
 * @return A struct representing the range
 **/
extern AtlRange_32f getStreamEdgeDenoiseRange( ACOS_STREAM stream );

/**
 * @brief Get the render denoise of the given camera stream
 * @param stream The struct of the specified stream
 * @return current smooth denoise
 **/
extern double getStreamSmoothDenoise( ACOS_STREAM stream );

/**
 * @brief Get the render denoise of the given camera stream
 * @param stream The struct of the specified stream
 * @return current edge denoise
 **/
extern double getStreamEdgeDenoise( ACOS_STREAM stream );


/*********************************************************************
 * Clip Data Management
 *********************************************************************/

/**
 * @brief sets a callback function for a new clip detected event
 * @param callback the callback containing new acos clip information
 **/
extern void setNewClipCallback( ACOS_CLIP_CALLBACK callback); 

/**
 * @brief sets a callback function for a clip deleted event
 * @param callback the callback to handle the clip deleted event
 **/
extern void setClipDeletedCallback( ACOS_CLIP_CALLBACK callback); 

/**
 * @brief Requests a full list of the currently existing recordings
 * @param recordingList A pointer to an unallocated pointer that will contain
 *        the array of ACOS_CLIP structs that represent the recordings
 * @return The number of existing recordings that are in the return list.
 *         A nonzero return value gives the number of items in the list,
 *         and indicates the pointer's contents must be freed byt the user.
 *         A return of 0 indicates an error, and that no allocation took place.
 **/
extern unsigned requestStoredRecordings( ACOS_CLIP** recordingList );

/**
 * @brief Checks whether the specified camera object is currently
 *        recording the data from its physical camera system
 * @return An AQ_SYSTEM_STATE enum that gives the state of the camera.
 *         If the given camera is not found, returns AQ_STATE_UNKNOWABLE
 **/
extern AQ_SYSTEM_STATE isCameraRecording( ACOS_CAMERA cam );

/**
 * @brief sends the command to start/stop recording data from a given camera
 * @param cam the camera to start/stop recording
 * @param on If true, starts recording, else stops recording
 * @timeout timeout in seconds to wait for command to complete
 * @return AQ_SUCCESS if command succeeds, else an error code for what went wrong
 **/
extern AQ_RETURN_CODE setCameraRecording( ACOS_CAMERA cam, bool on, double timeout );  

/**
 * @brief Deletes the specified clip. If deletion is successful, triggers
 *        the registered ClipDeletedCallback
 * @param clip the struct representing the clip to delete
 **/
extern bool deleteClip( ACOS_CLIP clip );


/********************************************************************
 * High-level operations and processing threads
 ********************************************************************/

/**
 * @brief Updates a camera's render model to the model in the given file.
 *        File must be a valid JSON file or else the update will fail.
 * @param cam The camera to perform global whtie balance on
 * @param modelfile The file containing the new model to use
 **/
extern bool updateCameraModel( ACOS_CAMERA cam, const char* modelfile );

/**
 * @brief Updates the list of saved models for the given clip. If the given 
 *        model is for a timestamp that already has an associated model, the 
 *        old model will be replaced. If the model specifies a new timestamp,
 *        the new model will just be added to the list of models for the clip.
 * @param[in] clip The clip to update
 * @param[in] modelfile The file containing the new model to use
 * @return true on success, false on failure
 **/
extern bool updateClipModels( ACOS_CLIP clip, const char* modelfile );

/**
 * @brief Triggers the camera's global white balance action thread,
 *        which balances teh white balance across all
 *        microcameras in the system.
 * @param cam The camera to perform global whtie balance on
 * @return AQ_SUCCESS on success, else an error code specifying type of failure
 **/
extern AQ_RETURN_CODE performGlobalWhiteBalance( ACOS_CAMERA cam );

/**
 * @brief Retrieves the current state of the global auto white balance loop
 *        for the specified camera
 * @param[in] cam The camera
 * @return true if enabled, else false
 **/
extern bool getGlobalWhiteBalanceAutoLoopState( ACOS_CAMERA cam );

/**
 * @brief Toggles a loop which automatically monitors microcamera
 *        state and triggers the camera's global white balance 
 *        action thread to rebalance the microcameras when microcamera
 *        color differences exceed an acceptable threshold 
 * @param cam The camera to enable the automatic white balance for
 * @param on If true, turns the loop on, esle turns it off
 * @return AQ_SUCCESS on success, else an error code specifying type of failure
 **/
extern AQ_RETURN_CODE toggleGlobalWhiteBalanceAutoLoop( ACOS_CAMERA cam, bool on );

/**
 * @brief Triggers the camera's global auto gain action thread
 *        which balances gain values across a camera system.
 * @param[in] cam The camera to perform gain adjustment on.  
 * @return AQ_SUCCESS on success, else an error code specifying type of failure
 */
extern AQ_RETURN_CODE performGlobalGain(ACOS_CAMERA cam);

/**
 * @brief Retrieves the current state of the global auto gain loop
 *        for the specified camera
 * @param[in] cam The camera
 * @return true if enabled, else false
 **/
extern bool getGlobalGainAutoLoopState( ACOS_CAMERA cam );

/**
 * @brief Toggles a loop which automatically adjusts camera gain
 *        settings, analyzing gain values every 2 seconds
 *        to determine if action needs to be taken.
 * @param[in] cam The camera to enable auto gain adjustment for.
 * @param[in] on If true, turns on, if false, turns off
 * @return AQ_SUCCESS on success, else an error code specifying type of failure
 */
extern AQ_RETURN_CODE toggleGlobalGainLoop(ACOS_CAMERA cam, bool on);

/**
 * @brief Triggers the camera's global auto shutter action thread
 *        which briefly turns on auto shutter for all microcameras
 *        and turns it back off.
 * @param[in] cam The camera to perform shutter adjustment on.  
 * @return AQ_SUCCESS on success, else an error code specifying type of failure
 */
extern AQ_RETURN_CODE performGlobalAutoShutter(ACOS_CAMERA cam);

/**
 * @brief Retrieves the current state of the global auto shutter loop
 *        for the specified camera
 * @param[in] cam The camera
 * @return true if enabled, else false
 **/
extern bool getGlobalShutterAutoLoopState( ACOS_CAMERA cam );

/**
 * @brief Toggles a loop which automatically adjusts camera auto shutter 
 *        settings. Currently turns auto shutter on/off every 2 seconds.
 * @param[in] cam The camera to enable auto shutter adjustment for.
 * @param[in] on If true, turns on, if false, turns off
 * @return AQ_SUCCESS on success, else an error code specifying type of failure
 */
extern AQ_RETURN_CODE toggleGlobalAutoShutterLoop(ACOS_CAMERA cam, bool on);


/********************************************************************
 *
 * Low level interface (microcamera controls)
 *
 * For all the following methods:
 * - mcam refers to the MICRO_CAMERA struct representing the microcamera
 *
 ********************************************************************/

/**
 * @brief Connects the API to a specific tegra 
 * @param ip network address of Tegra
 * @param port network socket to connect to 
 **/
extern AQ_RETURN_CODE mCamConnect(const char* tegraip, uint16_t tegraport);

/**
 * @brief disconnect from the mCam
 * @param ip on the client
 * @param port network socket to disconnect from 
 **/
extern AQ_RETURN_CODE mCamDisconnect( const char* tegraip, uint16_t clientport);

/**
 * @brief sets up the mCamera to stream 
 * @param port network socket to connect to 
 **/
extern bool initMCamFrameReceiver(uint16_t clientport, double wTime  ); // deprecate move to maintain all streams

/**
 * @brief sets up the mCamera to stream 
 * @param port network socket to connect to 
 **/
extern bool closeMCamFrameReceiver(uint16_t clientport); // deprecate move to maintain all streams

/**
 * @brief returns the number of microcameras connected to a camera system
 */
extern uint32_t getNumberOfMCams();  

/**
 * @brief Streams data from the mcam. Data is transferred via a socket 
 *        connection specified by the given ip address and port
 * @param mcam the mcam desired to stream from
 * @param client port the port desired to recieve on
 **/
extern bool startMCamStream( MICRO_CAMERA mcam, uint16_t clientPort);

/**
 * @brief Stops the mcam stream
 * @param mcam the mcam desired to stream from 
 * @param client port the port desired to recieve on
 **/
extern bool stopMCamStream( MICRO_CAMERA mcam, uint16_t clientPort );

/**
 * @brief sets the scale mode on the micro camera
 * @param port the connection to set the mode on
 * @param the mode to set ATL_SCALE_MODE_ALL = 0, ATL_SCALE_MODE_4K = 1, ATL_SCALE_MODE_HD = 2 
 */
extern bool setMCamStreamFilter(MICRO_CAMERA mcam, uint16_t port, int mode);


#ifndef SWIG //This function has been re-implemented in python
/**
 * @brief sets a callback function for a new-microcamera-detected event
 * @param callback the callback containing new micro camera information
 **/
extern void setNewMCamCallback( NEW_MICRO_CAMERA_CALLBACK callback ); 

/**
 * @brief sets up a callback to handle new micro camera frame event
 * @param the frame callback struct
 */
extern void setMCamFrameCallback(  MICRO_CAMERA_FRAME_CALLBACK callback );

/**
 * @brief grabs a frame from the associated frame reciever
 * @param port network socket to recieve from
 * @param wtime (optional) the length of time to wait for a stream
 * @return the most recent frame captured
 **/
extern FRAME grabMCamFrame(uint16_t clientport, double wTime);

/**
 * @brief returns the allocated pointer for grab frame
 * @param the pointer from the frame
 * @return true on success false on failure 
 **/
extern bool returnPointer(uint8_t const* ptr);//temporary function to return frame buffer

#endif //SWIG

/**
 * @brief Sets state change callbacks for the properties of a 
 *        specified microcamera. Callbacks and pointers to associated
 *        data structures are passed in via an mCamCallbacks struct
 *        which contains entries for each microcamera property.
 *        Callbacks will only be registered to properties with non-null
 *        entries in the struct, allowing a user to choose which
 *        properties to bind callbacks to.
 * @param mcam The microcamera to bind the callbacks to
 * @param callbacks The struct of callbacks to register
 **/
extern void setMCamPropertyCallbacks( MICRO_CAMERA mcam, MICRO_CAMERA_CALLBACKS callbacks );



/************************************************************************
*   AUTO SETTERS - return true on success and false on failure   
************************************************************************/

/**
 * @brief sets the specified micro camera auto exposure
 * @param the microcamera
 * @param the bool value to set to
 */
extern bool setMCamAutoExposure( MICRO_CAMERA mcam, bool on); 

/**
 * @brief sets the Focus to Auto
 * @param the microcamera
 * @param the state value to set to
 */
extern bool setMCamAutoFocus(MICRO_CAMERA mcam, int state);

/**
 * @brief sets the Framerate to Auto
 * @param the microcamera
 * @param the bool value to set to
 */
extern bool setMCamAutoFramerate(MICRO_CAMERA mcam, bool on);

/**
 * @brief sets the Jpeg Quality to Auto
 * @param the microcamera
 * @param the bool value to set to
 */
extern bool setMCamAutoJpegQuality(MICRO_CAMERA mcam, bool on);

/**
 * @brief sets the Gain to Auto
 * @param the microcamera
 * @param the bool value to set to
 */
extern bool setMCamAutoGain(MICRO_CAMERA mcam, bool on);

/**
 * @brief sets the Saturation to Auto
 * @param the microcamera
 * @param the bool value to set to
 */
extern bool setMCamAutoSaturation(MICRO_CAMERA mcam, bool on);

/**
 * @brief sets the Shutter to Auto
 * @param the microcamera
 * @param the bool value to set to
 */
extern bool setMCamAutoShutter(MICRO_CAMERA mcam, bool on);

/**
 * @brief sets the Contrast to Auto
 * @param the microcamera
 * @param the bool value to set to
 */
extern bool setMCamAutoContrast(MICRO_CAMERA mcam, bool on);

/**
 * @brief sets the Sharpening to Auto
 * @param the microcamera
 * @param the bool value to set to
 */
extern bool setMCamAutoSharpening(MICRO_CAMERA mcam, bool on);

/**
 * @brief sets the De-Noise to Auto
 * @param the microcamera
 * @param the bool value to set to
 */
extern bool setMCamAutoDeNoise(MICRO_CAMERA mcam, bool on);

/************************************************************************
*   SETTERS - return true on success and false on failure   
************************************************************************/

/**
 * @brief sets the specified micro camera exposure
 * @param exposure the value to set the target exposure
 */
extern bool setMCamExposure( MICRO_CAMERA mcam, double exposure); 

/**
 * @brief sets the specified micro camera focus
 * @param focus the value to move the focus motor from the relative position
 */
extern bool setMCamFocusRelative( MICRO_CAMERA mcam, double focus) ; 

/**
 * @brief sets the specified micro camera focus
 * @param focus the value to move the focus motor from the absolute position
 */
extern bool setMCamFocusAbsolute( MICRO_CAMERA mcam, double focus) ; 

/**
 * @brief sets the specified micro camera to default
 */
extern bool setMCamFocusDefault( MICRO_CAMERA mcam); 

/**
 * @brief sets the specified micro camera framerate
 * @param framerate the value to set the micro camera framerate
 */
extern bool setMCamFramerate( MICRO_CAMERA mcam, double framerate); 

/**
 * @brief sets the specified micro camera jpegQuality
 * @param jpegQuality the value to set the micro camera jpegQuality
 */
extern bool setMCamJpegQuality( MICRO_CAMERA mcam, double jpegQuality); 

/**
 * @brief sets the specified micro camera Gain
 * @param gain the value to set micro camera gain
 */
extern bool setMCamGain( MICRO_CAMERA mcam, double gain); 

/**
 * @brief sets the specified micro camera Saturation
 * @param saturation the value to set the micro camera saturation
 */
extern bool setMCamSaturation( MICRO_CAMERA mcam, double saturation); 

/**
 * @brief sets the specified micro camera shutter
 * @param shutter the value to set the micro camera shutter
 */
extern bool setMCamShutter( MICRO_CAMERA mcam, double shutter); 

/**
 * @brief sets the specified micro camera contrast
 * @param contrast the value to set the micro camera contrast
 */
extern bool setMCamContrast ( MICRO_CAMERA mcam, double contrast); 

/**
 * @brief sets the specified micro camera sharpening
 * @param sharpening the value to set the micro camera sharpening
 */
extern bool setMCamSharpening( MICRO_CAMERA mcam, double sharpening); 

/**
 * @brief sets the specified micro camera De Noise
 * @param sharpening the value to set the micro camera DeNoise
 */
extern bool setMCamDeNoise( MICRO_CAMERA mcam, double denoise); 

/**
 * @brief sets the specified micro camera white balance
 * @param red the value to set the micro camera red gain
 * @param blue the value to set the micro camera blue gain
 * @param green the value to set the micro camera green gain
 */
extern bool setMCamWhiteBalance( MICRO_CAMERA mcam, AtlWhiteBalance whitebalance); 

/**
 * @brief sets the specified micro camera compression settings
 * @param cp the compression settings
 */
extern bool setMCamCompressionParameters( MICRO_CAMERA mcam, AtlCompressionParameters cp);

/**
 * @brief sets the whitebalance mode on the micro camera
 * @param mode the mode to set the whitebalance
          Manual = 0, Auto = 1, Sunlight = 2, Florescent = 3,
          Shade = 4, Tungsten = 5, Cloudy = 6, Incandescent = 7,
          Horizon = 8, Flash = 9
 */
extern bool setMCamWhiteBalanceMode(MICRO_CAMERA mcam, int mode);

/**
 * @brief sets the sensor mode on the micro camera
 * @param mode the mode of the sensor
         4k-30fps = 0, 4k-60fps = 1, HD-60fps = 2
 */
extern bool setMCamSensorMode(MICRO_CAMERA mcam, int mode);

/**
 * @brief sets the IR Filter on the micro camera
 * @param on value on or off
 */
extern bool setMCamIrFilter(MICRO_CAMERA mcam, bool on);

/**
 * @brief sets the focal Length on the micro camera
 * @param value the value to set
 */
extern bool setMCamFocalLength(MICRO_CAMERA mcam, double value);

/**
 * @brief sets the current microcamera analytic
 * @param the type to enable
 */
extern bool setMCamCurrentAnalytic( MICRO_CAMERA mcam, const char* type);

/************************************************************************
*   AUTO GETTERS - check if auto if on or off   
************************************************************************/
/**
 * @brief returns the specified micro camera exposure target
 */
extern bool getMCamAutoExposure( MICRO_CAMERA mcam ); 

/**
 * @brief returns whether the specified microcamera is using auto gain
 */
extern bool getMCamAutoGain( MICRO_CAMERA mcam );

/**
 * @brief returns whether the specified microcamera is using auto shutter
 */
extern bool getMCamAutoShutter( MICRO_CAMERA mcam ); 

/**
 * @brief returns whether the specified microcamera is using auto saturation
 */
extern bool getMCamAutoSaturation( MICRO_CAMERA mcam ); 

/**
 * @brief returns whether the specified microcamera is using auto framerate
 */
extern bool getMCamAutoFramerate( MICRO_CAMERA mcam ); 

/**
 * @brief returns whether the specified microcamera is using auto contrast
 */
extern bool getMCamAutoContrast( MICRO_CAMERA mcam );

/**
 * @brief returns whether the specified microcamera is using auto denoise
 */
extern bool getMCamAutoDenoise( MICRO_CAMERA mcam ); 

/**
 * @brief returns whether the specified microcamera is using auto sharpening
 */
extern bool getMCamAutoSharpening( MICRO_CAMERA mcam ); 

/**
 * @brief returns whether the specified microcamera is using auto quality
 */
extern bool getMCamAutoJpegQuality( MICRO_CAMERA mcam );  

/**
 * @brief returns whether the specified microcamera is using auto white balance
 */
extern bool getMCamAutoWhiteBalance( MICRO_CAMERA mcam ); 



/************************************************************************
*   GETTERS
************************************************************************/

/**
 * @brief returns the specified micro camera exposure target
 * @return the target exposure of the micro camera
 */
extern double getMCamExposure( MICRO_CAMERA mcam ); 

/**
 * @brief returns the specified micro camera Gain
 * @return the gain of the micro camera
 */
extern double getMCamGain( MICRO_CAMERA mcam); 

/**
 * @brief returns the specified micro camera focus
 * @return the focus of the micro camera
 */
extern double getMCamFocus( MICRO_CAMERA mcam); 

/**
 * @brief returns the specified micro camera focus
 * @return the focus of the micro camera 
 * ATL_FOCUS_MOTOR_IDLE 0 ,
 * ATL_FOCUS_MOTOR_ACTIVE 1, 
 * ATL_FOCUS_MOTOR_END 2 ,
 * ATL_FOCUS_MOTOR_RUNNING 3, 
 * ATL_FOCUS_MOTOR_ERROR 4 
 */
extern int getMCamFocusState( MICRO_CAMERA mcam); 

/**
 * @brief returns the specified micro camera shutter
 * @return the shutter of the micro camera
 */
extern double getMCamShutter( MICRO_CAMERA mcam); 

/**
 * @brief returns the specified micro camera saturation
 * @return the saturation of the micro camera
 */
extern double getMCamSaturation( MICRO_CAMERA mcam); 

/**
 * @brief returns the specified micro camera framerate
 * @return the framerate of the micro camera
 */
extern double getMCamFramerate( MICRO_CAMERA mcam); 

/**
 * @brief returns the specified micro camera contrast
 * @return the contrast of the micro camera
 */
extern double getMCamContrast(MICRO_CAMERA mcam);

/**
 * @brief returns the specified micro camera denoise
 * @return the denoise of the micro camera
 */
extern double getMCamDeNoise(MICRO_CAMERA mcam);

/**
 * @brief returns the specified micro camera sharpening
 * @return the sharpening of the micro camera
 */
extern double getMCamSharpening(MICRO_CAMERA mcam);

/**
 * @brief returns the specified micro camera Jpeg Quality
 * @return the Jpeg Quality of the micro camera
 */
extern double getMCamJpegQuality( MICRO_CAMERA mcam); 


/**
 * @brief returns the specified micro camera ir filter
 * @return a bool on is true off is false
 */
extern bool getMCamIrFilter(MICRO_CAMERA mcam); 

/**
 * @brief returns the specified micro camera white balance mode
 * @return  the mode to set the whitebalance
          Manual = 0, Auto = 1, Sunlight = 2, Florescent = 3,
          Shade = 4, Tungsten = 5, Cloudy = 6, Incandescent = 7,
          Horizon = 8, Flash = 9
 */
extern int getMCamWhiteBalanceMode( MICRO_CAMERA mcam);

/**
 * @brief returns the Tegra module ID for the specific microcamera
 * @return the module ID
 */
extern uint64_t getMCamModuleID( MICRO_CAMERA mcam);

/**
 *  * @brief returns the specified micro camera compression parameters
 *   * @return the compression parameters
 *    */
extern AtlCompressionParameters getMCamCompressionParameters( MICRO_CAMERA mcam);

/**
 * @brief returns the specified micro camera sensor ID
 * @return the sensor ID
 */
extern uint64_t getMCamSensorID( MICRO_CAMERA mcam);

/**
 * @brief returns the specified micro camera pixel Size
 * @return the pixel Size
 */
extern double getMCamPixelSize( MICRO_CAMERA mcam);

/**
 * @brief returns the specified micro camera focal Length
 * @return the focal length
 */
extern double getMCamFocalLength( MICRO_CAMERA mcam);

/**
 * @brief get the available analytics pipelines available to the specified microcamera
 */
extern const char** getMCamAvailableAnalytics( MICRO_CAMERA mcam );

/**
 * @brief get the number of available analytics pipelines available to the specified microcamera
 */
extern int getMCamNumberAvailableAnalytics( MICRO_CAMERA mcam );

/**
 * @brief returns the specified micro camera current analytic
 * @return the current analytics
 */
extern const char* getMCamCurrentAnalytic( MICRO_CAMERA mcam);


/**
 * @brief returns the specified micro camera white balance
 * @return a struct of red and blue whitebalance values of the micro camera
 */
extern AtlWhiteBalance getMCamWhiteBalance( MICRO_CAMERA mcam); 

/************************************************************************
*   RANGE GETTERS - return pair of range values
************************************************************************/

/**
 * @brief returns the specified micro camera Gain range
 * @return a struct of first min, second max gain range of the micro camera
 */
extern PAIR_DOUBLE getMCamGainRange(MICRO_CAMERA mcam);

/**
 * @brief returns the specified micro camera exposure range
 * @return a struct of first min, second max exposure range of the micro camera
 */
extern PAIR_DOUBLE getMCamExposureRange(MICRO_CAMERA mcam);

/**
 * @brief returns the specified micro camera shutter range
 * @return a struct of first min, second max shutter range of the micro camera
 */ 
extern PAIR_DOUBLE getMCamShutterRange(MICRO_CAMERA mcam);

/**
 * @brief returns the specified micro camera saturation range
 * @return a struct of first min, second max saturation range of the micro camera
 */
extern PAIR_DOUBLE getMCamSaturationRange(MICRO_CAMERA mcam);

/**
 * @brief returns the specified micro camera framerate range
 * @return a struct of first min, second max framerate range of the micro camera
 */
extern PAIR_DOUBLE getMCamFramerateRange(MICRO_CAMERA mcam);

/**
 * @brief returns the specified micro camera contrast range
 * @return a struct of first min, second max contrast range of the micro camera
 */
extern PAIR_DOUBLE getMCamContrastRange(MICRO_CAMERA mcam);

/**
 * @brief returns the specified micro camera denoise range
 * @return a struct of first min, second max denoise range of the micro camera
 */
extern PAIR_DOUBLE getMCamDeNoiseRange(MICRO_CAMERA mcam);

/**
 * @brief returns the specified micro camera sharpening range
 * @return a struct of first min, second max sharpening range of the micro camera
 */
extern PAIR_DOUBLE getMCamSharpeningRange(MICRO_CAMERA mcam);

/**
 * @brief returns the specified micro camera Jpeg Quality range
 * @return a struct of first min, second max Jpeg Quality range of the micro camera
 */
extern PAIR_DOUBLE getMCamJpegQualityRange(MICRO_CAMERA mcam);

/**
 * @brief returns the specified micro camera white balance range
 * @return a struct of first min, second max white balance range of the micro camera
 */
extern PAIR_DOUBLE getMCamWhiteBalanceRange(MICRO_CAMERA mcam);


/****************************************************************
* Debugging functions
****************************************************************/

/**
 * @brief saves the current tegras state across all connected tegras
 * @param saveDir the directory to save to
 * @return false on failure true on success
 */
extern bool saveCameraState(const char* saveDir);

/**
 * @brief loads the current tegras state across all connected tegras
 * @param loadDir the directory to load from
 * @return false on failure true on success
 */
extern bool loadCameraState(const char* loadDir);

/**
 * @brief prints the current property manager to the console
 */
extern void printCameraProperties();

/**
 * @brief returns the current property manager
 * @param the buffer to fill with properties (example 1000000 for size)
 * @param size of the buffer
 */
extern void getCameraProperties( char* buffer, int size);


/**
 * @brief compliles the current state of the system into a issue report
 *        along with the submission summary and description. Produces a tarball
 *        at the specified location.Default is /etc/aqueti/issues if length is 0.
 * @param summary: Short header for submission
 * @param description: Full description of the issue
 * @param location: Location on disk to save the issue tar file
 */
extern AQ_RETURN_CODE issueSubmission( const char* summary, const char* description, const char* location);

/**
 * @brief returns a string for the specified aqueti error or status code
 * @param the error or status code
 */
extern const char* returnErrorMessage(int code);

/**
 * @brief sets the system status and log message callbacks
 * @param a struct of system callbacks to register
 */
extern void setSystemCallbacks( SYSTEM_CALLBACKS callbacks );


#ifdef __cplusplus
 }
#endif

#endif // ACOS_API_H

