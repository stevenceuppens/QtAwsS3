#include "s3client.h"
#include "s3client_p.h"

#include "s3objectreply.h"

#include <QNetworkRequest>

S3Client::S3Client(QObject *parent)
    : QObject(parent)
    , d_ptr(new S3ClientPrivate(this))
{}

void S3Client::setAccessKeyID(const QString &key)
{
    Q_D(S3Client);
    d->m_accessKeyID = key;
}

void S3Client::setAccessKeySecret(const QString &secret)
{
    Q_D(S3Client);
    d->m_accessKeySecret = secret;
}

S3ObjectReply *S3Client::getObject(const QString &objectName, const QString &bucketName)
{
    Q_D(const S3Client);

    QNetworkRequest getRequest = d->createRequest(objectName, bucketName);
    d->createAuthHeader(QStringLiteral("GET"), getRequest);
    return new S3ObjectReply(d->m_networkAccessManager->get(getRequest));
}

S3ObjectReply *S3Client::putObject(const QString &objectName, const QString &bucketName, const QByteArray data)
{
    Q_D(const S3Client);

    QNetworkRequest putRequest = d->createRequest(objectName, bucketName);
    d->createAuthHeader(QStringLiteral("PUT"), putRequest, data);
    return new S3ObjectReply(d->m_networkAccessManager->put(putRequest, data));
}

S3ObjectReply *S3Client::deleteObject(const QString &objectName, const QString &bucketName)
{
    Q_D(const S3Client);

    QNetworkRequest deleteRequest = d->createRequest(objectName, bucketName);
    d->createAuthHeader(QStringLiteral("DELETE"), deleteRequest);
    return new S3ObjectReply(d->m_networkAccessManager->deleteResource(deleteRequest));
}
