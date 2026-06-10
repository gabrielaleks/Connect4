#include "NetworkClient.h"

NetworkClient::NetworkClient(const QString& host, quint16 port, int localPlayerIndex, QObject* parent)
    : QObject(parent), _localPlayerIndex(localPlayerIndex)
{
    _socket = new QTcpSocket(this);
    _socket->connectToHost(host, port);

    connect(_socket, &QTcpSocket::readyRead, this, &NetworkClient::readData);
    connect(_socket, &QTcpSocket::connected, this, &NetworkClient::connected);
    connect(_socket, &QTcpSocket::disconnected, this, &NetworkClient::disconnected);
    connect(_socket, &QAbstractSocket::errorOccurred, this, [this](QAbstractSocket::SocketError) {
        emit errorOccurred(_socket->errorString());
    });
}

void NetworkClient::sendMove(int column) {
    _expectingEcho = true;
    _socket->write(QString::number(column).toUtf8() + "\n");
}

int NetworkClient::localPlayerIndex() const {
    return _localPlayerIndex;
}

void NetworkClient::readData() {
    QByteArray data = _socket->readAll();
    const QString prefix = "Client: ";

    for (const QByteArray& part : data.split('\n')) {
        QString msg = QString::fromUtf8(part).trimmed();
        if (!msg.startsWith(prefix)) continue;

        if (_expectingEcho) {
            _expectingEcho = false;
            continue;
        }

        QString payload = msg.mid(prefix.length()).trimmed();
        bool ok;
        int column = payload.toInt(&ok);
        if (ok && column >= 0 && column <= 6)
            emit moveReceived(column);
    }
}
