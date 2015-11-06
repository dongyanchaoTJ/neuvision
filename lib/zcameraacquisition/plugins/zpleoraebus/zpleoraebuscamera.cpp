#include "zpleoraebuscamera.h"

#include "zpleoraebuscamera_p.h"

#include "zcameraimage.h"

#include <QDebug>

namespace Z3D
{

ZCameraInterface::Ptr ZPleoraeBUSCamera::getCameraByMAC(QString name)
{
    ZPleoraeBUSCameraPrivate *cameraPrivate = ZPleoraeBUSCameraPrivate::getCameraByMAC(name);

    if (!cameraPrivate)
        return ZCameraInterface::Ptr(0);

    ZPleoraeBUSCamera *camera = new ZPleoraeBUSCamera();

    camera->d_ptr = cameraPrivate;
    camera->m_uuid = cameraPrivate->m_uuid;
    cameraPrivate->q_ptr = camera;

    QObject::connect(cameraPrivate, SIGNAL(newImageReceived(Z3D::ZImageGrayscale::Ptr)),
                     camera,        SIGNAL(newImageReceived(Z3D::ZImageGrayscale::Ptr)));
    QObject::connect(cameraPrivate, SIGNAL(error(QString)),
                     camera,        SIGNAL(error(QString)));
    QObject::connect(cameraPrivate, SIGNAL(warning(QString)),
                     camera,        SIGNAL(warning(QString)));
    QObject::connect(cameraPrivate, SIGNAL(attributeChanged(QString,QVariant)),
                     camera,        SIGNAL(attributeChanged(QString,QVariant)));

    return ZCameraInterface::Ptr( camera );
}

ZPleoraeBUSCamera::ZPleoraeBUSCamera(QObject *parent) :
    ZCameraBase(parent)
{

}

ZPleoraeBUSCamera::~ZPleoraeBUSCamera()
{
    qDebug() << Q_FUNC_INFO;

    /// stop acquisition (if running)
    if (isRunning())
        stopAcquisition();

    d_ptr->deleteLater();
}

bool ZPleoraeBUSCamera::startAcquisition()
{
    if (!ZCameraBase::startAcquisition())
        return false;

    return d_ptr->startAcquisition();
}

bool ZPleoraeBUSCamera::stopAcquisition()
{
    if (!ZCameraBase::stopAcquisition())
        return false;

    return d_ptr->stopAcquisition();
}

QList<ZCameraInterface::ZCameraAttribute> ZPleoraeBUSCamera::getAllAttributes()
{
    return d_ptr->getAllAttributes();
}

QVariant ZPleoraeBUSCamera::getAttribute(const QString &name) const
{
    return d_ptr->getAttribute(name);
}

bool ZPleoraeBUSCamera::setBufferSize(int bufferSize)
{
    return ZCameraBase::setBufferSize(bufferSize)
            && d_ptr->setBufferSize(bufferSize);
}

bool ZPleoraeBUSCamera::setAttribute(const QString &name, const QVariant &value, bool notify)
{
    return d_ptr->setAttribute(name, value, notify);
}

} // namespace Z3D