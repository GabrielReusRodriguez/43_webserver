/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetworkService.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gabriel Reus  <gabrielin@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:26:12 by Gabriel Reu       #+#    #+#             */
/*   Updated: 2025/01/11 20:35:25 by Gabriel Reu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#include "Services/NetworkService.hpp"
#include "Exceptions/NetWorkException.hpp"
#include "Debugger/Debugger.hpp"


NetworkService::NetworkService(void)
{
	this->fd_server_socket = SOCKET_NONE;
	this->running = false;
}

NetworkService::NetworkService(const NetworkService &net)
{
	this->fd_server_socket = net.fd_server_socket;
	this->addr = net.addr;
	this->running = net.running;
}

NetworkService::~NetworkService(void)
{
	this->stop();
}

NetworkService &	NetworkService::operator=(const NetworkService &net)
{
	if (this != &net)
	{
		this->stop();
		this->fd_server_socket = net.fd_server_socket;
		this->addr = net.addr;
		this->running = net.running;
	}
	return (*this);
}

void	NetworkService::start(void) 
{
	this->fd_server_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (this->fd_server_socket < 0)
	//	throw NetworkException("Error creando el socket del servidor.");
		throw NetworkException(errno);
	this->configure_socket();
	this->bind_socket_to_port();
	this->listen_call();
	Debugger::debug("POST listen call");
	this->running = true;
	this->run();
/*
	try
	{
		this->bind_socket_to_port();
	}
	catch(NetworkException& e)
	{
		std::cerr << e.what() << '\n';
		throw e;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		throw e;
	}
*/	
	
}

void NetworkService::stop(void)
{
	if (this->fd_server_socket >= 0)
	{
		close (this->fd_server_socket);
	}
}

void	NetworkService::configure_socket(void)
{
	this->addr.sin_family = AF_INET;
	this->addr.sin_addr.s_addr = INADDR_ANY;
	this->addr.sin_port = htons(SERVER_PORT);
}

void	NetworkService::bind_socket_to_port(void)
{
	if (bind(
			this->fd_server_socket, 
			(struct sockaddr *)&this->addr, 
			sizeof(this->addr)
			) < 0)
	{
		throw NetworkException(errno);
	}
}

void	NetworkService::listen_call(void)
{
	if (listen(this->fd_server_socket, SERVER_MAX_CONN) < 0)
	{
		throw NetworkException(errno);
	}
}

bool	NetworkService::isRunning(void) const
{
	return (this->running);
}

void	NetworkService::run(void)
{
	while (this->running)
	{
		
	}
}


/*
	protected:
		int					fd_server_socket;
		struct sockaddr_in 	addr;
//		bool				run;

	public:
		NetworkService(void);
		NetworkService(const NetworkService &net);
		~NetworkService(void);

		NetworkService &	operator=(const NetworkService &net);

//		bool	isRun(void) const;
		void	start(void);
		void	stop(void);

		*/