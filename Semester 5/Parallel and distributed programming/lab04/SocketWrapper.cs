﻿using System.Net;
using System.Net.Sockets;
using System.Text;

sealed class SocketWrapper
{
    // buffer used for reading data from the socket
    public const int BufferSize = 1024;

    public Socket Socket { get; init; }

    public int ID { get; init; }
    public string HostName { get; init; }
    public string Endpoint { get; init; }
    public IPEndPoint IPEndpoint { get; init; }

    public byte[] Buffer { get; } = new byte[BufferSize];
    public StringBuilder Response { get; } = new();

    // synchronization primitive that allows one or more threads to wait until a set number of signals are received
    public CountdownEvent CDE { get; init; }

    // used for signaling and synchronization
    public ManualResetEvent ConnectDone { get; } = new(false);
    public ManualResetEvent SendDone { get; } = new(false);
    public ManualResetEvent ReceiveDone { get; } = new(false);

    public static SocketWrapper New(string host, int id, CountdownEvent cde = null)
    {
        // get host name
        var hostName = host.Split('/')[0];
        // DNS resolution to get host entry
        var hostEntry = Dns.GetHostEntry(hostName);
        // get the first IP address from the address list
        var ipAddr = hostEntry.AddressList[0];
        var remoteEndpoint = new IPEndPoint(ipAddr, Parser.Port);

        // create a new socket
        var socket = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

        return new SocketWrapper
        {
            Socket = socket,
            HostName = hostName,
            Endpoint = host.Contains('/') ? host[host.IndexOf('/')..] : "/",
            IPEndpoint = remoteEndpoint,
            ID = id,
            CDE = cde
        };
    }
}