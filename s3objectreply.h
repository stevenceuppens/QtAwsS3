#ifndef S3OBJECTREPLY_H
#define S3OBJECTREPLY_H

#include "qtawss3_global.h"

#include <QObject>
#include <QSharedPointer>
#include <QNetworkReply>

class S3ObjectReplyPrivate;
class QTAWSS3SHARED_EXPORT S3ObjectReply : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(S3ObjectReply)
    Q_DECLARE_PRIVATE(S3ObjectReply)

public:
    explicit S3ObjectReply(QNetworkReply *reply);

public:
    bool isFinished() const;
    bool isRunning() const;
    QByteArray readAll();

signals:
    void finished();
    void error(QNetworkReply::NetworkError);
    void sslErrors(const QList<QSslError> &errors);
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    QSharedPointer<S3ObjectReplyPrivate> d_ptr;
};

#endif // S3OBJECTREPLY_H
