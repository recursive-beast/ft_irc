<p align="center">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="https://github.com/recursive-beast/ft_irc/assets/41545690/7e7fab14-ace3-4b81-9c67-2d05b0c8a4df">
    <source media="(prefers-color-scheme: light)" srcset="https://github.com/recursive-beast/ft_irc/assets/41545690/89589402-5e08-42e8-b22b-b24d1f4d55cc">
    <img alt="logo" src="https://github.com/recursive-beast/ft_irc/assets/41545690/89589402-5e08-42e8-b22b-b24d1f4d55cc">
  </picture>
</p>

# Introduction
The project implements a server that adheres to the Internet Relay Chat (IRC) protocol **from scratch**,
allowing users to connect with an IRC client and test the server.

This project aims to deepen understanding of networking protocols and server-client communication.

:warning: This educational project is not intended for production use.

# Features

- Real-time Text-Based Communication.
- Public and Private Messaging.
- Multiple Client Handling.
- Non-Blocking I/O Operations.
- TCP/IP Communication.
- Authentication and User Management.
- Channel Operations.
- Error Handling.

# Technologies Used

The server was built using the following technologies:

- [C++98](https://en.wikipedia.org/wiki/C%2B%2B)
- Sockets Programming using [socket](https://man7.org/linux/man-pages/man2/socket.2.html)
- Polling mechanism using [poll](https://man7.org/linux/man-pages/man2/poll.2.html)

# Usage

## Setup

1) clone the repo and go into the folder:

```
git clone git@github.com:recursive-beast/ft_irc.git
cd ft_irc
```

2) compile the project using a make command:

```
make
```

## Running the server

Once the server is compiled, you can start it using the following:

```
./ircserv <port> <password>
```

- `port`: The port number on which your IRC server will be listening to for incoming connections.
- `password`: The connection password. It will be needed by any IRC client that tries to connect to the server.

# Acknowledgments

Special thanks to [1337 coding school](https://1337.ma/en/) for providing the opportunity to work on this project and explore various technologies.
