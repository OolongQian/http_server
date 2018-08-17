#include <iostream>
#include <cstring>
#include "utility.hpp"
#include "server_http.hpp"
#include "client_http.hpp"
#include "server_https.hpp"
#include <boost/thread.hpp>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <fstream>
#include <vector>

using namespace std;
using namespace boost::property_tree;

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;


void RenderHTML(shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
	try {
		auto web_root_path = boost::filesystem::canonical("web");
		// Check if path is within web_root_path
		auto path = boost::filesystem::canonical(web_root_path / request->path);
		if (boost::filesystem::is_directory(path))
			path /= "index.html";
		if (distance(web_root_path.begin(), web_root_path.end()) > distance(path.begin(), path.end()) ||
				!equal(web_root_path.begin(), web_root_path.end(), path.begin()))
			throw invalid_argument("path must be within root path");

		SimpleWeb::CaseInsensitiveMultimap header;

		auto ifs = make_shared<ifstream>();
		ifs->open(path.string(), ifstream::in | ios::binary | ios::ate);

		if (*ifs) {
			auto length = ifs->tellg();
			ifs->seekg(0, ios::beg);

			header.emplace("Content-Length", to_string(length));
			response->write(header);

			// Trick to define a recursive function within this scope (for example purposes)
			class FileServer {
			public:
				static void read_and_send(const shared_ptr<HttpServer::Response> &response, const shared_ptr<ifstream> &ifs) {
					// Read and send 128 KB at a time
					static vector<char> buffer(131072); // Safe when server is running on one thread
					streamsize read_length;
					if ((read_length = ifs->read(&buffer[0], static_cast<streamsize>(buffer.size())).gcount()) > 0) {
						response->write(&buffer[0], read_length);
						if (read_length == static_cast<streamsize>(buffer.size())) {
							response->send([response, ifs](const SimpleWeb::error_code &ec) {
								if (!ec)
									read_and_send(response, ifs);
								else
									cerr << "Connection interrupted" << endl;
							});
						}
					}
				}
			};
			FileServer::read_and_send(response, ifs);
		} else
			throw invalid_argument("could not read file");
	}
	catch (const exception &e) {
		response->write(SimpleWeb::StatusCode::client_error_bad_request,
										"Could not open path " + request->path + ": " + e.what());
	}
}


int main() {
	/// 启动server，配置端口。
	HttpServer server;
	server.config.port = 8080;
	server.config.thread_pool_size = 2;


	/// 设置服务器处理GET的默认方法。
	server.default_resource["GET"] = [&](shared_ptr<HttpServer::Response> response,
																			shared_ptr<HttpServer::Request> request) {

		cout << "request path: " << request->path << endl;
		cout << "query_string: " << request->query_string << endl;
		cout << "full url: " << request->path + request->query_string << endl;

		/// GET的列表参数从url中以query_string的形式传入，parse出expression，调用exe进行运算。
		if (!request->query_string.empty()) {
			cout << request->query_string << endl;
			auto para = request->parse_query_string();

			string expression = para.cbegin()->second;
			cout << "expression: " << expression << endl;
			string cmd = "./prog " + expression;
			system(cmd.c_str());
		}
		/// 根据写在html form当中的文件路径返回response。
		RenderHTML(response, request);
	};

	/// 设置服务器处理POST的默认方法。
	server.default_resource["POST"] = [&](shared_ptr<HttpServer::Response> response,
																			 shared_ptr<HttpServer::Request> request) {
		/// POST的列表参数从实体体中传入，已经被整合在content当中，同样parse出expression，调用exe进行运算。
		if(request->content.size() != 0) {
			auto para = SimpleWeb::QueryString::parse(request->content.string());
			string expression = para.cbegin()->second;
			cout << "expression: " << expression << endl;
			string cmd = "./prog " + expression;
			system(cmd.c_str());
		}
		/// 根据写在html form当中的文件路径返回response。
		RenderHTML(response, request);
	};

	/// 运行服务器。
	thread server_thread([&server]() {
		server.start();
	});
	sleep(100);
	server_thread.join();
	return 0;
}
