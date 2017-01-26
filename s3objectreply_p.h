#ifndef S3OBJECTREPLY_P_H
#define S3OBJECTREPLY_P_H

#include "s3objectreply.h"

class S3ObjectReplyPrivate
{
    Q_DECLARE_PUBLIC(S3ObjectReply)

public:
    S3ObjectReplyPrivate(S3ObjectReply *_q)
        : q_ptr(_q)
    {}

private:
    S3ObjectReply *q_ptr;
    QNetworkReply *m_reply;
};

#endif // S3OBJECTREPLY_P_H
