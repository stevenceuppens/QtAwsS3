#ifndef S3CLIENT_H
#define S3CLIENT_H

#include "qtawss3_global.h"

#include <QObject>
#include <QSharedPointer>

class S3ObjectReply;

class S3ClientPrivate;
class QTAWSS3SHARED_EXPORT S3Client : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(S3Client)
    Q_DECLARE_PRIVATE(S3Client)

public:
    explicit S3Client(QObject *parent = Q_NULLPTR);

public:
    void setAccessKeyID(const QString &key);
    void setAccessKeySecret(const QString &secret);

    S3ObjectReply *getObject(const QString &objectName, const QString &bucketName);
    S3ObjectReply *putObject(const QString &objectName, const QString &bucketName, const QByteArray data);
    S3ObjectReply *deleteObject(const QString &objectName, const QString &bucketName);

private:
    QSharedPointer<S3ClientPrivate> d_ptr;
};

#endif // S3CLIENT_H
