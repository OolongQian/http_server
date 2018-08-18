#ifndef HTTPSERVER_SERVER_HTTPS_HPP
#define HTTPSERVER_SERVER_HTTPS_HPP

#include "server_http.hpp"
// #define USE_STANDALONE_ASIO

#ifdef USE_STANDALONE_ASIO
#include <asio/ssl.hpp>
#else

#include <boost/asio/ssl.hpp>

#endif

/**
 * 加密的https协议被看作是http协议的继承子类。
 * */

namespace SimpleWeb {
using HTTPS = asio::ssl::stream<asio::ip::tcp::socket>;

template<>
class Server<HTTPS> : public ServerBase<HTTPS> {
	bool set_session_id_context = false;

public:
	/**
	 * https 的端口为443而不是80，然后需要有一个服务器的经过CA认证的公钥，以及自己保有的私钥。
	 * */
	Server(const std::string &cert_file, const std::string &private_key_file,
	       const std::string &verify_file = std::string())
	/// 你看这里配置了443端口。
		: ServerBase<HTTPS>::ServerBase(443), context(asio::ssl::context::tlsv12) {
		context.use_certificate_chain_file(cert_file);  /// 创建了证书，包含公钥。
		context.use_private_key_file(private_key_file, asio::ssl::context::pem);  /// 创建了私钥。

		if (verify_file.size() > 0) {
			context.load_verify_file(verify_file);
			context.set_verify_mode(
				asio::ssl::verify_peer | asio::ssl::verify_fail_if_no_peer_cert |
				asio::ssl::verify_client_once);
			set_session_id_context = true;
		}
	}

protected:
	asio::ssl::context context;

	/**
	 * 相比于没有加密的http服务器，https在建立连接之后需要干点奇怪的事情。服务器和客户端进行握手之类的通信，用它们
	 * 自己的公钥私钥进行沟通，最终在本次会话秘钥上达成一致。
	 * 其实我也不知道它们在干什么，反正这两个函数大致上就在干这个事情吧。
	 * */
	void after_bind() override {
		if (set_session_id_context) {
			// Creating session_id_context from address:port but reversed due to small SSL_MAX_SSL_SESSION_ID_LENGTH
			auto session_id_context = std::to_string(acceptor->local_endpoint().port()) + ':';
			session_id_context.append(config.address.rbegin(), config.address.rend());
			SSL_CTX_set_session_id_context(context.native_handle(),
			                               reinterpret_cast<const unsigned char *>(session_id_context.data()),
			                               std::min<std::size_t>(session_id_context.size(),
			                                                     SSL_MAX_SSL_SESSION_ID_LENGTH));
		}
	}

	void accept() override {
		auto connection = create_connection(*io_service, context);

		acceptor->async_accept(connection->socket->lowest_layer(),
		                       [this, connection](const error_code &ec) {
			                       auto lock = connection->handler_runner->continue_lock();
			                       if (!lock)
				                       return;

			                       if (ec != asio::error::operation_aborted)
				                       this->accept();

			                       auto session = std::make_shared<Session>(
				                       config.max_request_streambuf_size, connection);

			                       if (!ec) {
				                       asio::ip::tcp::no_delay option(true);
				                       error_code ec;
				                       session->connection->socket->lowest_layer().set_option(option,
				                                                                              ec);

				                       session->connection->set_timeout(config.timeout_request);
				                       session->connection->socket->async_handshake(
					                       asio::ssl::stream_base::server,
					                       [this, session](const error_code &ec) {
						                       session->connection->cancel_timeout();
						                       auto lock = session->connection->handler_runner->continue_lock();
						                       if (!lock)
							                       return;
						                       if (!ec)
							                       this->read(session);
						                       else if (this->on_error)
							                       this->on_error(session->request, ec);
					                       });
			                       } else if (this->on_error)
				                       this->on_error(session->request, ec);
		                       });
	}
};
}; // namespace SimpleWeb

#endif //HTTPSERVER_SERVER_HTTPS_HPP
