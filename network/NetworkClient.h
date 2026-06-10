#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QString>

class NetworkClient : public QObject {
    Q_OBJECT

public:
    explicit NetworkClient(const QString& host, quint16 port, int localPlayerIndex, QObject* parent = nullptr);
    void sendMove(int column);
    int localPlayerIndex() const;

private:
    QTcpSocket* _socket;
    int _localPlayerIndex;
    bool _expectingEcho = false;

private slots:
    void readData();

signals:
    void moveReceived(int column);
    void connected();
    void disconnected();
    void errorOccurred(const QString& message);
};

#endif // NETWORKCLIENT_H
