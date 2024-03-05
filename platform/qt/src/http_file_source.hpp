#pragma once

#include <mbgl/storage/http_file_source.hpp>
#include <mbgl/storage/resource.hpp>

#include <QMap>
#include <QNetworkAccessManager>
#include <QObject>
#include <QPair>
#include <QPointer>
#include <QQueue>
#include <QUrl>
#include <QVector>

namespace mbgl {

class HTTPRequest;

class HTTPFileSource::Impl : public QObject
{
    Q_OBJECT

public:
    Impl();
    virtual ~Impl() = default;

    void request(HTTPRequest *);
    void cancel(HTTPRequest *);

public slots:
    void onReplyFinished();

private:
    QMap<QUrl, QPair<QPointer<QNetworkReply>, QVector<HTTPRequest *>>> m_pending;
    QMap<int, QNetworkAccessManager*> m_manager_map;
    int m_manager_count;
    int m_manager_cur_index;
};

} // namespace mbgl
