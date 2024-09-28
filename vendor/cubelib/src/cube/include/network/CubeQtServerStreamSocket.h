/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2020                                                     **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_gui.network
 *  @brief   Declaration of the class cube::QtServerStreamSocket
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_QTSERVERSTREAMSOCKET_H
#define CUBE_QTSERVERSTREAMSOCKET_H

#include "CubeSocket.h"
#include <QObject>

// Forward declaration
class QTcpSocket;
class QTcpServer;
class QThread;

namespace cube
{
/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::QtServerStreamSocket
 *  @ingroup CUBE_gui.network
 *  @brief   A Qt-based stream socket.
 **/
/*-------------------------------------------------------------------------*/

class QtServerStreamSocket
    : public QObject, public Socket
{
    Q_OBJECT
public:
    /// @name Construction and destruction.
    /// @{

    /// @brief Factory method.
    ///
    static SocketPtr
    create();

    /// @brief Create copy of the socket
    virtual SocketPtr
    copy();


    /// @brief Virtual destructor.
    ///
    virtual
    ~QtServerStreamSocket();

    /// @}
    /// @name Client interface
    /// @{

    /// @brief Client-side call to connection to a server address and port.
    ///
    /// @param address
    ///     Text representation of server address.
    /// @param port
    ///     Port number to connect to.
    ///
    /// @note Throws NetworkError exception if socket acquisition fails.
    ///
    virtual void
    connect( const std::string& address,
             int                port );

    /// @brief Close the internal connection socket.
    ///
    virtual void
    disconnect();

    /// @}
    /// @name Server interface
    /// @{

    /// @brief Listen for incoming connections.
    ///
    /// @param port
    ///     Network port to listen for connection requests.
    ///
    /// @note Throws NetworkError exception if socket acquisition fails.
    ///
    virtual void
    listen( int port );

    /// @brief Block until a new incoming connection was accepted.
    ///
    virtual void
    accept();


    /// @brief Disconnect server socket.
    ///
    virtual void
    shutdown();

    /// @}
    /// @name Data transfer
    /// @{

    /// @brief Send data to remote communication partner.
    ///
    /// @param buffer
    ///     Payload
    /// @param num_bytes
    ///     Number of bytes in the payload
    ///
    virtual size_t
    send( const void* buffer,
          size_t      num_bytes );

    /// @brief Receive data from remote communication partner.
    ///
    /// @param buffer
    ///     Payload
    /// @param num_bytes
    ///     Number of bytes in the payload.
    ///
    virtual size_t
    receive( void*  buffer,
             size_t num_bytes );

    /// @}
    /// @name Connection status
    /// @{

    /// @brief Check connection status.
    ///
    /// @return
    ///     True, if socket connection is established,
    ///     false, otherwise.
    ///
    virtual bool
    isConnected();

    /// @brief Check server socket status.
    ///
    /// @return
    ///     True, if server is listening on a socket,
    ///     false, otherwise.
    ///
    virtual bool
    isListening();

    /// @}
    /// @name Socket information
    /// @{

    /// @brief Returns the hostname of the machine.
    ///
    /// @return
    ///     Hostname of the machine.
    ///
    virtual std::string
    getHostname();

    /// @brief Get Socket information
    ///
    /// @return
    ///     Information string.
    ///
    std::string
    getInfoString();

/*
    /// @}

    static QtServerStreamSocket* single;*/

signals:
    void
    sendSignal( const void* buffer,
                size_t      num_bytes );
    void
    receiveSignal( void*  buffer,
                   size_t num_bytes );

    void
    connectSignal( const QString& address,
                   int            port );

    void
    disconnectSignal();

protected:
    /// @name Construction and destruction
    /// @{

    /// @brief Private default constructor.
    ///
    QtServerStreamSocket();

    /// @}

private slots:
    void
    socketConnect( const QString& address,
                   int            port );
    void
    socketSend( const void* buffer,
                size_t      num_bytes );

    void
    socketReceive( void*  buffer,
                   size_t num_bytes );

    void
    disconnectSlot();

private:
    /// Qt Socket
    QTcpSocket* mSocket;

    /// Qt Server socket
    QTcpServer* mServer;
//
//     QThread* socketIOThread;
};
}      // namespace cube

#endif // ! CUBE_QTSTREAMSOCKET_H
