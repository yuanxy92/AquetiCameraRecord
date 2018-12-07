/**
 * \file CompressionParameters.h
 * \brief 
 * \author Drew Perkins
 * \date 2017-08-07
 * 
 * * Copyright (C) 
 * 2017 - Aqueti Inc
 * Aqueti Inc. Proprietary 
 * 3333 Durham Chapel Hill Blvd Suite D100, Durham, North Carolina 27704 
 *
 * jpeg/h264/5 compression parameters
 *
 **/ 
#ifndef ATL_COMPRESSION_PARAMETERS_H
#define ATL_COMPRESSION_PARAMETERS_H

/**
*  \brief compression type enum
**/
typedef enum
{
	ATL_COMPRESSION_TYPE_NONE,
	ATL_COMPRESSION_TYPE_JPEG,
	ATL_COMPRESSION_TYPE_H264,
	ATL_COMPRESSION_TYPE_H265,

	NUM_ATL_COMPRESSION_TYPES
} AtlCompressionType;

/**
*  \brief hw preset for certain hardware encoders
**/
typedef enum
{
	NO_PRESET,
	GstOMXVideoEncHwPreset_UltraFast,
	GstOMXVideoEncHwPreset_Fast,
	GstOMXVideoEncHwPreset_Medium,
	GstOMXVideoEncHwPreset_Slow,

	NUM_HW_PRESETS
} AtlEncoderHWPreset;

/**
*  \brief bitrate control type
**/
typedef enum
{
	ENCODER_RATE_CONTROL_NONE,
	ENCODER_RATE_CONTROL_VARIABLE,
	ENCODER_RATE_CONTROL_CONSTANT,

	NUM_RATE_CONTROL_TYPES
} AtlEncoderRateControl;

/**
*  \brief profile 
**/
typedef enum
{
	NO_PROFILE,
	H264_BASELINE_PROFILE,
	H264_MAIN_PROFILE,
	H264_HIGH_PROFILE,

	NUM_PROFILES
} AtlEncoderProfile;

/**
*  \brief encoded level if supported
**/
typedef enum
{
	NO_LEVEL,
	H264_LEVEL_4_0,
	H264_LEVEL_4_1,
	H264_LEVEL_4_2,
	H264_LEVEL_5_0,
	H264_LEVEL_5_1,
	H264_LEVEL_5_2,

	NUM_LEVELS
} AtlEncoderLevel;

/**
*  \brief h264/5 compression parameters
*
**/
typedef struct
{
	uint8_t insert_sps_at_idr;

	/** quantization parameter and range for i frames **/
	uint8_t qp_iframe;
	uint8_t qp_max_iframe;
	uint8_t qp_min_iframe;
	
	/** quantization parameter and range for p frames **/
	uint8_t qp_pframe;
	uint8_t qp_max_pframe;
	uint8_t qp_min_pframe;
	
	/** quantization parameter and range for b frames **/
	uint8_t qp_bframe;
	uint8_t qp_max_bframe;
	uint8_t qp_min_bframe;
	
	uint32_t iframe_interval;
	uint8_t num_b_frames;
	uint64_t target_bitrate;
	uint8_t quality_preset_level;

	AtlCompressionType type;
	AtlEncoderHWPreset hw_preset;
	AtlEncoderRateControl rate_control;
	AtlEncoderProfile profile;
	AtlEncoderLevel level;

} AtlCompressionParameters;

#endif

