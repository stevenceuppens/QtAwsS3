#ifndef S3CLIENT_P_H
#define S3CLIENT_P_H

#include "s3client.h"

#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QCryptographicHash>
#include <QDebug>

/*
Example 1 -> https://s3.amazonaws.com/doc/s3-developer-guide/RESTAuthentication.html
*/

class S3ClientPrivate
{
    Q_DECLARE_PUBLIC(S3Client)

public:
    S3ClientPrivate(S3Client *_q)
        : q_ptr(_q)
        , m_networkAccessManager(new QNetworkAccessManager(_q))
    {}

private:
    QUrl createUrl(const QString &objectName, const QString &bucketName) const
    {
        return QUrl(QStringLiteral("https://") + bucketName + QStringLiteral(".s3.amazonaws.com/") + objectName);
    }

    QNetworkRequest createRequest(const QString &objectName, const QString &bucketName) const
    {
        QNetworkRequest request(createUrl(objectName, bucketName));
        return request;
    }

    void createAuthHeader(const QString &verb, QNetworkRequest &request, const QByteArray &data = QByteArray()) const
    {
        const QString endl = QStringLiteral("\n");

        QStringList canonicalString;
        canonicalString << verb << endl;
        if (!data.isEmpty()) {
            const QByteArray md5 = QCryptographicHash::hash(data, QCryptographicHash::Md5);
            canonicalString << QString(md5) << endl;
            canonicalString << QStringLiteral("application/vnd.ms-pkistl") << endl;
        }
        canonicalString << QDateTime::currentDateTime().toString() << endl;

        const QByteArray signature = hmacSha1(m_accessKeySecret.toLatin1(), canonicalString.join("").toLatin1());
        const QString header = "AWS " + m_accessKeyID + ":" + QString(signature);
        request.setRawHeader("Authorization", header.toLatin1());

        qDebug() << "Authorization " << header;
    }

private:
    QByteArray hmacSha1(QByteArray key, QByteArray baseString) const
    {
        int blockSize = 64; // HMAC-SHA-1 block size, defined in SHA-1 standard
        if (key.length() > blockSize) { // if key is longer than block size (64), reduce key length with SHA-1 compression
            key = QCryptographicHash::hash(key, QCryptographicHash::Sha1);
        }

        QByteArray innerPadding(blockSize, char(0x36)); // initialize inner padding with char "6"
        QByteArray outerPadding(blockSize, char(0x5c)); // initialize outer padding with char "quot;
        // ascii characters 0x36 ("6") and 0x5c ("quot;) are selected because they have large
        // Hamming distance (http://en.wikipedia.org/wiki/Hamming_distance)

        for (int i = 0; i < key.length(); i++) {
            innerPadding[i] = innerPadding[i] ^ key.at(i); // XOR operation between every byte in key and innerpadding, of key length
            outerPadding[i] = outerPadding[i] ^ key.at(i); // XOR operation between every byte in key and outerpadding, of key length
        }

        // result = hash ( outerPadding CONCAT hash ( innerPadding CONCAT baseString ) ).toBase64
        QByteArray total = outerPadding;
        QByteArray part = innerPadding;
        part.append(baseString);
        total.append(QCryptographicHash::hash(part, QCryptographicHash::Sha1));
        QByteArray hashed = QCryptographicHash::hash(total, QCryptographicHash::Sha1);
        return hashed.toBase64();
    }

private:
    S3Client *q_ptr;
    QNetworkAccessManager *m_networkAccessManager;
    QString m_accessKeyID;
    QString m_accessKeySecret;
};

#endif // S3CLIENT_P_H
