#pragma once

#include <memory>
#include <QPointer>

namespace Z3D
{

class ZCameraCalibration;
class ZCameraCalibrationPluginInterface;
class ZCameraCalibrator;
class ZMultiCameraCalibration;
class ZMultiCameraCalibrator;
class ZPinholeCameraCalibration;

typedef std::shared_ptr<ZCameraCalibration> ZCameraCalibrationPtr;
typedef QPointer<ZCameraCalibration> ZCameraCalibrationWeakPtr;

typedef std::shared_ptr<ZMultiCameraCalibration> ZMultiCameraCalibrationPtr;

typedef QPointer<ZPinholeCameraCalibration> ZPinholeCameraCalibrationWeakPtr;

} // namespace Z3D
