#include "fusionPCH.h"
#include "LidarNoise.h"
#include "../common/Helper.h"
#include "../common/MultiVariateNormalDistribution.h"

LidarNoise::LidarNoise()
	: m_covPosition(3, 3, { 20, 0, 0, 0, 20, 0, 0, 0, 0 })
	, m_covOrientation(3, 3, { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.1 })
{

}

vePose LidarNoise::sample(float64 t, const vePose& pose)
{
	cv::Mat pos = makeNoisy(toCv(pose.getPosition())(cv::Rect{ 0, 0, 1, 2 }), toCv(m_covPosition)(cv::Rect{ 0, 0, 2, 2 }));
	cv::Mat orientation = makeNoisy(toCv(pose.getOrientation())(cv::Rect{ 0, 2, 1, 1 }), toCv(m_covOrientation)(cv::Rect{ 2, 2, 1, 1 }));

	return vePose{ cVector<float64>(pos.at<float64>(0), pos.at<float64>(1), 0.0), m_covPosition, cDblVector(0.0, 0.0, orientation.at<float64>(0)), m_covOrientation, cBufferStamp() };
}
